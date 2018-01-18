#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <iostream>

#include "AboutDialog.hpp"
#include "model/Hack.hpp"
#include "model/ScreenMap.hpp"
#include "model/Writer.hpp"

using namespace Magick;

MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
, path("") {
  ui->setupUi(this);
  setFixedSize(this->width(), this->height());
  statusBar()->hide();
  enableButtons(false);
  resetControls();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::resetControls() {
  ui->sliderThreshold->setValue(50);
  ui->editThresholdValue->setText("50");
  ui->btInvertImage->setDefault(false);

  isOriginalView = false;
  negate = false;
  threshold = 50;
}

void MainWindow::log(QString message) {
  ui->console->append(message);
}

void MainWindow::logOpenFile(QString fileName) {
  QFileInfo info(fileName);
  Image img(info.absoluteFilePath().toStdString());

  log("> File opened: " + info.fileName());
  log("  At: " + info.absoluteDir().absolutePath());

  int w = img.columns();
  int h = img.rows();
  QString s("  w: " + QString::number(w) + " h:" + QString::number(h));

  if (w > Hack::SCREEN_WIDTH || h > Hack::SCREEN_HEIGHT) {
    s += " -> cropped to w: ";
    s += QString::number(Hack::SCREEN_WIDTH);
    s += " h:" + QString::number(Hack::SCREEN_HEIGHT);
  }

  log(s);
}

void MainWindow::logExportToHack(QString fileName, QString path, int numLines) {
  log("> Exported .ASM file to: " + fileName);
  log("  At: " + path);
  log("  Number of HACK instructions: " + QString::number(numLines));
}

void MainWindow::logExportToImage(QString fileName, QString path) {
  log("> Exported image to: " + fileName);
  log("  At: " + path);
}

void MainWindow::renderImage() {
  if (isOriginalView) {
    pixmap.loadFromData((char*)blobOriginal.data(), "XPM");
  } else {
    processImage();
    pixmap.loadFromData((char*)blobProcessed.data(), "XPM");
  }

  ui->label->setPixmap(pixmap);
}

void MainWindow::processImage() {
  Image img = image;
  double th = (threshold / 100.0) * QuantumRange;
  img.threshold(th);

  if (negate)
    img.negate();

  img.write(&blobProcessed, "XPM");
}

void MainWindow::enableButtons(bool enable) {
  ui->sliderThreshold->setEnabled(enable);
  ui->editThresholdValue->setEnabled(enable);
  ui->btInvertImage->setEnabled(enable);
  ui->btExportToHACK->setEnabled(enable);
  ui->btView->setEnabled(enable);
  ui->btExportToImage->setEnabled(enable);
  ui->btCloseImage->setEnabled(enable);

  if (enable) {
    ui->btView->show();
    ui->txtView->show();
    ui->btExportToImage->show();
    ui->btCloseImage->show();
  } else {
    ui->btView->hide();
    ui->txtView->hide();
    ui->btExportToImage->hide();
    ui->btCloseImage->hide();
  }
}

void MainWindow::on_btInvertImage_clicked() {
  negate = !negate;
  ui->btInvertImage->setDefault(negate);
  isOriginalView = false;
  renderImage();
}

void MainWindow::on_sliderThreshold_valueChanged(int value) {
  ui->editThresholdValue->setText(QString::number(value));
  threshold = value;
  isOriginalView = false;
  renderImage();
}

void MainWindow::on_btOpenImage_clicked() {
  QFileDialog fileDialog;
  QString fileName =
      fileDialog.getOpenFileName(this, tr("Open Image File"), path, tr("Files (*.*)"));

  if (fileName.isEmpty())
    return;

  Geometry geometry(Hack::SCREEN_WIDTH, Hack::SCREEN_HEIGHT);
  image.size(geometry);

  try {
    Image imgTmp(fileName.toStdString());
    image.composite(imgTmp, 0, 0);
    image.write(&blobOriginal, "XPM");
  } catch (...) {
    log("> Invalid image file!");
    return;
  }

  inputFile.setFile(fileName);
  path = inputFile.absoluteDir().absolutePath();
  ui->console->clear();
  logOpenFile(fileName);
  resetControls();
  enableButtons(true);
  ui->editThresholdValue->setFocus();

  isOriginalView = false;
  renderImage();
}

void MainWindow::on_editThresholdValue_textChanged(const QString& arg1) {
  QRegExp re("\\d*");

  if (!re.exactMatch(arg1)) {
    QString val = arg1.left(arg1.length() - 1);
    ui->editThresholdValue->setText(val);
    return;
  }

  int value = arg1.toInt();

  if (value > 100) {
    ui->editThresholdValue->setText("100");
    threshold = 100;
  } else if (value < 0) {
    ui->editThresholdValue->setText("0");
    threshold = 0;
  } else
    threshold = value;

  ui->sliderThreshold->setValue(threshold);
  isOriginalView = false;
  renderImage();
}

void MainWindow::on_btView_clicked() {
  isOriginalView = !isOriginalView;

  if (isOriginalView) {
    QIcon icon(":/icons/icons/edit-find.png");
    ui->btView->setIcon(icon);
    ui->txtView->setText("Original");
  } else {
    QIcon icon(":/icons/icons/edit-find-replace.png");
    ui->btView->setIcon(icon);
    ui->txtView->setText("Preview");
  }

  renderImage();
}

void MainWindow::on_actionOpen_triggered() {
  on_btOpenImage_clicked();
}

void MainWindow::on_actionExport_triggered() {
  on_btExportToHACK_clicked();
}

void MainWindow::on_actionExit_triggered() {
  this->close();
}

void MainWindow::on_actionAbout_triggered() {
  AboutDialog aboutDialog("https://github.com/benvenutti/img2hack", this);
  aboutDialog.exec();
}

void MainWindow::on_btExportToHACK_clicked() {
  Image img(blobProcessed);
  ScreenMap screenMap(img);

  QString path(inputFile.absoluteDir().absolutePath() + "/" + inputFile.baseName() + ".asm");
  std::ofstream outputFile(path.toStdString());

  Writer writer(outputFile, screenMap);
  int numLines = writer.compile();

  logExportToHack(inputFile.baseName() + ".asm", inputFile.absoluteDir().absolutePath(), numLines);

  if (outputFile.is_open())
    outputFile.close();
}

void MainWindow::on_btExportToImage_clicked() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save to Image"), "", tr("Files (*.*)"));

  if (fileName.isEmpty())
    return;

  Image img(blobProcessed);
  img.write(fileName.toStdString());

  QFileInfo info(fileName);
  logExportToImage(info.baseName() + ".asm", info.absoluteDir().absolutePath());
}

void MainWindow::on_btCloseImage_clicked() {
  ui->console->clear();
  enableButtons(false);
  resetControls();
  ui->label->clear();
  ui->label->setText("Open an image! =)");
}
