#include "buzzer.h"

#define GPIO_SET_HIGH_IMPEDANCE(gpio_ptr)   gpio_init(gpio_ptr, IO_DIRECTION_IN)

void buzzer_init(const buzzer_t* buzzer) {
    /* Wake-up from PR Mode */
    timer_init(buzzer->id, TIMER_MODE_CTC, TIMER_CLOCK_PS_1024);

    timer_config_output_compare_channel(buzzer->id, buzzer->channel, TIMER_COMPARE_TOGGLE, NO_NOTE, false);

    /* Put in PR Mode */
    timer_set_clock(buzzer->id, TIMER_CLOCK_NONE);
}

void buzzer_tone(const buzzer_t* buzzer, uint16_t tone) {
    timer_set_clock(buzzer->id, TIMER_CLOCK_PS_1024);

    gpio_init(&buzzer->gpio, IO_DIRECTION_OUT);

    timer_set_output_compare_value(buzzer->id, buzzer->channel, tone);
}

void buzzer_no_tone(const buzzer_t* buzzer) {
    GPIO_SET_HIGH_IMPEDANCE(&buzzer->gpio);
    
    timer_set_clock(buzzer->id, TIMER_CLOCK_NONE);
}
