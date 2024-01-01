#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QMainWindow>
#include "login.h"
#include "register.h"
#include "mainwindow.h"
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
    void on_LogIn_PB_clicked();

    void on_Register_PB_clicked();

private:
    Ui::MainMenu *ui;
    logIn* logInWindow;
    Register* registerWindow;
    MainWindow* mainWindow;

};

#endif // MAINMENU_H
