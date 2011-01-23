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

#ifndef __LPC1768_PINS_H__
#define __LPC1768_PINS_H__

#define LPC_PINSEL_BASE (0x4002C000)

#define LPC_PINSEL0 (*((uint32_t*) LPC_PINSEL_BASE))
#define LPC_PINSEL1 (*((uint32_t*) (LPC_PINSEL_BASE + 4)))
#define LPC_PINSEL2 (*((uint32_t*) (LPC_PINSEL_BASE + 8)))
#define LPC_PINSEL3 (*((uint32_t*) (LPC_PINSEL_BASE + 0xC)))
#define LPC_PINSEL4 (*((uint32_t*) (LPC_PINSEL_BASE + 0x10)))
#define LPC_PINSEL7 (*((uint32_t*) (LPC_PINSEL_BASE + 0x1C)))
#define LPC_PINSEL9 (*((uint32_t*) (LPC_PINSEL_BASE + 0x24)))
#define LPC_PINSEL10 (*((uint32_t*) (LPC_PINSEL_BASE + 0x28)))


#endif