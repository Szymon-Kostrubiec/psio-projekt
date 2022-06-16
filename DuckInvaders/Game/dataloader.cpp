#include "dataloader.h"

static std::vector<std::string> splitCsvLine(std::string &src) {
  std::vector<std::string> result;
  std::size_t position;
  char separator = ',';

  while ((position = src.find(separator)) not_eq std::string::npos) {
    std::string temp = src.substr(0, position);
    if (temp.empty()) {
      src.erase(0, 1);
      continue;
    } else
      result.emplace_back(temp);
    src.erase(0, position + 1);
  }
  result.emplace_back(src); // FIXME: bad practices

  //  result.erase(result.begin()); // remove the descriptor

  return result;
}

static std::vector<uint16_t>
transformVector(std::vector<std::string> const &src) {

  std::vector<uint16_t> result;

  for (auto const &str : src) {
    result.emplace_back(std::stoi(str));
  }
  return result;
}

DataLoader::DataLoader(const std::string &fileName) {
  std::fstream file(fileName, std::fstream::in);
  std::string line{};

  if (not file.is_open()) {
    std::cerr << "File " << fileName << " not opened. Terminating" << std::endl;
    std::terminate();
  }

  file >> line;
  heroHp = transformVector(splitCsvLine(line));
  file >> line;
  scoreIncrease = transformVector(splitCsvLine(line));
  file >> line;
  enemyHp = transformVector(splitCsvLine(line));
  file >> line;
  bossHp = transformVector(splitCsvLine(line));
  file >> line;
  projectileSpeed = transformVector(splitCsvLine(line));
}
