#ifndef CALENDARPOPUP_H
#define CALENDARPOPUP_H

#include <QWidget>
#include "databasemanager.hpp"
namespace Ui {
class CalendarPopUp;
}

class CalendarPopUp : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarPopUp(QWidget *parent = nullptr);
    ~CalendarPopUp();

private slots:
    void on_Save_PB_clicked();

private:
    Ui::CalendarPopUp *ui;
};

#endif // CALENDARPOPUP_H
