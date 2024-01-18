#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "databasemanager.hpp"
#include "mainwindow.h"
#include "resetcredentials.h"
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

    void on_ForgotenPassword_LA_linkActivated(const QString &link);

private:
    Ui::logIn *ui;
    std::shared_ptr<DatabaseManager> m_databaseManager;
    std::shared_ptr<MainWindow> m_mainWindow;
    std::shared_ptr<ResetCredentials> m_resetCredentials;

    QString Hash(const QString &password, const QString &salt);
};
#endif // LOGIN_H
