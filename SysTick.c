/******************************************************************************
 *
 * Module: SysTick
 *
 * File Name: SysTick.c
 *
 * Description: Source file for the ARM Cortex M4 SysTick driver
 *
 * Author: Saraa Gomaa
 *
 *******************************************************************************/

#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"

/* Global variable to hold the call back function */
static volatile void (*g_SysTickCallBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Function Definitions                                  *
 *******************************************************************************/

/**********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: ConfigPtr - Pointer to configuration structure
 * Return Value: None
 * Description: Initializes the SysTick timer with the specified value
 *********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds)
{
    uint32 ticks = (a_TimeInMilliSeconds * 16000) - 1; // Assuming 16MHz clock

    SYSTICK_CTRL_REG  = 0; // Disable SysTick during setup
    SYSTICK_RELOAD_REG = ticks; // Set reload register
    SYSTICK_CURRENT_REG = 0; // Clear current register
    SYSTICK_CTRL_REG = 0x07; // Enable SysTick with system clock and interrupts
}


/**********************************************************************
 * Service Name: SysTick_StartBusyWait
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: a_TimeInMilliseconds - Time interval in millisecond
 * Return Value: None
 * Description: Initializes the SysTick timer to use polling (busy wait)
 * for the specified time in millisecond. The function exits when the
 * time elapses and stops the timer.
 *********************************************************************/
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds)
{
    uint32 ticks = (a_TimeInMilliSeconds * 16000) - 1; // Assuming 16MHz clock

    SYSTICK_CTRL_REG  = 0; // Disable SysTick during setup
    SYSTICK_RELOAD_REG = ticks; // Set reload register
    SYSTICK_CURRENT_REG = 0; // Clear current register
    SYSTICK_CTRL_REG = 0x05; // Enable SysTick with system clock without interrupts

    while((SYSTICK_CTRL_REG & 0x00010000) == 0); // Wait for count flag to be set

    SYSTICK_CTRL_REG = 0; // Disable SysTick
}


/**********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: Interrupt handler for SysTick timer, used to call the
 * callback function
 *********************************************************************/
void SysTick_Handler(void)
{
    if (g_SysTickCallBackPtr != NULL_PTR)
    {
        (*g_SysTickCallBackPtr)();
    }
}


/**********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Ptr2Func - Pointer to the callback function
 * Return Value: None
 * Description: Sets up the SysTick timer callback to be executed in the
 * SysTick Handler
 *********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func)(void))
{
    g_SysTickCallBackPtr = Ptr2Func;
}


/**********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: Stops the SysTick timer
 *********************************************************************/
void SysTick_Stop(void)
{
    SYSTICK_CTRL_REG &= ~0x01; // Clear enable bit to stop SysTick
}


/**********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: Starts or resume the SysTick timer
 *********************************************************************/
void SysTick_Start(void)
{
    SYSTICK_CTRL_REG |= 0x01; // Set enable bit to start SysTick
}


/**********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: De-initializes the SysTick timer
 *********************************************************************/
void SysTick_DeInit(void)
{
    SYSTICK_CTRL_REG = 0; // Disable SysTick
    SYSTICK_RELOAD_REG = 0; // Clear reload register
    SYSTICK_CURRENT_REG = 0; // Clear current register
}
