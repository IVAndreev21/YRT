#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QRandomGenerator>
#include <QMessageBox>
#include "databasemanager.hpp"
#include "login.h"
#include "termsandconditions.h"
namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_next1_PB_clicked();

    void on_previous1_PB_clicked();

    void on_next2_PB_clicked();

    void on_previous2_PB_clicked();

    void on_next3_PB_clicked();

    void on_previous3_PB_clicked();

    void on_submit_PB_clicked();

    void on_Terns_and_conditions_stateChanged(int arg1);

private:
    Ui::Register *ui;
    std::unique_ptr<DatabaseManager> m_databaseManager;
    std::unique_ptr<logIn> m_LogIn;
    std::unique_ptr<TermsAndConditions> m_termsAndConditions;
    QSqlDatabase m_db;

    QString generateSalt();
    QString hashPassword(const QString& password, const QString& salt);

    bool m_accepted;
};
#endif // REGISTER_H
