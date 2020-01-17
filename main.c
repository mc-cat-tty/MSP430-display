#include <display7x4.h>


/*
 * main.c
 *
 *  Created on: 17 gen 2020
 *      Author: utente
 */


int main(void)
  {
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    init();
    while (1) {
        for (uint16_t i=0x0000; i<=0xffff; i++){
            display_readable(i, YELLOW, 500);
        }
    }
    return 0;
}
