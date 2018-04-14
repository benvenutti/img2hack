#pragma once

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog {
  Q_OBJECT

public:
  explicit AboutDialog(QString url, QWidget* parent = nullptr);
  ~AboutDialog();

private:
  Ui::AboutDialog* ui;
  QString m_url;
};
