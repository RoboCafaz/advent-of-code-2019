#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

const uint32_t SEEK = 19690720;
const char *FILE_PATH =
    "/Users/robert.cafazzo/personal_dev/advent-of-code-2019/data/day02_input";

std::vector<uint32_t> loadNumbers() {
  std::ifstream file(FILE_PATH);

  std::vector<uint32_t> numbers;
  if (file.is_open()) {
    std::string str;
    while (std::getline(file, str, ',')) {
      numbers.push_back(std::stoul(str));
    }
  } else {
    throw "Failed to open file.";
  }
  return numbers;
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

// numbers is passed by value so the default number set won't be overridden
std::vector<uint32_t> evaluate(uint32_t noun, uint32_t verb,
                               std::vector<uint32_t> numbers) {
  numbers[1] = noun;
  numbers[2] = verb;
  uint32_t index = 0;
  while (index < numbers.size()) {
    index = performOpCode(numbers[index], numbers, index);
  }
  return numbers;
}

int main() {
  std::vector<uint32_t> input = loadNumbers();

  std::vector<uint32_t> results{0};
  uint32_t noun = 0;
  uint32_t verb = 0;

  while (noun < 99 && results[0] != SEEK) {
    while (verb < 99 && results[0] != SEEK) {
      results = evaluate(noun, verb, input);
      verb++;
    }
    verb = 0;
    noun++;
  }

  bool first = true;
  for (auto number : results) {
    if (!first) {
      std::cout << ",";
    }
    std::cout << number;
    first = false;
  }
  std::cout << std::endl;

  return 0;
}