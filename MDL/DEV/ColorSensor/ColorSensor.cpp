#include "ColorSensor.h"
#include "Logger.h"

void colorsensor_task(intptr_t exinf) {
    rgb_raw_t rgb;
    uint8_t reflect;
    while(true) {
        ev3_color_sensor_get_rgb_raw(EV3_PORT_1, &rgb);
        reflect = ev3_color_sensor_get_reflect(EV3_PORT_1);

        ColorSensorLog.write(rgb.r, rgb.g, rgb.b, reflect);
        tslp_tsk(100 * 1000); /* マイクロ秒で指定 */
    }
}

void colorsensor_task_start() {
    act_tsk(COLORSENSOR_TASK);
}
