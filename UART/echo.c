#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/driverlib/dl_common.h"
#include "IndexMacros.h"

#define UART_TX_READY (UART0->STAT & 0x80)  // TX FIFO full flag
#define UART_RX_READY (UART0->STAT & 0x04)  // RX data available flag

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

void UART_Init() 
{
    // Reset and enable UART0
    UART0->GPRCM.RSTCTL = 0xB1000003; 
    UART0->GPRCM.PWREN = 0x26000001;
    DL_Common_delayCycles(24);

    // Configure UART pins
    IOMUX->SECCFG.PINCM[PA10INDEX] = 0x00000082; // UART TX on PA10 [USB cable to PC]
    IOMUX->SECCFG.PINCM[PA11INDEX] = 0x00040082; // UART RX on PA11 [USB cable to PC]

    // Set UART clock and parameters
    UART0->CLKSEL = 0x08;  // Running on a 32 MHz clock
    UART0->CLKDIV = 0x00;
    UART0->CTL0 &= ~0x01;  // Disable UART before setting parameters

    UART0->IBRD = 17;       // Integer part of baud rate divisor
    UART0->FBRD = 23;       // Fractional part of baud rate divisor
    UART0->LCRH = 0x00000030;  // 8 data bits, no parity, 1 stop bit
    UART0->CTL0 = 0x00020019;  // Enable UART and transmit
}

char UART_InChar() 
{
    while (!(UART_RX_READY));  // Wait until data is available
    return (char)(UART0->RXDATA);
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

int main(void) 
{
    init_Ports();
    UART_Init();

    while (1) 
    {
        UART_SendString("Hello MSPM0 to my computer!\r\n");  // Send a string over UART
        DL_Common_delayCycles(32000000);       // 1-second delay @ 32 MHz
    }
}