#include "AboutDialog.hpp"
#include "ui_AboutDialog.h"

#include <QDesktopServices>
#include <QUrl>
#include <QtCore>

AboutDialog::AboutDialog(QString url, QWidget* parent)
: QDialog(parent)
, ui(new Ui::AboutDialog)
, url(url) {
  ui->setupUi(this);
  setFixedSize(this->width(), this->height());
}

AboutDialog::~AboutDialog() {
  delete ui;
}

void AboutDialog::on_btLink_clicked() {
  QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}

void AboutDialog::on_btOK_clicked() {
  AboutDialog::close();
}
