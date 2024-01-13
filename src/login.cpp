#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>

logIn::logIn(QWidget *parent) : QWidget(parent), ui(new Ui::logIn)
{
    ui->setupUi(this);
    ui->password_LE->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Log In");

    databaseManager = std::make_unique<DatabaseManager>();
    databaseManager->openConnection();
}

logIn::~logIn()
{
    delete ui;
}

QString logIn::hashPassword(const QString &password, const QString &salt) {
    QByteArray passwordWithSalt = (password + salt).toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordWithSalt, QCryptographicHash::Sha256);
    return hashedPassword.toHex();
}

void logIn::on_LogIn_PB_clicked()
{
    QString username = ui->username_LE->text();
    QString password = ui->password_LE->text();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE username = :username");
    qry.bindValue(":username", username);

    if (qry.exec() && qry.next())
    {
        QString hashedPasswordFromDB = qry.value(16).toString();
        QString saltFromDB = qry.value(23).toString();
        QString hashedPasswordToCheck = hashPassword(password, saltFromDB);

        if (hashedPasswordToCheck == hashedPasswordFromDB)
        {
            QString userIBAN = qry.value(20).toString();
            QDate currentDate = QDate::currentDate();
            qry.prepare("UPDATE users SET `Last Active` = :currentDate WHERE username = :username");
            qry.bindValue(":currentDate", currentDate);
            qry.bindValue("username", username);

            if(qry.exec())
            {
                QMessageBox::information(this, "Login Successful", "Welcome to YRT Bank! \n\nYou have successfully logged in.");
                this->hide();
                mainWindow = std::make_unique<MainWindow>(userIBAN, username);
                mainWindow->show();
            }
            else
            {
                QMessageBox::critical(this, "Failure", "Application error please contact us immediately");
                qDebug() << qry.lastError();
            }
        }
        else
        {
            QMessageBox::critical(this, "Failure", "Wrong password or username");
        }
    }
}


void logIn::on_ForgotenPassword_LA_linkActivated(const QString &link)
{
    resetCredentials = std::make_unique<ResetCredentials>();
    this->hide();
    resetCredentials->show();
}

