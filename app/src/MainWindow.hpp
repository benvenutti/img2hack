#pragma once

#include <QFileInfo>
#include <QMainWindow>

#include <Magick++.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_btInvertImage_clicked();
  void on_sliderThreshold_valueChanged(int value);
  void on_btOpenImage_clicked();
  void on_btExportToHACK_clicked();
  void on_editThresholdValue_textChanged(const QString& arg1);

  void on_actionAbout_triggered();
  void on_actionOpen_triggered();
  void on_actionExport_triggered();
  void on_actionExit_triggered();

  void on_btView_clicked();
  void on_btCloseImage_clicked();
  void on_btExportToImage_clicked();

private:
  void processImage();
  void renderImage();
  void render(Magick::Image& image);
  void log(QString message);
  void logExportToHack(QString filaName, QString path, int numLines);
  void logExportToImage(QString filaName, QString path);
  void logOpenFile(QString fileName);
  void resetControls();
  void enableButtons(bool enable);

  Ui::MainWindow* ui;

  Magick::Image m_originalImage;
  Magick::Image m_processedImage;

  QPixmap pixmap;
  QFileInfo inputFile;
  QString path;

  bool isOriginalView;
  bool negate;
  int threshold;
};
