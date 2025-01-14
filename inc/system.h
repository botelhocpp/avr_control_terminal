// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#include "rtc.h"

#define EEPROM_TIME_ADDR          (0) 
#define EEPROM_TIME_SIZE          (EEPROM_TIME_ADDR + sizeof(rtc_time_t)) 

#define BUFFER_SIZE               (100)

#define TEMP_SENSOR_CHANNEL       (0)
#define LIGHT_SENSOR_CHANNEL      (1)
#define NUMBER_SENSORS            (2)

#define SYSTEM_STARTUP_TIME       (5)

#define LIGHT_PERCENTAGE_TRESHOLD (10)

typedef enum lcd_screen {
    LCD_TIME_SCREEN,
    LCD_SENSORS_SCREEN,
    LCD_NUMBER_SCREENS
} lcd_screen;

typedef struct eeprom_buffer_t {
  uint8_t address;
  uint8_t *data;
  uint8_t size;
  uint8_t index;
  bool done;
  bool write_mode;
} eeprom_buffer_t;

typedef struct usart_message_t {
  char data[BUFFER_SIZE];
  uint8_t size;
  uint8_t index;
  bool done;
} usart_message_t;

extern eeprom_buffer_t eeprom_buffer;

extern usart_message_t rx_message;

extern usart_message_t tx_message;

extern rtc_time_t rtc_time;

extern bool flag_ext_interrupt;

extern uint16_t temperature_sensor_raw;

extern uint16_t light_sensor_raw;

extern uint16_t temperature;

extern uint16_t light_percentage;

void system_init(void);

void system_peripheral_init(void);

void system_component_init(void);

void system_lcd_startup_screen(void);

void system_lcd_write_time(const rtc_time_t *rtc_time);

void system_lcd_write_sensors(uint16_t temperature, uint16_t light_percentage);

void system_drive_external_light(uint8_t value);

void system_eeprom_write(uint16_t initial_address, uint8_t *data, uint8_t size);

void system_eeprom_read(uint16_t initial_address, uint8_t *data, uint8_t size);

#endif // SYSTEM_H
