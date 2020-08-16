#include "Button.h"
#include "MotorController.h"

extern void drivecontroller_task_start();

static void button_clicked_handler(intptr_t button) {
    static uint32_t left = 400;
    static uint32_t right = 400;
    
    switch(button) {
    case ENTER_BUTTON:
        drivecontroller_task_start();
        break;
    case BACK_BUTTON:
        break;
    case LEFT_BUTTON:
        break;
    case RIGHT_BUTTON:
    	break;
    case UP_BUTTON:
        break;
    case DOWN_BUTTON:
    	break;
    }
}

void button_initialize() {
    ev3_button_set_on_clicked(BACK_BUTTON, button_clicked_handler, BACK_BUTTON);
    ev3_button_set_on_clicked(ENTER_BUTTON, button_clicked_handler, ENTER_BUTTON);
    ev3_button_set_on_clicked(LEFT_BUTTON, button_clicked_handler, LEFT_BUTTON);
    ev3_button_set_on_clicked(RIGHT_BUTTON, button_clicked_handler, RIGHT_BUTTON);
    ev3_button_set_on_clicked(UP_BUTTON, button_clicked_handler, UP_BUTTON);
    ev3_button_set_on_clicked(DOWN_BUTTON, button_clicked_handler, DOWN_BUTTON);
}
