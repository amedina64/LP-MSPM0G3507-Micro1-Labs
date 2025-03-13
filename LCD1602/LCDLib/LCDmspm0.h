#ifndef LCDMSPM0_H_
#define LCDMSPM0_H_

#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "stdint.h"

/*
    LCD Driver for MSPM0
    Author: Christopher A. Mendoza

    LCD-1602 Pinout:
    ----------------
    Pin  1: VSS  ---->  GND
    Pin  2: VDD  ---->  +5V
    Pin  3: VO   ---->  POT_OUT
    Pin  4: RS   ---->  PB6
    Pin  5: RW   ---->  GND
    Pin  6: EN   ---->  PB7
    Pin  7: D0   ---->  (NC)
    Pin  8: D1   ---->  (NC)
    Pin  9: D2   ---->  (NC)
    Pin 10: D3   ---->  (NC)
    Pin 11: D4   ---->  PB0
    Pin 12: D5   ---->  PB1
    Pin 13: D6   ---->  PB2
    Pin 14: D7   ---->  PB3
    Pin 15: Anode (+)
    Pin 16: Cathode (-)

    Notes:
    ------
    - Delay assumes a 32MHz system clock.
    - If the clock frequency is changed, update the delay macros accordingly.

    Available Functions:
    ---------------------
    - LCDStartup()
    - LCDSetText()
    - LCDClear()
    - DisplayEnable()
    - DisplayDisable()
    - CursorEnable()
    - CursorDisable()
    - BlinkyCursorEnable()
*/

/* LCD Command and Control Macros */
#define LCD_RegSel      (0b01000000)
#define LCD_EN          (0b10000000)
#define LCD_DATA        (0b00001111)
#define DISPLAY_ON      (0x0C)
#define DISPLAY_OFF     (0x08)
#define CURSOR_OFF      (0x0C)
#define CURSOR_ON       (0x0E)
#define CLEAR           (0x01)

/* GPIO Operations */
#define LowerNibble(x)  GPIOB->DOUT31_0 = (GPIOB->DOUT31_0 & 0xF0) + (x & 0x0F)

/* Delay Macros (Assuming 32MHz Clock) */
#define delay_ms(ms)    DL_Common_delayCycles(32000 * ms)
#define delay_us(us)    DL_Common_delayCycles(32 * us)

/* LCD Driver Function Prototypes */
void LCDStartup(void);
void LCDClear(void);
void LCDSetText(char* text, uint8_t x, uint8_t y);
void DisplayEnable(void);
void DisplayDisable(void);
void CursorEnable(void);
void CursorDisable(void);
void BlinkyCursorEnable(void);

/* Internal Helper Functions */
static void LCDTriggerEn(void);
static void LCDWriteCMD(unsigned char cmd);
static void LCDWriteData(unsigned char data);

#endif /* LCDMSPM0_H_ */