#include "calendar.hpp"
#include "ui_calendar.h"
#include "mainwindow.hpp"

// Constructor of Calendar class
Calendar::Calendar(std::shared_ptr<MainWindow> mainwindow, const QString& username_ref, QWidget* parent)
    : QWidget(parent), ui(new Ui::Calendar), m_mainWindow(mainwindow)
{
    ui->setupUi(this);
    m_username = username_ref;

    // Create and initialize the calendar pop-up
    m_calendarPopUp = std::make_unique<CalendarPopUp>(std::shared_ptr<Calendar>(this), m_username);

    m_calendar = ui->calendarWidget;
    m_calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    fetchEvents(); // Fetch events and highlight dates on the calendar
}

// Destructor of Calendar class
Calendar::~Calendar()
{
    delete ui;
}

// Function called when a date is clicked on the calendar
void Calendar::on_calendarWidget_clicked(const QDate &date)
{
    // Extract day, month, and year information from the clicked date
    QString selectedDay = QString::number(date.day());
    QString selectedMonth = date.toString("MMMM");
    QString selectedYear = QString::number(date.year());

    // Update the UI with the selected date information
    ui->day_LA->setText(selectedDay);
    ui->month_LA->setText(selectedMonth);
    ui->year_LA->setText(selectedYear);

    // Query the database for events on the selected date
    QSqlQuery qry;
    qry.prepare("SELECT * FROM calendar WHERE Username = :username AND `From` = :fromDate");
    qry.bindValue(":username", m_username);
    qry.bindValue(":fromDate", date);

    if (qry.exec())
    {
        QStringList events;

        while (qry.next())
        {
            // Extract title and description of each event
            QString title = qry.value(2).toString();
            QString description = qry.value(3).toString();

            // Append event details to the list
            events.append("Title: " + title + "\nDescription: " + description);
        }

        // Join the list of events into a formatted text
        QString eventsText = events.join("\n");

        // Update the events label in the UI
        ui->events_LA->setText(eventsText);
        ui->events_LA->setAlignment(Qt::AlignTop);
    }
}

// Function called when the "Back" button is clicked
void Calendar::on_back_PB_clicked()
{
    // Hide the current calendar window and show the main window
    this->hide();
    m_mainWindow->show();
}

// Fetch events from the database and highlight dates on the calendar
void Calendar::fetchEvents()
{
    QSqlQuery qry;
    qry.prepare("SELECT `From` FROM calendar WHERE Username = :username");
    qry.bindValue(":username", m_username);

    QList<QDate> highlightedDates;

    if (qry.exec())
    {
        while (qry.next())
        {
            // Extract dates of events from the database
            QDate eventDate = qry.value(0).toDate();
            highlightedDates.append(eventDate);
        }
    }

    // Clear previous date text formats
    m_calendar->setDateTextFormat(QDate(), QTextCharFormat());

    // Set background color for each date in the list
    QBrush brush(QColor(06, 125, 255));  // Set your desired background color
    QTextCharFormat format;
    format.setBackground(brush);

    for (const QDate& highlightedDate : highlightedDates)
    {
        // Apply the format to highlight each date with an event
        m_calendar->setDateTextFormat(highlightedDate, format);
    }
}

// Function called when the "Make Event" button is clicked
void Calendar::on_makeEvent_PB_clicked()
{
    // Show the calendar pop-up for creating events
    m_calendarPopUp->show();
}


