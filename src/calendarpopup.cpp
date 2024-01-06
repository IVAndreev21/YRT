#include "calendarpopup.h"
#include "ui_calendarpopup.h"

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
    QString timePeriod = ui->From_DE->text() + " - " + ui->Till_DE->text();
    QString repeat = ui->Repeat_CB->currentText();

    QSqlDatabase db;
    QSqlQuery query;

    query.prepare("INSERT INTO calendar (`Username`, `Title`, `Description`, `Time Period`, `Repeat`)"
                "VALUES (:username, :title, :description, :timePeriod, :repeat)");
    query.bindValue(":username", username);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":timePeriod", timePeriod);
    query.bindValue(":repeat", repeat);

    if(query.exec())
    {
        QMessageBox::information(this, "Event made", "Event has successfuly been made");
    }
    else
    {
        QMessageBox::critical(this, "Event failed", "Event has failed to be made");
        qDebug() << query.lastError().text();

    }
    this->hide();
}

