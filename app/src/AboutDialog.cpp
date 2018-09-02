#include "AboutDialog.hpp"
#include "ui_AboutDialog.h"

#include <QDesktopServices>
#include <QUrl>
#include <QtCore>

#include <utility>

AboutDialog::AboutDialog(QString url, QWidget* parent)
: QDialog{ parent }
, ui{ new Ui::AboutDialog }
, m_url{ std::move(url) } {
  ui->setupUi(this);
  setFixedSize(width(), height());

  connect(ui->btLink, &QPushButton::clicked,
          [this] { QDesktopServices::openUrl(QUrl(m_url, QUrl::TolerantMode)); });

  connect(ui->btOK, &QPushButton::clicked, [this] { AboutDialog::close(); });
}

AboutDialog::~AboutDialog() {
  delete ui;
}
