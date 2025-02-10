#include "ti/devices/msp/m0p/mspm0g350x.h"
#include "ti/devices/msp/peripherals/hw_gpio.h"
#include "ti/driverlib/dl_common.h"
#include "ti/driverlib/dl_timer.h"
#include "ti/driverlib/dl_timera.h"
#include "ti/devices/msp/msp.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"

/*
    Code created by Christopher A. Mendoza
    PWM - Center Aligned
    PWM - Edged Aligned
*/

#define Clk_Cycle_Delay     (16)
#define pincmIndex          (20)

void System_Power_Setup(){
    //First Reset the GPIOA & GPIOB
    GPIOA->GPRCM.RSTCTL = GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT;
    GPIOB->GPRCM.RSTCTL = GPIO_RSTCTL_KEY_UNLOCK_W | GPIO_RSTCTL_RESETSTKYCLR_CLR | GPIO_RSTCTL_RESETASSERT_ASSERT;
    //Next reset the Timer A1 & Timer A0
    TIMA1->GPRCM.RSTCTL = GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETSTKYCLR_CLR | GPTIMER_RSTCTL_RESETASSERT_ASSERT;
    TIMA0->GPRCM.RSTCTL = GPTIMER_RSTCTL_KEY_UNLOCK_W | GPTIMER_RSTCTL_RESETSTKYCLR_CLR | GPTIMER_RSTCTL_RESETASSERT_ASSERT;
    //Key Unlock and Disable
    GPIOA->GPRCM.PWREN = GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_DISABLE;
    GPIOB->GPRCM.PWREN = GPIO_PWREN_KEY_UNLOCK_W | GPIO_PWREN_ENABLE_DISABLE;
    //Timer Power Enable
    TIMA1->GPRCM.PWREN = GPTIMER_PWREN_KEY_UNLOCK_W | GPTIMER_PWREN_ENABLE_ENABLE;
    TIMA0->GPRCM.PWREN = GPTIMER_PWREN_KEY_UNLOCK_W | GPTIMER_PWREN_ENABLE_ENABLE;
    //Wait 16 Clock Cycles
    delay_cycles(Clk_Cycle_Delay);
}

//Setup the GPIO
void GPIO_Setup(){
    IOMUX->SECCFG.PINCM[20] = 5 | IOMUX_PINCM_PC_CONNECTED;
    GPIOA->DOESET31_0 = GPIO_PWM_C0_PIN;
    IOMUX->SECCFG.PINCM[20] = 5 | IOMUX_PINCM_PC_CONNECTED;
    GPIOA->DOESET31_0 = GPIO_PWM_C1_PIN;

}



int main(void)
{



    IOMUX->SECCFG.PINCM[0] = 0x81; 
    GPIOA->DOE31_0 |= 1;

 


    while (1) {
        GPIOA->DOUT31_0 |= 0x01;
        DL_Common_delayCycles(32000000);
        GPIOA->DOUT31_0 &= ~0x01;
        DL_Common_delayCycles(32000000);
    }
}