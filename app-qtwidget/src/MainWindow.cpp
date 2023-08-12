#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <core/Bitmap.h>
#include <core/BitmapToAssembly.h>
#include <core/Hack.h>
#include <core/ImageToBitmap.h>

#include <QFileDialog>
#include <QStandardPaths>
#include <QTemporaryFile>

#include <iostream>

MainWindow::MainWindow( QWidget* parent )
: QMainWindow{ parent }
, ui{ new Ui::MainWindow }
, m_path{ "" }
, m_aboutDlg{ "https://github.com/benvenutti/img2hack", this }
{
    ui->setupUi( this );
    setFixedSize( width(), height() );
    statusBar()->hide();
    enableButtons( false );
    resetControls();

    connect( ui->btOpenImage, SIGNAL( clicked() ), this, SLOT( openImage() ) );
    connect( ui->btCloseImage, SIGNAL( clicked() ), this, SLOT( closeImage() ) );
    connect( ui->btExportToHACK, SIGNAL( clicked() ), this, SLOT( exportToHack() ) );
    connect( ui->btExportToImage, SIGNAL( clicked() ), this, SLOT( exportToImage() ) );
    connect( ui->btInvertImage, SIGNAL( clicked() ), this, SLOT( invertImage() ) );
    connect( ui->btView, SIGNAL( clicked() ), this, SLOT( changeView() ) );

    connect( ui->sliderThreshold, SIGNAL( valueChanged( int ) ), this, SLOT( updateThresholdSlider( int ) ) );

    connect( ui->editThresholdValue, SIGNAL( textChanged( QString ) ), this, SLOT( updateThresholdValue( QString ) ) );

    connect( ui->actionExit, SIGNAL( triggered() ), this, SLOT( close() ) );
    connect( ui->actionAbout, &QAction::triggered, [this]() { m_aboutDlg.exec(); } );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetControls()
{
    ui->sliderThreshold->setValue( 50 );
    ui->editThresholdValue->setText( "50" );
    ui->btInvertImage->setDefault( false );

    m_isOriginalView = false;
    m_negate         = false;
    m_threshold      = 50;
}

void MainWindow::log( QString message )
{
    ui->console->append( message );
}

void MainWindow::logOpenFile( QString fileName )
{
    const QFileInfo info( fileName );
    const QImage    img( info.absoluteFilePath() );

    log( "> File opened: " + info.fileName() );
    log( "  At: " + info.absoluteDir().absolutePath() );

    const int w = img.width();
    const int h = img.height();
    QString   s( "  w: " + QString::number( w ) + " h:" + QString::number( h ) );

    if ( w > Hack::screen_width || h > Hack::screen_height )
    {
        s += " -> cropped to w: ";
        s += QString::number( Hack::screen_width );
        s += " h:" + QString::number( Hack::screen_height );
    }

    log( s );
}

void MainWindow::logExportToHack( QString fileName, QString path, int numLines )
{
    log( "> Exported .ASM file to: " + fileName );
    log( "  At: " + path );
    log( "  Number of HACK instructions: " + QString::number( numLines ) );
}

void MainWindow::logExportToImage( QString fileName, QString path )
{
    log( "> Exported image to: " + fileName );
    log( "  At: " + path );
}

void MainWindow::renderImage()
{
    if ( m_isOriginalView )
    {
        render( m_originalImage );
    }
    else
    {
        processImage();
        auto copy = m_processedImage;
        render( copy );
    }
}

void MainWindow::render( const QImage& image )
{
    ui->label->update();
    ui->label->setPixmap( QPixmap::fromImage( image ) );
}

void MainWindow::processImage()
{
    m_processedImage = m_originalImage;
    m_processedImage.fill( 255 );

    for ( int x = 0; x < m_processedImage.width(); x++ )
    {
        for ( int y = 0; y < m_processedImage.height(); y++ )
        {
            m_processedImage.setPixel(
                x, y, qGray( m_originalImage.pixel( x, y ) ) > m_threshold ? qRgb( 255, 255, 255 ) : qRgb( 0, 0, 0 ) );
        }
    }
}

void MainWindow::enableButtons( bool enable )
{
    ui->sliderThreshold->setEnabled( enable );
    ui->editThresholdValue->setEnabled( enable );
    ui->btInvertImage->setEnabled( enable );
    ui->btExportToHACK->setEnabled( enable );
    ui->btView->setEnabled( enable );
    ui->btExportToImage->setEnabled( enable );
    ui->btCloseImage->setEnabled( enable );

    if ( enable )
    {
        ui->btView->show();
        ui->txtView->show();
        ui->btExportToImage->show();
        ui->btCloseImage->show();
    }
    else
    {
        ui->btView->hide();
        ui->txtView->hide();
        ui->btExportToImage->hide();
        ui->btCloseImage->hide();
    }
}

void MainWindow::invertImage()
{
    m_negate = !m_negate;
    ui->btInvertImage->setDefault( m_negate );
    m_isOriginalView = false;
    renderImage();
}

void MainWindow::updateThresholdSlider( int value )
{
    ui->editThresholdValue->setText( QString::number( value ) );
    m_threshold      = value;
    m_isOriginalView = false;
    renderImage();
}

void MainWindow::openImage()
{
    QFileDialog fileDialog;
    QString     fileName = fileDialog.getOpenFileName( this, tr( "Open Image File" ), m_path, tr( "Files (*.*)" ) );

    if ( fileName.isEmpty() )
        return;

    try
    {
        m_originalImage.load( fileName );
        m_processedImage = m_originalImage;
    }
    catch ( ... )
    {
        log( "> Invalid image file!" );
        return;
    }

    m_inputFile.setFile( fileName );
    m_path = m_inputFile.absoluteDir().absolutePath();
    ui->console->clear();
    logOpenFile( fileName );
    resetControls();
    enableButtons( true );
    ui->editThresholdValue->setFocus();

    m_isOriginalView = false;
    renderImage();
}

void MainWindow::updateThresholdValue( const QString& value )
{
    const int v = value.toInt();

    if ( v > 100 )
    {
        ui->editThresholdValue->setText( "100" );
        m_threshold = 100;
    }
    else if ( v < 0 )
    {
        ui->editThresholdValue->setText( "0" );
        m_threshold = 0;
    }
    else
    {
        m_threshold = v;
    }

    ui->sliderThreshold->setValue( m_threshold );
    m_isOriginalView = false;
    renderImage();
}

void MainWindow::changeView()
{
    m_isOriginalView = !m_isOriginalView;

    if ( m_isOriginalView )
    {
        QIcon icon( ":/icons/edit-find.png" );
        ui->btView->setIcon( icon );
        ui->txtView->setText( "Original" );
    }
    else
    {
        QIcon icon( ":/icons/edit-find-replace.png" );
        ui->btView->setIcon( icon );
        ui->txtView->setText( "Preview" );
    }

    renderImage();
}

void MainWindow::exportToHack()
{
    const auto tempFilePath =
        std::filesystem::path( QStandardPaths::writableLocation( QStandardPaths::TempLocation ).toStdString() )
        / m_inputFile.baseName().toStdString();

    const QFileInfo fileInfo( tempFilePath );

    m_processedImage.save( fileInfo.absoluteFilePath() );

    const auto result = imageToBitmap( tempFilePath );

    if ( std::holds_alternative<Bitmap>( result ) )
    {
        const auto& bitmap = std::get<Bitmap>( result );

        const QString path( m_inputFile.absoluteDir().absolutePath() + "/" + m_inputFile.baseName() + ".asm" );
        std::ofstream outputFile( path.toStdString() );

        const auto numLines = bitmapToAssembly( outputFile, bitmap );

        logExportToHack( m_inputFile.baseName() + ".asm", m_inputFile.absoluteDir().absolutePath(), numLines );

        if ( outputFile.is_open() )
        {
            outputFile.close();
        }
    }
}

void MainWindow::exportToImage()
{
    QString fileName = QFileDialog::getSaveFileName( this, tr( "Save to Image" ), "", tr( "Files (*.*)" ) );

    if ( fileName.isEmpty() )
    {
        return;
    }

    m_processedImage.save( fileName );

    QFileInfo info( fileName );
    logExportToImage( info.baseName() + ".asm", info.absoluteDir().absolutePath() );
}

void MainWindow::closeImage()
{
    ui->console->clear();
    enableButtons( false );
    resetControls();
    ui->label->clear();
    ui->label->setText( "Open an image! =)" );
}
