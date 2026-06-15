#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "isorter.hpp"
#include <vector>
#include <random>

namespace Sort {

class BubbleSort : public ISorter {
public:
  BubbleSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  int currentI;
  int currentJ;
  int sortedCount;
  bool isDone;
  StepResult currentState;
};

class InsertionSort : public ISorter {
public:
  InsertionSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  int currentI;
  int currentJ;
  int sortedCount;
  bool isDone;
  StepResult currentState;
};

class QuickSort : public ISorter {
public:
  QuickSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  std::pair<int, int> currentRange;
  std::vector<std::pair<int, int>> stack;
  int pivot;
  int left;
  int right;
  bool isDone;
  StepResult currentState;
};

class MergeSort : public ISorter {
public:
  MergeSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  std::vector<int> temp;
  int stepSize;
  int left;
  int right;
  int mid;
  int leftIndex;
  int rightIndex;
  int tempIndex;
  bool isDone;
  StepResult currentState;
};

class BogoSort : public ISorter {
public:
  BogoSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  std::mt19937 generator;
  bool isDone;
  StepResult currentState;
};

class SelectionSort : public ISorter {
public:
  SelectionSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  int currentI;
  int currentJ;
  int minIndex;
  int sortedCount;
  bool isDone;
  StepResult currentState;
};

class GnomeSort : public ISorter {
public:
  GnomeSort(std::vector<int> &array);

  void step() override;
  StepResult getState() const override;
  void reset() override;

private:
  std::vector<int> *arrayPointer;
  int pos;
  int sortedCount;
  bool isDone;
  StepResult currentState;
};

} // namespace Sort
#endif