#include "DrawingCanvas.h"

#include <QColor>

DrawingCanvas::DrawingCanvas( QQuickItem* parent )
: QQuickPaintedItem( parent )
{
}

void DrawingCanvas::paint( QPainter* painter )
{
    if ( !m_imageProcessed.isNull() )
    {
        painter->drawImage( QPoint( 0, 0 ), m_imageProcessed );
    }
}

QUrl DrawingCanvas::imageUrl() const
{
    return m_imageUrl;
}

void DrawingCanvas::imageUrl( const QUrl& url )
{
    if ( url != m_imageUrl )
    {
        m_imageUrl = url;

        m_imageOriginal.load( url.path() );
        m_imageProcessed = QImage( m_imageOriginal.size(), m_imageOriginal.format() );

        emit imageUrlChanged();

        processImage();
        update();
    }
}

int DrawingCanvas::threshold() const
{
    return m_threshold;
}

void DrawingCanvas::threshold( int value )
{
    if ( m_threshold != value )
    {
        m_threshold = value;

        emit thresholdChanged();

        processImage();
        update();
    }
}

void DrawingCanvas::processImage()
{
    constexpr auto white = qRgb( 255, 255, 255 );
    constexpr auto black = qRgb( 0, 0, 0 );

    for ( int x = 0; x < m_imageProcessed.width(); ++x )
    {
        for ( int y = 0; y < m_imageProcessed.height(); ++y )
        {
            m_imageProcessed.setPixel( x, y, qGray( m_imageOriginal.pixel( x, y ) ) > m_threshold ? white : black );
        }
    }
}
