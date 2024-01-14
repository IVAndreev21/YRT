#ifndef CRYPTO_H
#define CRYPTO_H

#include <QWidget>

class MainWindow;

namespace Ui {
class Crypto;
}

class Crypto : public QWidget
{
    Q_OBJECT

public:
    explicit Crypto(std::shared_ptr<MainWindow> mainwindow, QWidget *parent = nullptr);
    ~Crypto();

private slots:
    void on_back_PB_clicked();

private:
    Ui::Crypto *ui;

    std::shared_ptr<MainWindow> m_mainWindow;
};

#endif // CRYPTO_H
