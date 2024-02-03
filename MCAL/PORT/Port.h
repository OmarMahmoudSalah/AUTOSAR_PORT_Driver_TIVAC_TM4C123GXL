/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Omar Salah
 *
 * Created on: Jan 12, 2024
 *  ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Module ID From Document
 * Port Driver  124*/

/* Define Vendor ID*/
#define PORT_VENDOR_ID    (3000U)

/* Define Module ID*/
#define PORT_MODULE_ID    (124U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/*---------------------------------------------------------------------------------------------*/
/*---------------------------------- Start Includes Section -----------------------------------*/
/*---------------------------------------------------------------------------------------------*/

/* Standard AUTOSAR types */
#include "../../General/Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION!=PORT_AR_RELEASE_MAJOR_VERSION)\
        ||(STD_TYPES_AR_RELEASE_MINOR_VERSION!=PORT_AR_RELEASE_MINOR_VERSION)\
        ||(STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"

#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION!=PORT_AR_RELEASE_MAJOR_VERSION)\
        ||(PORT_CFG_AR_RELEASE_MINOR_VERSION!=PORT_AR_RELEASE_MINOR_VERSION)\
        ||(PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"

#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "../../General/Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                               *
 *****************************************************************************/

/* Service ID for Port_Init */
#define PORT_INIT_SID                                 (uint8)0x00

/* Service ID for Sets the port pin direction */
#define PORT_SET_PIN_DIRECTION_SID                    (uint8)0x01

/* Service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIRECTION_SID               (uint8)0x02

/* Service ID for Port_RefreshPortDirection */
#define PORT_GET_VERSION_INFO_SID                     (uint8)0x03

/* Service ID for  Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID                         (uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/

/*Invalid Port Pin ID requested*/
#define PORT_E_PARAM_PIN                                (uint8)0x0A

/*Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE                   (uint8)0x0B

/*API Port_Init service called with wrong parameter*/
#define PORT_E_PARAM_CONFIG                             (uint8)0x0C

/* API Port_SetPinMode service called with invalid mode */
#define PORT_E_PARAM_INVALID_MODE                       (uint8)0x0D

/* API Port_SetPinMode service called, when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                        (uint8)0x0E

/* API sevice called without module initialization */
#define PORT_E_UNINIT                                   (uint8)0x0F

/* APIs called with a NULL Pointer, Error shall be reported */
#define PORT_E_PARAM_POINTER                            (uint8)0x10

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*Data type for the symbolic name of a port pin. */
typedef uint8 Port_PinType;

/*Data type for the symbolic name of a port pin mode. */
typedef uint8 Port_PinModeType;
/*Name: Port_PinDirectionType
 Type: Enumeration
 Range: PORT_PIN_IN Sets port pin as input.
 PORT_PIN_OUT Sets port pin as output.
 Description: Possible directions of a port pin.
 * */

/*PORT125_Conf*/
typedef enum
{
    PORT_PIN_IN, PORT_PIN_OUT
} Port_PinDirectionType;


/* PORT129_Conf*/
typedef enum
{
    PORT_PIN_LEVEL_LOW, PORT_PIN_LEVEL_HIGH
} PortPinLevelValue;

/*  PORT130_Conf*/

typedef enum
{
    PORT_PIN_MODE_ADC,
    PORT_PIN_MODE_ALT1,
    PORT_PIN_MODE_ALT2,
    PORT_PIN_MODE_ALT3,
    PORT_PIN_MODE_ALT4,
    PORT_PIN_MODE_ALT5,
    PORT_PIN_MODE_ALT6,
    PORT_PIN_MODE_ALT7,
    PORT_PIN_MODE_ALT8,
    PORT_PIN_MODE_ALT9,
    PORT_PIN_MODE_ALT14=14,
    PORT_PIN_MODE_DIO,
} PortPinInitialMode;



/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF, PULL_UP, PULL_DOWN
} Port_InternalResistorType;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct
{
    uint8 port_num;
    uint8 pin_num;
    Port_PinDirectionType direction;
    Port_InternalResistorType resistor;
    PortPinLevelValue initial_value;
    uint8 pinDirectionChangeRuntime;
    uint8 pinModeChangeRuntime;
    PortPinInitialMode mode;
} Port_ConfigPin;

typedef struct Port_ConfigType
{
    Port_ConfigPin Pin[PORT_CONFIGURED_CHANNLES];
} Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

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
 *              - Setup the internal resistor for i/p pin
 ************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr);


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
void Port_SetPinDirection(Port_PinType Pin_Index, Port_PinDirectionType Direction);
#endif

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
void Port_RefreshPortDirection(void);

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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

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
void Port_SetPinMode(Port_PinType Pin_Index, Port_PinModeType Mode);
#endif


/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

#endif /* PORT_H */

