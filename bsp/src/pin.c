#include "pin.h"

const gpio_t GPIO_PINS[PIN_NUMBER] = {
    /* PORT D */
    [D0] = { .port = IO_PORT_D, .pin = 0 },
    [D1] = { .port = IO_PORT_D, .pin = 1 },
    [D2] = { .port = IO_PORT_D, .pin = 2 },
    [D3] = { .port = IO_PORT_D, .pin = 3 },
    [D4] = { .port = IO_PORT_D, .pin = 4 },
    [D5] = { .port = IO_PORT_D, .pin = 5 },
    [D6] = { .port = IO_PORT_D, .pin = 6 },
    [D7] = { .port = IO_PORT_D, .pin = 7 },

    /* PORT B */
    [D8] = { .port = IO_PORT_B, .pin = 0 },
    [D9] = { .port = IO_PORT_B, .pin = 1 },
    [D10] = { .port = IO_PORT_B, .pin = 2 },
    [D11] = { .port = IO_PORT_B, .pin = 3 },
    [D12] = { .port = IO_PORT_B, .pin = 4 },
    [D13] = { .port = IO_PORT_B, .pin = 5 },

    /* PORT C */
    [A0] = { .port = IO_PORT_C, .pin = 0 },
    [A1] = { .port = IO_PORT_C, .pin = 1 },
    [A2] = { .port = IO_PORT_C, .pin = 2 },
    [A3] = { .port = IO_PORT_C, .pin = 3 },
    [A4] = { .port = IO_PORT_C, .pin = 4 },
    [A5] = { .port = IO_PORT_C, .pin = 5 }
};
