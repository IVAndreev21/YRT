#include "calendar.h"
#include "ui_calendar.h"
#include <QTextCharFormat>

Calendar::Calendar(const QString& username_ref, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Calendar)
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
    calendarPopUp->move(QPoint(150,150));
    calendarPopUp->show();
}

