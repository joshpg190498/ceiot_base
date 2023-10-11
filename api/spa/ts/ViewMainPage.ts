class ViewMainPage {
    showDevices(list:DeviceInt[],element:Main):void {

      let e:HTMLElement = document.getElementById("devicesList");
      e.innerHTML="";
      for (let device of list) {
        console.log(device)
          let image = "temp.png";
          e.innerHTML += `<li class="collection-item avatar">
            <img src="images/${image}" alt="" class="circle">
            <span class="title">${device.name}</span>
            <p>id: ${device.device_id}</p>
            <p>key: ${device.key}</p>
            <p>fecha de creación: ${new Date(device.created_at).toLocaleString()}</p>
            <p>última conexión: ${new Date(device.last_connection).toLocaleString()}</p>
          </li>  
          `;
      }
    }
}
