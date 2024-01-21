#pragma once
#include <QWidget>
#include <QProcess>
#include "databasemanager.hpp"
#include "mainwindow.hpp"
#include "resetcredentials.hpp"
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
    void on_logIn_PB_clicked();

    void on_forgotenPassword_LA_linkActivated(const QString &link);

private:
    Ui::logIn *ui;
    std::shared_ptr<DatabaseManager> m_databaseManager;
    std::shared_ptr<MainWindow> m_mainWindow;
    std::shared_ptr<ResetCredentials> m_resetCredentials;

    QString Hash(const QString &password, const QString &salt);

    void DisplayEventsNotification();

    QString m_username;

};
