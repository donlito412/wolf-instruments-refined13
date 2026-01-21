#include "FilterProcessor.h"

FilterProcessor::FilterProcessor() {
  filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
}

void FilterProcessor::prepare(const juce::dsp::ProcessSpec &spec) {
  sampleRate = (float)spec.sampleRate;
  filter.prepare(spec);
  filter.reset();
}

void FilterProcessor::process(juce::AudioBuffer<float> &buffer) {
  juce::dsp::AudioBlock<float> block(buffer);
  juce::dsp::ProcessContextReplacing<float> context(block);
  filter.process(context);
}

void FilterProcessor::reset() { filter.reset(); }

void FilterProcessor::setFilterType(FilterType type) {
  currentType = type;

  switch (type) {
  case LowPass:
    filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    break;
  case HighPass:
    filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    break;
  case BandPass:
    filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    break;
  case Notch:
    // Notch is not directly available, use bandpass inverted
    // For now, use bandpass (we can implement proper notch later)
    filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
    break;
  }
}

void FilterProcessor::setCutoff(float cutoffHz) {
  filter.setCutoffFrequency(cutoffHz);
}

void FilterProcessor::setResonance(float resonance) {
  // Resonance range: 0.0 to 1.0, map to Q factor (0.5 to 10.0)
  float q = 0.5f + resonance * 9.5f;
  filter.setResonance(q);
}
