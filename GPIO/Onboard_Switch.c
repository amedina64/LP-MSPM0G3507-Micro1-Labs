#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_common.h"

int main(void)
{
    // Step 1: Reset ports A and B (only once)
    // Power ports and wait 24 clock cyles
    GPIOA->GPRCM.RSTCTL = 0xB1000003;
    GPIOB->GPRCM.RSTCTL = 0xB1000003;
    GPIOA->GPRCM.PWREN = 0x26000001;
    GPIOB->GPRCM.PWREN = 0x26000001;
    DL_Common_delayCycles(24);


    // Step 2: Select mode for each pin you will be using

    /* 
        Bit     Field               Meaning if 1                            Meaning if 0
        25      HiZ                 Output states are HiZ and low           Outputs states are high and low
        20      DRV                 Output pins are high drive              Output pins are regular drive
        18      INENA               Input operation enabled                 Input operation disabled
        17      PIPU                Input: Pullup Resistor                  Input: No pullup resistor
        16      PIPD                Input: Pulldown Resistor                Input: No pulldown resistor
        7       PC                  Software connected to pin               Software is disconnected to pin
        5:0     PF                                                          No digital function
    */

    // onboard leds
    // PA0 --- PA0 --- LED1
    // LED02 (RGB) --- PB22 [BLUE]

    // Onboard Switches 
    // SW1 --- PA18, Index 39. Pull-down only
    // SW2 --- PB21, Index 48. Pull-Up only

    IOMUX->SECCFG.PINCM[0] = 0x81; // PA0
    IOMUX->SECCFG.PINCM[49] = 0x00100081; // PB22

    IOMUX->SECCFG.PINCM[48] = 0x00060081;         // PB2 onboard switch 2. (SW2 is PULL-UP ONLY)
    IOMUX->SECCFG.PINCM[39] = 0x00050081;         // SW1 in pull down configuration
    GPIOA->DOE31_0 |= (1 << 0);                   // set doe register to enable peripheral (1 means using mode 1 or GPIO)
    GPIOB->DOE31_0 |= (1 << 22);

    while (1)
    {
        // Handle SW1 (pull-down, red LED)
        if (!(GPIOA->DIN31_0 & (1 << 18)))
        {
            GPIOA->DOUT31_0 |= (1 << 0);
        }
        else
        {
            GPIOA->DOUT31_0 &= ~(1 << 0);
        }

        // Handle SW2 (pull-up, blue LED)
        if (!(GPIOB->DIN31_0 & (1 << 21)))
        {
            GPIOB->DOUT31_0 |= (1 << 22);
        }
        else
        {
            GPIOB->DOUT31_0 &= ~(1 << 22);
        }

        DL_Common_delayCycles(300000);
    }
}

