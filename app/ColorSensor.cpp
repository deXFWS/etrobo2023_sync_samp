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
ColorSensor::ColorSensor(PORT_2)
            :mColorSensor(colorSensor),
             mBlack(10.0f),
             mWhite(50.0f),
             mBlue(50.0f){

}

/*
カラーセンサ
*/
//ColorSensor::ColorSensor():
    //ColorSensor(PORT_2){}     //ポート番号確認

bool ColorSensor::ResBlack() const{
    //反射光の強さを見て閾値以下で
    if(mColorSensor.getBrightness)
}

/* 反射光は使用しないため無効化
int8_t getBrightness() constz{
    return mColorSensor.getBrightness(); //反射光の強さ(0-100)
}
*/

void ColorSensor::getRAWColor()