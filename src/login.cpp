#include "login.hpp"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>

logIn::logIn(QWidget *parent) : QWidget(parent), ui(new Ui::logIn)
{
    ui->setupUi(this);
    ui->password_LE->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Log In");

    m_databaseManager = std::make_shared<DatabaseManager>();
    m_databaseManager->OpenConnection();
    m_resetCredentials = std::make_shared<ResetCredentials>(std::shared_ptr<logIn>(this));

}

logIn::~logIn()
{
    delete ui;
}

QString logIn::Hash(const QString &password, const QString &salt) {
    QByteArray passwordWithSalt = (password + salt).toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordWithSalt, QCryptographicHash::Sha256);
    return hashedPassword.toHex();
}

void logIn::on_logIn_PB_clicked()
{
    m_username = ui->username_LE->text();
    QString password = ui->password_LE->text();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", m_username);

    if (qry.exec() && qry.next())
    {

        QString hashedPasswordFromDB = qry.value("Password").toString();

        QString saltFromDB = qry.value("Password Salt").toString();
        QString hashedPasswordToCheck = Hash(password, saltFromDB);
        if (hashedPasswordToCheck == hashedPasswordFromDB)
        {
            QString userIBAN = qry.value("IBAN").toString();
            QDate currentDate = QDate::currentDate();

            qry.prepare("UPDATE users SET `Last Active` = :currentDate WHERE Username = :username");
            qry.bindValue(":currentDate", currentDate);
            qry.bindValue(":username", m_username);

            if(qry.exec())
            {
                QMessageBox::information(this, "Login Successful", "Welcome to YRT Bank! \n\nYou have successfully logged in.");
                this->hide();
                m_mainWindow = std::make_shared<MainWindow>(this, userIBAN, m_username);
                m_mainWindow->show();
                DisplayEventsNotification();
            }
            else
            {
                QMessageBox::critical(this, "Failure", "Application error please contact us immediately");
                qDebug() << qry.lastError();
                qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
                qDebug() << qry.boundValues();  // Print the bound values for further inspection
            }
        }
        else
        {
            QMessageBox::critical(this, "Failure", "Wrong password or username");
            qDebug() << qry.lastError();
            qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
            qDebug() << qry.boundValues();  // Print the bound values for further inspection
        }
    }
    else
    {
        QMessageBox::critical(this, "Failure", "Wrong password or username");
        qDebug() << qry.lastError();
        qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
        qDebug() << qry.boundValues();  // Print the bound values for further inspection
    }
}


void logIn::on_forgotenPassword_LA_linkActivated(const QString &link)
{
    this->hide();
    m_resetCredentials->show();
}

void logIn::DisplayEventsNotification()
{
    QString executablePath = QCoreApplication::applicationDirPath();
    QProcess process;
    QFileInfo executableInfo(executablePath);
    QString sourceFolderPath = executableInfo.absolutePath() + "/../../../YRT/src";

    // Specify the working directory as an argument
    QStringList arguments;
    arguments << "WindowsNotification.py" << m_username;

    // Start the process detached with the specified working directory
    bool success = QProcess::startDetached("C:/Users/boyan/AppData/Local/Programs/Python/Python312/python.exe", arguments, sourceFolderPath);

    if (!success) {
        qDebug() << "Error starting process: " << process.errorString();
    } else {
        qDebug() << "Process started successfully.";
    }
}
