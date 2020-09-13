#include "Button.h"
#include "MotorController.h"
#include "DriveController.h"
#include "LineTraceController.h"
#include "ColorSensor.h"

#include "DriveAction.h"

ActLineTrace gActLineTrace;

static void button_clicked_handler(intptr_t button) {
    static bool linetrace = false;

    switch(button) {
    case ENTER_BUTTON:
        if(linetrace == false) {
            request_action(&gActLineTrace);
            linetrace = true;
        } else {
            gLineTraceController.stop();
            gDriveController.stop(false);
            linetrace = false;
        }
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
