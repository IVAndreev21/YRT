#include "addheir.hpp"
#include "ui_addheir.h"
#include <QMessageBox>
#include "mainwindow.hpp"
AddHeir::AddHeir(std::shared_ptr<MainWindow> mainwindow, QString& username_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::AddHeir), m_mainwindow(mainwindow)
{
    ui->setupUi(this);
    ui->addHeir_PB->hide();
    ui->enterPass_LA->hide();
    ui->password_LE->hide();
    ui->securityAnswer_LE->hide();
    ui->password_LE->setEchoMode(QLineEdit::Password);
    m_username = username_ref;
}

AddHeir::~AddHeir()
{
    delete ui;
}

void AddHeir::on_heir_LE_editingFinished()
{
    QString heirUsername = ui->heir_LE->text();

    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", heirUsername);

    if (qry.exec() && qry.next()) {
        // Record found
        ui->detected_LA->setText("User " + heirUsername + " has been detected!");
        ui->detected_LA->setStyleSheet("color: rgb(0, 255, 0);");
        ui->password_LE->show();
        ui->enterPass_LA->show();

    } else {
        // No record found
        ui->detected_LA->setText(heirUsername + " not found");
        ui->detected_LA->setStyleSheet("color: rgb(255, 0, 0);");
    }
}


void AddHeir::on_password_LE_editingFinished()
{
    QSqlQuery qry;
    QString password = ui->password_LE->text();
    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", m_username);
    if (qry.exec() && qry.next()) {
        QString hashedPasswordFromDB = qry.value("Password").toString();

        QString saltFromDB = qry.value("Password Salt").toString();
        QString hashedPasswordToCheck = Hash(password, saltFromDB);

        if (hashedPasswordToCheck == hashedPasswordFromDB)
        {
            QString securityQuestion = qry.value("Security Question").toString();
            ui->securityQuestion_LA->setText(securityQuestion);
            ui->securityAnswer_LE->show();
            ui->addHeir_PB->show();
        }
    }
}


QString AddHeir::Hash(const QString& toHash, const QString& salt) {
    QByteArray toHashWithSalt = (toHash + salt).toUtf8();
    QByteArray hashed = QCryptographicHash::hash(toHashWithSalt, QCryptographicHash::Sha256);
    return hashed.toHex();
}


void AddHeir::on_addHeir_PB_clicked()
{
    QSqlQuery qry;
    QString heirUsername = ui->heir_LE->text();

    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", m_username);
    if(qry.exec() && qry.next())
    {
        QString hashedAnswer = Hash(ui->securityAnswer_LE->text(), qry.value("Security Answer Salt").toString());
        QString answerFromDB = qry.value("Security Answer").toString();

        if(answerFromDB == hashedAnswer)
        {
            qry.prepare("UPDATE users SET Heir = :heirUsername WHERE Username = :username");
            qry.bindValue(":username", m_username);
            qry.bindValue(":heirUsername", heirUsername);
            if(qry.exec())
            {
                QMessageBox::information(this, "Heir added", "A heir has successfully been added for your account");
                this->hide();
                m_mainwindow->HeirVerified();
            }
        }
        else
        {
            QMessageBox::critical(this, "Security answer incorrect", "Your answer to the security question don't match");
        }
    }
    else
    {
        QMessageBox::critical(this, "Failure", "Wrong password or username");
    }

}


void AddHeir::on_abort_PB_clicked()
{

    this->hide();
    m_mainwindow->show();
}

