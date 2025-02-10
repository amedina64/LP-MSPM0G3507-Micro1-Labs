#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti_msp_dl_config.h"
#include "IndexMacros.h"

#define UART_TX_READY (UART0->STAT & 0x80)  // TX FIFO full flag
#define UART_RX_READY (UART0->STAT & 0x04)  // RX data available flag

void UART_SendString(const char *str);
void UART_OutChar(char data);

int main(void) 
{
    // Enable GPIO power for ports A and B
    GPIOA->GPRCM.RSTCTL = 0xB1000003;
    GPIOA->GPRCM.PWREN = 0x26000001;
    GPIOB->GPRCM.RSTCTL = 0xB1000003;
    GPIOB->GPRCM.PWREN = 0x26000001;

    // --- Configure Switches ---
    // Configure SW2 (PB21 - Pull-up falling edge trigger)
    IOMUX->SECCFG.PINCM[PB21INDEX] = 0x00060081;  // Set pinmux for PB21 (input, pull-up)
    GPIOB->POLARITY31_16 = 0x00000800;             // Falling edge trigger for PB21
    GPIOB->CPU_INT.ICLR = 0x00200000;              // Clear any pending interrupt on PB21
    GPIOB->CPU_INT.IMASK = 0x00200000;             // Enable interrupt for PB21
    NVIC->IP[0] = (NVIC->IP[0] & (~0x0000FF00)) | (2 << 14);  // Priority for IRQ1 (Group1)
    NVIC->ISER[0] = 1 << 1;                                   // Enable interrupt for Group1

    // --- Configure UART0 ---
    // Assumptions: 32 MHz and 115200 Baud Rate
    // Configure UART0 (TX: PA10,  RX: PA11) [USB Cable to PC]
    UART0->GPRCM.RSTCTL = 0xB1000003; 
    UART0->GPRCM.PWREN = 0x26000001;
    DL_Common_delayCycles(24);
    IOMUX->SECCFG.PINCM[PA10INDEX] = 0x00000082; // UART TX on PA10 [USB cable to PC]
    IOMUX->SECCFG.PINCM[PA11INDEX] = 0x00040082; // UART RX on PA11 [USB cable to PC]

    UART0->CLKSEL = 0x08;  // Running on a 32 MHz clock
    UART0->CLKDIV = 0x00;
    UART0->CTL0 &= ~0x01;  // Disable UART before setting parameters
    UART0->IBRD = 17;       // Integer part of baud rate divisor
    UART0->FBRD = 23;       // Fractional part of baud rate divisor
    UART0->LCRH = 0x00000030;  // 8 data bits, no parity, 1 stop bit
    UART0->CTL0 = 0x00020019;  // Enable UART and transmit


    // Enable NVIC for GPIO interrupt (Group 1, IRQ17)
    NVIC->ICPR[0] = (1 << 17);         // Clear pending interrupt
    NVIC->ISER[0] = (1 << 17);         // Enable interrupt for IRQ17
    NVIC->IP[17] = (NVIC->IP[17] & (~0xFF000000)) | (2 << 30);  // Priority 2
    
    __enable_irq();

    while (1) 
    {
        __WFI();
    }
}

void UART_OutChar(char data) 
{
    while (UART_TX_READY);  
    UART0->TXDATA = data;
}


void UART_SendString(const char *str) 
{
    while (*str) 
    {
        UART_OutChar(*str++);
    }
}


void GROUP1_IRQHandler() 
{
    if (GPIOB->CPU_INT.IIDX == 22) 
    {
        UART_SendString("Hello there!\r\n");
    }
}