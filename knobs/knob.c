
#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/multicore.h"
#include "pico/binary_info.h"
#include "pico/double.h"

const float ADC_FACTOR = 3.3f / (1 << 12);
const uint LED_PIN = 25;


void knob_reader() {
    while(1) {
        adc_select_input(0);
        uint16_t red = adc_read();
        adc_select_input(1);
        uint16_t green = adc_read();
        adc_select_input(2);
        uint16_t blue = adc_read();

        printf("red = %f green = %f blue = %f\n", red * ADC_FACTOR, green * ADC_FACTOR, blue * ADC_FACTOR);
        printf("red = %f \n", round((float)red / (1<<12) * 100));
        sleep_ms(100);
    }
}


int main() {
    bi_decl(bi_program_description("This is a Knob tool"));
    stdio_init_all();
    adc_init();
    adc_gpio_init(26);
    adc_gpio_init(27);
    adc_gpio_init(28);

    multicore_launch_core1(knob_reader);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(1) {
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
    }
}

