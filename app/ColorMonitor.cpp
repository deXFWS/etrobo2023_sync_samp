#include "ColorSensor.h"

// #ifdef robo_no,,,

//定数宣言
const float ColorMonitor::BLACK_JDG = 10.0f;
const float ColorMonitor::WHITE_JDG = 50.0f;
const float ColorMonitor::BLUE_JDG = 50.0f;

// #endif robo_no,,,

/*
コンストラクタ
*/
ColorMonitor::ColorMonitor(const ev3api::ColorSensor& colorSensor)
            :mColorSensor(colorSensor),
             mBlack(10.0f),
             mWhite(50.0f),
             mBlue(50.0f){

}

/*
カラーセンサ
*/

/* 反射光は使用しないため無効化
int8_t getBrightness() constz{
    return mColorSensor.getBrightness(); //反射光の強さ(0-100)
}
*/

//黒色判定
bool ColorMonitor::Black_HSV(){
    bool jdg_val;

    calcHSV();
    
    //↓の数値はあてずっぽうなので実機で計測したい
    if((loc_hsv.h < 0.40f) && (loc_hsv.s < 0.1f)){
        jdg_val = true;
    }else{
        jdg_val = false;
    }
    return jdg_val;
}

//白色判定
bool ColorMonitor::White_HSV(){
    bool jdg_val;

    calcHSV();
    
    //↓の数値はあてずっぽうなので実機で計測したい
    if((loc_hsv.h > 0.40f) && (loc_hsv.s > 0.1f)){
        jdg_val = true;
    }else{
        jdg_val = false;
    }
    return jdg_val;
}

//青色判定
bool ColorMonitor::Blue_HSV(){
    bool jdg_val;

    calcHSV();
    
    //↓の数値はあてずっぽうなので実機で計測したい
    if((loc_hsv.h > 0.30f) && (loc_hsv.h < 0.33f)){
        jdg_val = true;
    }else{
        jdg_val = false;
    }
    return jdg_val;
}

//キャリブレーションを行い
//黒と白の時のrgb値をオフセットする
void ColorMonitor::getRGB(){
    mColorSensor.getRAWColor(rgb_val);

    //start_calivration
    mRed = ((float)(rgb_val.r - offsetBlack.r))*coefficientWhite.r;
    mGreen = ((float)(rgb_val.g - offsetBlack.g))*coefficientWhite.g;
    mBlue = ((float)(rgb_val.b - offsetBlack.b))*coefficientWhite.b;
}

void ColorMonitor::getRAWColor(rgb_raw_t & rgb){
    mColorSensor.getRAWColor(rgb_val);

    rgb.r = rgb_val.r;
    rgb.g = rgb_val.g;
    rgb.b = rgb_val.b;
}

//
void ColorMonitor::getHSVValue(hsv_val_t & hsv){
    calcHSV();
    hsv = loc_hsv;
}

//RGB→HSV変換処理
//calcHSV();で
//loc_hsv.h, loc_hsv.s, loc_hsv.vとして呼び出し
void ColorMonitor::calcHSV(){
    getRGB();
    float r,g,b;
    r = (float)(mRed)/100.0f;
    g = (float)(mGreen)/100.0f;
    b = (float)(mBlue)/100.0f;

    float max = r > g ? r : g;
    max = max > b ? max : b;

    float min = r < g ? r : g;
    min = min > b ? min : b;

    float h = max - min;
    loc_hsv.s = h;

    if(max != 0.0f){
        loc_hsv.s /= max; //Saturation 彩度
    }
    if(h > 0.0f){
        if(max == r){
            h = (g - b)/h;
            if(h < 0.0f){
                h += 6.0f;
            }
        }else if(max == g){
            h = 2.0f + (b - r)/h;
        }else{
            h = 4.0f + (r - g)/h;
        }
    }
    loc_hsv.h = h/6.0f; //Hue 色相

    loc_hsv.v = max; //Value,Braightness 明度
}

//キャリブレーション用の黒rgbと白rgb
void ColorMonitor::ColorCalib(offset_val_t offset, coof_val_t coefficient){
    offsetBlack.r = offset.r;
    offsetBlack.g = offset.g;
    offsetBlack.b = offset.b;

    coefficientWhite.r = coefficient.r;
    coefficientWhite.g = coefficient.g;
    coefficientWhite.b = coefficient.b;
}

