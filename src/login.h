#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "databasemanager.hpp"
#include "mainwindow.h"
namespace Ui {
class logIn;
}

class logIn : public QWidget
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = nullptr);
    ~logIn();

private slots:
    void on_LogIn_PB_clicked();

private:
    Ui::logIn *ui;
    std::unique_ptr<DatabaseManager> databaseManager;
    std::unique_ptr<MainWindow> mainWindow;
    QString hashPassword(const QString &password, const QString &salt);
};
#endif // LOGIN_H
