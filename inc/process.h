// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>
#include <stdbool.h>

#include "messages.h"
#include "rtc.h"

#define MAX_NUMBER_ARGS     (3)

#define MAX_NUMBER_TOKENS   ((MAX_NUMBER_ARGS) + 1)

void process_set(const char tokens[][BUFFER_SIZE], uint8_t number_args);

void process_get(const char tokens[][BUFFER_SIZE], uint8_t number_args);

void process_store(const char tokens[][BUFFER_SIZE], uint8_t number_args);

void process_load(const char tokens[][BUFFER_SIZE], uint8_t number_args);

#endif // PROCESS_H
