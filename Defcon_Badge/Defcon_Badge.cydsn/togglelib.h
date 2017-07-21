/* ========================================
 *
 * Copyright Nullify, 2016
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF NULLIY.
 *
 * ========================================
*/
#ifndef TOGGLELIB_H_   /* Include guard */
#define TOGGLELIB_H_
#include <project.h>
#include "lightlib.h"

/* Toggle Flags */
#define LEFT_TOGGLE 1
#define RIGHT_TOGGLE 2
#define BOARD_TOGGLE 3

/* Toggle delay after button press (milliseconds) */
#define TOGGLE_DELAY 150
    
/* Function declarations */
void enable_toggle_interrupts();

#endif // TOGGLELIB_H_