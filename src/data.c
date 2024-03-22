/******************************************************************************
 * Copyright (C) 2024 by Illia Baliuk
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Illia Baliuk are not liable for any misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file data.c
 * @brief Basic data manipulation
 *
 * @author Illia Baliuk
 * @date March 21 2024
 *
 */

#include "data.h"
#include "platform.h"

uint8_t my_itoa(int32_t data, uint8_t* ptr, uint32_t base) {

    // Pointer to move through the chain
    uint8_t* revers = ptr;
    uint8_t isNegative = 0;
    uint8_t count = 0;

    if (data == 0) {
        *ptr++ = '0';
        *ptr = '\0';
        return 2;
    }

    if (data < 0) {
        isNegative = 1;
        data = -data;
    }

    *revers++ = '\0'; // in the future the last element
    count++;
    
    while (data != 0) {
        uint8_t remainder = data % base;
        *revers++ = (remainder > 9) ? 'a' + (remainder - 10) : '0' + remainder;
        data /= base;
        count++;
    }

    // Add the negative sign if necessary
    if (isNegative) {
        *revers++ = '-';
        count++;
    }

    // reverse the line
	uint8_t* head = revers - 1;
    uint8_t* tail = revers - count;

    while (tail < head) {
        uint8_t temp = *tail;
        *tail++ = *head;
        *head-- = temp;
    }

    return count;
}

int32_t my_atoi(uint8_t* ptr, uint8_t digits, uint32_t base) {
    int32_t total = 0, sign = 1;
    int32_t number;
    if (*ptr == '-') {
        sign = -1;
        ++ptr;
        --digits;
    }
    while (digits > 1) {

        if (*ptr >= '0' && *ptr <= '9') {
            number = *ptr - '0';
        } else if (*ptr >= 'a' && *ptr <= 'f') {
            number = 10 + (*ptr - 'a');
        } else if (*ptr >= 'A' && *ptr <= 'F') {
            number = 10 + (*ptr - 'A');
        } else {
            return 0; // Invalid character
        }

        total = total * base + number;
        ++ptr;
        --digits;
    }
    total *= sign;
    return total;
}
