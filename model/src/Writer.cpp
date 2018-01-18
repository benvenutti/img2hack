#include "Writer.hpp"

#include "Hack.hpp"
#include "ScreenMap.hpp"

#include <bitset>
#include <string>

Writer::Writer(std::ofstream& output, const ScreenMap& screenMap)
: m_output(output)
, m_screenMap(screenMap) {}

int Writer::compile() {
  int numOps = 0;

  for (auto w : m_screenMap) {

    std::bitset<16> bin(w.first);
    std::string comment("\t// word: ");

    if (w.first == -1 || w.first == 1) {
      m_output << "D=" << w.first << comment << bin << std::endl;
      numOps++;
    } else if (w.first == 0)
      continue;
    else if (w.first == -32768) {
      m_output << "@" << (w.first * (-1) - 1) << comment << bin << std::endl;
      m_output << "D=!A" << std::endl;
      numOps += 2;
    } else if (w.first < 0) {
      m_output << "@" << w.first * (-1) << comment << bin << std::endl;
      m_output << "D=-A" << std::endl;
      numOps += 2;
    } else {
      m_output << "@" << w.first << comment << bin << std::endl;
      m_output << "D=A" << std::endl;
      numOps += 2;
    }

    for (auto adr : w.second) {
      m_output << "@" << (Hack::SCREEN_ADR + adr) << std::endl;
      m_output << "M=D" << std::endl;
      numOps += 2;
    }
  }

  m_output << "(END)" << std::endl; // does not count as op
  m_output << "@END" << std::endl;
  m_output << "0;JMP" << std::endl;
  numOps += 2;

  return numOps;
}
