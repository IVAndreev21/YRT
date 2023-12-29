#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QRandomGenerator>
#include <QMessageBox>
#include "databasemanager.hpp"
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

private:
    Ui::Register *ui;
    std::unique_ptr<DatabaseManager> databaseManager;
};

#endif // REGISTER_H
