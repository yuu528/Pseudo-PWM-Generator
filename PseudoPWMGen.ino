#include <TimerOne.h>

//PWM周波数[Hz]
#define FPWM_FREQ 50

//PWM分解能 小さくすると周波数上限を上げられる
#define FPWM_RES 16

//ピンの出力値用 0pin(RX)と1pin(TX)は使えない
volatile unsigned int fAnalogWritePins[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned int fAnalogWriteCount = 0; //PWM周期カウンタ

void setup() {
  //PWM分解能と周波数より割り込み周期(出力1のときのON時間[us])を計算、割り込みを設定
  Timer1.initialize(1000000 / FPWM_RES / FPWM_FREQ);
  Timer1.attachInterrupt(fAnalogInterrupt);
}

void loop() {
  //なにもしない
}

/*
 * fAnalogWrite 指定したPINから偽のPWM出力をする
 * (byte) pin   : ピン番号(2 <= pin <= 19)
 * (byte) value : PWM出力値(0 <= value <= FPWM_RES)
 */
void fAnalogWrite(byte pin, unsigned int value) {
  //0, 1pinを省くためpin - 2とする
  fAnalogWritePins[pin - 2] = value;
}

/*
 * fAnalogInterrupt 偽PWMの割り込み処理をする
 */
void fAnalogInterrupt() {
  if(fAnalogWriteCount) {
    //PWM周期中
    for(byte i = 0; i <= 5; i++) {
      //fAnalogWritePins[pin]に設定されたPWM比を満たしたらLOWに
      //+2や+6、+12をしてforカウンタと配列添字、ポート番号をうまく揃える
      if(fAnalogWritePins[i] <= fAnalogWriteCount) PORTD &= ~_BV(i + 2);
      if(fAnalogWritePins[i + 6] <= fAnalogWriteCount) PORTB &= ~_BV(i);
      if(fAnalogWritePins[i + 12] <= fAnalogWriteCount) PORTC &= ~_BV(i);
    }
    fAnalogWriteCount++;
    //PWM100%地点に達したらまたはじめから
    if(fAnalogWriteCount >= FPWM_RES) fAnalogWriteCount = 0;
  } else {
    //PWM周期開始時
    for(byte i = 0; i <= 5; i++) {
      //1以上の値が設定されていたらHIGHにする
      if(fAnalogWritePins[i]) PORTD |= _BV(i + 2);
      if(fAnalogWritePins[i + 6]) PORTB |= _BV(i);
      if(fAnalogWritePins[i + 12]) PORTC |= _BV(i);
    }
    
    fAnalogWriteCount++;
  }
}
