#pragma once

#include <QWidget>
#include <QDebug>
#include <QCalendarWidget>
#include <QSqlQuery>
#include <QTextCharFormat>
#include "calendarpopup.hpp"

class MainWindow;

namespace Ui {
class Calendar;
}

class Calendar : public QWidget
{
    Q_OBJECT

public:
    Calendar(std::shared_ptr<MainWindow> mainwindow, const QString& username_ref, QWidget* parent = nullptr);
    ~Calendar();
    void fetchEvents();

private slots:
    void on_calendarWidget_clicked(const QDate& date);
    void on_back_PB_clicked();

    void on_makeEvent_PB_clicked();

private:
    Ui::Calendar* ui;
    std::unique_ptr<CalendarPopUp> m_calendarPopUp;
    QString m_username;
    QCalendarWidget* m_calendar;
    std::shared_ptr<MainWindow> m_mainWindow;
    void DisplayEvents();
};
