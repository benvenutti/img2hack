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

  auto begin() { return m_words.begin(); }
  auto begin() const { return m_words.begin(); }
  auto end() { return m_words.end(); }
  auto end() const { return m_words.end(); }

private:
  void add(std::int16_t word, int address);
  void read(const Magick::Image& image);

  std::map<std::int16_t, std::set<int>> m_words;
};
