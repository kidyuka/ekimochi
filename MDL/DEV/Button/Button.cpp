#include "Button.h"
#include "MotorController.h"
#include "DriveController.h"
#include "LineTraceController.h"
#include "ColorSensor.h"

static void button_clicked_handler(intptr_t button) {
    static uint32_t left = 400;
    static uint32_t right = 400;
    
    switch(button) {
    case ENTER_BUTTON:

        gLineTraceController.setSpeed(400);
        gLineTraceController.start();
        //gDriveController.reqTurn(100);
        //gDriveController.setSpeed(500);
        //gDriveController.setSteer(0);
        break;
    case BACK_BUTTON:
        drivecontroller_task_start();
        colorsensor_task_start();
        break;
    case LEFT_BUTTON:
        gLineTraceController.stop(false);
        gDriveController.setSpeed(350);
        gDriveController.setCurvature(-300);
        break;
    case RIGHT_BUTTON:
        gLineTraceController.stop(false);
        gDriveController.setSpeed(350);
        gDriveController.setCurvature(300);
    	break;
    case UP_BUTTON:
        gDriveController.setSpeed(500);
        gDriveController.reqTurn(1);
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
