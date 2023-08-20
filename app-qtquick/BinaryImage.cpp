#include "BinaryImage.h"

#include <QColor>

BinaryImage::BinaryImage( QQuickItem* parent )
: QQuickPaintedItem( parent )
{
}

void BinaryImage::paint( QPainter* painter )
{
    if ( !m_imageProcessed.isNull() )
    {
        painter->drawImage( QPoint( 0, 0 ), m_imageProcessed );
    }
}

QUrl BinaryImage::imageUrl() const
{
    return m_imageUrl;
}

void BinaryImage::imageUrl( const QUrl& url )
{
    if ( url != m_imageUrl )
    {
        m_imageUrl = url;

        m_imageOriginal.load( url.path() );
        m_imageProcessed = QImage( m_imageOriginal.size(), m_imageOriginal.format() );

        setWidth( m_imageProcessed.width() );
        setHeight( m_imageProcessed.height() );

        processImage();
        update();

        emit imageUrlChanged();
    }
}

float BinaryImage::threshold() const
{
    return m_threshold;
}

void BinaryImage::threshold( float value )
{
    if ( m_threshold != value )
    {
        m_threshold = value;

        emit thresholdChanged();

        processImage();
        update();
    }
}

bool BinaryImage::invert() const
{
    return m_invert;
}

void BinaryImage::invert( bool value )
{
    if ( m_invert != value )
    {
        m_invert = value;

        emit invertChanged();

        m_imageProcessed.invertPixels();
        update();
    }
}

void BinaryImage::processImage()
{
    constexpr auto white = qRgb( 255, 255, 255 );
    constexpr auto black = qRgb( 0, 0, 0 );

    const auto pixelOn  = m_invert ? white : black;
    const auto pixelOff = m_invert ? black : white;

    const auto limit = static_cast<int>( m_threshold * 255 / 100.0f );

    const auto width  = m_imageProcessed.width();
    const auto height = m_imageProcessed.height();

    for ( int x = 0; x < width; ++x )
    {
        for ( int y = 0; y < height; ++y )
        {
            m_imageProcessed.setPixel( x, y, qGray( m_imageOriginal.pixel( x, y ) ) > limit ? pixelOff : pixelOn );
        }
    }
}
