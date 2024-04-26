#include <chrono>
#include <thread>
#include <iostream>

volatile char gibberish_reader = 0;

void access_memory(const size_t size, const size_t step, const int delay_ms, char* arr, bool isReading) {
  size_t index = 0;

  while (index < size) {
    if (isReading) {
      gibberish_reader = arr[index];
    } else {
      arr[index] = 0;
    }

    index += step;

    if (index / step % 1000 == 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
  }
}

int main(int argc, char* argv[]) {
  return 0;
}
