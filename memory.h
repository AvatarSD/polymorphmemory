#ifndef MEMORY_H
#define MEMORY_H

#include <inttypes.h>

/* I2C Memory Map
 * __________________HEADER_____________________
 * |__START__|__SIZE__|_DESCRIPTIONS_|_OPTIONS_|
 * |0        |16      |guid          |ro       |
 * |16       |2       |require temp  |ro       |
 * |18       |1       |sensors count |ro       |
 * |19       |2       |[res]stat&ctl |rw       |
 * ---------------------------------------------
 * |SIZE: 21 |
 *
 * ________________Device Node__________________
 * |__START__|__SIZE__|_DESCRIPTIONS_|_OPTIONS_|
 * |0        |8       |ROM           |ro       |
 * |8        |2       |Temp          |ro       |
 * |10       |1       |[res]stat&ctl |rw       |
 * ---------------------------------------------
 * |SIZE: 11 |
 *
 * ___________________Main__________________
 * |__START__|__SIZE__|____DESCRIPTIONS____|
 * |0        |21      |HEADER              |
 * |21       |14      |[res]               |
 * |35+N     |46+N    |Nodes(N={0..19})    |
 * -----------------------------------------
 * |SIZE:256 |
 *
 */

/* EEPROM Memory Map
 *
 *
 *
 */

void write(uint8_t addr, uint8_t data);
uint8_t read(uint8_t addr);


#endif
