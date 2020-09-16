#include "ColorSensor.h"
#include "Logger.h"

ColorSensor gColorSensor;

void colorsensor_initilize() {

}

void colorsensor_task() {
}

ColorSensor::ColorSensor() {
    mData.rgb.r = 0;
    mData.rgb.g = 0;
    mData.rgb.b = 0;
    mData.reflect = 0;
}

void ColorSensor::get(ColorSensorData* data) {
    *data = mData;
}

void ColorSensor::runTask() {
    ev3_color_sensor_get_rgb_raw(EV3_PORT_1, &mData.rgb);
    mData.reflect = ev3_color_sensor_get_reflect(EV3_PORT_1);
}
