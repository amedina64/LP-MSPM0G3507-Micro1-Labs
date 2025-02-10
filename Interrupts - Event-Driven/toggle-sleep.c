#include "ti/driverlib/m0p/dl_interrupt.h"
#include "ti_msp_dl_config.h"
#include "IndexMacros.h"

// SW2 (PB21, Pull-up) - Falling edge interrupt, toggles LED1 (PA0)
// SW1 (PA18, Pull-down) - Rising edge interrupt, toggles LED2 (PB22)

int main(void)
{
    // Enable GPIO power for ports A and B
    GPIOB->GPRCM.RSTCTL = 0xB1000003;
    GPIOB->GPRCM.PWREN = 0x26000001;
    GPIOA->GPRCM.RSTCTL = 0xB1000003;
    GPIOA->GPRCM.PWREN = 0x26000001;
    DL_Common_delayCycles(24);

    // --- Configure LEDs ---
    // Configure LED1 (PA0)
    IOMUX->SECCFG.PINCM[PA0INDEX] = 0x81;    // Set pinmux for PA0 (LED1)
    GPIOA->DOE31_0 |= (1 << 0);               // Set PA0 as output (LED1)

    // Configure LED2 (PB22 - Blue component of RGB LED)
    IOMUX->SECCFG.PINCM[PB22INDEX] = 0x81;    // Set pinmux for PB22 (LED2 - Blue)
    GPIOB->DOE31_0 |= (1 << 22);              // Set PB22 as output (LED2)

    // --- Configure Switches ---
    // Configure SW2 (PB21 - Pull-up, falling edge trigger)
    IOMUX->SECCFG.PINCM[PB21INDEX] = 0x00060081;  // Set pinmux for PB21 (input, pull-up)
    GPIOB->POLARITY31_16 = 0x00000800;             // Falling edge trigger for PB21
    GPIOB->CPU_INT.ICLR = 0x00200000;              // Clear any pending interrupt on PB21
    GPIOB->CPU_INT.IMASK = 0x00200000;             // Enable interrupt for PB21

    // Configure SW1 (PA18 - Pull-down, rising edge trigger)
    IOMUX->SECCFG.PINCM[PA18INDEX] = 0x00050081;   // Set pinmux for PA18 (input, pull-down)
    GPIOA->POLARITY31_16 = 0x00000010;             // Rising edge trigger for PA18
    GPIOA->CPU_INT.ICLR = 0x00040000;              // Clear any pending interrupt on PA18
    GPIOA->CPU_INT.IMASK = 0x00040000;             // Enable interrupt for PA18

    // --- Configure NVIC ---
    // Set priority and enable interrupt for Group 1 (PB21)
    NVIC->IP[0] = (NVIC->IP[0] & (~0x0000FF00)) | (2 << 14);  // Priority for IRQ1 (Group1)
    NVIC->ISER[0] = 1 << 1;                                   // Enable IRQ1 for Group1

    // Set priority and enable interrupt for Group 0 (PA18)
    NVIC->IP[0] = (NVIC->IP[0] & (~0x000000FF)) | (2 << 6);   // Priority for IRQ0 (Group0)
    NVIC->ISER[0] = 1 << 0;                                   // Enable IRQ0 for Group0

    // Enable global interrupts and enter sleep mode
    __enable_irq();

    while (1)
    {
        __WFI();  // Wait For Interrupt (sleep mode)
    }
}

// Interrupt handler for Group 1 (PB21 -> LED1) and (PA18 -> LED2)
void GROUP1_IRQHandler(void)
{
    if (GPIOB->CPU_INT.IIDX == 22)  // Check if PB21 triggered the interrupt
    {
        GPIOA->DOUTTGL31_0 = (1 << 0);  // Toggle LED1 (PA0)
        GPIOB->CPU_INT.ICLR = (1 << 21);  // Clear interrupt flag for PB21
    }

    if(GPIOA->CPU_INT.IIDX == 19) // Check if PA18 triggered the the interrupt
    {
        GPIOB->DOUTTGL31_0 = (1 << 22);  // Toggle LED2 (PB22)
        GPIOA->CPU_INT.ICLR = (1 << 18);  // Clear interrupt flag for PA18
    }
}