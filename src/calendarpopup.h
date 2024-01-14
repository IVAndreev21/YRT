#ifndef CALENDARPOPUP_H
#define CALENDARPOPUP_H

#include <QWidget>
#include <QMessageBox>

class Calendar;

namespace Ui {
class CalendarPopUp;
}

class CalendarPopUp : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarPopUp(std::shared_ptr<Calendar> Calendar, const QString& username_ref, QWidget *parent = nullptr);
    ~CalendarPopUp();

private slots:
    void on_Save_PB_clicked();

    void on_Abort_PB_clicked();

private:
    Ui::CalendarPopUp *ui;
    QString username;

    std::shared_ptr<Calendar> m_calendar;
};

#endif // CALENDARPOPUP_H
