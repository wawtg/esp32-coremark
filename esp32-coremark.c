/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#define STACK_SIZE 20000

#define tskCORE_0 0
#define tskCORE_1 1

void coremark_main(void *arguments);

void app_main()
{
    printf("Hello world!\n");

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

	TaskHandle_t taskHandle;

    char *argv[] = {"0x0", "0x0", "0x66", "0", "7", "1", "2000"};

    printf("sizeof = %d, %s\n", sizeof(signed short), "ee_s16");
    printf("sizeof = %d, %s\n", sizeof(unsigned short), "ee_u16");
    printf("sizeof = %d, %s\n", sizeof(signed int), "ee_s32");
    printf("sizeof = %d, %s\n", sizeof(float), "ee_f32");
    printf("sizeof = %d, %s\n", sizeof(unsigned char), "ee_u8");
    printf("sizeof = %d, %s\n", sizeof(unsigned int), "ee_u32");
    printf("sizeof = %d, %s\n", sizeof(int *), "ee_u32");
    printf("sizeof = %d, %s\n", sizeof(size_t), "size_t");

	xTaskCreatePinnedToCore(coremark_main, "coremark", STACK_SIZE, (void *) argv, 10, &taskHandle, tskCORE_0); // Core 0

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
}
