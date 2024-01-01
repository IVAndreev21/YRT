#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &IBAN_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    databaseManager = std::make_unique<DatabaseManager>();
    databaseManager->openConnection();
    db = databaseManager->getDatabase();
    IBAN = IBAN_ref;

    populateTransactionTreeWidget();
    updateDashboard();

    ui->Pay_to_LE->setPlaceholderText("**** **** **** 0164");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatepfp()
{
    QLabel *imageLabel = ui->pfp_acc_LA;
    QLabel *imageLabel2 = ui->pfp_acc_LA_2;
    QFrame *frame = ui->frame;
    QFrame *frame2 = ui->frame_2;

    QSqlQuery query;
    query.prepare("SELECT pfp FROM users WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", IBAN);

    if (query.exec() && query.first())
    {
        QByteArray imageData = query.value(0).toByteArray();
        QPixmap userPixmap;
        userPixmap.loadFromData(QByteArray::fromBase64(imageData));

        if (!userPixmap.isNull())
        {
            imageLabel->setParent(frame);
            imageLabel2->setParent(frame2);

            imageLabel->setGeometry(0, 0, frame->width(), frame->height());
            imageLabel2->setGeometry(0, 0, frame2->width(), frame2->height());

            QBitmap mask1(userPixmap.size());
            mask1.fill(Qt::color0); // Transparent mask
            QPainter painter1(&mask1);
            painter1.setRenderHint(QPainter::Antialiasing);
            painter1.setBrush(Qt::color1); // Fill with opaque color
            painter1.drawEllipse(QPointF(frame->width() / 2, frame->height() / 2), frame->width() / 2, frame->height() / 2);
            frame->setMask(mask1);
            frame->setStyleSheet("background-color: white; border-radius: " + QString::number(frame->width() / 2) + "px;");

            QBitmap mask2(userPixmap.size());
            mask2.fill(Qt::color0); // Transparent mask
            QPainter painter2(&mask2);
            painter2.setRenderHint(QPainter::Antialiasing);
            painter2.setBrush(Qt::color1); // Fill with opaque color
            painter2.drawEllipse(QPointF(frame2->width() / 2, frame2->height() / 2), frame2->width() / 2, frame2->height() / 2);
            frame2->setMask(mask2);
            frame2->setStyleSheet("background-color: white; border-radius: " + QString::number(frame2->width() / 2) + "px;");

            ui->pfp_acc_LA->setPixmap(userPixmap);
            ui->pfp_acc_LA_2->setPixmap(userPixmap);
        }
        else
        {
            qDebug() << "Invalid or empty image data.";
        }
    }
}

void MainWindow::on_dashboard_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_transactions_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pfp_acc_PB_clicked()
{
    QString ImagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QCoreApplication::applicationDirPath(), tr("Image Files (*.jpg *.png)"), 0, QFileDialog::DontUseNativeDialog);

    if (!ImagePath.isEmpty())
    {
        QPixmap Image(ImagePath);
        QBuffer ImageBufferData;

        if (ImageBufferData.open(QIODevice::ReadWrite))
        {
            QString fileExtension = QFileInfo(ImagePath).suffix().toLower();
            if (fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png")
            {
                if (fileExtension == "jpg" || fileExtension == "jpeg")
                    Image.save(&ImageBufferData, "JPG");
                else if (fileExtension == "png")
                    Image.save(&ImageBufferData, "PNG");

                ImageBufferData.close();
                QByteArray FinalDataToSave = ImageBufferData.buffer().toBase64();
                QSqlQuery qry;
                qry.prepare("UPDATE users SET pfp = :pfp WHERE IBAN = :IBAN");
                qry.bindValue(":pfp", FinalDataToSave);
                qry.bindValue(":IBAN", IBAN);

                if (qry.exec())
                {
                    QSqlDatabase::database().commit();
                    ui->pfp_acc_LA->setPixmap(Image);
                    ui->pfp_acc_LA_2->setPixmap(Image);
                }
            }
            else
            {
                QMessageBox::warning(this, tr("Unsupported Format"), tr("Only JPG and PNG files are supported."));
            }
        }
    }
}

void MainWindow::on_payments_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_crypto_PB_clicked()
{
}

void MainWindow::on_settings_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_make_tr_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_confrim_mt_PB_clicked()
{
    QString receiverIBAN = ui->IBAN_mt_LE->text();
    QString amountStr = ui->amount_mt_LE->text();
    QString type = ui->type_mt_CB->currentText();
    QString firstName = ui->first_name_mt_LE->text();
    QString lastName = ui->last_name_mt_LE->text();

    QSqlQuery receiverQuery;
    receiverQuery.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    receiverQuery.bindValue(":IBAN", receiverIBAN);

    if (receiverQuery.exec() && receiverQuery.next())
    {
        QString receiverFName = receiverQuery.value(1).toString();
        QSqlQuery senderQuery;
        senderQuery.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
        senderQuery.bindValue(":IBAN", IBAN);

        if (senderQuery.exec() && senderQuery.next())
        {
            double senderBalance = senderQuery.value(19).toDouble();
            double senderExpenseBalance = senderQuery.value(22).toDouble();
            bool conversionOK;
            double amount = amountStr.toDouble(&conversionOK);

            if (conversionOK && senderBalance >= amount)
            {
                QSqlQuery receiverQuery;
                receiverQuery.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
                receiverQuery.bindValue(":IBAN", receiverIBAN);

                if (receiverQuery.exec() && receiverQuery.next())
                {
                    double senderNewBalance = senderBalance - amount;
                    double senderNewExpenseBalance = senderExpenseBalance + amount;
                    double receiverBalance = receiverQuery.value(19).toDouble();
                    double receiverNewBalance = receiverBalance + amount;

                    QSqlQuery updateSenderQuery;
                    updateSenderQuery.prepare("UPDATE users SET balance = :newBalance, expenses = :expense WHERE IBAN = :IBAN");
                    updateSenderQuery.bindValue(":newBalance", senderNewBalance);
                    updateSenderQuery.bindValue(":expense", senderNewExpenseBalance);
                    updateSenderQuery.bindValue(":IBAN", IBAN);

                    QSqlQuery updateReceiverQuery;
                    updateReceiverQuery.prepare("UPDATE users SET balance = :newBalance WHERE IBAN = :IBAN");
                    updateReceiverQuery.bindValue(":newBalance", receiverNewBalance);
                    updateReceiverQuery.bindValue(":IBAN", receiverIBAN);

                    if (updateSenderQuery.exec() && updateReceiverQuery.exec())
                    {
                        QSqlQuery insertQuery;
                        QString Date = QDateTime::currentDateTime().toString();
                        insertQuery.prepare("INSERT INTO transactions (Date, IBAN, `Sender First Name`, `Sender Last Name`, `Receiver First Name`, `Receiver Last Name`, Phone, Type, Amount, Description) "
                                            "VALUES (:Date, :IBAN, :Sender_First_Name, :Sender_Last_Name, :Receiver_First_Name, :Receiver_Last_Name, :Phone, :Type, :Amount, :Description)");
                        insertQuery.bindValue(":Date", Date);
                        insertQuery.bindValue(":IBAN", receiverIBAN);
                        insertQuery.bindValue(":Sender_First_Name", senderQuery.value(1));
                        insertQuery.bindValue(":Sender_Last_Name", senderQuery.value(2));
                        insertQuery.bindValue(":Receiver_First_Name", firstName);
                        insertQuery.bindValue(":Receiver_Last_Name", lastName);
                        insertQuery.bindValue(":Phone", senderQuery.value(10));
                        insertQuery.bindValue(":Type", type);
                        insertQuery.bindValue(":Amount", amountStr);
                        insertQuery.bindValue(":Description", "Transfer to " + receiverFName);

                        if (insertQuery.exec())
                        {
                            QTreeWidgetItem *item = new QTreeWidgetItem(ui->Transactions_tr_TW);
                            item->setText(0, QDateTime::currentDateTime().toString());
                            item->setText(1, receiverIBAN);
                            item->setText(2, senderQuery.value(1).toString() + senderQuery.value(2).toString());
                            item->setText(3, firstName + lastName);
                            item->setText(4, type);
                            item->setText(5, amountStr);
                            item->setText(6, "Transfer to " + receiverFName);

                            ui->Transactions_tr_TW->addTopLevelItem(item);
                            QMessageBox::information(this, "Transaction success", "Transaction has been successful");
                        }
                        else
                        {
                            QMessageBox::critical(this, "Transaction failure", "Transaction failed");
                            qDebug() << insertQuery.lastError().text();
                        }
                    }
                    else
                    {
                        QMessageBox::critical(this, "Update failure", "Failed to update balances");
                    }
                }
                else
                {
                    QMessageBox::critical(this, "Receiver not found", "Receiver not found in the database");
                }
            }
            else
            {
                QMessageBox::critical(this, "Invalid amount or insufficient funds", "Invalid amount or insufficient funds for this transaction");
            }
        }
        else
        {
            QMessageBox::critical(this, "Sender not found", "Sender not found in the database");
        }
    }
}

void MainWindow::populateTransactionTreeWidget()
{
    ui->Transactions_tr_TW->clear();
    QSqlQuery query;
    query.prepare("SELECT * FROM transactions");

    if (query.exec())
    {
        while (query.next())
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->Transactions_tr_TW);
            item->setText(0, query.value(1).toString());
            item->setText(1, query.value(2).toString());
            item->setText(2, query.value(3).toString() + " " + query.value(4).toString());
            item->setText(3, query.value(5).toString() + " " + query.value(6).toString());
            item->setText(4, query.value(8).toString());
            item->setText(5, query.value(9).toString());
            item->setText(6, query.value(10).toString());

            ui->Transactions_tr_TW->addTopLevelItem(item);
        }
    }
}

void MainWindow::updatePieChart()
{
}

void MainWindow::on_cancel_mt_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::updateDashboard()
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    qry.bindValue(":IBAN", IBAN);

    if (qry.exec() && qry.next())
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
        qDebug() << "Query failed or no record found.";
    }


    QPieSeries *series = new QPieSeries();
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", IBAN);

    if (query.exec() && query.next())
    {
        userExpenses = query.value(22).toDouble();

        query.prepare("SELECT SUM(amount) AS totalIncome FROM transactions WHERE IBAN = :IBAN");
        query.bindValue(":IBAN", IBAN);

        if (query.exec() && query.next())
        {
            userIncome = query.value("totalIncome").toDouble();
        }
    }

    series->append("Income", userIncome);
    series->append("Expenses", userExpenses);

    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();
    slice0->setLabelColor(Qt::white);

    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible();
    slice1->setPen(QPen(Qt::darkGreen, 2));
    slice1->setBrush(Qt::green);
    slice1->setLabelColor(Qt::white);

    QChart *chart = new QChart();
    chart->setBackgroundBrush(Qt::NoBrush);

    chart->addSeries(series);
    chart->setTitle("Total Balance");
    chart->backgroundBrush();
    chart->setTitleBrush(Qt::white);
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->PieChart_LY->addWidget(chartView);
}

void MainWindow::on_Send_QT_PB_clicked()
{

}

