#include <display7x4.h>

/*
* Remember to call init() function
*/

/*
 * main.c
 *
 * Author: Francesco Mecatti
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
