#include "writer.h"

#include <bitset>
#include <string>

#include "hack.h"

using namespace std;

Writer::Writer(ofstream& output, map<int16_t, set<int>> words)
: output(output)
, words(words) {}

Writer::~Writer() {}

int Writer::compile() {
  int numOps = 0;

  for (auto w : words) {

    bitset<16> bin(w.first);
    string comment("\t// word: ");

    if (w.first == -1 || w.first == 1) {
      output << "D=" << w.first << comment << bin << endl;
      numOps++;
    } else if (w.first == 0)
      continue;
    else if (w.first == -32768) {
      output << "@" << (w.first * (-1) - 1) << comment << bin << endl;
      output << "D=!A" << endl;
      numOps += 2;
    } else if (w.first < 0) {
      output << "@" << w.first * (-1) << comment << bin << endl;
      output << "D=-A" << endl;
      numOps += 2;
    } else {
      output << "@" << w.first << comment << bin << endl;
      output << "D=A" << endl;
      numOps += 2;
    }

    for (auto adr : words.at(w.first)) {
      output << "@" << (HACK::SCREEN_ADR + adr) << endl;
      output << "M=D" << endl;
      numOps += 2;
    }
  }

  output << "(END)" << endl; // does not count as op
  output << "@END" << endl;
  output << "0;JMP" << endl;
  numOps += 2;

  return numOps;
}
