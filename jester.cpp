#include <stdio.h>
#include "pico/stdlib.h"
volatile uint GLOBAL_QUEUE[128];
volatile uint _INDEX;
void gpio_callback(uint gpio, uint32_t events) {
    _INDEX++;
    if (_INDEX > 127) {
	    _INDEX = 0;
    }
    GLOBAL_QUEUE[_INDEX-1] = 0;
    GLOBAL_QUEUE[_INDEX] = gpio;
}

int main()
{
    stdio_init_all();
    sleep_ms(5000);
    printf("Hello World!");
    for (int i = 6; i < 8; i++) {
        gpio_set_function(i, GPIO_FUNC_SIO);
	gpio_pull_up(i);
        gpio_set_irq_enabled_with_callback(i, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, gpio_callback);
    }
    

    while (true) {
	    uint cur = GLOBAL_QUEUE[_INDEX];
	    if (cur != 0) {
		    printf("GPIO: %d \r\n", cur); 
		    _INDEX++;
            }
    }
    return 0;
}
