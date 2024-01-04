#ifndef CRYPTO_H
#define CRYPTO_H

#include <QWidget>

namespace Ui {
class Crypto;
}

class Crypto : public QWidget
{
    Q_OBJECT

public:
    explicit Crypto(QWidget *parent = nullptr);
    ~Crypto();

private:
    Ui::Crypto *ui;
};

#endif // CRYPTO_H
