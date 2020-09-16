#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include "ev3api.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}

extern void	colorsensor_task();

struct ColorSensorData {
    rgb_raw_t rgb;
    uint8_t   reflect;
};

#define COLORSENSOR_BUFFER_SIZE 100;
class ColorSensor {
private:
    ColorSensorData mData;
public:
    ColorSensor();
    void get(ColorSensorData* data);
    void runTask();
};

extern ColorSensor gColorSensor;

#endif // __cplusplus
#endif // COLORSENSOR_H