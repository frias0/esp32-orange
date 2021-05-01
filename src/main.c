#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define GPIO_LED  19
int led_state = 0;

void setup_gpio() {
    printf("GPIO Setup\n");

    gpio_reset_pin(GPIO_LED);
    gpio_pad_select_gpio(GPIO_LED);
    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(GPIO_LED, GPIO_PULLDOWN_ONLY);
}

void led_toggle() {
    led_state = !led_state;
    gpio_set_level(GPIO_LED, led_state);
}

void wait(int ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void toggle_forever() {
    while (true) {
        led_toggle();
        wait(1000);
    }
}

void app_main() {
    printf("Hello, world!\n");
    setup_gpio();
    toggle_forever();
}
