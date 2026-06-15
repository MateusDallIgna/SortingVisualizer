#include "../include/algorithms.hpp"
#include <algorithm>
#include <random>

namespace Sort {

BubbleSort::BubbleSort(std::vector<int> &array)
    : arrayPointer(&array), currentI(0), currentJ(0), sortedCount(0),
      isDone(false) {
  reset();
}

void BubbleSort::step() {
  if (isDone)
    return;

  int size = arrayPointer->size();

  if (currentI >= size - 1) {
    isDone = true;
    currentState = StepResult();
    currentState.done = true;
    currentState.sortedCount = size;
    return;
  }

  if (currentJ >= size - currentI - 1) {
    currentI++;
    sortedCount = currentI;
    currentJ = 0;
    return;
  }

  currentState = StepResult();
  currentState.indexA = currentJ;
  currentState.indexB = currentJ + 1;
  currentState.sortedCount = sortedCount;

  if ((*arrayPointer)[currentJ] > (*arrayPointer)[currentJ + 1]) {
    std::swap((*arrayPointer)[currentJ], (*arrayPointer)[currentJ + 1]);
    currentState.swapped = true;
  } else {
    currentState.swapped = false;
  }

  currentJ++;
}

StepResult BubbleSort::getState() const { return currentState; }

void BubbleSort::reset() {
  currentI = 0;
  currentJ = 0;
  sortedCount = 0;
  isDone = false;
  currentState = StepResult();
}

InsertionSort::InsertionSort(std::vector<int> &array)
    : arrayPointer(&array), currentI(0), currentJ(0), sortedCount(0),
      isDone(false) {
  reset();
}

void InsertionSort::step() {
  if (isDone)
    return;

  int size = arrayPointer->size();

  if (currentI >= size) {
    isDone = true;
    currentState = StepResult();
    currentState.done = true;
    currentState.sortedCount = size;
    return;
  }

  if (currentJ == 0) {
    currentI++;
    sortedCount = currentI;
    currentJ = currentI;
    if (currentI >= size) {
      isDone = true;
      currentState = StepResult();
      currentState.done = true;
      currentState.sortedCount = size;
      return;
    }
  }

  currentState = StepResult();
  currentState.indexA = currentJ;
  currentState.indexB = currentJ - 1;
  currentState.sortedCount = sortedCount;

  if (currentJ > 0 && (*arrayPointer)[currentJ] < (*arrayPointer)[currentJ - 1]) {
    std::swap((*arrayPointer)[currentJ], (*arrayPointer)[currentJ - 1]);
    currentState.swapped = true;
    currentJ--;
  } else {
    currentState.swapped = false;
    currentI++;
    sortedCount = currentI;
    currentJ = currentI;
  }
}

StepResult InsertionSort::getState() const { return currentState; }

void InsertionSort::reset() {
  currentI = 0;
  currentJ = 0;
  sortedCount = 0;
  isDone = false;
  currentState = StepResult();
}

QuickSort::QuickSort(std::vector<int> &array)
    : arrayPointer(&array), isDone(false) {
  reset();
}

void QuickSort::step() {
  if (isDone)
    return;

  if (currentRange.first >= currentRange.second) {
    if (!stack.empty()) {
      currentRange = stack.back();
      stack.pop_back();
    } else {
      isDone = true;
      currentState = StepResult();
      currentState.done = true;
      return;
    }
  }

  if (pivot == -1) {
    pivot = currentRange.first;
    left = currentRange.first + 1;
    right = currentRange.second;
  }

  currentState = StepResult();
  currentState.indexA = left;
  currentState.indexB = right;
  currentState.pivot = pivot;

  if (left <= right) {
    if ((*arrayPointer)[left] < (*arrayPointer)[pivot]) {
      left++;
    } else if ((*arrayPointer)[right] > (*arrayPointer)[pivot]) {
      right--;
    } else {
      std::swap((*arrayPointer)[left], (*arrayPointer)[right]);
      currentState.swapped = true;
      left++;
      right--;
    }
  } else {
    std::swap((*arrayPointer)[pivot], (*arrayPointer)[right]);
    currentState.indexA = pivot;
    currentState.indexB = right;
    currentState.swapped = true;
    currentState.pivot = right;

    int newPivot = right;

    if (currentRange.second > newPivot + 1)
      stack.push_back({newPivot + 1, currentRange.second});
    if (currentRange.first < newPivot - 1)
      stack.push_back({currentRange.first, newPivot - 1});

    pivot = -1;
    left = 0;
    right = 0;

    if (!stack.empty()) {
      currentRange = stack.back();
      stack.pop_back();
    } else {
      isDone = true;
      currentState = StepResult();
      currentState.done = true;
    }
  }
}

StepResult QuickSort::getState() const { return currentState; }

void QuickSort::reset() {
  int size = arrayPointer->size();
  currentRange = {0, size - 1};
  stack.clear();
  pivot = -1;
  left = 0;
  right = 0;
  isDone = false;
  currentState = StepResult();
}

MergeSort::MergeSort(std::vector<int> &array)
    : arrayPointer(&array), isDone(false), stepSize(1) {
  reset();
}

void MergeSort::step() {
  if (isDone)
    return;

  int size = arrayPointer->size();

  if (left >= size) {
    if (stepSize >= size) {
      isDone = true;
      currentState = StepResult();
      currentState.done = true;
      return;
    }
    stepSize *= 2;
    left = 0;
    leftIndex = -1;
  }

  int mid = left + stepSize / 2 - 1;
  if (mid < 0)
    mid = 0;

  int rightBound = std::min(left + stepSize - 1, size - 1);

  if (left >= size || mid >= size) {
    left += stepSize;
    leftIndex = -1;
    return;
  }

  currentState = StepResult();
  currentState.mergeLeft = left;
  currentState.mergeRight = rightBound;
  currentState.mergeMid = mid;

  if (leftIndex < 0) {
    leftIndex = left;
    rightIndex = mid + 1;
    tempIndex = left;
    if ((int)temp.size() < size)
      temp.resize(size);
  }

  currentState.indexA = leftIndex;
  currentState.indexB = rightIndex;

  if (leftIndex <= mid && rightIndex <= rightBound) {
    if ((*arrayPointer)[leftIndex] <= (*arrayPointer)[rightIndex]) {
      temp[tempIndex++] = (*arrayPointer)[leftIndex++];
    } else {
      temp[tempIndex++] = (*arrayPointer)[rightIndex++];
      currentState.swapped = true;
    }
  } else if (leftIndex <= mid) {
    temp[tempIndex++] = (*arrayPointer)[leftIndex++];
  } else if (rightIndex <= rightBound) {
    temp[tempIndex++] = (*arrayPointer)[rightIndex++];
  }

  if (leftIndex > mid && rightIndex > rightBound) {
    for (int i = left; i <= rightBound; i++) {
      (*arrayPointer)[i] = temp[i];
    }
    leftIndex = -1;
    left += stepSize;
  }
}

StepResult MergeSort::getState() const { return currentState; }

void MergeSort::reset() {
  int size = arrayPointer->size();
  temp.resize(size);
  stepSize = 1;
  left = 0;
  right = stepSize - 1;
  mid = 0;
  leftIndex = -1;
  rightIndex = 0;
  tempIndex = 0;
  isDone = false;
  currentState = StepResult();
}

BogoSort::BogoSort(std::vector<int> &array)
    : arrayPointer(&array), generator(std::random_device{}()), isDone(false) {
  reset();
}

void BogoSort::step() {
  if (isDone)
    return;

  currentState = StepResult();

  bool isSortedNow = std::is_sorted(arrayPointer->begin(), arrayPointer->end());

  if (isSortedNow) {
    isDone = true;
    currentState.done = true;
    return;
  }

  std::shuffle(arrayPointer->begin(), arrayPointer->end(), generator);

  currentState.indexA = -1;
  currentState.indexB = -1;
  currentState.swapped = true;
}

StepResult BogoSort::getState() const { return currentState; }

void BogoSort::reset() {
  isDone = false;
  currentState = StepResult();
}

SelectionSort::SelectionSort(std::vector<int> &array)
    : arrayPointer(&array), currentI(0), currentJ(0), minIndex(0),
      sortedCount(0), isDone(false) {
  reset();
}

void SelectionSort::step() {
  if (isDone)
    return;

  int size = arrayPointer->size();

  if (currentI >= size - 1) {
    isDone = true;
    currentState = StepResult();
    currentState.done = true;
    currentState.sortedCount = size;
    return;
  }

  currentState = StepResult();
  currentState.indexA = currentJ;
  currentState.indexB = minIndex;
  currentState.sortedCount = sortedCount;

  if (currentJ < size) {
    if ((*arrayPointer)[currentJ] < (*arrayPointer)[minIndex])
      minIndex = currentJ;
    currentJ++;
  }

  if (currentJ >= size) {
    if (minIndex != currentI) {
      std::swap((*arrayPointer)[currentI], (*arrayPointer)[minIndex]);
      currentState.swapped = true;
    }
    currentI++;
    sortedCount = currentI;
    currentJ = currentI;
    minIndex = currentI;
  }
}

StepResult SelectionSort::getState() const { return currentState; }

void SelectionSort::reset() {
  currentI = 0;
  currentJ = 0;
  minIndex = 0;
  sortedCount = 0;
  isDone = false;
  currentState = StepResult();
}

GnomeSort::GnomeSort(std::vector<int> &array)
    : arrayPointer(&array), pos(0), sortedCount(0), isDone(false) {
  reset();
}

void GnomeSort::step() {
  if (isDone)
    return;

  int size = arrayPointer->size();

  if (pos >= size) {
    isDone = true;
    currentState = StepResult();
    currentState.done = true;
    currentState.sortedCount = size;
    return;
  }

  currentState = StepResult();
  currentState.indexA = pos;
  currentState.indexB = pos - 1;
  currentState.sortedCount = sortedCount;

  if (pos == 0 || (*arrayPointer)[pos] >= (*arrayPointer)[pos - 1]) {
    pos++;
    sortedCount = pos;
    currentState.swapped = false;
  } else {
    std::swap((*arrayPointer)[pos], (*arrayPointer)[pos - 1]);
    currentState.swapped = true;
    pos--;
  }
}

StepResult GnomeSort::getState() const { return currentState; }

void GnomeSort::reset() {
  pos = 0;
  sortedCount = 0;
  isDone = false;
  currentState = StepResult();
}

} // namespace Sort