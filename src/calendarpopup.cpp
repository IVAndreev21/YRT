#include "calendarpopup.h"
#include "ui_calendarpopup.h"
#include "calendar.h"
#include <QSqlQuery>
CalendarPopUp::CalendarPopUp(std::shared_ptr<Calendar> calendar,const QString& username_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::CalendarPopUp), m_calendar(calendar)
{
    ui->setupUi(this);
    m_username = username_ref;

    ui->from_DE->setDate(QDate::currentDate());
    ui->Till_DE->setDate(QDate::currentDate());
}
CalendarPopUp::~CalendarPopUp()
{
    delete ui;
}

void CalendarPopUp::on_Save_PB_clicked()
{
    QString title = ui->title_LE->text();
    QString description = ui->description_LE->text();
    QDate from = ui->from_DE->date();
    QDate till = ui->Till_DE->date();
    QString repeat = ui->repeat_CB->currentText();

    QSqlQuery query;

    query.prepare("INSERT INTO calendar (`Username`, `Title`, `Description`, `From`, `Till`, `Repeat`)"
                "VALUES (:username, :title, :description, :from, :till, :repeat)");
    query.bindValue(":username", m_username);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":from", from);
    query.bindValue(":till", till);
    query.bindValue(":repeat", repeat);

    if(query.exec())
    {
        QMessageBox::information(this, "Event made", "Event has successfuly been made");
    }
    else
    {
        QMessageBox::critical(this, "Event failed", "Event has failed to be made");

    }

    this->hide();
    m_calendar->fetchEvents();
}


void CalendarPopUp::on_Abort_PB_clicked()
{

    ui->title_LE->clear();
    ui->description_LE->clear();
    ui->from_DE->clear();
    ui->Till_DE->clear();
    ui->repeat_CB->clear();

    this->hide();
}

