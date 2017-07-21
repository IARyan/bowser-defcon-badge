/* ========================================
 *
 * Red Badge source code. The volunteer badge
 * is used to send encoded morse code message.
 *
 * Author(s): Ryan Grandgenett <rmgrandgenett@unomaha.edu>
 *
 * Eye Color: Red
 * Stage1: Morse Code
 * Stage2: Binary
 * Stage3: Substitution
 * Stage4: Serial
 * Stage5: Organizer
 *
 * Serial: Print the morse code output
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
#include <project.h>
#include <string.h>
#include <stdio.h>
#include "lightlib.h"
#include "togglelib.h"
#include "state.h"
#include "morse.h"
#include "binary.h"
#include "substitution.h"

int main()
{
    /* Enable interrupts (needed for toggles and DEFCONPARTY PWM) */
    CyGlobalIntEnable;
    
    /* Make sure IR_LED and BOARD_LED are off to save battery */
    turn_off(IR_LED);
    turn_off(BOARD_LED);
    
    /* Enable toggle buttons */
    enable_toggle_interrupts();

    /* Initialize LEDs to off and default color value */
    init_led(RED);
      
    /* Set the default state to Defcon Party */
    badge_state = DEFCONPARTY;
    
    /* Start the Defcon Party Time PWM */
    PWM_Defcon_Start();
    
    for(;;)
    {           
        switch(badge_state) {
        case MORSE:
            morse_message(LEFT_RIGHT_LED, "DEFCON25");
        break;
        case BINARY:
            binary_message("DEFCON25");
        break;
        case DEFCONPARTY:
            CySysPmSleep();
        break;
        }      
    }
}