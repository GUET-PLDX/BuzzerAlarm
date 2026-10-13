# BuzzerAlarm

无源蜂鸣器报警模块 / Buzzer alarm module

## 硬件需求 / Required Hardware

pwm\_buzzer

## 构造参数 / Constructor Arguments

* alarm\_freq:      1500
* alarm\_duration:  300
* alarm\_delay:     300

## 功能简介 / Features

* 用于驱动无源蜂鸣器进行报警提示。
* 支持指定频率、持续时间和间隔时间的报警音。
* 提供按音名/八度播放（PlayNote）与任意频率播放（Play）接口。
* 在发生致命错误时自动发出报警声。

This module drives a passive buzzer for alarm indication.

* Supports custom alarm frequency, duration, and delay.
* Provides PlayNote (by note name/octave) and Play (by frequency) interfaces.
* Will play an alarm sound automatically on fatal errors.

## 主要成员函数 / Main Member Functions

* `void Play(uint32_t freq, uint32_t duration)`

  * 以指定频率和持续时间发出蜂鸣声。
  * Play a beep at the given frequency and duration.
* `void PlayNote(NoteName note, uint32_t octave, uint32_t duration)`

  * 以音名+八度指定频率，发出蜂鸣声。
  * Play a musical note (by name/octave) for the given duration.

## 依赖 / Depends

无（No dependencies）

## LibXR 2.0 静态装配

使用 xrobot 1.0.1 的 `module` / 有序 `args`；构造函数显式注入外设与服务，实例按依赖顺序创建。参数名和顺序以头文件中的构造函数为准，固件示例见 `User/RobotConfig/`。

保留 PLDX 控制、协议、超时与离线保护。 `OnMonitor()` 由生成的监控循环直接调用。
