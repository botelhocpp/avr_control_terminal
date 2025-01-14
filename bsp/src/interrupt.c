// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include "interrupt.h"

#include "atmega328p.h"
#include "gpio.h"

const uint16_t pin_change_mask_registers[] = {PCMSK0_ADDR, PCMSK1_ADDR, PCMSK2_ADDR};

const gpio_t INT_PINS[] = {
    [EXT_INTERRUPT_NUM_0] { .port = IO_PORT_D, .pin = 2 },
    [EXT_INTERRUPT_NUM_1] { .port = IO_PORT_D, .pin = 3 }
};

static uint8_t prv_pin_change_get_pcint_index(uint8_t pcint);

void ext_interrupt_enable(ext_interrupt_num num, ext_interrupt_trigger trigger, bool enable_pullup) { 
    if(num > EXT_INTERRUPT_NUM_1) {
        return;
    }

    gpio_init(&INT_PINS[num], enable_pullup);

    EICRA |= (trigger << 2*num);
    EIMSK |= (1U << num);
}

void ext_interrupt_disable(ext_interrupt_num num) {
    EIMSK &= ~(1U << num);
}

void pin_change_interrupt_group_enable(uint8_t pcint) {
    uint8_t pcint_index = prv_pin_change_get_pcint_index(pcint);

    PCICR |= (1U << pcint_index);
}

void pin_change_interrupt_group_disable(uint8_t pcint) {
    uint8_t pcint_index = prv_pin_change_get_pcint_index(pcint);

    PCICR &= ~(1U << pcint_index);
}

void pin_change_interrupt_enable(uint8_t pcint) {
    uint8_t pcint_index = prv_pin_change_get_pcint_index(pcint);

    HWREG(pin_change_mask_registers[pcint_index]) |= (1U << (pcint - 8*pcint_index));

    pin_change_interrupt_group_enable(pcint);
}

void pin_change_interrupt_disable(uint8_t pcint) {
    uint8_t pcint_index = prv_pin_change_get_pcint_index(pcint);

    HWREG(pin_change_mask_registers[pcint_index]) &= ~(1U << (pcint - 8*pcint_index));
}

uint8_t prv_pin_change_get_pcint_index(uint8_t pcint) {
    uint8_t index = 2;

    if(pcint >= 0 && pcint <= 7) {
        index = 0;
    }
    else if(pcint >= 8 && pcint <= 14) {
        index = 1;
    }

    return index;
}
