#include "calendar.h"
#include "ui_calendar.h"
#include "mainwindow.h"

Calendar::Calendar(std::shared_ptr<MainWindow> mainwindow, const QString& username_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::Calendar), mainWindow(mainwindow)
{
    ui->setupUi(this);
    username = username_ref;

    calendarPopUp = std::make_unique<CalendarPopUp>(std::shared_ptr<Calendar>(this), username);

    calendar = ui->calendarWidget;
    calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    fetchEvents();
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::on_calendarWidget_clicked(const QDate &date)
{

    selectedDate == date;
    QString selectedDay = QString::number(date.day());
    QString selectedMonth = date.toString("MMMM");
    QString selectedYear = QString::number(date.year());

    ui->day_LA->setText(selectedDay);
    ui->month_LA->setText(selectedMonth);
    ui->year_LA->setText(selectedYear);

    QSqlQuery qry;
    qry.prepare("SELECT * FROM calendar WHERE Username = :username AND `From` = :fromDate");
    qry.bindValue(":username", username);
    qry.bindValue(":fromDate", date);

    if (qry.exec())
    {
        QStringList events;

        while (qry.next())
        {
            QString title = qry.value(2).toString();
            QString description = qry.value(3).toString();

            events.append("Title: " + title + ", Description: " + description);
        }
        QString eventsText = events.join("\n");

        // Assuming 'ui->label' is the QLabel in your UI
        ui->events_LA->setText(eventsText);
        ui->events_LA->setAlignment(Qt::AlignTop);

    }
}

void Calendar::on_back_PB_clicked()
{
    this->hide();
    mainWindow->show();
}

void Calendar::fetchEvents()
{
    QSqlQuery qry;
    qry.prepare("SELECT `From` FROM calendar WHERE Username = :username");
    qry.bindValue(":username", username);

    QList<QDate> highlightedDates;

    if (qry.exec())
    {
        while (qry.next())
        {
            QDate eventDate = qry.value(0).toDate();
            highlightedDates.append(eventDate);
        }
    }

    // Clear previous date text formats
    calendar->setDateTextFormat(QDate(), QTextCharFormat());

    // Set background color for each date in the list
    QBrush brush(QColor(06, 125, 255));  // Set your desired background color
    QTextCharFormat format;
    format.setBackground(brush);

    for (const QDate& highlightedDate : highlightedDates)
    {
        calendar->setDateTextFormat(highlightedDate, format);
    }
}

void Calendar::on_makeEvent_PB_clicked()
{
    calendarPopUp->show();
}

