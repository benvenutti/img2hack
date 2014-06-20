#ifndef SCREENMAP_H
#define SCREENMAP_H

#include <inttypes.h>
#include <Magick++.h>
#include <map>
#include <set>

class ScreenMap
{
public:
    ScreenMap(Magick::Image img);
    void add(int16_t word, int address);
    std::map< int16_t, std::set<int> > getMap();

private:
    void readImage();

    Magick::Image image;
    std::map< int16_t, std::set<int> > words;

};

#endif // SCREENMAP_H
