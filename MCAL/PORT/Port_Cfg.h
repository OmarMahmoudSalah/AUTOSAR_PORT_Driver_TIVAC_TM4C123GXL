/******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Omar Salah
 *
 * Created on: Jan 12 2024
 ******************************************************************************/

#ifndef MCAL_PORT_PORT_CFG_H_
#define MCAL_PORT_PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/*   */

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                   (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                   (STD_ON)

/* Pre-compile option for Set Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API              (STD_ON)

/* Pre-compile option for Set Pin Mode API */
#define PORT_SET_PIN_MODE_API                   (STD_ON)

/* MCU Specific Static Configurations            */
/* Number of the configured Dio Channels */
#define PORT_CONFIGURED_CHANNLES                 (43U)

/* Ports */

#define PORT_A                                    (0U)
#define PORT_B                                    (1U)
#define PORT_C                                    (2U)
#define PORT_D                                    (3U)
#define PORT_E                                    (4U)
#define PORT_F                                    (5U)

#define PIN_0                                     (0U)
#define PIN_1                                     (1U)
#define PIN_2                                     (2U)
#define PIN_3                                     (3U)
#define PIN_4                                     (4U)
#define PIN_5                                     (5U)
#define PIN_6                                     (6U)
#define PIN_7                                     (7U)

/*
 * PORT207: These symbolic names for the individual port pins (e.g. PORT_A_PIN_0)
 shall be defined in the configuration tool.
 PORT076: The PORT Driver module’s implementer shall define symbolic names in
 the file Port_Cfg.h */
enum PortsPinsIndex
{
    /*PORT A*/
    PORTA_PIN_0,
    PORTA_PIN_1,
    PORTA_PIN_2,
    PORTA_PIN_3,
    PORTA_PIN_4,
    PORTA_PIN_5,
    PORTA_PIN_6,
    PORTA_PIN_7,
    /*PORT B*/
    PORTB_PIN_0,
    PORTB_PIN_1,
    PORTB_PIN_2,
    PORTB_PIN_3,
    PORTB_PIN_4,
    PORTB_PIN_5,
    PORTB_PIN_6,
    PORTB_PIN_7,
    /*PORT C*/
    PORTC_PIN_0,
    PORTC_PIN_1,
    PORTC_PIN_2,
    PORTC_PIN_3,
    PORTC_PIN_4,
    PORTC_PIN_5,
    PORTC_PIN_6,
    PORTC_PIN_7,
    /*PORT D*/
    PORTD_PIN_0,
    PORTD_PIN_1,
    PORTD_PIN_2,
    PORTD_PIN_3,
    PORTD_PIN_4,
    PORTD_PIN_5,
    PORTD_PIN_6,
    PORTD_PIN_7,
    /*PORT E*/
    PORTE_PIN_0,
    PORTE_PIN_1,
    PORTE_PIN_2,
    PORTE_PIN_3,
    PORTE_PIN_4,
    PORTE_PIN_5,
    /*PORT F*/
    PORTF_PIN_0,
    PORTF_PIN_1,
    PORTF_PIN_2,
    PORTF_PIN_3,
    PORTF_PIN_4,
};

#endif /* MCAL_PORT_PORT_CFG_H_ */

