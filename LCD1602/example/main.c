#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "stdint.h"
#include "LCDLib/LCDmspm0.h"


/*
    This example shows a basic example of 
    LCD 1602, with cursor and Blinky,
    and along with some text.

    -Christopher A. Mendoza

*/

void init_Ports(void){
    // Reset and power up GPIO ports A and B
    GPIOA->GPRCM.RSTCTL = 0xB1000003;
    GPIOB->GPRCM.RSTCTL = 0xB1000003;
    GPIOA->GPRCM.PWREN = 0x26000001;
    GPIOB->GPRCM.PWREN = 0x26000001;
    // Small delay for stabilization
    DL_Common_delayCycles(24);
}


int main(void)
{

    init_Ports();
    LCDStartup(); 
    
    DisplayDisable();
    delay_ms(3000);
    DisplayEnable();
    
    CursorEnable();
    delay_ms(2000);
    
    BlinkyCursorEnable();
    delay_ms(2000);
    
    while (1) {        
        LCDSetText("UTEP GO Miners!", 0, 0);
        delay_ms(1000);
        LCDClear();
        LCDSetText("This Works!!", 0, 0);
        delay_ms(1000);
        LCDClear();
    }
}
