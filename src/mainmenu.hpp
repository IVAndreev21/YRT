#pragma once

#include <QWidget>
#include <QMainWindow>
#include "login.hpp"
#include "register.hpp"
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
