#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class logIn;
}

class logIn : public QWidget
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = nullptr);
    ~logIn();

private:
    Ui::logIn *ui;
};

#endif // LOGIN_H
