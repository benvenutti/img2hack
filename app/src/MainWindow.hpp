#pragma once

#include "AboutDialog.hpp"

#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QPixmap>
#include <QString>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow();

private slots:
    void openImage();
    void closeImage();
    void invertImage();
    void updateThresholdValue( const QString& value );
    void updateThresholdSlider( int value );
    void exportToHack();
    void changeView();
    void exportToImage();

private:
    void processImage();
    void renderImage();
    void render( const QImage& image );
    void log( QString message );
    void logExportToHack( QString filaName, QString m_path, int numLines );
    void logExportToImage( QString filaName, QString m_path );
    void logOpenFile( QString fileName );
    void resetControls();
    void enableButtons( bool enable );

    Ui::MainWindow* ui;

    QImage m_originalImage;
    QImage m_processedImage;

    QFileInfo m_inputFile;
    QPixmap   m_pixmap; // TODO: remove?
    QString   m_path;

    AboutDialog m_aboutDlg;

    bool m_isOriginalView;
    bool m_negate;
    int  m_threshold;
};
