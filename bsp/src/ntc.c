// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#include "ntc.h"

#include <math.h>

#define NTC_RX ((NTC_R0) * exp(-(NTC_BETA)/(NTC_T0)))

float ntc_convert_temperature(uint16_t raw_data) {
    float voltage = ((NTC_VREF) * (raw_data)) / ((1.0) * (NTC_ADC_MAX));

    float ntc_resistence = ((NTC_VREF) * (NTC_RES_DIV)) / (voltage) - NTC_RES_DIV;
    
    float temperature_kelvin = NTC_BETA / log((ntc_resistence)/(NTC_RX));
    
    return temperature_kelvin - 273.0;
}
