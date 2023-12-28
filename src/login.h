#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "databasemanager.hpp"
namespace Ui {
class logIn;
}

class logIn : public QWidget
{
    Q_OBJECT

public:
    explicit logIn(QWidget *parent = nullptr);
    ~logIn();

private slots:
    void on_submit_PB_clicked();

private:
    Ui::logIn *ui;
    std::unique_ptr<DatabaseManager> databaseManager;
};
#endif // LOGIN_H
