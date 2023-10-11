const express = require("express");
const bodyParser = require("body-parser");
const {MongoClient} = require("mongodb");
const PgMem = require("pg-mem");
const crypto = require("crypto")

const db = PgMem.newDb();

    const render = require("./render.js");
// Measurements database setup and access

let database = null;
const collectionName = "measurements";

async function startDatabase() {
    const uri = "mongodb://localhost:27017/?maxPoolSize=20&w=majority";	
    const connection = await MongoClient.connect(uri, {useNewUrlParser: true});
    database = connection.db();
}

async function getDatabase() {
    if (!database) await startDatabase();
    return database;
}

async function insertMeasurement(message) {
    const {insertedId} = await database.collection(collectionName).insertOne(message);
    return insertedId.toString();
}

async function getMeasurements() {
    return await database.collection(collectionName).find({}).toArray();	
}

async function getDeviceMeasurements(deviceId) {
    return await database.collection(collectionName).find({id: deviceId}).toArray()
}

async function getLastDeviceMeasurement(deviceId) {
    return await database.collection(collectionName).findOne({id: deviceId}, {sort: {timestamp: -1}})
}

// API Server

const app = express();

app.use(bodyParser.urlencoded({extended:false}));

app.use(express.static('spa/static'));

const PORT = 8080;

app.post('/measurement', async function (req, res) {
    const key = req.headers.authorization
    const deviceId = req.body.id
    const device = db.public.one(`SELECT * FROM devices WHERE device_id='${deviceId}'`)
    if(device) {
        if(key === device.key) {
            const timestamp = new Date().toISOString()
            const insertedId = await insertMeasurement({id:req.body.id, t:req.body.t, h:req.body.h, p:req.body.p, timestamp: timestamp})
            const message = `Registro guardado en DB con id ${insertedId} - ` + "temp: " + req.body.t + "  humidity: " + req.body.h + "  pressure : " + req.body.p + "  timestamp : " + timestamp
            console.log(message);
            res.status(200).send(message)	
        } else {
            const message = "Dispositivo no autorizado para esta operación."
            console.log(message)
            res.status(403).send(message)
        }
    } else {
        const message = "Dispositivo no registrado"
        console.log(message)
        res.status(403).send(message)
    }

});

app.post('/device', function (req, res) {
    const deviceId = req.body.id
    const deviceName = `Dispositivo ESP32 ${deviceId}`
    const existingDevice = db.public.one(`SELECT * FROM devices WHERE device_id='${deviceId}'`)
    if(existingDevice) {
        console.log('Dispositivo existente. Se enviará la key registrada en DB')
        res.send(`key:${existingDevice.key}`);
    } else {
        const deviceKey = crypto.randomBytes(8).toString('hex')
        db.public.none("INSERT INTO devices VALUES ('"+deviceId+ "', '"+deviceName+"', '"+deviceKey+"'" + ",'" + new Date().toISOString() + "')");
        console.log(`Dispositivo nuevo registrado con MAC ${deviceId} y Key ${deviceKey}`)
        res.send(`key:${deviceKey}`);
    }
});


app.get('/web/device', function (req, res) {
	var devices = db.public.many("SELECT * FROM devices").map( function(device) {
		console.log(device);
		return '<tr><td><a href=/web/device/'+ device.device_id +'>' + device.device_id + "</a>" +
			       "</td><td>"+ device.name+"</td><td>"+ device.key+"</td></tr>";
	   }
	);
    const deviceResult = devices.join('')
	res.send("<html>"+
		     "<head><title>Sensores</title></head>" +
		     "<body>" +
		        "<table border=\"1\">" +
		           "<tr><th>id</th><th>name</th><th>key</th></tr>" +
		           deviceResult +
		        "</table>" +
		     "</body>" +
		"</html>");
});

app.get('/web/device/:id', async function (req,res) {
    const deviceMeasurements = await getDeviceMeasurements(req.params.id)
    const htmlTableMeasurement = await buildHtmlTableMeasurement(deviceMeasurements)

    var template = "<html>"+
                     "<head><title>Sensor {{name}}</title></head>" +
                     "<body>" +
		        "<h1>{{ name }}</h1>"+
		        "id  : {{ id }}<br/>" +
		        "Key : {{ key }}" +
                "<hr>" +
                htmlTableMeasurement +
                     "</body>" +
                "</html>";


    var device = db.public.many("SELECT * FROM devices WHERE device_id = '"+req.params.id+"'");
    console.log(device);
    res.send(render(template,{id:device[0].device_id, key: device[0].key, name:device[0].name}));
});	

app.get('/web/measurement', async function (req, res) {
    const measurements = await getMeasurements()
    const htmlTableMeasurement = await buildHtmlTableMeasurement(measurements)
    res.status(200).send(`
    <html>
        <head><title> Measurements </title></head>
        <body>
            ${htmlTableMeasurement}
        </body>
    </html>`)
})

async function buildHtmlTableMeasurement(measurements) {
    let htmlMeasurements = []
    for (let measurement of measurements) {
        const htmlMeasurement = `
        <tr>
            <td>${measurement.id}</td>
            <td>${measurement.t}</td>
            <td>${measurement.h}</td>
            <td>${measurement.p}</td>
            <td>${measurement.timestamp}</td>
        </tr>`
        htmlMeasurements.push(htmlMeasurement)
    }
    const htmlResult = htmlMeasurements.join('')
    return `
    <table border=1>
            <tr><th>id</th><th>temperatura</th><th>humedad</th><th>presión</th><th>timestamp</th></tr>
            ${htmlResult}
    </table>`
}


app.get('/term/device/:id', function (req, res) {
    var red = "\33[31m";
    var green = "\33[32m";
    var blue = "\33[33m";
    var reset = "\33[0m";
    var template = "Device name " + red   + "   {{name}}" + reset + "\n" +
		   "       id   " + green + "       {{ id }} " + reset +"\n" +
	           "       key  " + blue  + "  {{ key }}" + reset +"\n";
    var device = db.public.many("SELECT * FROM devices WHERE device_id = '"+req.params.id+"'");
    console.log(device);
    res.send(render(template,{id:device[0].device_id, key: device[0].key, name:device[0].name}));
});

app.get('/measurement', async (req,res) => {
    res.send(await getMeasurements());
});

app.get('/device', async function(req,res) {
    const devices = db.public.many("SELECT * FROM devices")
    for (let i=0; i < devices.length; i++) {
        const lastMeasurement = await getLastDeviceMeasurement(devices[i].device_id)
        devices[i].last_connection = lastMeasurement.timestamp
    }
    res.send(devices);
});

startDatabase().then(async() => {

    const addAdminEndpoint = require("./admin.js");
    addAdminEndpoint(app, render);

    await insertMeasurement({id:'00', t:'18', h:'78', p:'1000', timestamp: new Date().toISOString()});
    await insertMeasurement({id:'00', t:'19', h:'77', p:'1001', timestamp: new Date().toISOString()});
    await insertMeasurement({id:'00', t:'17', h:'77', p:'1002', timestamp: new Date().toISOString()});
    await insertMeasurement({id:'01', t:'17', h:'77', p:'1003', timestamp: new Date().toISOString()});
    console.log("mongo measurement database Up");

    db.public.none("CREATE TABLE devices (device_id VARCHAR, name VARCHAR, key VARCHAR, created_at TIMESTAMP)");
    db.public.none("INSERT INTO devices VALUES ('00', 'Fake Device 00', '123456', CURRENT_TIMESTAMP)");
    db.public.none("INSERT INTO devices VALUES ('01', 'Fake Device 01', '234567', CURRENT_TIMESTAMP)");
    db.public.none("CREATE TABLE users (user_id VARCHAR, name VARCHAR, key VARCHAR)");
    db.public.none("INSERT INTO users VALUES ('1','Ana','admin123')");
    db.public.none("INSERT INTO users VALUES ('2','Beto','user123')");

    console.log("sql device database up");

    app.listen(PORT, () => {
        console.log(`Listening at ${PORT}`);
    });
});
