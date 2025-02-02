#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_common.h"

#define OUTPUT 0x81

int main(void)
{
    // Step 1: Reset ports (EXACTLY ONCE), power ports and wait at least 24 clk cycles
    // Power ports and wait 24 clock cyles
    GPIOA->GPRCM.RSTCTL = 0xB1000003;
    GPIOA->GPRCM.PWREN = 0x26000001;
    DL_Common_delayCycles(24);


    // Step 2: Select mode for each pin you will be using
    // In this example, we will use PA0 as a simple output pin

    IOMUX->SECCFG.PINCM[0] = OUTPUT;
    GPIOA->DOE31_0 |= 1;

    while (1) 
    {
        GPIOA->DOUT31_0 |= 0x01;
        DL_Common_delayCycles(3000000);
        GPIOA->DOUT31_0 &= ~(0x01);
        DL_Common_delayCycles(3000000);
    }
}