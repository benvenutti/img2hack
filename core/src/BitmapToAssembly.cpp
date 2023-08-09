#include <core/BitmapToAssembly.h>

#include <core/Hack.hpp>

#include <bitset>

namespace
{

constexpr auto comment = "  // word: ";
constexpr auto newl    = "\n";

} // namespace

std::size_t bitmapToAssembly( std::ofstream& out, const Bitmap& bitmap )
{
    std::size_t numOps = 0;

    for ( const auto& w : bitmap )
    {
        const auto word = w.first;

        if ( word == 0 )
        {
            continue;
        }

        const std::bitset<16> bin( word );

        if ( word == -1 || word == 1 )
        {
            out << "D=" << word << comment << bin << newl;
            numOps++;
        }
        else if ( word == -32768 )
        { // TODO magic number?
            out << "@" << ( word * ( -1 ) - 1 ) << comment << bin << newl;
            out << "D=!A" << newl;
            numOps += 2;
        }
        else if ( word < 0 )
        {
            out << "@" << word * ( -1 ) << comment << bin << newl;
            out << "D=-A" << newl;
            numOps += 2;
        }
        else
        {
            out << "@" << word << comment << bin << newl;
            out << "D=A" << newl;
            numOps += 2;
        }

        for ( auto addr : w.second )
        {
            out << "@" << ( Hack::screen_addr + addr ) << newl;
            out << "M=D" << newl;
            numOps += 2;
        }
    }

    out << "(END)" << newl; // does not count as op
    out << "@END" << newl;
    out << "0;JMP" << newl;
    numOps += 2;

    return numOps;
}
