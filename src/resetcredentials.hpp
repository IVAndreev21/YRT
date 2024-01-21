#pragma once

#include <QWidget>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlError>

class logIn;

namespace Ui {
class ResetCredentials;
}

class ResetCredentials : public QWidget
{
    Q_OBJECT

public:
    explicit ResetCredentials(std::shared_ptr<logIn> login, QWidget *parent = nullptr);
    ~ResetCredentials();

private slots:
    void on_email_LE_editingFinished();

    void on_security_question_LE_editingFinished();

    void on_reset_username_PB_clicked();

    void on_reset_password_PB_clicked();

    void on_confirm_password_PB_clicked();

    void on_confirm_username_PB_clicked();

    void on_back_PB_clicked();

private:
    Ui::ResetCredentials *ui;

    QString Hash(const QString& asnwer, const QString& salt);
    QString m_SQSalt;

    std::shared_ptr<logIn> m_LogIn;
};
