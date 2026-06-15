#pragma once
#include "stepResult.hpp"
#include "theme.hpp"
#include <vector>

class Render {
public:
  static void draw(const std::vector<int> array, const StepResult &state,
                   int width, int height, const Theme::Colors& colors);
};