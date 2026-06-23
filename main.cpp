#include "include/algorithms.hpp"
#include "include/isorter.hpp"
#include "include/render.hpp"
#include "include/theme.hpp"
#include <algorithm>
#include <iostream>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

const int WIDTH = 2080;
const int HEIGHT = 920;
const char *TITLE = "SORTING VISUALIZER";
const int BASE_FPS = 5;
int fps = BASE_FPS;

int main() {

  int amountOfNumbers = 0;

  std::cout << "Amount of Numbers to be Sorted: ";
  std::cin >> amountOfNumbers;

  if (amountOfNumbers < 2) {
    std::cout << "Invalid input, put a amount of numbers at least greater "
                 "than 1 \n";
    return 0;
  }

  std::cout << "SORT ALGORITHM:" << std::endl;
  std::cout << "0 - Bubble Sort (DEFAULT)" << std::endl;
  std::cout << "1 - Insertion Sort" << std::endl;
  std::cout << "2 - Bogo Sort" << std::endl;
  std::cout << "3 - Quick Sort" << std::endl;
  std::cout << "4 - Merge Sort" << std::endl;
  std::cout << "5 - Selection Sort" << std::endl;
  std::cout << "6 - Gnome Sort" << std::endl;

  int algorithmChoice = 0;
  std::cin >> algorithmChoice;

  if (algorithmChoice < 0 || algorithmChoice > 6) {
    std::cout << "Invalid output" << std::endl;
    return 0;
  }

  InitWindow(WIDTH, HEIGHT, TITLE);
  InitAudioDevice();
  SetTargetFPS(fps);

  std::vector<int> numbers(amountOfNumbers);
  for (int i = 0; i < amountOfNumbers; i++) {
    numbers[i] = GetRandomValue(20, HEIGHT - 100);
  }

  ISorter *currentSorter = nullptr;
  bool resetOnChange = false;
  int lastAlgorithm = algorithmChoice;

  const char *algorithmNames[] = {
    "Bubble Sort", "Insertion Sort", "Bogo Sort",
    "Quick Sort", "Merge Sort", "Selection Sort", "Gnome Sort"
  };
  const char *currentAlgorithmName = algorithmNames[algorithmChoice];

  if (algorithmChoice == 0) {
    currentSorter = new Sort::BubbleSort(numbers);
  } else if (algorithmChoice == 1) {
    currentSorter = new Sort::InsertionSort(numbers);
  } else if (algorithmChoice == 2) {
    currentSorter = new Sort::BogoSort(numbers);
  } else if (algorithmChoice == 3) {
    currentSorter = new Sort::QuickSort(numbers);
  } else if (algorithmChoice == 4) {
    currentSorter = new Sort::MergeSort(numbers);
  } else if (algorithmChoice == 5) {
    currentSorter = new Sort::SelectionSort(numbers);
  } else if (algorithmChoice == 6) {
    currentSorter = new Sort::GnomeSort(numbers);
  }

  std::string cachedTheme = "";
  Theme::Colors colors = Theme::getDefaultColors();

  while (!WindowShouldClose()) {

    std::string currentTheme = Theme::getCurrentThemeName();
    if (currentTheme != cachedTheme) {
      colors = Theme::getThemeColors(currentTheme);
      cachedTheme = currentTheme;
    }

    if (IsKeyPressed(KEY_R)) {
      for (int i = 0; i < amountOfNumbers; i++) {
        numbers[i] = GetRandomValue(20, HEIGHT - 100);
      }
      currentSorter->reset();
    }

    if (IsKeyPressed(KEY_N)) {
      resetOnChange = !resetOnChange;
    }

    if (IsKeyPressed(KEY_ZERO)) {
      if (lastAlgorithm != 0) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::BubbleSort(numbers);
        lastAlgorithm = 0;
      }
    }

    if (IsKeyPressed(KEY_ONE)) {
      if (lastAlgorithm != 1) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::InsertionSort(numbers);
        lastAlgorithm = 1;
      }
    }

    if (IsKeyPressed(KEY_TWO)) {
      if (lastAlgorithm != 2) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::BogoSort(numbers);
        lastAlgorithm = 2;
      }
    }

    if (IsKeyPressed(KEY_THREE)) {
      if (lastAlgorithm != 3) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::QuickSort(numbers);
        lastAlgorithm = 3;
      }
    }

    if (IsKeyPressed(KEY_FOUR)) {
      if (lastAlgorithm != 4) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::MergeSort(numbers);
        lastAlgorithm = 4;
      }
    }

    if (IsKeyPressed(KEY_FIVE)) {
      if (lastAlgorithm != 5) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::SelectionSort(numbers);
        lastAlgorithm = 5;
      }
    }

    if (IsKeyPressed(KEY_SIX)) {
      if (lastAlgorithm != 6) {
        if (resetOnChange) {
          for (int i = 0; i < amountOfNumbers; i++) {
            numbers[i] = GetRandomValue(20, HEIGHT - 100);
          }
        }
        delete currentSorter;
        currentSorter = new Sort::GnomeSort(numbers);
        lastAlgorithm = 6;
      }
    }

    if (IsKeyPressed(KEY_EQUAL) || IsKeyPressed(KEY_KP_ADD)) {
      fps = std::min(fps * 2, 640);
      SetTargetFPS(fps);
    }

    if (IsKeyPressed(KEY_MINUS) || IsKeyPressed(KEY_KP_SUBTRACT)) {
      fps = std::max(fps / 2, 1);
      SetTargetFPS(fps);
    }

    currentSorter->step();

    BeginDrawing();

    StepResult state = currentSorter->getState();
    Render::draw(numbers, state, WIDTH, HEIGHT, colors);

    if (state.done) {
      DrawText("SORTED!", 20, 20, 40, colors.sorted);

      for (int i = 0; i < amountOfNumbers; i++) {
        std::cout << numbers[i] << " ";
      }
      std::cout << std::endl;
    }

    currentAlgorithmName = algorithmNames[lastAlgorithm];
    DrawText(currentAlgorithmName, 20, 70, 20, colors.pivot);

    std::string modeText = resetOnChange ? "Mode: NEW" : "Mode: CONTINUE";
    DrawText(modeText.c_str(), 20, 100, 20, colors.defaultBar);

    std::string themeText = cachedTheme.empty() ? "CURRENT THEME: default" : ("CURRENT THEME: " + cachedTheme);
    DrawText(themeText.c_str(), 20, 130, 20, colors.defaultBar);

    int speedPercent = (fps * 100) / BASE_FPS;
    std::string speedText = "SPEED: " + std::to_string(speedPercent) + "%";
    DrawText(speedText.c_str(), 20, 160, 20, colors.swapping);

    EndDrawing();
  }

  CloseAudioDevice();
  CloseWindow();
  delete currentSorter;

  return 0;
}
