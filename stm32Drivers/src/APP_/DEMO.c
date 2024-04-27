#include"DEMO.h"



u8 arr[9]= {1,1,0,1,0,1,0,1,};
// 1 pressed , 0 not pressed 
/*  ["MODE"0,"START/STOP"1,"Pause/Continue"2,
     "UP"3,"DOWN"4,"LEFT"5,
     "RIGHT"6,"EDIT"7,"OK"8]*/

Clk_t current_time = {0, 0, 0};
Date_t current_date = {11, 4, 2024};
void Clock(void)
{
   
u8 current_X =0; //col
u8 Current_Y =0; //rows 
u8 current_edit_position=0; 

if(arr[0]==0)
{

do
{
    LCD_gointo_X_Y(current_X++,Current_Y);

}while(arr[6]); // right


while (arr[8] == 0) { // while OK button is not pressed      
LCD_gointo_X_Y(current_X,2); //sec row "the clock"  hours / min / sec 

if (arr[3] == 0)
 { // UP button pressed
            if (current_edit_position == 0)
             { // Editing hours
                current_time.hours = (current_time.hours + 1) % 24; // Increment hours, looping from 23 to 0
            } else if (current_edit_position == 1) { // Editing minutes
                current_time.minutes = (current_time.minutes + 1) % 60; // Increment minutes, looping from 59 to 0
            } else if (current_edit_position == 2) { // Editing seconds
               current_time.seconds = (current_time.seconds + 1) % 60; // Increment seconds, looping from 59 to 0
            }
   
        }
       else if (arr[4] == 0) // DOWN button pressed
        { 
             if (current_edit_position == 0)
             { // Editing hours
                current_time.hours = (current_time.hours - 1) % 24; // Increment hours, looping from 23 to 0
            } else if (current_edit_position == 1) { // Editing minutes
                current_time.minutes = (current_time.minutes - 1) % 60; // Increment minutes, looping from 59 to 0
            } else if (current_edit_position == 2) { // Editing seconds
               current_time.seconds = (current_time.seconds - 1) % 60; // Increment seconds, looping from 59 to 0
            }
        
        }
       else if (arr[5] == 0) { // LEFT button pressed
            current_edit_position = (current_edit_position + 2) % 3; // Move left in editing position (0 -> 2, 1 -> 0, 2 -> 1)
        } 
      else if (arr[6] == 0) { // RIGHT button pressed
            current_edit_position = (current_edit_position + 1) % 3; // Move right in editing position (0 -> 1, 1 -> 2, 2 -> 0)
        }
    }
}



}


void Display (void)
{

}




//10ms
void ReadSwitch(void)
{


}