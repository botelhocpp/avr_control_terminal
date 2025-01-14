// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include "system.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "bsp.h"
#include "buzzer.h"
#include "lcd.h"
#include "ntc.h"

#include "messages.h"

#define SYSTEM_TICK_TIMER   (TIMER_0)

#define SYSTEM_TICK_MS      (10)
#define SYSTEM_TICK_PS      (1024)

#define BUZZER_TONE_TIME    (100)

#define ADC_DEFAULT_CHANNEL (TEMP_SENSOR_CHANNEL)

/* Public variables */

bool flag_ext_interrupt = true;

uint16_t temperature_sensor_raw = 0;

uint16_t light_sensor_raw = 0;

uint16_t temperature = 0;

uint16_t light_percentage = 0;

eeprom_buffer_t eeprom_buffer = {
    .address = 0,
    .data = NULL,
    .size = 0,
    .index = 0,
    .done = false,
    .write_mode = false
};

usart_message_t rx_message = {
  .size = 0,
  .done = false
};

usart_message_t tx_message = {
  .data = WELCOME_STR,
  .size = WELCOME_STR_SIZE,
  .index = 0,
  .done = false
};

rtc_time_t rtc_time = {
    .hour = 0,
    .min = 0,
    .sec = 0
};

/* Private variables */

static const gpio_t *external_light = &PD6;

static const gpio_t *builtin_led = &BOARD_LED;

static const buzzer_t *buzzer = &TIMER2_CHANNEL_B;

static const lcd_t lcd = {
    .address = LCD_NXP_EXPANSOR_ADDRESS,
    .backlight = true
};

uint8_t current_adc_channel = ADC_DEFAULT_CHANNEL;

/* Public Functions */

void system_init(void) {
    __disable_interrupts();

    system_peripheral_init();

    system_component_init();

    __enable_interrupts();

    system_lcd_startup_screen();

    uint8_t seconds_counter = 0;

    while(seconds_counter < SYSTEM_STARTUP_TIME) {
        cpu_sleep();

        if(flag_ext_interrupt) {
            seconds_counter++;
        }  
    }
}

void system_peripheral_init(void) {
    wdt_disable_reset();
    
    cpu_setup();

    usart_init(BAUDRATE_115200, ENABLE_INTERRUPT, ENABLE_INTERRUPT);

    twi_init(TWI_CLOCK_SELECT_100KHZ, DISABLE_INTERRUPT);

    eeprom_init(EEPROM_MODE_ERASE_WRITE, DISABLE_INTERRUPT);

    ext_interrupt_enable(EXT_INTERRUPT_NUM_0, EXT_INTERRUPT_TRIGGER_FALLING, true);

    adc_init(ADC_REFERENCE_AVCC, ADC_AUTO_TRIGGER_NONE, ADC_PRESCALER_64, ENABLE_INTERRUPT);

    adc_disable();

    timer_init(SYSTEM_TICK_TIMER, TIMER_MODE_CTC, TIMER_CLOCK_PS_1024);

    timer_config_output_compare_channel(SYSTEM_TICK_TIMER, TIMER_CHANNEL_A, TIMER_MODE_CTC, TMR_CALC_MS(SYSTEM_TICK_MS, SYSTEM_TICK_PS), DISABLE_INTERRUPT);

    wdt_init(WDT_TIMEOUT_1S, ENABLE_INTERRUPT);
}

void system_component_init(void) {
    gpio_init(external_light, IO_DIRECTION_OUT);

    gpio_write(external_light, 0);

    gpio_init(builtin_led, IO_DIRECTION_OUT);

    gpio_write(builtin_led, 1);

    adc_disable_digital_input(TEMP_SENSOR_CHANNEL);

    adc_disable_digital_input(LIGHT_SENSOR_CHANNEL);

    adc_select_channel(ADC_DEFAULT_CHANNEL);

    buzzer_init(buzzer);

    rtc_init();

    lcd_init(&lcd);

    lcd_create_big_numbers(&lcd);
}

void system_lcd_startup_screen(void) {
    lcd_home(&lcd);

    lcd_print(&lcd, "Control Terminal");

    lcd_set_cursor(&lcd, 1, 1);
    lcd_print(&lcd, "Version 1.0.0");
}

void system_lcd_write_time(const rtc_time_t *rtc_time) {
    lcd_clear(&lcd);

    lcd_write_big_number(&lcd, 0, rtc_time->hour / 10);
    lcd_write_big_number(&lcd, 2, rtc_time->hour % 10);
    lcd_write(&lcd, ':');

    lcd_write_big_number(&lcd, 5, rtc_time->min / 10);
    lcd_write_big_number(&lcd, 7, rtc_time->min % 10);
    lcd_write(&lcd, ':');

    lcd_write_big_number(&lcd, 10, rtc_time->sec / 10);
    lcd_write_big_number(&lcd, 12, rtc_time->sec % 10);
}

void system_lcd_write_sensors(uint16_t temperature, uint16_t light_percentage) {
    static char buffer[17];

    lcd_clear(&lcd);

    snprintf(buffer, 17, "Temp: %d C", temperature);

    lcd_print(&lcd, buffer);  

    snprintf(buffer, 17, "Light: %3d%%", light_percentage);

    lcd_set_cursor(&lcd, 0, 1);

    lcd_print(&lcd, buffer);    
}

void system_drive_external_light(uint8_t value) {
    gpio_write(external_light, value);
}

void system_eeprom_write(uint16_t initial_address, uint8_t *data, uint8_t size) {
    eeprom_buffer.address = initial_address;
    eeprom_buffer.data = data;
    eeprom_buffer.size = size;
    eeprom_buffer.write_mode = true;
    eeprom_enable_interrupt();
}

void system_eeprom_read(uint16_t initial_address, uint8_t *data, uint8_t size) {
    eeprom_buffer.address = initial_address;
    eeprom_buffer.data = data;
    eeprom_buffer.size = size;
    eeprom_buffer.write_mode = false;
    eeprom_enable_interrupt();
}

/* Interrupt Handlers */

void __vector_TIMER0_COMPA_ISR(void) {
    static uint8_t system_tick_count = 0;

    system_tick_count++;

    if(system_tick_count == BUZZER_TONE_TIME / SYSTEM_TICK_MS) {
        buzzer_no_tone(buzzer);
        timer_disable_interrupt(SYSTEM_TICK_TIMER, TIMER_OUTPUT_COMPARE_A_INTERRUPT);
        system_tick_count = 0;
    }
}

void __vector_USART_UDRE_ISR(void) {
    if(tx_message.index < tx_message.size) {
        usart_write(tx_message.data[tx_message.index++]);
    }
    else {
        tx_message.index = 0;
        tx_message.done = true;
        usart_disable_interrupt(USART_TX_INTERRUPT);
    }
}

void __vector_USART_RX_ISR(void) {
    if(rx_message.done) {
        return;
    }

    char data = usart_read();
    
    if(data == '\0' || data == '\n' || data == '\r') {
        /* Store RX data */
        rx_message.data[rx_message.size] = '\0';
        rx_message.done = true;

        /* Play a tone */
        buzzer_tone(buzzer, NOTE_D5);
        timer_enable_interrupt(SYSTEM_TICK_TIMER, TIMER_OUTPUT_COMPARE_A_INTERRUPT);
    }
    else if(data == '\b') {
        /* Process backspace even with blank input */
        if(rx_message.size > 0) {
            rx_message.size--;

            /* Print RX data */
            tx_message.data[0] = '\b'; 
            tx_message.data[1] = ' '; 
            tx_message.data[2] = '\b'; 
            tx_message.size = 3;
            tx_message.done = false;
            usart_enable_interrupt(USART_TX_INTERRUPT);
        }
    }
    else {
        rx_message.data[rx_message.size++] = data;

        /* Print RX data */
        tx_message.data[0] = data; 
        tx_message.size = 1;
        tx_message.done = false;
        usart_enable_interrupt(USART_TX_INTERRUPT);
    }
}

void __vector_INT0_ISR(void) {
    flag_ext_interrupt = true;

    adc_enable();

    adc_start_conversion_on_channel(current_adc_channel);
}

void __vector_EE_READY_ISR(void) {
    if(eeprom_buffer.index < eeprom_buffer.size) {
        if(eeprom_buffer.write_mode) {
            eeprom_write_data(eeprom_buffer.address++, eeprom_buffer.data[eeprom_buffer.index++]);
        }
        else {
            eeprom_buffer.data[eeprom_buffer.index++] = eeprom_read_data(eeprom_buffer.address++);
        }
    }
    else {
        eeprom_buffer.index = 0;
        eeprom_buffer.done = true;
        eeprom_disable_interrupt();
    }
}

void __vector_ADC_ISR(void) {
    uint16_t adc_value = adc_read_value();

    adc_disable();

    switch(current_adc_channel) {
        case TEMP_SENSOR_CHANNEL:
            temperature_sensor_raw = adc_value;
            break;
        case LIGHT_SENSOR_CHANNEL:
            light_sensor_raw = adc_value;
            break;
    }

    current_adc_channel = (current_adc_channel + 1) % NUMBER_SENSORS;
}

void __vector_WDT_ISR(void) {
    twi_status current_twi_status = twi_get_status();

    snprintf(
        tx_message.data, 
        sizeof(tx_message.data), 
        "\n\rTime-out reset!"
        "\n\rTWI Status: 0x%02X"
        "\n\r",
        (uint8_t) current_twi_status
    );
    
    usart_print(tx_message.data);
}
