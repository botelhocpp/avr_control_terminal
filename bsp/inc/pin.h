// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#ifndef PIN_H
#define PIN_H

#include "timer.h"

#define CREATE_GPIO_PIN_ARRAY
#define CREATE_TIMER_CHANNELS_ARRAY

#ifdef CREATE_GPIO_PIN_ARRAY

#include "gpio.h"

#define PIN_NUMBER  (20)

#define BOARD_LED   (PB5)

#define PD0         ((const gpio_t) { .port = IO_PORT_D, .pin = 0 })
#define PD1         ((const gpio_t) { .port = IO_PORT_D, .pin = 1 })
#define PD2         ((const gpio_t) { .port = IO_PORT_D, .pin = 2 })
#define PD3         ((const gpio_t) { .port = IO_PORT_D, .pin = 3 })
#define PD4         ((const gpio_t) { .port = IO_PORT_D, .pin = 4 })
#define PD5         ((const gpio_t) { .port = IO_PORT_D, .pin = 5 })
#define PD6         ((const gpio_t) { .port = IO_PORT_D, .pin = 6 })
#define PD7         ((const gpio_t) { .port = IO_PORT_D, .pin = 7 })

#define PB0         ((const gpio_t) { .port = IO_PORT_B, .pin = 0 })
#define PB1         ((const gpio_t) { .port = IO_PORT_B, .pin = 1 })
#define PB2         ((const gpio_t) { .port = IO_PORT_B, .pin = 2 })
#define PB3         ((const gpio_t) { .port = IO_PORT_B, .pin = 3 })
#define PB4         ((const gpio_t) { .port = IO_PORT_B, .pin = 4 })
#define PB5         ((const gpio_t) { .port = IO_PORT_B, .pin = 5 })

#define PC0         ((const gpio_t) { .port = IO_PORT_C, .pin = 0 })
#define PC1         ((const gpio_t) { .port = IO_PORT_C, .pin = 1 })
#define PC2         ((const gpio_t) { .port = IO_PORT_C, .pin = 2 })
#define PC3         ((const gpio_t) { .port = IO_PORT_C, .pin = 3 })
#define PC4         ((const gpio_t) { .port = IO_PORT_C, .pin = 4 })
#define PC5         ((const gpio_t) { .port = IO_PORT_C, .pin = 5 })

#define D0  (0)
#define D1  (1)
#define D2  (2)
#define D3  (3)
#define D4  (4)
#define D5  (5)
#define D6  (6)
#define D7  (7)
#define D8  (8)
#define D9  (9)
#define D10 (10)
#define D11 (11)
#define D12 (12)
#define D13 (13)
#define A0  (14)
#define A1  (15)
#define A2  (16)
#define A3  (17)
#define A4  (18)
#define A5  (19)

extern const gpio_t *GPIO_PINS[PIN_NUMBER];

#ifdef CREATE_TIMER_CHANNELS_ARRAY

#define OC0A                    (TIMER0_CHANNEL_A)
#define OC0B                    (TIMER0_CHANNEL_B)
#define OC1A                    (TIMER1_CHANNEL_A)
#define OC1B                    (TIMER1_CHANNEL_B)
#define OC2A                    (TIMER2_CHANNEL_A)
#define OC2B                    (TIMER2_CHANNEL_B)

#define TIMER0_CHANNEL_A        ((const timer_channel_t) { .id = TIMER_0, .channel = TIMER_CHANNEL_A })
#define TIMER0_CHANNEL_B        ((const timer_channel_t) { .id = TIMER_0, .channel = TIMER_CHANNEL_B })
#define TIMER1_CHANNEL_A        ((const timer_channel_t) { .id = TIMER_1, .channel = TIMER_CHANNEL_A })
#define TIMER1_CHANNEL_B        ((const timer_channel_t) { .id = TIMER_1, .channel = TIMER_CHANNEL_B })
#define TIMER2_CHANNEL_A        ((const timer_channel_t) { .id = TIMER_2, .channel = TIMER_CHANNEL_A })
#define TIMER2_CHANNEL_B        ((const timer_channel_t) { .id = TIMER_2, .channel = TIMER_CHANNEL_B })

extern const gpio_t *TIMER_CHANNEL_PINS[TIMER_MODULES_NUMBER][TIMER_CHANNELS_NUMBER];

const gpio_t *pin_get_gpio_from_timer_channel(const timer_channel_t *timer_channel);

#endif // CREATE_TIMER_CHANNELS_ARRAY

#endif // CREATE_GPIO_PIN_ARRAY

#endif // PIN_H
