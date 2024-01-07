#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QDebug>
#include <QCalendarWidget>
#include <QSqlQuery>
#include "calendarpopup.h"
namespace Ui {
class Calendar;
}

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar(const QString& username_ref, QWidget *parent = nullptr);
    ~Calendar();

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::Calendar *ui;
    std::unique_ptr<CalendarPopUp> calendarPopUp;
    QString username;

    QCalendarWidget* calendar;
};

#endif // CALENDAR_H
