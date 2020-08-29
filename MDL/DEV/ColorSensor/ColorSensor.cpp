#include "ColorSensor.h"
#include "Logger.h"

void colorsensor_initilize() {

}

void colorsensor_task() {
    rgb_raw_t rgb;
    uint8_t reflect;

    ev3_color_sensor_get_rgb_raw(EV3_PORT_1, &rgb);
    reflect = ev3_color_sensor_get_reflect(EV3_PORT_1);

    ColorSensorLog.write(rgb.r, rgb.g, rgb.b, reflect);
}
