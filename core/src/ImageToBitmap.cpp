#include <core/ImageToBitmap.h>

#include <core/Hack.h>

#include <QFileInfo>
#include <QImage>

namespace
{

void addWord( Bitmap& bitmap, const std::int16_t word, const int address )
{
    if ( bitmap.find( word ) != bitmap.end() )
    {
        bitmap.at( word ).insert( address );
    }
    else
    {
        bitmap.emplace( word, std::set<int>{ address } );
    }
}

} // namespace

Result imageToBitmap( const std::filesystem::path& pathToImage )
{
    std::error_code errorCode;

    if ( !std::filesystem::exists( pathToImage, errorCode ) )
    {
        return Error::file_does_not_exit;
    }

    const QFileInfo fileInfo( pathToImage );
    const QImage    image( fileInfo.absoluteFilePath() );

    if ( image.isNull() )
    {
        return Error::file_is_not_an_image;
    }

    Bitmap        bitmap;
    int           counter = 0;
    std::int16_t  word    = 0;
    std::uint16_t mask    = 1;
    int           adr     = 0;

    for ( int y = 0; y < Hack::screen_height; ++y )
    {
        for ( int x = 0; x < Hack::screen_width; ++x )
        {
            if ( image.valid( x, y ) )
            {
                const auto     pixel = image.pixel( x, y );
                constexpr auto white = QRgb( 0xffffffff );

                if ( pixel != white )
                {
                    word |= mask;
                }
            }

            mask <<= 1;
            counter++;

            if ( counter > Hack::word_size - 1 )
            {
                addWord( bitmap, word, adr );
                counter = 0;
                word    = 0;
                mask    = 1;
                adr++;
            }
        }
    }

    return std::move( bitmap );
}
