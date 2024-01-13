#include "calendar.h"
#include "ui_calendar.h"
#include <QTextCharFormat>
#include "mainwindow.h"

Calendar::Calendar(std::shared_ptr<MainWindow> mainwindow, const QString& username_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::Calendar), mainWindow(mainwindow)
{
    ui->setupUi(this);
    username = username_ref;

    calendarPopUp = std::make_unique<CalendarPopUp>(username);
    calendarPopUp->setParent(this);
    calendarPopUp->hide();

    calendar = ui->calendarWidget;
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    QString selectedDay = QString::number(date.day());
    QString selectedMonth = date.toString("MMMM");
    QString selectedYear = QString::number(date.year());

    ui->day_LA->setText(selectedDay);
    ui->month_LA->setText(selectedMonth);
    ui->year_LA->setText(selectedYear);
}

void Calendar::on_back_PB_clicked()
{
    this->hide();
    mainWindow->show();
}
