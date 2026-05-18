#pragma once
#include "stepResult.hpp"

class ISorter {
public:
  virtual void step() = 0;
  virtual StepResult getState() const = 0;

  virtual void reset() = 0;

  virtual ~ISorter() = default;
};