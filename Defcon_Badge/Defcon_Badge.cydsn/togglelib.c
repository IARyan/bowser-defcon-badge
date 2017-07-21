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
#include <project.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "lightlib.h"
#include "togglelib.h"
#include "state.h"

/* Signal handler for left toggle press */
CY_ISR( SWL_Handler ) { 
    uint8 current_color; 
    uint32 rand_color; 
    
    /* Make sure Defcon party time PWM is off */
    PWM_Defcon_Stop();
    
   /* Get the current color of the leds and pick a new one */
   current_color = get_color(LEFT_LED);
   rand_color = (rand() % 7) + 1;
    
    while (current_color == rand_color){
        rand_color = (rand() % 7) + 1;
    }

    init_led(rand_color);
    
    /* Badge State is MORSE */
    badge_state = MORSE;
    
    /* Clear interrupt */
    SWL_ClearInterrupt();
}

/* Signal handler for right toggle press */
CY_ISR( SWR_Handler ) {
    uint8 current_color; 
    uint32 rand_color; 
    
    /* Make sure Defcon party time PWM is off */
    PWM_Defcon_Stop();
    
   /* Get the current color of the leds and pick a new one */
   current_color = get_color(LEFT_LED);
   rand_color = (rand() % 7) + 1;
    
    while (current_color == rand_color){
        rand_color = (rand() % 7) + 1;
    }

    init_led(rand_color);
    
    /* Badge State is BINARY_MESSAGE */
    badge_state = BINARY;
    
   /* Clear interrupt */
    SWR_ClearInterrupt();
}

/* Signal handler for on board toggle press */
CY_ISR( SWB_Handler ) {
    badge_state = DEFCONPARTY;
    
    /* Start the Defcon Party Time PWM */
    PWM_Defcon_Start();
        
    /* Clear interrupt */
    SWB_ClearInterrupt();
}

/* Signal handler for organizer lights */
CY_ISR( DEFCON_Handler ) {
    /* Generate random eye colors */
    uint8 current_color_left = get_color(LEFT_LED);
    uint8 current_color_right = get_color(RIGHT_LED);
    uint32 rand_num_left = (rand() % 7) + 1;
    uint32 rand_num_right = (rand() % 7) + 1;
    
    while (current_color_left == rand_num_left){
        rand_num_left = (rand() % 7) + 1;
    }
    
   while (current_color_right == rand_num_right){
        rand_num_right = (rand() % 7) + 1;
    }
    
    set_color(LEFT_LED, rand_num_left);
    set_color(RIGHT_LED, rand_num_right);
    turn_off(LEFT_RIGHT_LED);
    turn_on(LEFT_RIGHT_LED);
    
    DEFCON_Int_ClearPending();
    PWM_Defcon_ReadStatusRegister();
}

void enable_toggle_interrupts() {
    /* Setup toggle interrupts  */
    SWB_Int_StartEx( SWB_Handler );
    SWL_Int_StartEx( SWL_Handler );
    SWR_Int_StartEx( SWR_Handler );
    DEFCON_Int_StartEx( DEFCON_Handler );
    /* Seed random */
    srand(time(NULL));
}