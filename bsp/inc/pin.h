// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#ifndef PIN_H
#define PIN_H

#include "gpio.h"

#define PIN_NUMBER  (20)

#define BOARD_LED   (PB5)

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

#define PD0 (GPIO_PINS[D0])
#define PD1 (GPIO_PINS[D1])
#define PD2 (GPIO_PINS[D2])
#define PD3 (GPIO_PINS[D3])
#define PD4 (GPIO_PINS[D4])
#define PD5 (GPIO_PINS[D5])
#define PD6 (GPIO_PINS[D6])
#define PD7 (GPIO_PINS[D7])

#define PB0 (GPIO_PINS[D8])
#define PB1 (GPIO_PINS[D9])
#define PB2 (GPIO_PINS[D10])
#define PB3 (GPIO_PINS[D11])
#define PB4 (GPIO_PINS[D12])
#define PB5 (GPIO_PINS[D13])

#define PC0 (GPIO_PINS[A0])
#define PC1 (GPIO_PINS[A1])
#define PC2 (GPIO_PINS[A2])
#define PC3 (GPIO_PINS[A3])
#define PC4 (GPIO_PINS[A4])
#define PC5 (GPIO_PINS[A5])

extern const gpio_t GPIO_PINS[PIN_NUMBER];

#endif // PIN_H
