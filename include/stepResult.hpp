#pragma once

struct StepResult {
  int indexA;
  int indexB;
  bool swapped;
  bool done;

  int sortedCount;
  int pivot;
  int mergeLeft;
  int mergeRight;
  int mergeMid;

  StepResult() : indexA(-1), indexB(-1), swapped(false), done(false),
                 sortedCount(0), pivot(-1), mergeLeft(-1), mergeRight(-1), mergeMid(-1) {}
};