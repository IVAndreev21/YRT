#pragma once

#include <QWidget>
#include <QRandomGenerator>
#include <QMessageBox>
#include "databasemanager.hpp"
#include "login.hpp"
#include "termsandconditions.hpp"
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

    void on_terms_and_conditions_stateChanged(int arg1);

private:
    Ui::Register *ui;
    std::unique_ptr<DatabaseManager> m_databaseManager;
    std::unique_ptr<logIn> m_LogIn;
    std::unique_ptr<TermsAndConditions> m_termsAndConditions;
    QSqlDatabase m_db;

    QString GenerateSalt();
    QString Hash(const QString& password, const QString& salt);

    bool m_accepted;
};
