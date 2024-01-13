#include "addheir.h"
#include "ui_addheir.h"
#include <QMessageBox>
AddHeir::AddHeir(QString& username_ref, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddHeir)
{
    ui->setupUi(this);
    ui->addHeir_PB->hide();
    ui->enterPass_LA->hide();
    ui->password_LE->hide();

    username = username_ref;
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
    qry.bindValue(":username", username);
    if (qry.exec() && qry.next()) {
        QString hashedPasswordFromDB = qry.value(16).toString();

        QString saltFromDB = qry.value(23).toString();
        QString hashedPasswordToCheck = hash(password, saltFromDB);

        if (hashedPasswordToCheck == hashedPasswordFromDB)
        {
            QString securityQuestion = qry.value(17).toString();
            ui->securityQuestion_LA->setText(securityQuestion);
            ui->securityAnswer_LE->show();
            ui->addHeir_PB->show();
        }
    }
}


QString AddHeir::hash(const QString& toHash, const QString& salt) {
    QByteArray toHashWithSalt = (toHash + salt).toUtf8();
    QByteArray hashed = QCryptographicHash::hash(toHashWithSalt, QCryptographicHash::Sha256);
    return hashed.toHex();
}


void AddHeir::on_addHeir_PB_clicked()
{
    QSqlQuery qry;
    QString heirUsername = ui->heir_LE->text();

    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", username);
    if(qry.exec() && qry.next())
    {
        QString hashedAnswer = hash(ui->securityAnswer_LE->text(), qry.value(26).toString());
        QString answerFromDB = qry.value(18).toString();

        if(answerFromDB == hashedAnswer)
        {
            qry.prepare("UPDATE users SET Heir = :heirUsername WHERE Username = :username");
            qry.bindValue(":username", username);
            qry.bindValue(":heirUsername", heirUsername);
            if(qry.exec())
            {
                QMessageBox::information(this, "success", "success");
            }
        }
        else
        {
            QMessageBox::critical(this, "Security answer incorrect", "Your answer to the security question don't match");
        }
    }
}

