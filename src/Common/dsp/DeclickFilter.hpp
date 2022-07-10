#pragma once

struct DeclickFilter
{
  bool smooth_enabled = true;
  double smooth_ramp = 1;

  // The HIGHER the smooth_constant, the faster the smoothing will take effect
  // 2048 seems to work well and doesn't have a noticeable affect on the
  // snappiness of drum sounds.  Low values, such as 256 or lower, will have
  // a dramatic affect on the punch of drums.
  double smooth_constant = 2048.0;
  double smooth_rate = (smooth_constant / rack::settings::sampleRate);

  float previous_left_audio = 0.0;
  float previous_right_audio = 0.0;

  // Trigger the declick filter before a large jump in voltages due to
  // sample position, or waveform selection, or other types of events that
  // would normally create clicks and pops in the output.

  void trigger()
  {
    smooth_ramp = 0;
  }

  void updateSampleRate()
  {
    smooth_rate = (smooth_constant / rack::settings::sampleRate);
  }

  void process(float *left_audio_ptr, float *right_audio_ptr)
  {
    if(smooth_enabled && (smooth_ramp < 1))
    {
      smooth_ramp += smooth_rate;
      *left_audio_ptr = (previous_left_audio * (1 - smooth_ramp)) + ((*left_audio_ptr) * smooth_ramp);
      *right_audio_ptr = (previous_right_audio * (1 - smooth_ramp)) + ((*right_audio_ptr) * smooth_ramp);
    }

    previous_left_audio = *left_audio_ptr;
    previous_right_audio = *right_audio_ptr;
  }

};