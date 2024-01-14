#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QDebug>
#include <QCalendarWidget>
#include <QSqlQuery>
#include <QTextCharFormat>
#include "calendarpopup.h"

class MainWindow;

namespace Ui {
class Calendar;
}

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar(std::shared_ptr<MainWindow> mainwindow, const QString& username_ref, QWidget *parent = nullptr);
    ~Calendar();
    void fetchEvents();

private slots:
    void on_calendarWidget_clicked(const QDate &date);
    void on_back_PB_clicked();

    void on_makeEvent_PB_clicked();

private:
    Ui::Calendar *ui;
    std::unique_ptr<CalendarPopUp> calendarPopUp;
    QString username;
    QCalendarWidget* calendar;
    std::shared_ptr<MainWindow> mainWindow;
    void displayEvents();

    const QDate selectedDate;
};

#endif // CALENDAR_H
