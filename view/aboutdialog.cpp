#include "view/aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QDesktopServices>
#include <QtCore>
#include <QUrl>

AboutDialog::AboutDialog(QString url, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog),
    url(url)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_btLink_clicked()
{
    QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}

void AboutDialog::on_btOK_clicked()
{
    AboutDialog::close();
}
