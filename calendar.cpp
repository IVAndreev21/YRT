#include "calendar.h"
#include "ui_calendar.h"

calendar::calendar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::calendar)
{
    ui->setupUi(this);
}

calendar::~calendar()
{
    delete ui;
}

void calendar::on_calendarWidget_clicked(const QDate &date)
{

}

