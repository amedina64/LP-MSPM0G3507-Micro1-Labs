#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "LCDLib/LCDmspm0.h"
#include "stdint.h"
#include "math.h"


/*Initialize the pins*/
void LCDStartup(void){
    //For now we will use 4 Bit Mode
    delay_ms(110);
    //Data Pins
    IOMUX->SECCFG.PINCM[11] = 0x81; //      D4
    IOMUX->SECCFG.PINCM[12] = 0x81; //      D5
    IOMUX->SECCFG.PINCM[14] = 0x81; //      D6
    IOMUX->SECCFG.PINCM[15] = 0x81; //      D7
    //Control Pins
    IOMUX->SECCFG.PINCM[22] = 0x81; //      Register Select
    IOMUX->SECCFG.PINCM[23] = 0x81; //      Enable
    //Start the LED
    GPIOB->DOE31_0 |= (LCD_DATA | LCD_EN | LCD_RegSel); //setup the pins

    GPIOB->DOUT31_0 = 0x03;
    LCDTriggerEn();
    delay_ms(5);
    LCDTriggerEn();
    delay_ms(5);
    LCDTriggerEn();
    delay_ms(5);

    GPIOB->DOUT31_0 = 0x02; //switch to 4-bit
    LCDTriggerEn();
    delay_ms(5);

    LCDWriteCMD(0x28); //4-bit, 2 line, 5x8
    LCDWriteCMD(0x08); // Instruction Flow
    LCDWriteCMD(0x01); // Clear LCD
    LCDWriteCMD(0x06); // Auto-Increment
    LCDWriteCMD(0x0C); // Display, No Blink
 
}

static void LCDTriggerEn(void){
    GPIOB->DOUT31_0 |= LCD_EN;
    GPIOB->DOUT31_0 &= ~LCD_EN;
}

static void LCDWriteCMD(unsigned char cmd){
    GPIOB->DOUT31_0 &= ~LCD_RegSel; //Set the RS to Data
    LowerNibble(cmd >> 4); //Upper Nibble
    LCDTriggerEn();
    LowerNibble(cmd);
    LCDTriggerEn();
    delay_ms(5); 
}

static void LCDWriteData(unsigned char cmd){
    GPIOB->DOUT31_0 |= LCD_RegSel; //Set the RS to Data
    LowerNibble(cmd >> 4); //Upper Nibble
    LCDTriggerEn();
    LowerNibble(cmd);
    LCDTriggerEn();
    delay_us(50);
}

void LCDSetText(char* text, uint8_t x, uint8_t y){
    uint32_t i;
    if(x < 16){
        x |= 0x80;          // Set the LCD for first line write
        switch (y) {
            case 1:
                x |= 0x40;  // Set the LCD for second line write
                break;
            case 2:
                x |= 0x60;  // Set the LCD for first line write revers
                break;
            case 3:
                x |= 0x20;  // Set the LCD for second line write reverse
                break;
        }
        LCDWriteCMD(x);
    }
    i = 0;
    while(text[i] != '\0'){
        LCDWriteData(text[i]);
        i++;
    }
}



void LCDClear(void){
    LCDWriteCMD(CLEAR);
}
void DisplayEnable(void){
    LCDWriteCMD(DISPLAY_ON);
}
void DisplayDisable(void){
    LCDWriteCMD(DISPLAY_OFF);
}
void CursorEnable(void){
    LCDWriteCMD(CURSOR_ON);
}
void CursorDisable(void){
    LCDWriteCMD(CURSOR_OFF);
}
void BlinkyCursorEnable(void){
    LCDWriteCMD(0x0F);
}

