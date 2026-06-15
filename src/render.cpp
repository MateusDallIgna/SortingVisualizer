#include "../include/render.hpp"
#include <raylib.h>

void Render::draw(const std::vector<int> array, const StepResult &state,
                  int width, int height, const Theme::Colors& colors) {

  ClearBackground(colors.background);

  float barWidth = (float)width / array.size();
  int gapBetweenBars = 2;

  for (int index = 0; index < (int)array.size(); index++) {
    Color color = colors.defaultBar;

    if (state.done) {
      color = colors.done;
    } else {
      if (state.mergeLeft >= 0 && index >= state.mergeLeft &&
          index <= state.mergeRight) {
        color = colors.comparingAlt;
      }

      if (index == state.pivot) {
        color = colors.pivot;
      }

      if (index < state.sortedCount) {
        color = colors.sorted;
      }

      if (index == state.indexA) {
        color = state.swapped ? colors.pivot : colors.comparing;
      } else if (index == state.indexB) {
        color = state.swapped ? colors.comparingAlt : colors.swapping;
      }
    }

    float x = index * barWidth;
    int y = height - array[index];
    DrawRectangle(x, y, barWidth - gapBetweenBars, array[index], color);
  }
}
