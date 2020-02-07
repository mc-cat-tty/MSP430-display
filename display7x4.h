/*
 * display7x4.h
 *
 * Author: Francesco Mecatti
 */

#ifndef INCLUDE_DISPLAY7X4_H_
#define INCLUDE_DISPLAY7X4_H_

#include <msp430.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define SEGMENTS_NUM 8
#define SELECTORS_NUM 8
#define OUT_NUM SEGMENTS_NUM+SELECTORS_NUM

typedef struct {
    volatile uint8_t *port;
    uint16_t bit;
} out;

typedef enum {GREEN, RED, YELLOW} color;  //YELLOW supported only by display_readable() function

static const out a = {.port = &P3OUT, .bit = BIT5};
static const out b = {.port = &P3OUT, .bit = BIT6};
static const out c = {.port = &P7OUT, .bit = BIT0};
static const out d = {.port = &P6OUT, .bit = BIT4};
static const out e = {.port = &P6OUT, .bit = BIT3};
static const out f = {.port = &P6OUT, .bit = BIT2};
static const out g = {.port = &P6OUT, .bit = BIT1};
static const out dp = {.port = &P6OUT, .bit = BIT0};
static const out R1 = {.port = &P1OUT, .bit = BIT4};
static const out G1 = {.port = &P1OUT, .bit = BIT5};
static const out R2 = {.port = &P1OUT, .bit = BIT2};
static const out G2 = {.port = &P1OUT, .bit = BIT3};
static const out R3 = {.port = &P4OUT, .bit = BIT0};
static const out G3 = {.port = &P4OUT, .bit = BIT3};
static const out R4 = {.port = &P8OUT, .bit = BIT2};
static const out G4 = {.port = &P3OUT, .bit = BIT7};

out segments_arr[SEGMENTS_NUM];  // Arrays
out selectors_arr[SELECTORS_NUM];
out out_arr[OUT_NUM];

void setup(void);
void init(void);
void on(out);
void off(out);
void list_on(int, ...);
void list_off(int, ...);
void all_segments_on(void);
void all_selectors_on(void);
void all_segments_off(void);
void all_selectors_off(void);
void all_on(void);
void all_off(void);
void toggle(out);
void dir_out(void);
void hex_on(uint8_t);
void dec_on(uint8_t);
void char_on(char);
void delay_ms(int);
uint8_t get(uint16_t, uint8_t);  // Default: hex
uint8_t get_decimal(uint16_t, uint8_t);
void blink(out, int);
void display(uint16_t, color);  // For numbers
void display_readable(uint16_t, color, int);
void display_decimal(uint16_t, color, bool*);
void display_decimal_readable(uint16_t, color);
void display_text(char*, color);  // For strings (case insensitive)
void display_text_sliding(char*, color, int);
void display_text_loop(char*, color, int, int);

#endif //INCLUDE_DISPLAY7X4_H_
