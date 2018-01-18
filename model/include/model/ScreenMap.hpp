#pragma once

#include <cstdint>
#include <map>
#include <set>

namespace Magick {
class Image;
}

class ScreenMap {
public:
  explicit ScreenMap(const Magick::Image& image);

  void add(std::int16_t word, int address);

  using PixelMap = std::map<std::int16_t, std::set<int>>;
  using iterator = PixelMap::iterator;
  using const_iterator = PixelMap::const_iterator;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

private:
  void read(const Magick::Image& image);

  PixelMap m_words;
};
