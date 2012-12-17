/* This file is part of rflpc. Copyright 2010-2011 Michael Hauspie
 *
 * rflpc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rflpc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rflpc.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  Author: Michael Hauspie <michael.hauspie@univ-lille1.fr>
  Created:
  Time-stamp: <2012-12-17 16:17:23 (hauspie)>
*/
#include <rflpc17xx/rflpc17xx.h>

#define LED_PIN RFLPC_LED_1_PIN
#define PWM_PIN1 MBED_DIP23
#define PWM_PIN2 MBED_DIP21

#define PERIOD 10000

volatile uint16_t ps;

RFLPC_IRQ_HANDLER uart_rx(void)
{
    char c = rflpc_uart_getchar(RFLPC_UART0);

    switch (c)
    {
	case '+':
	    ps = ps << 1;
	    if (ps == 0)
		ps = 1;
	    if (ps >= PERIOD)
		ps = PERIOD-1;
	    rflpc_pwm_single_edge(PWM_PIN1, ps>>1);
	    rflpc_pwm_single_edge(PWM_PIN2, ps);
	    break;
	case '-':
	    ps = ps >> 1;
	    rflpc_pwm_single_edge(PWM_PIN1, ps>>1);
	    rflpc_pwm_single_edge(PWM_PIN2, ps);
	    break;
	case 'a':
	    rflpc_pwm_start(PWM_PIN1);
	    break;
	case 'A':
	    rflpc_pwm_stop(PWM_PIN1);
	    break;

	case 'z':
	    rflpc_pwm_start(PWM_PIN2);
	    break;
	case 'Z':
	    rflpc_pwm_stop(PWM_PIN2);
	    break;	    
    }
}

int main()
{
#ifdef RFLPC_CONFIG_ENABLE_UART
    rflpc_uart_init(RFLPC_UART0);
    rflpc_uart_set_rx_callback(RFLPC_UART0, uart_rx);
#endif

#ifdef RFLPC_CONFIG_ENABLE_PRINTF
    printf("Hello World\r\n");
#endif

    rflpc_gpio_use_pin(LED_PIN);
    rflpc_gpio_set_pin_mode_output(LED_PIN);

    rflpc_pwm_init(PWM_PIN1);
    rflpc_pwm_init(PWM_PIN2);
    rflpc_pwm_init(MBED_DIP25);
    
    ps = 500;
    rflpc_pwm_single_edge(PWM_PIN1, ps);
    rflpc_pwm_single_edge(PWM_PIN2, 0);
    rflpc_pwm_double_edge(MBED_DIP25, 1000, 2000);
    rflpc_pwm_start(PWM_PIN1);
    rflpc_pwm_start(PWM_PIN2);
    rflpc_pwm_start(MBED_DIP25);
    rflpc_pwm_set_period(PERIOD);

    while (1)
    {
	int i;
	rflpc_gpio_set_pin(LED_PIN);
	for (i = 0 ; i < 20000000 ; ++i);
	rflpc_gpio_clr_pin(LED_PIN);
	for (i = 0 ; i < 20000000 ; ++i);
    }
    return 0;
}
