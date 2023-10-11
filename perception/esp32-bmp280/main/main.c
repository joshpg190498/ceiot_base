/* HTTP GET Example using plain POSIX sockets

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include <bmp280.h>
#include "../config.h"

/* HTTP Constants that aren't configurable in menuconfig */
#define WEB_PATH "/measurement"
#define AUTO_REGISTER_PATH "/device"

char DEVICE_ID[18] = "XX:XX:XX:XX:XX:XX";
char API_KEY[17] = "1234567890123456";

static const char *TAG = "temp_collector";

static char *BODY = "id=%s&t=%0.2f&h=%0.2f&p=%0.2f";
static char *BODY_DEVICE = "id=%s";

static char *REQUEST_POST = "POST "WEB_PATH" HTTP/1.0\r\n"
    "Host: "API_IP_PORT"\r\n"
    "User-Agent: "USER_AGENT"\r\n"
    "Content-Type: application/x-www-form-urlencoded\r\n"
    "Content-Length: %d\r\n"
    "Authorization: %s\r\n"
    "\r\n"
    "%s";

static char *AUTO_REGISTER_POST = "POST "AUTO_REGISTER_PATH" HTTP/1.0\r\n"
    "Host: "API_IP_PORT"\r\n"
    "User-Agent: "USER_AGENT"\r\n"
    "Content-Type: application/x-www-form-urlencoded\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s";

static void http_get_task(void *pvParameters)
{
    const struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
    };
    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;
    char body[64];
    char recv_buf[64];

    char send_buf[256];

    bmp280_params_t params;
    bmp280_init_default_params(&params);
    bmp280_t dev;
    memset(&dev, 0, sizeof(bmp280_t));

    ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));

    bool bme280p = dev.id == BME280_CHIP_ID;
    ESP_LOGI(TAG, "BMP280: found %s\n", bme280p ? "BME280" : "BMP280");

    float pressure, temperature, humidity;


    while(1) {
        if (bmp280_read_float(&dev, &temperature, &pressure, &humidity) != ESP_OK) {
            ESP_LOGI(TAG, "Temperature/pressure reading failed\n");
        } else {
            ESP_LOGI(TAG, "Pressure: %.2f Pa, Temperature: %.2f C", pressure, temperature);
//            if (bme280p) {
                ESP_LOGI(TAG,", Humidity: %.2f\n", humidity);
                sprintf(body, BODY, DEVICE_ID, temperature , humidity, pressure);
                sprintf(send_buf, REQUEST_POST, (int)strlen(body), API_KEY, body);
//	    } else {
//                sprintf(send_buf, REQUEST_POST, temperature , 0);
//            }
	    ESP_LOGI(TAG,"sending: \n%s\n",send_buf);
        }    

        int err = getaddrinfo(API_IP, API_PORT, &hints, &res);

        if(err != 0 || res == NULL) {
            ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }

        /* Code to print the resolved IP.

           Note: inet_ntoa is non-reentrant, look at ipaddr_ntoa_r for "real" code */
        addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
        ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

        s = socket(res->ai_family, res->ai_socktype, 0);
        if(s < 0) {
            ESP_LOGE(TAG, "... Failed to allocate socket.");
            freeaddrinfo(res);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TAG, "... allocated socket");

        if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
            ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
            close(s);
            freeaddrinfo(res);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }

        ESP_LOGI(TAG, "... connected");
        freeaddrinfo(res);

        if (write(s, send_buf, strlen(send_buf)) < 0) {
            ESP_LOGE(TAG, "... socket send failed");
            close(s);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TAG, "... socket send success");

        struct timeval receiving_timeout;
        receiving_timeout.tv_sec = 5;
        receiving_timeout.tv_usec = 0;
        if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
                sizeof(receiving_timeout)) < 0) {
            ESP_LOGE(TAG, "... failed to set socket receiving timeout");
            close(s);
            vTaskDelay(4000 / portTICK_PERIOD_MS);
            continue;
        }
        ESP_LOGI(TAG, "... set socket receiving timeout success");

        /* Read HTTP response */
        do {
            bzero(recv_buf, sizeof(recv_buf));
            r = read(s, recv_buf, sizeof(recv_buf)-1);
            for(int i = 0; i < r; i++) {
                putchar(recv_buf[i]);
            }
        } while(r > 0);

        ESP_LOGI(TAG, "... done reading from socket. Last read return=%d errno=%d.", r, errno);
        close(s);

        for(int countdown = 10; countdown >= 0; countdown--) {
            ESP_LOGI(TAG, "%d... ", countdown);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        ESP_LOGI(TAG, "Starting again!");
    }
}

char* postDevice(char *mac_str) {

    // se declara un arreglos para el envío y la rpta
    char body[64];
    char send_buf[256];
    char recv_dev_buf[256];

    ESP_LOGI(TAG, "Length of mac_str: %d", (int)strlen(mac_str));
    ESP_LOGI(TAG, "mac_str ss: %s", mac_str);

    //formatear la solicitud POST con la dirección MAC
    sprintf(body, BODY_DEVICE, mac_str );

    sprintf(send_buf, AUTO_REGISTER_POST,
            (int)strlen(body), body);

    // estructura ddrinfo
    struct addrinfo hints = {
        .ai_family = AF_INET, // ipv4
        .ai_socktype = SOCK_STREAM, // socket
    };

    // declaración de punteros y variables
    struct addrinfo *res;
    struct in_addr *addr;
    int s, r;

   // obtener información del servidor
    int err = getaddrinfo(API_IP, API_PORT, &hints, &res);
    if(err != 0 || res == NULL) {
        ESP_LOGE(TAG, "POST_DEVICE: DNS lookup failed err=%d res=%p", err, res);
        return NULL;
    }

    // obtener dirección ip del servidor a partir de la estructura res y de almacena en addr
    addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
    ESP_LOGI(TAG, "POST_DEVICE: DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

    // crear un socket utilizando la info proporcionada por getaddrinfo
    s = socket(res->ai_family, res->ai_socktype, 0);
    if(s < 0) {
        ESP_LOGE(TAG, "POST_DEVICE: ... Failed to allocate socket.");
        freeaddrinfo(res);
        return NULL;
    }

    // establecer conexión con el servidor utilizando socket creado
    if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
        ESP_LOGE(TAG, "POST_DEVICE: ... socket connect failed errno=%d", errno);
        close(s);
        freeaddrinfo(res);
        return NULL;
    }

    // libera la memoria asignada por getaddrinfo
    freeaddrinfo(res);

    // Se envía la cadena send_buff al servidor usando el socket
    if (write(s, send_buf, strlen(send_buf)) < 0) {
        ESP_LOGE(TAG, "POST_DEVICE: ... socket send failed");
        close(s);
        return NULL;
    }

    // Tiempo de espera de 5 segundos para recebir rpta del servidor
    struct timeval receiving_timeout;
    receiving_timeout.tv_sec = 5;
    receiving_timeout.tv_usec = 0;
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
            sizeof(receiving_timeout)) < 0) {
        ESP_LOGE(TAG, "POST_DEVICE: ... failed to set socket receiving timeout");
        close(s);
        return NULL;
    }

    // Leer respuesta del servidor    
    bzero(recv_dev_buf, sizeof(recv_dev_buf));
    r = read(s, recv_dev_buf, sizeof(recv_dev_buf)-1);
    if(r <= 0) {
        ESP_LOGE(TAG, "POST_DEVICE: ... failed to read from socket");
        close(s);
        return NULL;
    }

    ESP_LOGI(TAG, "POST_DEVICE: Respuesta recibida: %s", recv_dev_buf);

    close(s);

    char *key_str = strstr(recv_dev_buf, "key:");
    if (key_str != NULL) {
        key_str += 4; // Saltar el "key: "
        ESP_LOGI(TAG, "POST_DEVICE: Clave recibida: %s", key_str);
        return strdup(key_str); // Devolver una copia de la clave
    }

    ESP_LOGE(TAG, "POST_DEVICE: No se pudo encontrar la clave en la respuesta.");
    return NULL; // Si no se pudo encontrar la clave en la respuesta
}

char* getMacAddress() {
    uint8_t mac[6];
    esp_read_mac(mac, ESP_MAC_WIFI_STA);

    static char mac_str[18];  // Declaramos una cadena estática para almacenar la dirección MAC

    snprintf(mac_str, 18, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    ESP_LOGI(TAG, "GET_MAC_ADDRESS: Esp32 MAC address is %s", mac_str); // Agregado el log
    return mac_str;
}

void initialize_and_run()
{
    char *mac_str = getMacAddress();

    if(mac_str != NULL) {
        char *key_str = postDevice(mac_str);
        if(key_str != NULL) {
            if (strlen(mac_str) < sizeof(DEVICE_ID) && strlen(key_str) < sizeof(API_KEY)) {
                strncpy(DEVICE_ID, mac_str, 18);
                strncpy(API_KEY, key_str, 17);
            } else {
                ESP_LOGE(TAG, "initialize_and_run: DEVICE_ID or API_KEY is too small for copying");
            }
        }
    }

    http_get_task(NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK( nvs_flash_init() );
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(i2cdev_init());

    ESP_ERROR_CHECK(example_connect());

    xTaskCreate(&initialize_and_run, "initialize_and_run", 4096, NULL, 5, NULL);
}
