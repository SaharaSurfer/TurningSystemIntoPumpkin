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
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <mode> <delay_ms>" << std::endl;
    std::cerr << "Mode: r (read) or w (write)" << std::endl;
    return 1;
  }

  constexpr size_t kArrSize = 16UL * 1024 * 1024 * 1024;
  constexpr size_t kPageSize = 4 * 1024;

  const char* mode = argv[1];
  const int delay_ms = std::stoi(argv[2]);

  if (delay_ms < 0) {
    std::cerr << "Delay must be non-negative." << std::endl;
    return 1;
  }

  bool isReading;
  if (*mode == 'r') {
    isReading = true;
  } else if (*mode == 'w') {
    isReading = false;
  } else {
    std::cerr << "Invalid mode. Please use 'r' for read or 'w' for write." << std::endl;
    return 1;
  }

  char* massive_array = new char[kArrSize];

  if (massive_array == nullptr) {
    std::cerr << "Memory allocation failed." << std::endl;
    return 1;
  }
  
  access_memory(kArrSize, kPageSize, delay_ms, massive_array, isReading);

  delete[] massive_array;

  return 0;
}
