#pragma once

#include <QImage>
#include <QPainter>
#include <QQuickPaintedItem>
#include <QUrl>
#include <QtQml>

class BinaryImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY( QUrl imageUrl READ imageUrl WRITE imageUrl NOTIFY imageUrlChanged )
    Q_PROPERTY( int threshold READ threshold WRITE threshold NOTIFY thresholdChanged )
    QML_ELEMENT

public:
    explicit BinaryImage( QQuickItem* parent = nullptr );

    void paint( QPainter* painter ) override;

    QUrl imageUrl() const;

    void imageUrl( const QUrl& url );

    float threshold() const;

    void threshold( float value );

signals:
    void imageUrlChanged();
    void thresholdChanged();

private:
    void processImage();

    QUrl   m_imageUrl;
    float  m_threshold;
    QImage m_imageOriginal;
    QImage m_imageProcessed;
};
