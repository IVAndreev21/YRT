#include "calendarpopup.h"
#include "ui_calendarpopup.h"
#include <QSqlQuery>
CalendarPopUp::CalendarPopUp(const QString& username_ref, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CalendarPopUp)
{
    ui->setupUi(this);
    username = username_ref;
}

CalendarPopUp::~CalendarPopUp()
{
    delete ui;
}

void CalendarPopUp::on_Save_PB_clicked()
{
    QString title = ui->Title_LE->text();
    QString description = ui->Description_LE->text();
    QDate from = ui->From_DE->date();
    QDate till = ui->Till_DE->date();
    QString repeat = ui->Repeat_CB->currentText();

    QSqlQuery query;

    query.prepare("INSERT INTO calendar (`Username`, `Title`, `Description`, `From`, `Till`, `Repeat`)"
                "VALUES (:username, :title, :description, :from, :till, :repeat)");
    query.bindValue(":username", username);
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
}


void CalendarPopUp::on_Abort_PB_clicked()
{

    ui->Title_LE->clear();
    ui->Description_LE->clear();
    ui->From_DE->clear();
    ui->Till_DE->clear();
    ui->Repeat_CB->clear();

    this->hide();

}

