#pragma once

// clang-format off
/* === MODULE MANIFEST V2 ===
module_description: 无源蜂鸣器报警模块 / Buzzer alarm module
depends: []
=== END MANIFEST === */
// clang-format on

#include "libxr.hpp"
#include "pwm.hpp"

class BuzzerAlarm {
 public:
  // NOLINTNEXTLINE
  enum class NoteName { C = 0, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B };

  BuzzerAlarm(LibXR::PWM& pwm, uint32_t alarm_freq = 1500,
              uint32_t alarm_duration = 300, uint32_t alarm_delay = 300)
      : alarm_freq_(alarm_freq),
        alarm_duration_(alarm_duration),
        alarm_delay_(alarm_delay),
        pwm_(&pwm) {
    LibXR::Assert::RegisterFatalErrorCallback(
        LibXR::Callback<const char*, uint32_t>::Create(
            [](bool in_isr, BuzzerAlarm* alarm, const char* file,
               uint32_t line) {
              UNUSED(file);
              UNUSED(line);

              if (in_isr) {
                return;
              }

              alarm->Play(alarm->alarm_freq_, alarm->alarm_duration_);
              LibXR::Thread::Sleep(alarm->alarm_delay_);
            },
            this));
    // Fuji Shan Xia MIDI [0.46875, 1.46875 s): skip the leading rest and
    // use the higher note during overlap. Relative times rounded to
    // milliseconds.
    PlayNote(NoteName::C, 6, 260);
    PlayNote(NoteName::C, 7, 313);
    PlayNote(NoteName::B, 6, 312);
    PlayNote(NoteName::C, 7, 115);
  }

  void Play(uint32_t freq, uint32_t duration) {
    pwm_->SetConfig({freq});
    pwm_->Enable();
    pwm_->SetDutyCycle(0.01f);
    LibXR::Thread::Sleep(duration);
    pwm_->Disable();
  }

  void PlayNote(NoteName note, uint32_t octave, uint32_t duration) {
    int midi_num = static_cast<int>(note) + static_cast<int>((octave + 1) * 12);
    float freq =
        440.0f * std::pow(2.0f, (static_cast<float>(midi_num) - 69.0f) / 12.0f);
    Play(static_cast<uint32_t>(freq), static_cast<uint32_t>(duration));
  }

  void OnMonitor() {}

 private:
  uint32_t alarm_freq_;
  uint32_t alarm_duration_;
  uint32_t alarm_delay_;

  LibXR::PWM* pwm_;
};
