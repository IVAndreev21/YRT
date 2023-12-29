#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>
logIn::logIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::logIn)
{
    ui->setupUi(this);
    this->setWindowTitle("Log In");
    databaseManager = std::make_unique<DatabaseManager>();
    mainWindow = std::make_unique<MainWindow>();
}

logIn::~logIn()
{
    delete ui;
}

void logIn::on_submit_PB_clicked()
{
    QString username = ui->username_LE->text();
    QString password = ui->password_LE->text();
    if (databaseManager->openConnection())
    {
        QSqlDatabase db = databaseManager->getDatabase();
        if (db.isValid() && db.isOpen())
        {
            QSqlQuery qry;
            qry.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
            qry.bindValue(":username", username);
            qry.bindValue(":password", password);
            if(qry.exec())
            {
                while(qry.next())
                {
                    QString usernameFromDB = qry.value(15).toString();
                    QString passworFromDB = qry.value(16).toString();

                    if(username == usernameFromDB && password == passworFromDB)
                    {
                        QMessageBox::information(this, "Login Successful", "Welcome to YRT Bank! \n\nYou have successfully logged in.");
                        this->hide();
                        mainWindow->show();
                    }
                    else
                    {
                        QMessageBox::critical(this, "failure", "Wrong password or useranme");
                    }
                }
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Database is not open or valid.");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "Database connection failed.");
    }
}

