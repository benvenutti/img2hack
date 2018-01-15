#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog {
  Q_OBJECT

public:
  explicit AboutDialog(QString url, QWidget* parent = 0);
  ~AboutDialog();

private slots:
  void on_btLink_clicked();
  void on_btOK_clicked();

private:
  Ui::AboutDialog* ui;
  QString url;
};

#endif // ABOUTDIALOG_H
