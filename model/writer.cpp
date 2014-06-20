#include "model/writer.h"

#include "model/hack.h"

using namespace std;

Writer::Writer(ofstream& output, map< int16_t, set<int> > words)
:   output(output),
    words(words)
{
}

Writer::~Writer()
{
}

int Writer::compile()
{
    int numOps = 0;

    for (auto w: words) {

        if (w.first == -1 || w.first == 1) {
            output << "D=" << w.first << endl;
            numOps++;
        }
        else if (w.first == 0)
            continue;
        else if (w.first == -32768) {
            output << "@" << (w.first * (-1) - 1) << endl;
            output << "D=!A" << endl;
            numOps += 2;
        }
        else if (w.first < 0){
            output << "@" << w.first * (-1) << endl;
            output << "D=-A" << endl;
            numOps += 2;
        } else {
            output << "@" << w.first << endl;
            output << "D=A" << endl;
            numOps += 2;
        }

        for (auto adr: words.at(w.first)) {
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
