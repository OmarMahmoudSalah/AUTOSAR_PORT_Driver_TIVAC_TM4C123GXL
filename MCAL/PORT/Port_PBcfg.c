/******************************************************************************
 *
 * Module: PORT
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM  Microcontroller - Port Driver
 *
 * Author: Omar Salah
 *
 * Created on: Jan 12, 2024
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/*PB structure used with PORT_Init API */
 const Port_ConfigType Port_Configuration = {
                                                /*PORT A*/
                                                PORT_A,PIN_0,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_1,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_2,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_3,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_4,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_5,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_6,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_A,PIN_7,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                /* Port B */
                                                PORT_B,PIN_0,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_1,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_2,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_3,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_4,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_5,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_6,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_B,PIN_7,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                /* Port C */
                                                PORT_C,PIN_0,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_1,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_2,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_3,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_4,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_5,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_6,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_C,PIN_7,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                /* Port D */
                                                PORT_D,PIN_0,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_1,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_2,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_3,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_4,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_5,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_6,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_D,PIN_7,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                /* Port E */
                                                PORT_E,PIN_0,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_E,PIN_1,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_E,PIN_2,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_E,PIN_3,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_E,PIN_4,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_E,PIN_5,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                /* Port F */
                                                PORT_F,PIN_0,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_F,PIN_1,PORT_PIN_OUT,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,/* LED */
                                                PORT_F,PIN_2,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_F,PIN_3,PORT_PIN_IN,OFF,PORT_PIN_LEVEL_LOW,STD_ON,STD_ON,PORT_PIN_MODE_DIO,
                                                PORT_F,PIN_4,PORT_PIN_IN,PULL_UP,PORT_PIN_LEVEL_HIGH,STD_ON,STD_ON,PORT_PIN_MODE_DIO /*Buttpn*/

 };
