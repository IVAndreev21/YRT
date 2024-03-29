#include "resetcredentials.hpp"
#include "ui_resetcredentials.h"
#include "login.hpp"  // Include the forward declaration of the logIn class

// Constructor
ResetCredentials::ResetCredentials(std::shared_ptr<logIn> login, QWidget* parent)
    : QWidget(parent), ui(new Ui::ResetCredentials), m_LogIn(login)
{
    // Setup UI
    ui->setupUi(this);
    ui->security_question_LE->hide();
    ui->stackedWidget->hide();
    ui->reset_password_PB->hide();
    ui->reset_username_PB->hide();
    ui->confirm_password_LE->setEchoMode(QLineEdit::Password);
}

// Destructor
ResetCredentials::~ResetCredentials()
{
    delete ui;
}

// Handle email line edit editing finished event
void ResetCredentials::on_email_LE_editingFinished()
{
    QString email = ui->email_LE->text();
    qDebug() << email;

    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE Email = :email");
    qry.bindValue(":email", email);

    if (qry.exec() && qry.next()) {
        // Record found
        ui->email_verified_LA->setText("User with email " + email + " has been detected!");
        ui->email_verified_LA->setStyleSheet("color: rgb(0, 255, 0);");
        ui->security_question_LA->setText(qry.value(17).toString());
        ui->security_question_LE->show();

        m_SQSalt = qry.value(22).toString();
        qDebug() << m_SQSalt;

    } else {
        // No record found
        ui->email_verified_LA->setText("No user found with email " + email);
        ui->email_verified_LA->setStyleSheet("color: rgb(255, 0, 0);");
        ui->security_question_LE->hide(); // Assuming you want to hide the security question if no record is found
    }
}

// Hash function for security answer
QString ResetCredentials::Hash(const QString& answer, const QString& salt)
{
    QByteArray answerWithSalt = (answer + salt).toUtf8();
    QByteArray hashedAnswer = QCryptographicHash::hash(answerWithSalt, QCryptographicHash::Sha256);
    return hashedAnswer.toHex();
}

// Handle security question line edit editing finished event
void ResetCredentials::on_security_question_LE_editingFinished()
{
    QSqlQuery qry;
    QString email = ui->email_LE->text();
    qry.prepare("SELECT * FROM users WHERE Email = :email");
    qry.bindValue(":email", email);
    if(qry.exec() && qry.next())
    {
        QString hashedAnswer = Hash(ui->security_question_LE->text(), qry.value(26).toString());
        QString answerFromDB = qry.value(18).toString();

        if(answerFromDB == hashedAnswer)
        {
            ui->reset_password_PB->show();
            ui->reset_username_PB->show();
        }
        else
        {
            QMessageBox::critical(this, "Security answer incorrect", "Your answer to the security question doesn't match");
        }
    }
}

// Handle reset password button clicked event
void ResetCredentials::on_reset_password_PB_clicked()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(0);
}

// Handle reset username button clicked event
void ResetCredentials::on_reset_username_PB_clicked()
{
    ui->stackedWidget->show();
    ui->stackedWidget->setCurrentIndex(1);
}

// Handle confirm password button clicked event
void ResetCredentials::on_confirm_password_PB_clicked()
{
    QSqlQuery qry;
    if(ui->new_password_LE->text() == ui->confirm_password_LE->text())
    {
        QString email = ui->email_LE->text();
        QString password = ui->new_password_LE->text();

        qry.prepare("SELECT * FROM users WHERE email = :email");
        qry.bindValue(":email", email);
        if(qry.exec() && qry.next())
        {
            QString salt = qry.value(23).toString();
            QString hashedPassword = Hash(password, salt);

            qry.prepare("UPDATE users SET Password = :password WHERE email = :email");
            qry.bindValue(":email", email);
            qry.bindValue(":password", hashedPassword);
            if(qry.exec())
            {
                QMessageBox::information(this, "Password reset", "Your password has been reset");
            }
        }
        else
        {
            QMessageBox::critical(this, "Data not inserted", "Data was not inserted correctly. Please contact us immediately");
            qDebug() << qry.lastError().text();
            qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
            qDebug() << qry.boundValues();  // Print the bound values for further inspection
        }
    }
    else
    {
        QMessageBox::critical(this, "Password don't match", "Your passwords don't match");
    }
}

// Handle confirm username button clicked event
void ResetCredentials::on_confirm_username_PB_clicked()
{
    QSqlQuery qry;
    QString username = ui->new_username_LE->text();
    QString email = ui->email_LE->text();

    qry.prepare("SELECT * FROM users WHERE email = :email");
    qry.bindValue(":email", email);
    if(qry.exec() && qry.next())
    {
        qry.prepare("UPDATE users SET Username = :username WHERE email = :email");
        qry.bindValue(":username", username);
        qry.bindValue(":email", email);
        if(qry.exec())
        {
            QMessageBox::information(this, "Username reset", "Your username has been reset");
            this->hide();
            m_LogIn->show();
            qDebug() << qry.lastError().text();
            qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
            qDebug() << qry.boundValues();  // Print the bound values for further inspection
        }
    }
    else
    {
        QMessageBox::critical(this, "Data not inserted", "Data was not inserted correctly. Please contact us immediately");
        qDebug() << qry.lastError().text();
        qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
        qDebug() << qry.boundValues();  // Print the bound values for further inspection
    }
}

// Handle back button clicked event
void ResetCredentials::on_back_PB_clicked()
{
    this->hide();
    m_LogIn->show();
}
