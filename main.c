#include <msp430.h>
#include "display7x4.h"

/*
 * main.c
 *
 *  Created on: 24 gen 2020
 *      Author: utente
 */


void main (void) {
    WDTCTL = WDTPW + WDTHOLD;
    init();
    while (1) {
        display_text_loop("Sacripante", RED, 500, 100);
    }
}
