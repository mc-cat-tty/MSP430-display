/*
 * display7x4.c
 *
 * Author: Francesco Mecatti
 */

#include "display7x4.h"


void delay_ms(int ms){
    while(ms){
        __delay_cycles(1000);
        ms--;
    }
}

void init(void){
    out segments_aux[SEGMENTS_NUM] = {a, b, c, d, e, f, g, dp};
    out selectors_aux[SELECTORS_NUM] = {R1, G1, R2, G2, R3, G3, R4, G4};
    out out_aux[OUT_NUM] = {a, b, c, d, e, f, g, dp, R1, G1, R2, G2, R3, G3, R4, G4};
    memcpy(segments_arr, segments_aux, SEGMENTS_NUM*sizeof(out));
    memcpy(selectors_arr, selectors_aux, SELECTORS_NUM*sizeof(out));
    memcpy(out_arr, out_aux, OUT_NUM*sizeof(out));
    dir_out();
    all_off();
}

void on(out o){
    *o.port |= o.bit;
}

void off(out o){
    *o.port &= ~o.bit;
}

void toggle(out o){
    *o.port ^= o.bit;
}

void all_segments_on(void){
    int i;
    for (i=0; i<SEGMENTS_NUM; i++){
        on(segments_arr[i]);
    }
}

void all_segments_off(void){
    int i;
    for (i=0; i<SEGMENTS_NUM; i++){
        off(segments_arr[i]);
    }
}

void all_selectors_on(void){
    int i;
    for (i=0; i<SELECTORS_NUM; i++){
        on(selectors_arr[i]);
    }
}

void all_selectors_off(void){
    int i;
    for (i=0; i<SELECTORS_NUM; i++){
        off(selectors_arr[i]);
    }
}

void all_on(void){
    all_segments_on();
    all_selectors_on();
}

void all_off(void){
    all_segments_off();
    all_selectors_off();
}

void dir_out(void){
    P3DIR |= BIT5;
    P3DIR |= BIT6;
    P7DIR |= BIT0;
    P6DIR |= BIT4;
    P6DIR |= BIT3;
    P6DIR |= BIT2;
    P6DIR |= BIT1;
    P6DIR |= BIT0;

    P8DIR |= BIT2;
    P3DIR |= BIT7;
    P4DIR |= BIT0;
    P4DIR |= BIT3;
    P1DIR |= BIT2;
    P1DIR |= BIT3;
    P1DIR |= BIT4;
    P1DIR |= BIT5;
}

void list_on(int num, ...){
    va_list valist;
    int i;
    va_start(valist, num);
    for (i=0; i<num; i++){
        on(va_arg(valist, out));
    }
    va_end(valist);
}

void list_off(int num, ...){
    va_list valist;
    int i;
    va_start(valist, num);
    for (i=0; i<num; i++){
        off(va_arg(valist, out));
    }
    va_end(valist);
}

void hex_on(uint8_t n){ // This function accepts an hex number
    n = n & 0x0f;  // Keeping only Last Significant Nibble
    all_segments_off();
    switch (n){
        case 0x0:
            list_on(6, a, b, c, d, e, f);
            break;
        case 0x1:
            list_on(2, b, c);
            break;
        case 0x2:
            list_on(5, a, b, d, e, g);
            break;
        case 0x3:
            list_on(5, a, b, c, d, g);
            break;
        case 0x4:
            list_on(4, b, c, f, g);
            break;
        case 0x5:
            list_on(5, a, c, d, f, g);
            break;
        case 0x6:
            list_on(6, a, c, d, e, f, g);
            break;
        case 0x7:
            list_on(3, a, b, c);
            break;
        case 0x8:
            list_on(7, a, b, c, d, e, f, g);
            break;
        case 0x9:
            list_on(6, a, b, c, d, f, g);
            break;
        case 0xa:
            list_on(6, a, b, c, e, f, g);
            break;
        case 0xb:
            list_on(5, c, d, e, f, g);
            break;
        case 0xc:
            list_on(4, a, d, e, f);
            break;
        case 0xd:
            list_on(5, b, c, d, e, g);
            break;
        case 0xe:
            list_on(5, a, d, e, f, g);
            break;
        case 0xf:
            list_on(4, a, e, f, g);
            break;
    }
}

void dec_on(uint8_t n){ // This function accepts an hex number
    n = n & 0x0f;  // Keeping only Last Significant Nibble
    all_segments_off();
    switch (n){
        case 0:
            list_on(6, a, b, c, d, e, f);
            break;
        case 1:
            list_on(2, b, c);
            break;
        case 2:
            list_on(5, a, b, d, e, g);
            break;
        case 3:
            list_on(5, a, b, c, d, g);
            break;
        case 4:
            list_on(4, b, c, f, g);
            break;
        case 5:
            list_on(5, a, c, d, f, g);
            break;
        case 6:
            list_on(6, a, c, d, e, f, g);
            break;
        case 7:
            list_on(3, a, b, c);
            break;
        case 8:
            list_on(7, a, b, c, d, e, f, g);
            break;
        case 9:
            list_on(6, a, b, c, d, f, g);
            break;
    }
}

void char_on(char ch){  // Case insensitive
    all_segments_off();
    switch (ch){
        case '0':
            list_on(6, a, b, c, d, e, f);
            break;
        case '1':
            list_on(2, b, c);
            break;
        case '2':
            list_on(5, a, b, d, e, g);
            break;
        case '3':
            list_on(5, a, b, c, d, g);
            break;
        case '4':
            list_on(4, b, c, f, g);
            break;
        case '5':
            list_on(5, a, c, d, f, g);
            break;
        case '6':
            list_on(6, a, c, d, e, f, g);
            break;
        case '7':
            list_on(3, a, b, c);
            break;
        case '8':
            list_on(7, a, b, c, d, e, f, g);
            break;
        case '9':
            list_on(6, a, b, c, d, f, g);
            break;
        case 'a':
        case 'A':
            list_on(6, a, b, c, e, f, g);
            break;
        case 'b':
        case 'B':
            list_on(5, c, d, e, f, g);
            break;
        case 'c':
        case 'C':
            list_on(4, a, d, e, f);
            break;
        case 'd':
        case 'D':
            list_on(5, b, c, d, e, g);
            break;
        case 'e':
        case 'E':
            list_on(5, a, d, e, f, g);
            break;
        case 'f':
        case 'F':
            list_on(4, a, e, f, g);
            break;
        case 'g':
        case 'G':
            list_on(5, a, c, d, e, f);
            break;
        case 'h':
        case 'H':
            list_on(4, c, e, f, g);
            break;
        case 'i':
        case 'I':
            list_on(2, e, f);
            break;
        case 'j':
        case 'J':
            list_on(4, b, c, d, e);
            break;
        case 'k':
        case 'K':
            list_on(5, a, c, e, f, g);
            break;
        case 'l':
        case 'L':
            list_on(3, d, e, f);
            break;
        case 'm':
        case 'M':
            list_on(3, a, c, e);
            break;
        case 'n':
        case 'N':
            list_on(4, a, b, c, e, f);
            break;
        case 'o':
        case 'O':
            list_on(6, a, b, c, d, e, f);
            break;
        case 'p':
        case 'P':
            list_on(5, a, b, e, f, g);
            break;
        case 'q':
        case 'Q':
            list_on(5, a, b, c, f, g);
            break;
        case 'r':
        case 'R':
            list_on(4, a, b, e, f);
            break;
        case 's':
        case 'S':
            list_on(5, a, c, d, f, g);
            break;
        case 't':
        case 'T':
            list_on(4, d, e, f, g);
            break;
        case 'u':
        case 'U':
            list_on(5, b, c, d, e, f);
            break;
        case 'v':
        case 'V':
            list_on(4, b, c, d, f);
            break;
        case 'w':
        case 'W':
            list_on(3, b, d, f);
            break;
        case 'x':
        case 'X':
            list_on(5, b, c, e, f, g);
            break;
        case 'y':
        case 'Y':
            list_on(5, b, c, d, f, g);
            break;
        case 'z':
        case 'Z':
            list_on(4, a, b, d, g);
            break;
        case '_':
            list_on(1, d);
            break;
        case ' ':
        default:
            list_on(0);
            break;
    }
}

uint8_t get(uint16_t num, uint8_t pos) {  // Returns digit at position pos
    switch (pos){
        case 0:
            return (num%0x100);
        case 1:
            return ((num/0x10)%0x100);
        case 2:
            return (num/0x100);
        case 3:
            return (num/0x1000);
    }
    return 0x00;
}

void blink(out o, int ms){
    on(o);
    delay_ms(ms);
    off(o);
}

void display(uint16_t num, color c){
    all_off();
    static const int ms = 1;
    switch (c) {
        case RED:
            hex_on(get(num, 0));
            blink(R1, ms);
            hex_on(get(num, 1));
            blink(R2, ms);
            hex_on(get(num, 2));
            blink(R3, ms);
            hex_on(get(num, 3));
            blink(R4, ms);
            break;
        case GREEN:
            hex_on(get(num, 0));
            blink(G1, ms);
            hex_on(get(num, 1));
            blink(G2, ms);
            hex_on(get(num, 2));
            blink(G3, ms);
            hex_on(get(num, 3));
            blink(G4, ms);
            break;
    }
}

void display_readable(uint16_t num, color c, int time){  // 'time' represent how much time (in ms) 'num' will be shown
    int i;
    time /= (float) 9.9;  // Divisor obtained empirically
    if (c == YELLOW){
        for (i=0; i<time; i++){
            if (i%2 == 0)
                display(num, GREEN);
            else
                display(num, RED);
        }
    }
    else{
        for (i=0; i<time; i++){
            display(num, c);
        }
    }
}

uint8_t get_decimal(uint16_t num, uint8_t pos) {  // Returns digit at position pos
    switch (pos){
        case 0:
            return (num%10);
        case 1:
            return ((num/10)%10);
        case 2:
            return ((num/100)%10);
        case 3:
            return (num/1000);
    }
    return 0;
}

void display_decimal(uint16_t num, color c, bool *dots){
    all_off();
    static const int ms = 1;
    switch (c) {
        case RED:
            dec_on(get_decimal(num, 0));
            if (dots != NULL && dots[3]) on(dp);
            blink(R1, ms);
            dec_on(get_decimal(num, 1));
            if (dots != NULL && dots[2]) on(dp);
            blink(R2, ms);
            dec_on(get_decimal(num, 2));
            if (dots != NULL && dots[1]) on(dp);
            blink(R3, ms);
            dec_on(get_decimal(num, 3));
            if (dots != NULL && dots[0]) on(dp);
            blink(R4, ms);
            break;
        case GREEN:
            dec_on(get_decimal(num, 0));
            if (dots != NULL && dots[3]) on(dp);
            blink(G1, ms);
            dec_on(get_decimal(num, 1));
            if (dots != NULL && dots[2]) on(dp);
            blink(G2, ms);
            dec_on(get_decimal(num, 2));
            if (dots != NULL && dots[1]) on(dp);
            blink(G3, ms);
            dec_on(get_decimal(num, 3));
            if (dots != NULL && dots[0]) on(dp);
            blink(G4, ms);
            break;
    }
}

void display_text(char *text, color c){  // Four characters-long text
    all_off();
    static const int ms = 1;
    switch (c) {
        case RED:
            if (text[0] != '\0'){
                char_on(text[0]);
                blink(R4, ms);
                if (text[1] != '\0'){
                    char_on(text[1]);
                    blink(R3, ms);
                    if (text[2] != '\0'){
                        char_on(text[2]);
                        blink(R2, ms);
                        if (text[3] != '\0'){
                            char_on(text[3]);
                            blink(R1, ms);
                        }
                    }
                }
            }
            break;
        case GREEN:
            if (text[0] != '\0'){
                char_on(text[0]);
                blink(G4, ms);
                if (text[1] != '\0'){
                    char_on(text[1]);
                    blink(G3, ms);
                    if (text[2] != '\0'){
                        char_on(text[2]);
                        blink(G2, ms);
                        if (text[3] != '\0'){
                            char_on(text[3]);
                            blink(G1, ms);
                        }
                    }
                }
            }
            break;
        }
}

void display_text_readable(char *text, color c, int time){
    int i, j;
    int len = strlen(text);
    time /= (float) 9.9;  // Divisor obtained empirically
    if (len == 4){
        for (i=0; i<(time/len); i++){
            display_text(text, c);
        }
    }
    else {
        for (i=0; i<len+1; i++){
            for (j=0; j<(time/len); j++){
                display_text((text+i), c);
            }
        }
    }
}
