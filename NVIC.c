/******************************************************************************
 *
 * Module: NVIC
 *
 * File Name: NVIC.c
 *
 * Description: Source file for the ARM Cortex M4 NVIC driver
 *
 * Author: Saraa Gomaa
 *
 *******************************************************************************/

#include "NVIC.h"
#include "tm4c123gh6pm_registers.h"

/*******************************************************************************
 *                           Function Definitions                              *
 *******************************************************************************/
/**********************************************************************
 * Service Name: NVIC_EnableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: IRQ_Num - IRQ number to be enabled
 * Return Value: None
 * Description: Function to enable the interrupt request for the specified IRQ.
 *********************************************************************/
void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num < 32)
    {
        NVIC_EN0_REG |= (1 << IRQ_Num); //Enable IRQ in NVIC Enable Register 0
    }
    else if (IRQ_Num < 64)
    {
        NVIC_EN1_REG |= (1 << (IRQ_Num - 32)); //Enable IRQ in NVIC Enable Register 1
    }
    else if (IRQ_Num < 96)
    {
        NVIC_EN2_REG |= (1 << (IRQ_Num - 64)); //Enable IRQ in NVIC Enable Register 2
    }
    else if (IRQ_Num < 128)
    {
        NVIC_EN3_REG |= (1 << (IRQ_Num - 96)); //Enable IRQ in NVIC Enable Register 3
    }
    else
    {
        //Handle the error or unsupported IRQ number
    }
}

/**********************************************************************
 * Service Name: NVIC_DisableIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: IRQ_Num - IRQ number to be disabled
 * Return Value: None
 * Description: Function to disable the interrupt request for the specified IRQ.
 *********************************************************************/
void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num)
{
    if (IRQ_Num < 32)
        {
            NVIC_DIS0_REG |= (1 << IRQ_Num); //Disable IRQ in NVIC Disable Register 0
        }
        else if (IRQ_Num < 64)
        {
            NVIC_DIS1_REG |= (1 << (IRQ_Num - 32)); //Disable IRQ in NVIC Disable Register 1
        }
        else if (IRQ_Num < 96)
        {
            NVIC_DIS2_REG |= (1 << (IRQ_Num - 64)); //Disable IRQ in NVIC Disable Register 2
        }
        else if (IRQ_Num < 128)
        {
            NVIC_DIS3_REG |= (1 << (IRQ_Num - 96)); //Disable IRQ in NVIC Disable Register 3
        }
        else
        {
            //Handle the error or unsupported IRQ number
        }
}


/**********************************************************************
 * Service Name: NVIC_SetPriorityIRQ
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: IRQ_Num - IRQ number for which priority is to be set
 *             IRQ_Priority - Priority level to be assigned to the specified IRQ
 * Return Value: None
 * Description: Function to set the priority level for the specified IRQ.
 *********************************************************************/
void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority)
{
        //Determine which NVIC priority register to use
        uint8 registerIndex = IRQ_Num / 4; //Each priority register handles 4 IRQs
        uint8 irqPos = IRQ_Num % 4; //Position within the register (0 to 3)
        //Base address of the NVIC priority registers
        volatile uint32 *NVIC_PRI_REG = (volatile uint32 *)0xE000E400;
        //Calculate the specific priority register address
        volatile uint32 *targetReg = NVIC_PRI_REG + registerIndex;
        //Determine bit offset based on IRQ position within the register
        uint8 bitOffset = 0;
        switch (irqPos)
        {
            case 0: //INTA (Bits 5 to 7)
                bitOffset = 5;
                break;
            case 1: //INTB (Bits 13 to 15)
                bitOffset = 13;
                break;
            case 2: //INTC (Bits 21 to 23)
                bitOffset = 21;
                break;
            case 3: //INTD (Bits 29 to 31)
                bitOffset = 29;
                break;
        }
        //Mask to clear the 3 bits for the specific IRQ
        uint32 mask = 0x7; // Mask for 3 bits of priority
        //Clear the bits for the specific IRQ
        *targetReg = (*targetReg & ~(mask << bitOffset));
        //Set the new priority for the IRQ
        *targetReg |= (IRQ_Priority << bitOffset);
}


/**********************************************************************
 * Service Name: NVIC_EnableException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Exception_Num - Exception number to be enabled
 * Return Value: None
 * Description: Function to enable the specified exception in the NVIC.
 *********************************************************************/
void NVIC_EnableException(NVIC_ExceptionType Exception_Num)
{
    /*
     * Check the type of exception specified by Exception_Num.
     * Depending on the exception type, set the corresponding bit in the
     * System Handler Control and State Register (SYSHNDCTRL) to enable the
     * Exception handling.
     */
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            //Enable memory management fault exception
            NVIC_SYSTEM_SYSHNDCTRL |= MEM_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            //Enable bus fault exception
            NVIC_SYSTEM_SYSHNDCTRL |= BUS_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            //Enable usage fault exception
            NVIC_SYSTEM_SYSHNDCTRL |= USAGE_FAULT_ENABLE_MASK;
            break;
        default:
            /* Other exceptions cannot be enabled/disabled */
            break;
    }
}


/**********************************************************************
 * Service Name: NVIC_DisableException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Exception_Num - Exception number to be disabled
 * Return Value: None
 * Description: Function to disable the specified exception in the NVIC.
 *********************************************************************/
void NVIC_DisableException(NVIC_ExceptionType Exception_Num)
{
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            //Disable memory management fault exception
            NVIC_SYSTEM_SYSHNDCTRL &= ~MEM_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            //Disable bus fault exception
            NVIC_SYSTEM_SYSHNDCTRL &= ~BUS_FAULT_ENABLE_MASK;
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            //Disable usage fault exception
            NVIC_SYSTEM_SYSHNDCTRL &= ~USAGE_FAULT_ENABLE_MASK;
            break;
        default:
            /* Other exceptions cannot be enabled/disabled */
            break;
    }
}


/**********************************************************************
 * Service Name: NVIC_SetPriorityException
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters: Exception_Num - Exception number for which priority is to be set
 *             Exception_Priority - Priority level to be assigned to the specified exception
 * Return Value: None
 * Description: Function to set the priority level for the specified exception.
 *********************************************************************/
void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority)
{
    /*
     * Check the type of exception specified by Exception_Num.
     * Depending on the exception type, set the priority by modifying
     * The corresponding priority register.
     */
    switch (Exception_Num)
    {
        case EXCEPTION_MEM_FAULT_TYPE:
            //Set the priority for memory management fault exception
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~MEM_FAULT_PRIORITY_MASK) | (Exception_Priority << MEM_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_BUS_FAULT_TYPE:
            //Set the priority for bus fault exception
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~BUS_FAULT_PRIORITY_MASK) | (Exception_Priority << BUS_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_USAGE_FAULT_TYPE:
            //Set the priority for usage fault exception
            NVIC_SYSTEM_PRI1_REG = (NVIC_SYSTEM_PRI1_REG & ~USAGE_FAULT_PRIORITY_MASK) | (Exception_Priority << USAGE_FAULT_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_SVC_TYPE:
            //Set the priority for supervisor call (SVC) exception
            NVIC_SYSTEM_PRI2_REG = (NVIC_SYSTEM_PRI2_REG & ~SVC_PRIORITY_MASK) | (Exception_Priority << SVC_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_DEBUG_MONITOR_TYPE:
            //Set the priority for debug monitor exception
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~DEBUG_MONITOR_PRIORITY_MASK) | (Exception_Priority << DEBUG_MONITOR_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_PEND_SV_TYPE:
            //Set the priority for PendSV (pendable service call) exception
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~PENDSV_PRIORITY_MASK) | (Exception_Priority << PENDSV_PRIORITY_BITS_POS);
            break;
        case EXCEPTION_SYSTICK_TYPE:
            //Set the priority for SysTick timer exception
            NVIC_SYSTEM_PRI3_REG = (NVIC_SYSTEM_PRI3_REG & ~SYSTICK_PRIORITY_MASK) | (Exception_Priority << SYSTICK_PRIORITY_BITS_POS);
            break;
        default:
            /* Other exceptions cannot have their priority set */
            break;
    }
}
