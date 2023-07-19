#include "ColorSensor.h"

// #ifdef robo_no,,,

//定数宣言
const float ColorSensor::BLACK_JDG = 10.0f;
const float ColorSensor::WHITE_JDG = 50.0f;
const float ColorSensor::BLUE_JDG = 50.0f;

// #endif robo_no,,,

/*
コンストラクタ
*/
ColorSensor::ColorSensor(PORT_3)
            :mColorSensor(colorSensor),
             mBlack(10.0f),
             mWhite(50.0f),
             mBlue(50.0f){

}

/*
カラーセンサ
*/
//ColorSensor::ColorSensor():
    //ColorSensor(PORT_3){}     //ポート番号確認

bool ColorSensor::ResBlack() const{
    //反射光の強さを見て閾値以下で
    if(mColorSensor.getBrightness)
}

/* 反射光は使用しないため無効化
int8_t getBrightness() constz{
    return mColorSensor.getBrightness(); //反射光の強さ(0-100)
}
*/

//キャリブレーションを行い
//黒と白の時のrgb値をオフセットする
void ColorSensor::getRGB(){
    mColorSensor.getRAWColor(rgb_val);

    //start_calivration
    mRed = ((float)(rgb_val.r - offsetBlack.r))*coefficientWhite.r;
    mGreen = ((float)(rgb_val.g - offsetBlack.g))*coefficientWhite.g;
    mBlue = ((float)(rgb_val.b - offsetBlack.b))*coefficientWhite.b;
}

void ColorSensor::getRAWColor(rgb_raw_t & rgb){
    mColorSensor.getRAWColor(rgb_val);

    rgb.r = rgb_val.r;
    rgb.g = rgb_val.g;
    rgb.b = rgb_val.b;
}

//
void ColorSensor::getHSVValue(hsv_val_t & hsv){
    calcHSV();
    hsv = loc_hsv;
}

//RGB→HSV変換処理
//calcHSV();で
//loc_hsv.h, loc_hsv.s, loc_hsv.vとして呼び出し
void ColorSensor::calcHSV(){
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
void ColorSensor::ColorCalib(offset_val_t offset, coof_val_t coefficient){
    offsetBlack.r = offset.r;
    offsetBlack.g = offset.g;
    offsetBlack.b = offset.b;

    coefficientWhite.r = coefficient.r;
    coefficientWhite.g = coefficient.g;
    coefficientWhite.b = coefficient.b;
}

