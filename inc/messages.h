// Copyright (c) 2025 Pedro Botelho
// All rights reserved

#ifndef MESSAGES_H
#define MESSAGES_H

#define BUFFER_SIZE (100)

#define WELCOME_STR         ("\n\r"\
                            "AVR BSP Terminal\n\r"\
                            "\n\r"\
                            "CPU: ATmega328P\n\r"\
                            "Clock: 16MHz\n\r"\
                            "Flash: 32KB\n\r"\
                            "SRAM: 2KB\n\r"\
                            "EEPROM: 1KB\n\r"\
                            "\n\r> ")
#define WELCOME_STR_SIZE    (sizeof(WELCOME_STR) - 1)

#define TIME_STRING_FORMAT  ("XX:XX:XX")
#define TIME_STRING_SIZE    (sizeof(TIME_STRING_FORMAT) - 1)

#define NEWLINE_STR         ("\n\r")
#define NEWLINE_STR_SIZE    (sizeof(NEWLINE_STR) - 1)

#define TERMINAL_STR        ("\n\r> ")
#define TERMINAL_STR_SIZE   (sizeof(TERMINAL_STR) - 1)

#define BACKSPACE_STR       ("\b \b")
#define BACKSPACE_STR_SIZE  (sizeof(BACKSPACE_STR) - 1)

#define STORE_STR           ("\n\rTime stored.")
#define STORE_STR_SIZE      (sizeof(STORE_STR) - 1)

#define LOAD_STR            ("\n\rTime loaded.")
#define LOAD_STR_SIZE       (sizeof(LOAD_STR) - 1)

#define INVALID_STR         ("\n\rInvalid command.")
#define INVALID_STR_SIZE    (sizeof(INVALID_STR) - 1)

#define EMPTY_STR           ("")
#define EMPTY_STR_SIZE      (sizeof(EMPTY_STR) - 1)

#define RTC_ERROR_STR       ("\n\rRTC has been disconnected.")
#define RTC_ERROR_STR_SIZE  (sizeof(RTC_ERROR_STR) - 1)

#define PROCESS_ERROR_STR       ("\n\rInvalid number of arguments!")
#define PROCESS_ERROR_STR_SIZE  (sizeof(PROCESS_ERROR_STR) - 1)

#define VARIABLE_ERROR_STR       ("\n\rInvalid variable!")
#define VARIABLE_ERROR_STR_SIZE  (sizeof(VARIABLE_ERROR_STR) - 1)

#endif // MESSAGES_H
