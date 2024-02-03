/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Omar Salah
 *
 * Created on: Jan 13, 2024
 ******************************************************************************/


/***************************************************************************
 *                        Pre Processors Directives                        *
 ***************************************************************************/
#define AccesPtr(X)  *(volatile uint32 *) ( (volatile uint8 *) X )

#include "Port.h"

/*PORT_DEV_ERROR_DETECT */

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "../../SERVICE/Det.h"

/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

#include "../../General/tm4c123gh6pm_registers.h"


STATIC const Port_ConfigPin * Port_Channel_Config  = NULL_PTR;
STATIC volatile uint8 PORT_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_Init(const Port_ConfigType * ConfigPtr )
{
    volatile uint8 index;
    volatile uint32 delay;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
        /* check if the input configuration pointer is not a NULL_PTR */
        if(ConfigPtr == NULL_PTR)
        {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
        PORT_E_PARAM_CONFIG);
        }
        else
        {   /* Do Nothing */    }
    #endif

        /*
         * Set the module state to initialized and point to the PB configuration structure using a global pointer.
         * This global pointer is global to be used by other functions to read the PB configuration structures
         */
        Port_Channel_Config=ConfigPtr->Pin;

    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    for (index = 0; index < PORT_CONFIGURED_CHANNLES; index++)
    {

    switch (Port_Channel_Config[index].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        SYSCTL_RCGCGPIO_REG |= (1 << Port_Channel_Config[index].port_num);
        delay = SYSCTL_RCGCGPIO_REG;


        if (((Port_Channel_Config[index].port_num == 3) && (Port_Channel_Config[index].pin_num == 7)) || ((Port_Channel_Config[index].port_num == 5) && (Port_Channel_Config[index].pin_num == 0)))
        {
            /* PD7 or PF0 */
            *(volatile uint32*) ((volatile uint8*) PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B; /* Unlock the GPIOCR register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET),Port_Channel_Config[index].pin_num); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else if ((Port_Channel_Config[index].port_num == 2) && (Port_Channel_Config[index].pin_num <= 3)) /* PC0 to PC3 */
        {
            continue;
            /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }

        if(Port_Channel_Config[index].direction == PORT_PIN_OUT)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[index].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

            if(Port_Channel_Config[index].initial_value == PORT_PIN_LEVEL_HIGH)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Channel_Config[index].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
            }
            else
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Channel_Config[index].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
            }
        }
        else if(Port_Channel_Config[index].direction == PORT_PIN_IN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channel_Config[index].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

            if(Port_Channel_Config[index].resistor == PULL_UP)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channel_Config[index].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
            }
            else if(Port_Channel_Config[index].resistor == PULL_DOWN)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channel_Config[index].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
            }
            else
            {
                /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channel_Config[index].pin_num);
                /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channel_Config[index].pin_num);
            }
        }
        else
        {
            /* Do Nothing */
        }

        if (Port_Channel_Config[index].mode == PORT_PIN_MODE_DIO)
        {
        /* Setup the pin mode as GPIO */

        /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[index].pin_num);
        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[index].pin_num);
        /* Clear the PMCx bits for this pin */
        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Channel_Config[index].pin_num * 4));
        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[index].pin_num);

        }
        else if (Port_Channel_Config[index].mode == PORT_PIN_MODE_ADC)
        {
        /* Setup the pin mode as ADC */

        /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
        SET_BIT(AccesPtr(PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Channel_Config[index].pin_num);
        /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
        CLEAR_BIT(AccesPtr(PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET),Port_Channel_Config[index].pin_num);
        /* Clear the PMCx bits for this pin */
        AccesPtr(PortGpio_Ptr+PORT_CTL_REG_OFFSET) &= ~(0X0000000F << Port_Channel_Config[index].pin_num * 4 );
        /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
        CLEAR_BIT(AccesPtr(PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Channel_Config[index].pin_num);
        }
        else
        {
        /* Setup the pin mode as Any Alternative Mode */

        /* Set the corresponding bit in the GPIODEN register to Enable digital functionality on this pin */
         SET_BIT(AccesPtr(PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Channel_Config[index].pin_num);

         /* Clear the corresponding bit in the GPIOAMSEL register to Disable analog functionality on this pin */
         CLEAR_BIT(AccesPtr(PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Channel_Config[index].pin_num);

         /* Set the PMCx bits for this pin */
          AccesPtr(PortGpio_Ptr+PORT_CTL_REG_OFFSET) |= ((Port_Channel_Config[index].mode & 0X0000000F) << Port_Channel_Config[index].pin_num * 4 );

        /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
         SET_BIT(AccesPtr(PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET),Port_Channel_Config[index].pin_num);
        }

    }
    PORT_Status = PORT_INITIALIZED;
    return;
}

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
    volatile uint8 index;
    volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    boolean error = FALSE;

    /* API service called prior to module initialization*/
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_REFRESH_PORT_DIRECTION_SID,
                        PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */

    }
    if (FALSE == error)
    {
        for (index = 0; index < PORT_CONFIGURED_CHANNLES; index++)
        {

            /* PORT061: The function Port_RefreshPortDirection shall exclude those port
             pins from refreshing that are configured as ‘pin direction changeable during runtime‘. */
            if (Port_Channel_Config[index].pinDirectionChangeRuntime == STD_ON)
            {
                /*Skip Iteration */
                continue;

            }

            else if (Port_Channel_Config[index].direction == PORT_PIN_OUT)
            {
                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET),
                        Port_Channel_Config[index].pin_num);
            }

            else if (Port_Channel_Config[index].direction == PORT_PIN_IN)
            {
                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                CLEAR_BIT(
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET),
                        Port_Channel_Config[index].pin_num);

            }
            else
            {
                /* Do Nothing */
            }

        }

    }

}

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number, Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)

void Port_SetPinMode(Port_PinType Pin_Index, Port_PinModeType Mode)
{
    volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    /* API service called prior to module initialization*/
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
        PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */

    }

    /* Port Pin Mode passed not valid*/
    if ((Mode > PORT_PIN_MODE_DIO)
            || ((Mode > PORT_PIN_MODE_ALT9 && Mode < PORT_PIN_MODE_ALT14)))
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
        PORT_E_PARAM_INVALID_MODE);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */

    }

    /* Incorrect Port Pin ID passed */
    if (Pin_Index >= PORT_CONFIGURED_CHANNLES)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
        PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */

    }

    /*Port Pin Mode Not configured as changeable */
    if (Port_Channel_Config[Pin_Index].pinModeChangeRuntime == STD_ON)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID,
        PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;

    }
    else
    {
        /* Do Nothing */
    }

    if (FALSE == error)
    {
        switch (Port_Channel_Config[Pin_Index].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        if (Port_Channel_Config[Pin_Index].mode == PORT_PIN_MODE_DIO)
                {
                /* Setup the pin mode as GPIO */

                /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channel_Config[Pin_Index].pin_num);
                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channel_Config[Pin_Index].pin_num);
                /* Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Channel_Config[Pin_Index].pin_num * 4));
                /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channel_Config[Pin_Index].pin_num);

                }
                else if (Port_Channel_Config[Pin_Index].mode == PORT_PIN_MODE_ADC)
                {
                /* Setup the pin mode as ADC */

                /* Set the corresponding bit in the GPIOAMSEL register to Enable analog functionality on this pin */
                SET_BIT(AccesPtr(PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Channel_Config[Pin_Index].pin_num);
                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(AccesPtr(PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET),Port_Channel_Config[Pin_Index].pin_num);
                /* Clear the PMCx bits for this pin */
                AccesPtr(PortGpio_Ptr+PORT_CTL_REG_OFFSET) &= ~(0X0000000F << Port_Channel_Config[Pin_Index].pin_num * 4 );
                /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
                CLEAR_BIT(AccesPtr(PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Channel_Config[Pin_Index].pin_num);
                }
                else
                {
                /* Setup the pin mode as Any Alternative Mode */

                /* Set the corresponding bit in the GPIODEN register to Enable digital functionality on this pin */
                 SET_BIT(AccesPtr(PortGpio_Ptr+PORT_DIGITAL_ENABLE_REG_OFFSET),Port_Channel_Config[Pin_Index].pin_num);

                 /* Clear the corresponding bit in the GPIOAMSEL register to Disable analog functionality on this pin */
                 CLEAR_BIT(AccesPtr(PortGpio_Ptr+PORT_ANALOG_MODE_SEL_REG_OFFSET),Port_Channel_Config[Pin_Index].pin_num);

                 /* Set the PMCx bits for this pin */
                  AccesPtr(PortGpio_Ptr+PORT_CTL_REG_OFFSET) |= ((Port_Channel_Config[Pin_Index].mode & 0X0000000F) << Port_Channel_Config[Pin_Index].pin_num * 4 );

                /* Enable Alternative function for this pin by Set the corresponding bit in GPIOAFSEL register */
                 SET_BIT(AccesPtr(PortGpio_Ptr+PORT_ALT_FUNC_REG_OFFSET),Port_Channel_Config[Pin_Index].pin_num);
        }

    }

}

    #endif

#endif
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Sets the port pin direction.
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin_Index, Port_PinDirectionType Direction)
{
    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)

    /* API service called prior to module initialization*/
    if (PORT_NOT_INITIALIZED==PORT_Status){
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }

    /* Incorrect Port Pin ID passed */
    if (Pin_Index >= PORT_CONFIGURED_CHANNLES)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
        PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* Do Nothing */
    }

       /*Port Pin Direction not configured as changeable */
    if (Port_Channel_Config[Pin_Index].pinDirectionChangeRuntime == STD_ON)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID,
        PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;

    }
    else
    {
        /* Do Nothing */
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {
        switch (Port_Channel_Config[Pin_Index].port_num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32*) GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        if ((Port_Channel_Config[Pin_Index].port_num == 2)
                && (Port_Channel_Config[Pin_Index].pin_num <= 3)) /* PC0 to PC3 */
        {
            return;
            /* Do Nothing ...  this is the JTAG pins */
        }

        if (Port_Channel_Config[Pin_Index].direction == PORT_PIN_OUT)
        {
            /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET),
                    Port_Channel_Config[Pin_Index].pin_num);
        }
        else if (Port_Channel_Config[Pin_Index].direction == PORT_PIN_IN)
        {
            /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
            CLEAR_BIT(
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET),
                    Port_Channel_Config[Pin_Index].pin_num);
        }

    }

}
#endif

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if (NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,PORT_GET_VERSION_INFO_SID,PORT_E_PARAM_POINTER);
    }
    else
        /* Do Nothing */
#endif
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16) PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16) PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8) PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8) PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8) PORT_SW_PATCH_VERSION;
    }

}
#endif

