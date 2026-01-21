#pragma once
#include <JuceHeader.h>

class FilterProcessor {
public:
  FilterProcessor();

  enum FilterType { LowPass = 0, HighPass, BandPass, Notch };

  void prepare(const juce::dsp::ProcessSpec &spec);
  void process(juce::AudioBuffer<float> &buffer);
  void reset();

  void setFilterType(FilterType type);
  void setCutoff(float cutoffHz);
  void setResonance(float resonance);

private:
  juce::dsp::StateVariableTPTFilter<float> filter;
  FilterType currentType = LowPass;
  float sampleRate = 44100.0f;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterProcessor)
};
