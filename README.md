# Pseudo PWM Generator

Pseudo PWM GeneratorはArduinoにおいて、すべてのピンからの疑似PWM信号を出力可能にするプログラムです。

## 必要ライブラリ
 - TimerOne

## 説明

### 関数

#### fAnalogWrite  
引数にピン番号(0, 1以外)とPWM dutyを入力することで疑似PWM信号を出力できます。

Example:
```c
fAnalogWrite(3, 100); //Pin3からPWM duty: 100で出力
```

#### fAnalogInterrupt
割り込みで使用。特に変更する必要はありません。
疑似PWM信号を生成する処理をします。

### 定数

#### FPWM_FREQ
周波数を設定します。後述するFPWM_RESの値にもよりますが、あまり高い周波数は出せません。そのため、周波数は必ずしも設定したとおりになるわけではありません。

Example:
```c
#define FPWM_FREQ 200 //PWM周波数を200Hzに設定
```

#### FPWM_RES
分解能を設定します。256段階より大きいとかなり遅い（200Hzくらいになる）のでそれ以下に設定するのがおすすめです。

Example:
```c
#define FPWM_RES 256 //PWM分解能を256段階に設定
```

#### fAnalogWritePins
この配列に、fAnalogWriteで設定された各ピンのPWM dutyを格納します。特に変更する必要はありません。

#### fAnalogWriteCount
PWMのカウンタです。1サイクルがどこまで進んだかをこの変数に記録しておきます。特に変更する必要はありません。
