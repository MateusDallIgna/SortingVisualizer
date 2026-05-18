#include "include/algorithms.hpp"
#include "include/isorter.hpp"
#include "include/render.hpp"
#include <iostream>
#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

const int WIDTH = 2080;
const int HEIGHT = 920;
const char *TITLE = "SORTING VISUALIZER";
const int FPS = 5;

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

  int algorithmChoice = 0;
  std::cin >> algorithmChoice;

  if (algorithmChoice < 0 || algorithmChoice > 4) {
    std::cout << "Invalid output" << std::endl;
    return 0;
  }

  InitWindow(WIDTH, HEIGHT, TITLE);
  SetTargetFPS(FPS);

  std::vector<int> numbers(amountOfNumbers);
  for (int i = 0; i < amountOfNumbers; i++) {
    numbers[i] = GetRandomValue(20, HEIGHT - 100);
  }

  ISorter *currentSorter = nullptr;
  bool resetOnChange = false;
  int lastAlgorithm = algorithmChoice;

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
  }

  while (!WindowShouldClose()) {

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

    currentSorter->step();

    BeginDrawing();

    StepResult state = currentSorter->getState();
    Render::draw(numbers, state, WIDTH, HEIGHT);

    if (state.done) {
      DrawText("SORTED!", 20, 20, 40, GREEN);

      for (int i = 0; i < amountOfNumbers; i++) {
        std::cout << numbers[i] << " ";
      }
      std::cout << std::endl;
    }

    std::string modeText = resetOnChange ? "Mode: NEW" : "Mode: CONTINUE";
    DrawText(modeText.c_str(), 20, 70, 20, WHITE);

    EndDrawing();
  }

  CloseWindow();
  delete currentSorter;

  return 0;
}
