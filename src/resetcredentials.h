#ifndef RESETCREDENTIALS_H
#define RESETCREDENTIALS_H

#include <QWidget>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlError>
namespace Ui {
class ResetCredentials;
}

class ResetCredentials : public QWidget
{
    Q_OBJECT

public:
    explicit ResetCredentials(QWidget *parent = nullptr);
    ~ResetCredentials();

private slots:
    void on_Email_LE_editingFinished();

    void on_security_question_LE_editingFinished();

    void on_reset_username_PB_clicked();

    void on_reset_password_PB_clicked();

    void on_confirm_password_PB_clicked();

    void on_confirm_username_PB_clicked();

private:
    Ui::ResetCredentials *ui;

    QString hashSecurityQuestion(const QString& asnwer, const QString& salt);
    QString SQSalt;
};

#endif // RESETCREDENTIALS_H
