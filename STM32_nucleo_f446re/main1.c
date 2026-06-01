#include <stdint.h>
#include<stdio.h>

volatile uint32_t *pClocken     = (volatile uint32_t*) 0x40023830;
volatile uint32_t *pGPIOAmoder  = (volatile uint32_t*) 0x40020000;
volatile uint32_t *pGPIOout     = (volatile uint32_t*) 0x40020014;

extern void initialise_monitor_handles(void);

int main(void) {
    // 1. Added 'volatile' to prevent the compiler from skipping or optimizing register writes
    

    // 2. Enable GPIOA peripheral clock
    *pClocken |= (1 << 0);

    // 3. Configure PA5 as a General Purpose Output Pin
    *pGPIOAmoder &= ~(3 << 10); // Clear bits 11:10
    *pGPIOAmoder |=  (1 << 10); // Set mode to 01 (Output)
	initialise_monitor_handles();

    // 4. Infinite blinking loop
    while(1) {
        // Turn the LED ON (Set bit 5)
        *pGPIOout |= (1 << 5);

        printf("LED turned on\n");
        // Software Delay loop
        // Uses 'volatile' so the compiler doesn't throw this empty loop away
        for(volatile uint32_t i = 0; i < 500000; i++);

        // Turn the LED OFF (Clear bit 5 using bitwise AND NOT)
        *pGPIOout &= ~(1 << 5);
        printf("LED turned off\n");
        // Software Delay loop
        for(volatile uint32_t i = 0; i < 500000; i++);
    }
}
