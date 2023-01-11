/*************************************************************************

  Copyright 2011-2015 Ibrahim Sha'ath

  This file is part of LibKeyFinder.

  LibKeyFinder is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  LibKeyFinder is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with LibKeyFinder.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************/

#include <JuceHeader.h>

#include "fftadapter.h"

// Included here to allow substitution of a separate implementation .cpp
#include <cmath>
#include <cstring>

namespace KeyFinder {
	std::mutex fftwPlanMutex;


  class FftAdapterPrivate {
  public:
	  std::complex<float>* input;
	  std::complex<float>* output;
	  juce::dsp::FFT* plan;

  };

  FftAdapter::FftAdapter(unsigned int inFrameSize) : priv(new FftAdapterPrivate) {
	  frameSize = (int)log2((double)inFrameSize) + 1;
	  priv->input = (std::complex<float>*)malloc(sizeof(std::complex<float>) * frameSize);
	  priv->output = (std::complex<float>*)malloc(sizeof(std::complex<float>) * frameSize);
	  memset(priv->output, 0, sizeof(std::complex<float>) * frameSize);
	  fftwPlanMutex.lock();
	  priv->plan = new juce::dsp::FFT(static_cast<int> (frameSize));
	  fftwPlanMutex.unlock();
  }

  FftAdapter::~FftAdapter() {
	  free(priv->plan);
	  free(priv->input);
	  free(priv->output);
	  delete priv;
  }

  unsigned int FftAdapter::getFrameSize() const {
	  return priv->plan->getSize();
  }

  void FftAdapter::setInput(unsigned int i, double real) {
	  if (i >= frameSize) {
		  std::ostringstream ss;
		  ss << "Cannot set out-of-bounds sample (" << i << "/" << frameSize << ")";
		  throw Exception(ss.str().c_str());
	  }
	  if (!std::isfinite(real)) {
		  throw Exception("Cannot set sample to NaN");
	  }
	  priv->input[2 * i] = real;
	  priv->input[2 * i + 1] = 0;

  }

  double FftAdapter::getOutputReal(unsigned int i) const {
	  if (i >= frameSize) {
		  std::ostringstream ss;
		  ss << "Cannot get out-of-bounds sample (" << i << "/" << frameSize << ")";
		  throw Exception(ss.str().c_str());
	  }
	  return reinterpret_cast<double*> (priv->output)[2 * i];

  }

  double FftAdapter::getOutputImaginary(unsigned int i) const {
	  if (i >= frameSize) {
		  std::ostringstream ss;
		  ss << "Cannot get out-of-bounds sample (" << i << "/" << frameSize << ")";
		  throw Exception(ss.str().c_str());
	  }
	  return reinterpret_cast<double*> (priv->output)[2 * i + 1];
  }

  double FftAdapter::getOutputMagnitude(unsigned int i) const {
	  if (i >= frameSize) {
		  std::ostringstream ss;
		  ss << "Cannot get out-of-bounds sample (" << i << "/" << frameSize << ")";
		  throw Exception(ss.str().c_str());
	  }
	  return sqrt(pow(getOutputReal(i), 2) + pow(getOutputImaginary(i), 2));
  }

  void FftAdapter::execute() {
	  priv->plan->perform(priv->input, priv->output, false);
  }

  // ================================= INVERSE =================================

 class InverseFftAdapterPrivate {
  public:
	std::complex<float>* input;
	std::complex<float>* output;
	juce::dsp::FFT* plan;

  };

  InverseFftAdapter::InverseFftAdapter(unsigned int inFrameSize) {
	  frameSize = (int)log2((double)inFrameSize) + 1;
	  priv->input = (std::complex<float>*)malloc(sizeof(std::complex<float>) * frameSize);
	  priv->output = (std::complex<float>*)malloc(sizeof(std::complex<float>) * frameSize);
	  memset(priv->output, 0, sizeof(std::complex<float>) * frameSize);
	  fftwPlanMutex.lock();
	  priv->plan = new juce::dsp::FFT(static_cast<int> (frameSize));
	  fftwPlanMutex.unlock();

  }

  InverseFftAdapter::~InverseFftAdapter() {
	  free(priv->plan);
	  free(priv->input);
	  free(priv->output);
	  delete priv;
  }

  unsigned int InverseFftAdapter::getFrameSize() const {
	  return priv->plan->getSize();
  }

  void InverseFftAdapter::setInput(unsigned int i, double real, double imag) {
	  if (i >= frameSize) {
		  std::ostringstream ss;
		  ss << "Cannot set out-of-bounds sample (" << i << "/" << frameSize << ")";
		  throw Exception(ss.str().c_str());
	  }
	  if (!std::isfinite(real)) {
		  throw Exception("Cannot set sample to NaN");
	  }
	  priv->input[2 * i] = real;
	  priv->input[2 * i + 1] = imag;
  }

  double InverseFftAdapter::getOutput(unsigned int i) const {
	  if (i >= frameSize) {
		  std::ostringstream ss;
		  ss << "Cannot get out-of-bounds sample (" << i << "/" << frameSize << ")";
		  throw Exception(ss.str().c_str());
	  }
	  return reinterpret_cast<double*> (priv->output)[2 * i];

  }

  void InverseFftAdapter::execute() {
	  priv->plan->perform(priv->input, priv->output, true);

  }

}
