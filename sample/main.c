/* This file is part of rfBareMbed.                        
 *									 
 * rfBareMbed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by	 
 * the Free Software Foundation, either version 3 of the License, or	 
 * (at your option) any later version.					 
 * 									 
 * rfBareMbed is distributed in the hope that it will be useful,		 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 
 * GNU General Public License for more details.				 
 * 									 
 * You should have received a copy of the GNU General Public License	 
 * along with rfBareMbed.  If not, see <http://www.gnu.org/licenses/>.	 
 */

#include <debug.h>
#include <uart.h>

#include <printf.h>
#include <interrupt.h>

uint32_t data = (LED1|LED2);
uint32_t data2 = 0xfadebeef;
char test1 = 0xAB;
void *add_data = &data;
void *add_data2 = &test1;

int a,b,c,d;
char e;



void test_data_bss()
{
    SET_LED(LED1|LED2|LED3|LED4);
    LPC_DELAY(1000000);
    CLR_LED(LED1|LED2|LED3|LED4);
    

    /* Check data section initialisation */
    if (data == (LED1 | LED2))
	SET_LED(LED1);

    LPC_DELAY(1000000);
    if (test1 == 0xAB)
	SET_LED(LED2);

    LPC_DELAY(1000000);
    if (add_data == &data)
	SET_LED(LED3);

    LPC_DELAY(1000000);
    if (data2 == 0xfadebeef)
	SET_LED(LED4);

    
    /* Check bss section initialisation */
    LPC_DELAY(1000000);
    if (a == 0 && b == 0 && c == 0 && d == 0)
	LED_VAL(LED1|LED4);
    else
	LED_VAL(LED2|LED3);
    LPC_DELAY(1000000);
}

void test_uart()
{
    char c = 'a';

    
    while (1)
    {
	lpc_uart0_putchar(c);
	++c;
	if (c == 'z'+1)
	{
	    lpc_uart0_putchar('\n');
	    lpc_uart0_putchar('\r');
	    c = 'a';
	}
    }
    
}

void test_echo()
{
    while (1)
    {
	char c = lpc_uart0_getchar();
	printf("Received '%c'\n\r", c);
    }
}

void test_printf()
{
    int a = -3;
    unsigned int b = 0xCAFED0CA;
    unsigned char byte = 0xFF;
    const char *str = "Pouet world!";
    char c = 'J';

    printf("Hello world\r\n");
    printf("Hello int world: '%d'\r\n", a);
    printf("Hello unsigned int world: '%u'\r\n", a);
    printf("Hello char world: '%c'\r\n", c);
    printf("Hello string world: '%s'\r\n", str);
    printf("Hello hexa world: '%x'\r\n", b);
    printf("Hello pointer world: '%p' '%P'\r\n", &b, str);
    printf("Hello multiple world: '%x' '%x' '%X' '%s'\r\n", b, byte,b, str);
}

void uart0_rx(char c)
{
    printf("Received '%c' via interrupt\r\n", c);
}

void test_echo_irq()
{
    lpc_uart0_set_rx_callback(uart0_rx);
    while (1)
	;
}

extern uint32_t _interrupt_start;
extern uint32_t _interrupt_end;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _text_end;


LPC_IRQ_HANDLER rit_handler()
{
    static int i = 0;

    ++i;
    LED_VAL(i % 16);
}


void test_rit()
{
    lpc_set_handler(RIT_IRQn, rit_handler);
    lpc_enable_interrupt(RIT_IRQn);
    LPC_RIT->RICOMPVAL = 10000;
    LPC_RIT->RICTRL |= 2; /* reset counter every time an interrupt is raised */
}

int main()
{
    INIT_LEDS();
    if (lpc_uart0_init() == -1)
	LPC_STOP(LED1 | LED3, 1000000);

    lpc_init_interrupts();

    test_data_bss();
/*    test_uart();*/
/*    test_printf();*/
    printf("Interrupt vector: %p %p\r\n", &_interrupt_start, &_interrupt_end);
    printf(".text: 0x00 %p\r\n", &_text_end);
    printf(".data: %p %p\r\n", &_data_start, &_data_end);
    printf(".bss: %p %p %x %x\r\n", &_bss_start, &_bss_end, _bss_start, _bss_end);
    printf("%d %d %d %d\r\n", a, b, c, d);
    printf("%p %p %p %p\r\n", &a, &b, &c, &d);
/*    test_echo();*/
/*    test_rit();*/
    test_echo_irq();
    
    LPC_STOP(LED2 | LED3, 1000000);

    return 0;
}
