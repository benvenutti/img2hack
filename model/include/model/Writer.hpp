#pragma once

#include <fstream>

class ScreenMap;

class Writer {
public:
  Writer(std::ofstream& output, const ScreenMap& screenMap);

  int compile();

private:
  std::ofstream& m_output;
  const ScreenMap& m_screenMap;
};
