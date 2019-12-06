#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <vector>

const char *FILE_PATH =
    "/Users/robert.cafazzo/personal_dev/advent-of-code-2019/data/day01_input";

std::vector<uint32_t> loadNumbers() {
  std::ifstream file(FILE_PATH);
  std::vector<uint32_t> numbers;

  if (file.is_open()) {
    std::string str;
    while (std::getline(file, str)) {
      numbers.push_back(std::stoul(str));
    }
  } else {
    throw "Failed to open file.";
  }
  return numbers;
}

uint32_t calculateFuelReq(uint32_t mass) {
  auto req = (mass / 3);
  if (req > 2) {
    req -= 2;
    req += calculateFuelReq(req);
  } else {
    req = 0;
  }
  std::cout << "Fuel req for item with mass " << mass << ": " << req
            << std::endl;
  return req;
}

int main() {
  auto numbers = loadNumbers();

  uint32_t fuelReqs = 0;

  for (auto mass : numbers) {
    fuelReqs += calculateFuelReq(mass);
  }

  std::cout << "Total fuel req: " << fuelReqs << std::endl;

  return 0;
}