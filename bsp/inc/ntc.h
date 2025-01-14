// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#ifndef NTC_H
#define NTC_H

#include <stdint.h>

#include "adc.h"

#define NTC_VREF    (ADC_AREF)
#define NTC_ADC_MAX (ADC_MAX_VALUE)
#define NTC_RES_DIV (10000.0)
#define NTC_BETA    (3600.0)
#define NTC_R0      (10000.0)
#define NTC_T0      (273.0 + 25.0)

float ntc_convert_temperature(uint16_t raw_data);

#endif // NTC_H
