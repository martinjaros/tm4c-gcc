#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

int main(void)
{
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    while(1)
    {
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        ROM_SysCtlDelay(1000000);
        ROM_GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        ROM_SysCtlDelay(1000000);
    }
}
