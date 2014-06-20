#ifndef WRITER_H
#define WRITER_H

#include <inttypes.h>
#include <fstream>
#include <map>
#include <set>

class Writer
{
    public:
        Writer(std::ofstream& output, std::map< int16_t, std::set<int> > words);
        virtual ~Writer();
        int compile();

    private:
        std::ofstream& output;
        std::map< int16_t, std::set<int> > words;
};

#endif
