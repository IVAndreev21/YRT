#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QMainWindow>
#include "login.h"
#include "register.h"
namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_logIn_PB_clicked();

    void on_register_PB_clicked();

private:
    Ui::MainMenu *ui;
    logIn* logInWindow;
    Register* registerWindow;
};

#endif // MAINMENU_H
