#include "Button.h"

static void button_clicked_handler(intptr_t button) {
    switch(button) {
    case ENTER_BUTTON:
        syslog(LOG_NOTICE, "Enter button clicked.");
        break;
    case BACK_BUTTON:
        syslog(LOG_NOTICE, "Back button clicked.");
        break;
    case LEFT_BUTTON:
    	syslog(LOG_NOTICE, "Left button clicked.");
        break;
    case RIGHT_BUTTON:
    	syslog(LOG_NOTICE, "Right button clicked.");
        break;
    case UP_BUTTON:
    	syslog(LOG_NOTICE, "Up button clicked.");
        break;
    case DOWN_BUTTON:
    	syslog(LOG_NOTICE, "Down button clicked.");
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
