// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include <string.h>

#include "bsp.h"
#include "ntc.h"

#include "system.h"
#include "process.h"
#include "messages.h"

#define TICK_COUNT_MAX  (5)

static uint8_t tokenize_string(char *str, char tokens[][BUFFER_SIZE]);

int main(void) {
    system_init();

    uint8_t tick_count = 0;

    lcd_screen current_screen = LCD_TIME_SCREEN;

    char tokens[MAX_NUMBER_TOKENS][BUFFER_SIZE];

    while(1) {
        __reset_watchdog();

        /* If has already printed and gotten an input, process it */
        if(rx_message.done && tx_message.done) {
            uint8_t number_tokens = tokenize_string(rx_message.data, tokens);

            uint8_t number_args = number_tokens - 1;

            if(number_tokens > 0) {
                if(strcmp(tokens[0], "set") == 0) {
                    process_set(&tokens[1], number_args);
                }
                else if(strcmp(tokens[0], "get") == 0) {
                    process_get(&tokens[1], number_args);
                }
                else if(strcmp(tokens[0], "store") == 0) {
                    process_store(&tokens[1], number_args);
                }
                else if(strcmp(tokens[0], "load") == 0) {
                    process_load(&tokens[1], number_args);
                }
                else if(rx_message.size != 0) {    
                    strcpy(tx_message.data, INVALID_STR);
                    tx_message.size = INVALID_STR_SIZE;
                }
            }
            
            strcat(tx_message.data, TERMINAL_STR);
            tx_message.size += TERMINAL_STR_SIZE;
            tx_message.done = false;
            usart_enable_interrupt(USART_TX_INTERRUPT);

            rx_message.done = false;
            rx_message.size = 0;
        }

        /* Read RTC and update LCD after 1s */
        if(flag_ext_interrupt) {
            temperature = (uint16_t) ntc_convert_temperature(temperature_sensor_raw);

            light_percentage = (100.0 / ADC_MAX_VALUE) * light_sensor_raw;

            system_drive_external_light(light_percentage <= LIGHT_PERCENTAGE_TRESHOLD);

            rtc_read_time(&rtc_time);

            tick_count += 1;

            if(tick_count == TICK_COUNT_MAX) {
                tick_count = 0;

                current_screen = (current_screen + 1) % LCD_NUMBER_SCREENS;
            }
            
            switch(current_screen) {
                case LCD_TIME_SCREEN:
                    system_lcd_write_time();
                    break;
                case LCD_SENSORS_SCREEN:
                    system_lcd_write_sensors();
                    break;
                default:
                    break;
            }

            flag_ext_interrupt = false;
        }

        cpu_sleep();
    } 
}

uint8_t tokenize_string(char *str, char tokens[][BUFFER_SIZE]) {
    uint8_t token_count = 0;
    
    const char *token = strtok(str, " ");

    while (token != NULL && token_count < MAX_NUMBER_TOKENS) {
        strncpy(tokens[token_count++], token, BUFFER_SIZE);

        token = strtok(NULL, " ");
    }

    return token_count;
}
