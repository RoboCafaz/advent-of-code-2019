#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

const char *FILE_PATH =
    "/Users/robert.cafazzo/personal_dev/advent-of-code-2019/data/day02_input";

void loadNumbers(std::vector<uint32_t> &numbers) {
  std::ifstream file(FILE_PATH);

  if (file.is_open()) {
    std::string str;
    while (std::getline(file, str, ',')) {
      numbers.push_back(std::stoul(str));
    }
  } else {
    throw "Failed to open file.";
  }
}

void performOpCode(std::vector<uint32_t> &numbers, uint32_t index,
                   uint32_t (*func)(uint32_t, uint32_t)) {
  auto firstIndex = numbers[index + 1];
  auto secondIndex = numbers[index + 2];
  auto resultIndex = numbers[index + 3];

  auto max = numbers.size();
  if (firstIndex >= max || secondIndex >= max || resultIndex >= max) {
    throw "Out of range!";
  }
  std::cout << "[" << firstIndex << "," << secondIndex << "," << resultIndex
            << "]" << std::endl;
  numbers[resultIndex] = func(numbers[firstIndex], numbers[secondIndex]);
}

uint32_t performOpCode(uint32_t opCode, std::vector<uint32_t> &numbers,
                       uint32_t index) {
  std::cout << "Executing OP Code " << opCode << " at index " << index << ":";
  switch (opCode) {
  case 1:
    performOpCode(numbers, index, [](uint32_t a, uint32_t b) { return a + b; });
    return index + 4;
  case 2:
    performOpCode(numbers, index, [](uint32_t a, uint32_t b) { return a * b; });
    return index + 4;
  case 99:
    std::cout << " DIE" << std::endl;
    return UINT32_MAX;
  }
}

int main() {
  std::vector<uint32_t> numbers;
  loadNumbers(numbers);

  // This instruction was pretty stupid.
  numbers[1] = 12;
  numbers[2] = 2;

  uint32_t index = 0;
  while (index < numbers.size()) {
    index = performOpCode(numbers[index], numbers, index);
  }

  bool first = true;
  for (auto number : numbers) {
    if (!first) {
      std::cout << ",";
    }
    std::cout << number;
    first = false;
  }
  std::cout << std::endl;

  return 0;
}