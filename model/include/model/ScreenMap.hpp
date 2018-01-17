#pragma once

#include <Magick++.h>

#include <cstdint>
#include <map>
#include <set>

class ScreenMap {
public:
  ScreenMap(Magick::Image image);
  void add(std::int16_t word, int address);
  const std::map<std::int16_t, std::set<int>>& getMap() const;

private:
  void readImage();

  Magick::Image m_image;
  std::map<std::int16_t, std::set<int>> m_words;
};
