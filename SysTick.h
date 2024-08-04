/******************************************************************************
 *
 * Module: SysTick
 *
 * File Name: SysTick.h
 *
 * Description: Header file for the ARM Cortex M4 SysTick driver
 *
 * Author: Saraa Gomaa
 *
 *******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

/*******************************************************************************
 *                                Inclusions                                   *
 *******************************************************************************/
#include "std_types.h"

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

/**********************************************************************
 * Service Name: SysTick_Init
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: ConfigPtr - Pointer to configuration structure
 * Return Value: None
 * Description: Initializes the SysTick timer with the specified value
 *********************************************************************/
void SysTick_Init(uint16 a_TimeInMilliSeconds);


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
void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds);


/**********************************************************************
 * Service Name: SysTick_Handler
 * Sync/Async: Asynchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: Interrupt handler for SysTick timer, used to call the
 * callback function
 *********************************************************************/
void SysTick_Handler(void);


/**********************************************************************
 * Service Name: SysTick_SetCallBack
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Ptr2Func - Pointer to the callback function
 * Return Value: None
 * Description: Sets up the SysTick timer callback to be executed in the
 * SysTick Handler
 *********************************************************************/
void SysTick_SetCallBack(volatile void (*Ptr2Func) (void));


/**********************************************************************
 * Service Name: SysTick_Stop
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: Stops the SysTick timer
 *********************************************************************/
void SysTick_Stop(void);


/**********************************************************************
 * Service Name: SysTick_Start
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: Starts or resume the SysTick timer
 *********************************************************************/
void SysTick_Start(void);


/**********************************************************************
 * Service Name: SysTick_DeInit
 * Sync/Async: Synchronous
 * Reentrancy: Non-Reentrant
 * Parameters: None
 * Return Value: None
 * Description: De-initializes the SysTick timer
 *********************************************************************/
void SysTick_DeInit(void);

#endif /* SYSTICK_H_ */
