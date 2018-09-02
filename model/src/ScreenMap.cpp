#include "ScreenMap.hpp"

#include "Hack.hpp"

#include <Magick++.h>

ScreenMap::ScreenMap(const Magick::Image& image) {
  read(image);
}

void ScreenMap::add(std::int16_t word, int address) {
  if (m_words.find(word) != m_words.end()) {
    m_words.at(word).insert(address);
  } else {
    m_words.emplace(word, std::set<int>{ address });
  }
}

void ScreenMap::read(const Magick::Image& image) {
  int counter = 0;
  std::int16_t word = 0;
  std::uint16_t mask = 1;
  int adr = 0;

  for (int y = 0; y < Hack::screen_height; ++y) {
    for (int x = 0; x < Hack::screen_width; ++x) {
      if (Magick::ColorMono{ image.pixelColor(x, y) }.mono()) {
        word |= mask;
      }

      mask <<= 1;
      counter++;

      if (counter > Hack::word_size - 1) {
        add(word, adr);
        counter = 0;
        word = 0;
        mask = 1;
        adr++;
      }
    }
  }
}
