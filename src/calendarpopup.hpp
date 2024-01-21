#pragma once

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
    CalendarPopUp(std::shared_ptr<Calendar> Calendar, const QString& username_ref, QWidget *parent = nullptr);
    ~CalendarPopUp();

private slots:
    void on_save_PB_clicked();

    void on_abort_PB_clicked();

private:
    Ui::CalendarPopUp *ui;
    QString m_username;

    std::shared_ptr<Calendar> m_calendar;
};

