// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include "pin.h"

#ifdef CREATE_GPIO_PIN_ARRAY

const gpio_t *GPIO_PINS[PIN_NUMBER] = {
    [D0] = &PD0,
    [D1] = &PD1,
    [D2] = &PD2,
    [D3] = &PD3,
    [D4] = &PD4,
    [D5] = &PD5,
    [D6] = &PD6,
    [D7] = &PD7,
    [D8] = &PB0,
    [D9] = &PB1,
    [D10] = &PB2,
    [D11] = &PB3,
    [D12] = &PB4,
    [D13] = &PB5,
    [A0] = &PC0,
    [A1] = &PC1,
    [A2] = &PC2,
    [A3] = &PC3,
    [A4] = &PC4,
    [A5] = &PC5
};

#ifdef CREATE_TIMER_CHANNELS_ARRAY

const gpio_t *TIMER_CHANNEL_PINS[TIMER_MODULES_NUMBER][TIMER_CHANNELS_NUMBER] = {
    [TIMER_0] = { &PD6, &PD5 },
    [TIMER_1] = { &PB1, &PB2 },
    [TIMER_2] = { &PB3, &PD3 }
};

const gpio_t *pin_get_gpio_from_timer_channel(const timer_channel_t *timer_channel) {
    return TIMER_CHANNEL_PINS[timer_channel->id][timer_channel->channel];
}

#endif // CREATE_TIMER_CHANNELS_ARRAY

#endif // CREATE_GPIO_PIN_ARRAY