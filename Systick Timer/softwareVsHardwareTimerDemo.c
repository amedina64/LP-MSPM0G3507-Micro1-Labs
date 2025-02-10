#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_common.h"
#include "IndexMacros.h"

// Toggle blue and red LEDs with different timing intervals
// Red LED toggles every second in main loop, blue LED toggles via interrupt every 2 seconds


#define RED_LED_PIN 0
#define BLUE_LED_PIN 22
#define SYSTICK_LOAD_VALUE 3200000

volatile uint8_t tics = 0;

void init_Ports() 
{
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

    // Configure pins for output
    IOMUX->SECCFG.PINCM[PA0INDEX] = 0x81;
    IOMUX->SECCFG.PINCM[PB22INDEX] = 0x81;
    GPIOA->DOE31_0 |= (1 << RED_LED_PIN);
    GPIOB->DOE31_0 |= (1 << BLUE_LED_PIN);

    // Initialize SysTick Timer. Enable systick on the LAST step.

    SysTick->CTRL = 0;
	SysTick->VAL = 0;	
	SysTick->LOAD = 3200000; // 3200000/32MHz - > 0.1s -> 100ms
    SysTick->CTRL = 0x07;	// 1       1       1    ->  0x07, start timer

    // Set interrupt priority for SysTick (lowest priority)
    SCB->SHP[1] = (SCB->SHP[1] & ~0xC0000000) | (1 << 30);

    while (1) 
    {
        // Toggle red LED every second
        GPIOA->DOUT31_0 ^= (1 << RED_LED_PIN);
        DL_Common_delayCycles(32000000);  // 1-second delay
    }
}

void SysTick_Handler() 
{
    // Toggle blue LED every 2 seconds
    if (++tics >= 20) 
    {
        GPIOB->DOUTTGL31_0 ^= (1 << BLUE_LED_PIN);
        tics = 0;
    }
}