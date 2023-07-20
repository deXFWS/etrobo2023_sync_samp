//ColorSensor.h

#ifndef EV3_UNIT_COLORSENSOR_H_
#define EV3_UNIT_COLORSENSOR_H_

#include "ColorSensor.h"

class ColorMonitor{
public:
    explicit ColorMonitor(const ev3api::ColorSensor& colorSensor);

    typedef struct{
        float h;
        float s;
        float v;
    } hsv_val_t;

    typedef struct{
        int16_t r;
        int16_t g;
        int16_t b;
    } offset_val_t;

    typedef struct{
        float r;
        float g;
        float b;
    } cool_val_t;

    //色判定
    bool Black_HSV;
    bool White_HSV;
    bool Blue_HSV;

    void getRGB; //debug用公開関数
    void getRAWColor;
    void getHSVValue;
    void ColorCalib;

}

#endif

