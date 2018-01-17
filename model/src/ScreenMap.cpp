#include "ScreenMap.hpp"

#include "Hack.hpp"

using namespace Magick;
using namespace std;

ScreenMap::ScreenMap(Image img)
: image(img) {
  readImage();
}

void ScreenMap::add(int16_t word, int address) {
  auto it = words.find(word);

  if (it != words.end())
    words.at(word).insert(address);
  else {
    set<int> s;
    s.insert(address);
    words.insert(pair<int16_t, set<int>>(word, s));
  }
}

map<int16_t, set<int>> ScreenMap::getMap() {
  return words;
}

void ScreenMap::readImage() {
  int counter = 0;
  int16_t word = 0;
  uint16_t mask = 1;
  int adr = 0;

  for (int i = 0; i < Hack::SCREEN_HEIGHT; ++i) {
    for (int j = 0; j < Hack::SCREEN_WIDTH; ++j) {

      ColorRGB c(image.pixelColor(j, i));

      if (c.red() * QuantumRange == 0) {
        word = word | mask;
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
