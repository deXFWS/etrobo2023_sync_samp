#ifndef EV3_UNIT_COLORSENSOR_H_
#define EV3_UNIT_COLORSENSOR_H_

using namespace ev3api;

class ColorMonitor{
public:
    void init();

    /////↓RGB取得/////
    rgb_raw_t rgb;
    ColorSensor solorSensor;
    uint16_t Red;
    uint16_t Green;
    uint16_t Blue;
    /////↑RGB取得/////

    explicit ColorMonitor();

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
    } coef_val_t;

    //色判定
    bool Black_HSV();
    bool White_HSV();
    bool Blue_HSV();

    void getRGB(); //debug用公開関数
    void getRAWColor(rgb_raw_t & rgb);
    void getHSVValue(hsv_val_t & hsv);
    void ColorCalib(offset_val_t offset, coef_val_t coefficient);

private:
    float mRed;
    float mGreen;
    float mBlue;

};

#endif

