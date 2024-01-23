#include "calendarpopup.hpp"
#include "ui_calendarpopup.h"
#include "calendar.hpp"
#include <QSqlQuery>
// Constructor of CalendarPopUp class
CalendarPopUp::CalendarPopUp(std::shared_ptr<Calendar> calendar,const QString& username_ref, QWidget* parent)
    : QWidget(parent), ui(new Ui::CalendarPopUp), m_calendar(calendar)
{
    ui->setupUi(this);
    m_username = username_ref;

    // Set default dates to the current date
    ui->from_DE->setDate(QDate::currentDate());
    ui->till_DE->setDate(QDate::currentDate());
}

// Destructor of CalendarPopUp class
CalendarPopUp::~CalendarPopUp()
{
    delete ui;
}

// Function called when the "Save" button is clicked
void CalendarPopUp::on_save_PB_clicked()
{
    // Retrieve event details from the UI
    QString title = ui->title_LE->text();
    QString description = ui->description_LE->text();
    QDate from = ui->from_DE->date();
    QDate till = ui->till_DE->date();
    QString repeat = ui->repeat_CB->currentText();

    // Prepare SQL query to insert the event into the calendar table
    QSqlQuery query;
    query.prepare("INSERT INTO calendar (`Username`, `Title`, `Description`, `From`, `Till`, `Repeat`)"
                  "VALUES (:username, :title, :description, :from, :till, :repeat)");
    query.bindValue(":username", m_username);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":from", from);
    query.bindValue(":till", till);
    query.bindValue(":repeat", repeat);

    // Execute the query and show appropriate message box
    if(query.exec())
    {
        QMessageBox::information(this, "Event made", "Event has successfully been made");
    }
    else
    {
        QMessageBox::critical(this, "Event failed", "Event has failed to be made");
    }

    // Hide the pop-up and update the calendar with the new event
    this->hide();
    m_calendar->fetchEvents();
}

// Function called when the "Abort" button is clicked
void CalendarPopUp::on_abort_PB_clicked()
{
    // Clear input fields and hide the pop-up
    ui->title_LE->clear();
    ui->description_LE->clear();
    ui->from_DE->clear();
    ui->till_DE->clear();
    ui->repeat_CB->clear();

    this->hide();
}

