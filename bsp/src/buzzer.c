// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include "buzzer.h"

#include "pin.h"

#define GPIO_SET_HIGH_IMPEDANCE(gpio_ptr)   gpio_init(gpio_ptr, IO_DIRECTION_IN)

void buzzer_init(const buzzer_t* buzzer) {
    /* Wake-up from PR Mode */
    timer_init(buzzer->id, TIMER_MODE_CTC, TIMER_CLOCK_PS_1024);

    timer_config_output_compare_channel(buzzer->id, buzzer->channel, TIMER_COMPARE_TOGGLE, NO_NOTE, false);

    /* Put in PR Mode */
    timer_set_clock(buzzer->id, TIMER_CLOCK_NONE);
}

void buzzer_tone(const buzzer_t* buzzer, uint16_t tone) {
    const gpio_t *gpio_pin = pin_get_gpio_from_timer_channel(buzzer);

    timer_set_clock(buzzer->id, TIMER_CLOCK_PS_1024);

    gpio_init(gpio_pin, IO_DIRECTION_OUT);

    timer_set_output_compare_value(buzzer->id, buzzer->channel, tone);
}

void buzzer_no_tone(const buzzer_t* buzzer) {
    const gpio_t *gpio_pin = pin_get_gpio_from_timer_channel(buzzer);

    GPIO_SET_HIGH_IMPEDANCE(gpio_pin);
    
    timer_set_clock(buzzer->id, TIMER_CLOCK_NONE);
}
