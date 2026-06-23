#include "../include/render.hpp"
#include <raylib.h>
#include <cmath>
#include <cstdlib>

static struct {
  int idxA, idxB;
  int startA, startB;
  float progress;
  bool active;
} anim = {-1, -1, 0, 0, 0.0f, false};

const float ANIM_DURATION = 0.3f;

static Sound swapSound = {0};
static bool soundReady = false;

static void InitSwapSound() {
  int sampleRate = 44100;
  int sampleCount = sampleRate * 0.1;
  short *samples = (short *)malloc(sampleCount * sizeof(short));
  if (!samples) return;

  for (int i = 0; i < sampleCount; i++) {
    float t = (float)i / sampleRate;
    samples[i] = (short)(32767.0f * sinf(2.0f * 3.14159265f * 440.0f * t));
  }

  Wave wave = {(unsigned int)sampleCount, (unsigned int)sampleRate, 16, 1, samples};
  swapSound = LoadSoundFromWave(wave);
  free(samples);
  soundReady = (swapSound.frameCount > 0);
}

static void PlaySwapSound(int value, int maxHeight) {
  if (!soundReady) InitSwapSound();
  if (!soundReady) return;
  float pitch = 0.5f + 1.5f * (1.0f - (float)value / maxHeight);
  SetSoundPitch(swapSound, pitch);
  PlaySound(swapSound);
}

void Render::draw(const std::vector<int> array, const StepResult &state,
                  int width, int height, const Theme::Colors& colors) {

  ClearBackground(colors.background);

  float barWidth = (float)width / array.size();
  int gap = 2;

  if (state.swapped && !anim.active) {
    anim.idxA = state.indexA;
    anim.idxB = state.indexB;
    anim.startA = array[state.indexB];
    anim.startB = array[state.indexA];
    anim.progress = 0.0f;
    anim.active = true;
    PlaySwapSound(array[state.indexA], height);
  }

  if (anim.active) {
    anim.progress += GetFrameTime() / ANIM_DURATION;
    if (anim.progress >= 1.0f) {
      anim.progress = 1.0f;
      anim.active = false;
    }
  }

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

    int barHeight = array[index];
    if (anim.active && index == anim.idxA) {
      barHeight = (int)(anim.startA + (array[index] - anim.startA) * anim.progress);
    } else if (anim.active && index == anim.idxB) {
      barHeight = (int)(anim.startB + (array[index] - anim.startB) * anim.progress);
    }

    float x = index * barWidth;
    int y = height - barHeight;
    DrawRectangle(x, y, barWidth - gap, barHeight, color);
  }
}
