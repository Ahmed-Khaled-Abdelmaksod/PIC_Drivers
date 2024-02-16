/* 
 * File:   MCAL_std_types.h
 * Author: Ahmed Khaled
 *
 * Created on 30 ?????, 2023, 11:11 ?
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

#include"std_libraries.h"
#include"compilor.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;


typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef enum
{
    E_OK,
    E_NOT_OK
}Std_ReturnType;

#endif	/* MCAL_STD_TYPES_H */

