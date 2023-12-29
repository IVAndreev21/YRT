#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    databaseManager = std::make_unique<DatabaseManager>();
    if(databaseManager->openConnection())
    {
        QSqlQuery qry;

        qry.prepare("SELECT * FROM users WHERE username = :username");
        qry.bindValue(":username", username);


        if (qry.exec() && qry.next()) // Execute the query and move to the first record
        {
            QString firstName = qry.value(1).toString();
            QString lastName = qry.value(2).toString();
            QString balance = qry.value(19).toString();

            ui->clientname_LA->setText(firstName + " " + lastName[0] + ".");
            ui->balance_LA_2->setText("BGN " + balance);
            updatepfp();
        }
        else
        {
            // Handle the case where the query fails or no record is found
            qDebug() << "Query failed or no record found.";
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatepfp()
{

}
void MainWindow::on_transactions_PB_clicked()
{

}

