#include "calendarpopup.h"
#include "ui_calendarpopup.h"

CalendarPopUp::CalendarPopUp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CalendarPopUp)
{
    ui->setupUi(this);

}

CalendarPopUp::~CalendarPopUp()
{
    delete ui;
}

void CalendarPopUp::on_Save_PB_clicked()
{
    this->hide();
}

