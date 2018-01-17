#include "ScreenMap.hpp"

#include "Hack.hpp"

ScreenMap::ScreenMap(Magick::Image image)
: m_image{ image } {
  readImage();
}

void ScreenMap::add(int16_t word, int address) {
  if (m_words.find(word) != m_words.end())
    m_words.at(word).insert(address);
  else {
    m_words.emplace(word, std::set<int>{ address });
  }
}

const std::map<int16_t, std::set<int>>& ScreenMap::getMap() const {
  return m_words;
}

void ScreenMap::readImage() {
  int counter = 0;
  int16_t word = 0;
  uint16_t mask = 1;
  int adr = 0;

  for (int i = 0; i < Hack::SCREEN_HEIGHT; ++i) {
    for (int j = 0; j < Hack::SCREEN_WIDTH; ++j) {

      Magick::ColorMono pixel{ m_image.pixelColor(j, i) };

      if (pixel.mono()) {
        word |= mask;
      }

      mask <<= 1;
      counter++;

      if (counter > Hack::WORD_SIZE - 1) {
        add(word, adr);
        counter = 0;
        word = 0;
        mask = 1;
        adr++;
      }
    }
  }
}
