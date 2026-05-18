#include "../include/render.hpp"
#include <raylib.h>

void Render::draw(const std::vector<int> array, const StepResult &state,
                  int width, int height) {

  Color darkBlue = {46, 52, 64, 255};
  Color lightBlue = {136, 192, 208, 255};
  Color cyan = {140, 170, 200, 255};
  Color orange = {235, 160, 90, 255};
  Color green = {163, 190, 140, 255};
  Color yellow = {235, 200, 100, 255};
  Color pink = {235, 203, 209, 255};
  Color gray = {216, 222, 233, 255};

  ClearBackground(darkBlue);

  float barWidth = (float)width / array.size();
  int gapBetweenBars = 2;

  for (int index = 0; index < (int)array.size(); index++) {
    Color color = lightBlue;

    if (state.done) {
      color = gray;
    } else {
      if (state.mergeLeft >= 0 && index >= state.mergeLeft &&
          index <= state.mergeRight) {
        color = pink;
      }

      if (index == state.pivot) {
        color = yellow;
      }

      if (index < state.sortedCount) {
        color = green;
      }

      if (index == state.indexA) {
        color = state.swapped ? yellow : cyan;
      } else if (index == state.indexB) {
        color = state.swapped ? pink : orange;
      }
    }

    float x = index * barWidth;
    int y = height - array[index];
    DrawRectangle(x, y, barWidth - gapBetweenBars, array[index], color);
  }
}
