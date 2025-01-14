// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include "process.h"

#include <stdio.h>
#include <string.h>

#include "bsp.h"
#include "system.h"

/* Private Functions */

static void prv_process_print_error(const char *time_string);

/* Public Functions */

void process_set(const char tokens[][BUFFER_SIZE], uint8_t number_args) {
    if(number_args < 2) {
        prv_process_print_error(PROCESS_ERROR_STR);
        return;
    }

    if(strcmp(tokens[0], "time") == 0) {
        sscanf(tokens[1], "%02hhd:%02hhd:%02hhd", &rtc_time.hour, &rtc_time.min, &rtc_time.sec);

        if(!rtc_set_time(&rtc_time)) {
            prv_process_print_error(RTC_ERROR_STR);
            return;
        }
    }
    else {
        prv_process_print_error(VARIABLE_ERROR_STR);
        return;
    }

    strcpy(tx_message.data, EMPTY_STR);
    tx_message.size = EMPTY_STR_SIZE;
}

void process_get(const char tokens[][BUFFER_SIZE], uint8_t number_args) {
    static char buffer[BUFFER_SIZE];

    if(number_args < 1) {
        prv_process_print_error(PROCESS_ERROR_STR);
        return;
    }

    if(strcmp(tokens[0], "time") == 0) {
        snprintf(buffer, BUFFER_SIZE, "%02hhd:%02hhd:%02hhd", rtc_time.hour, rtc_time.min, rtc_time.sec);
    }
    else if(strcmp(tokens[0], "temp") == 0) {
        snprintf(buffer, BUFFER_SIZE, "%d ºC", temperature);
    }
    else if(strcmp(tokens[0], "light") == 0) {
        snprintf(buffer, BUFFER_SIZE, "%d%%", light_percentage);
    }
    else {
        prv_process_print_error(VARIABLE_ERROR_STR);
        return;
    }

    strcpy(tx_message.data, NEWLINE_STR);
    strcat(tx_message.data, buffer);
    tx_message.size = NEWLINE_STR_SIZE + strlen(buffer);
}

void process_store(const char tokens[][BUFFER_SIZE], uint8_t number_args) {
    if(number_args < 1) {
        prv_process_print_error(PROCESS_ERROR_STR);
        return;
    }

    if(strcmp(tokens[0], "time") == 0) {
        system_eeprom_write(EEPROM_TIME_ADDR, (uint8_t *) &rtc_time, sizeof(rtc_time_t));
    }
    else {
        prv_process_print_error(VARIABLE_ERROR_STR);
        return;
    }

    strcpy(tx_message.data, STORE_STR);
    tx_message.size = STORE_STR_SIZE;
}

void process_load(const char tokens[][BUFFER_SIZE], uint8_t number_args) {
    if(number_args < 1) {
        prv_process_print_error(PROCESS_ERROR_STR);
        return;
    }

    if(strcmp(tokens[0], "time") == 0) {
        system_eeprom_read(EEPROM_TIME_ADDR, (uint8_t *) &rtc_time, sizeof(rtc_time_t));

        /* Wait for operation conclusion... */
        cpu_sleep();

        if(!rtc_set_time(&rtc_time)) {
            prv_process_print_error(RTC_ERROR_STR);
            return;
        }
    }
    else {
        prv_process_print_error(VARIABLE_ERROR_STR);
        return;
    }

    strcpy(tx_message.data, LOAD_STR);
    tx_message.size = LOAD_STR_SIZE;
}

/* Private Functions */

void prv_process_print_error(const char *time_string) {
    strcpy(tx_message.data, time_string);
    tx_message.size = strlen(time_string);
    tx_message.done = false;
    usart_enable_interrupt(USART_TX_INTERRUPT);
}
