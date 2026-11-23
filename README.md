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

## 开机音效

构造实例时同步播放 `assets/fuji_shan_xia.mid` 从第一个音符开始的一秒，
去掉开头 468.750 ms 静音，截取原文件的 0.468750–1.468750 s。
此文件来自用户提供的 `富士山下_爱给网_aigei_com.mid`，
SHA-256 为 `9c18ec3ca601b739a0d1e929bd428c3e16553694260b5b5d22113b54b6b31317`。

源 MIDI 为 480 ticks/beat，开头速度为 625000 µs/beat（96 BPM）：

| 区间（ms） | 蜂鸣器输出 |
| --- | --- |
| 0–260 | C6，MIDI 音符 84，约 1046 Hz |
| 260–573 | C7，MIDI 音符 96，约 2093 Hz |
| 573–885 | B6，MIDI 音符 95，约 1975 Hz |
| 885–1000 | C7，MIDI 音符 96，约 2093 Hz |

原始起音时间为 468.750、729.167、1041.667 和 1354.167 ms；
减去第一个音符的起音时间，再将相对时间取整后，
对应播放时长为 260、313、312、115 ms，总计 1000 ms。
蜂鸣器为单声部，音符重叠时取较高音，不模拟钢琴音色、力度和延音踏板。
音序已转换为构造函数中的固定调用，固件无需读取 MIDI 文件。
开机音效和致命错误报警均使用 1% PWM 占空比（`0.01f`）。
`alarm_freq`、`alarm_duration` 和 `alarm_delay` 仍只控制致命错误报警。

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
