# AVR Control Terminal

A simple automated control system made with the AVR ATmega328P, with a terminal accessible via serial interface.

This project was made to be energy sensitive, using interrupts in all peripherals and idle sleep mode to ensure eficiency.

## Components:

- Serial Terminal: Via USART0, accessible via serial interface.
- NTC Sensor: Via ADC channel 0.
- LDR Sensor: Via ADC channel 1.
- LED Light: Via Timer0 channel A (PWM).
- Buzzer: Via Timer2 channel B (PWM) 
- RTC DS3231: Via TWI.
- LCD 16x2: Via TWI.
