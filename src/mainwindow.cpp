#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
MainWindow::MainWindow(logIn* login, const QString& IBAN_ref, const QString& username_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_IBAN = IBAN_ref;
    m_username = username_ref;

    series = new QPieSeries;
    chart = new QChart;
    chartView = new QChartView(chart);

    m_crypto = std::make_shared<Crypto>(std::shared_ptr<MainWindow>(this));
    m_addHeir = std::make_shared<AddHeir>(std::shared_ptr<MainWindow>(this), m_username);
    updateDashboard(series, chart, chartView);
    ui->card_holder_LA->setText(m_clientFName + " " + m_clientLName[0]);
    ui->SecurityAnswer_LE->setEchoMode(QLineEdit::Password);
    ui->IBAN_qt_LE->setPlaceholderText("BG00YRT00000000000000");

    transactions_TV = ui->Transactions_tr_TV;
    Recent_tr_TV = ui->Recent_tr_TV;

    UpdateTransactions(transactions_TV, Recent_tr_TV);
    UpdateSettings();

    ui->Password_LE->setEchoMode(QLineEdit::Password);
    m_calendar = std::make_shared<Calendar>(std::shared_ptr<MainWindow>(this), m_username);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
    delete chartView;
}

void MainWindow::updatepfp()
{
    QLabel *imageLabel = ui->pfp_acc_LA;
    QLabel *imageLabel2 = ui->pfp_acc_LA_2;
    QFrame *frame = ui->frame;
    QFrame *frame2 = ui->frame_2;

    QSqlQuery query;
    query.prepare("SELECT pfp FROM users WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", m_IBAN);

    if (query.exec() && query.first())
    {
        QByteArray imageData = query.value("pfp").toByteArray();
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
                qry.bindValue(":IBAN", m_IBAN);

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
    m_crypto->show();
    this->hide();
}

void MainWindow::on_settings_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_make_tr_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow::performTransaction(const QString& receiverIBAN, const QString& amountStr, const QString& type, const QString& firstName, const QString& lastName)
{
        QSqlQuery senderQuery;
        senderQuery.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
        senderQuery.bindValue(":IBAN", m_IBAN);

        if (senderQuery.exec() && senderQuery.next())
        {
            double senderBalance = senderQuery.value("Balance").toDouble();
            double senderExpenseBalance = senderQuery.value("Expenses").toDouble();
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
                    double receiverBalance = receiverQuery.value("Balance").toDouble();
                    double receiverNewBalance = receiverBalance + amount;

                    QSqlQuery updateSenderQuery;
                    updateSenderQuery.prepare("UPDATE users SET balance = :newBalance, expenses = :expense WHERE IBAN = :IBAN");
                    updateSenderQuery.bindValue(":newBalance", senderNewBalance);
                    updateSenderQuery.bindValue(":expense", senderNewExpenseBalance);
                    updateSenderQuery.bindValue(":IBAN", m_IBAN);

                    QSqlQuery updateReceiverQuery;
                    updateReceiverQuery.prepare("UPDATE users SET balance = :newBalance WHERE IBAN = :IBAN");
                    updateReceiverQuery.bindValue(":newBalance", receiverNewBalance);
                    updateReceiverQuery.bindValue(":IBAN", receiverIBAN);

                    if (updateSenderQuery.exec() && updateReceiverQuery.exec())
                    {
                        QSqlQuery insertQuery;
                        QString Date = QDateTime::currentDateTime().toString();
                        insertQuery.prepare("INSERT INTO transactions (Date, `IBAN`, `Sender First Name`, `Sender Last Name`, `Receiver First Name`, `Receiver Last Name`, Phone, Type, Amount, Description, `Sender IBAN`) "
                                            "VALUES (:Date, :IBAN, :Sender_First_Name, :Sender_Last_Name, :Receiver_First_Name, :Receiver_Last_Name, :Phone, :Type, :Amount, :Description, :Sender_IBAN)");
                        insertQuery.bindValue(":Date", Date);
                        insertQuery.bindValue(":IBAN", receiverIBAN);
                        insertQuery.bindValue(":Sender_First_Name", senderQuery.value(1));
                        insertQuery.bindValue(":Sender_Last_Name", senderQuery.value(2));
                        insertQuery.bindValue(":Receiver_First_Name", firstName);
                        insertQuery.bindValue(":Receiver_Last_Name", lastName);
                        insertQuery.bindValue(":Phone", senderQuery.value(10));
                        insertQuery.bindValue(":Type", type);
                        insertQuery.bindValue(":Amount", amountStr);
                        insertQuery.bindValue(":Description", "Transfer to " + firstName);
                        insertQuery.bindValue(":Sender_IBAN", m_IBAN);

                        if (insertQuery.exec())
                        {
                            QMessageBox::information(this, "Transaction success", "Transaction has been successful");
                        }
                        else
                        {
                            QMessageBox::critical(this, "Transaction failure", "Transaction failed");
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


    updateDashboard(series, chart, chartView);
    UpdateTransactions(transactions_TV, Recent_tr_TV);

}
void MainWindow::on_confrim_mt_PB_clicked()
{
    QString receiverIBAN = ui->IBAN_mt_LE->text();
    QString amountStr = ui->amount_mt_LE->text();
    QString type = ui->type_mt_CB->currentText();
    QString firstName = ui->first_name_mt_LE->text();
    QString lastName = ui->last_name_mt_LE->text();

    performTransaction(receiverIBAN, amountStr, type, firstName, lastName);
}

void MainWindow::UpdateTransactions(QTableView* transasctions_TV, QTableView* Recent_tr_TV)
{
    // First Query
    QSqlQueryModel* query = new QSqlQueryModel();
    QString userIBAN = m_IBAN;
    QString queryString = "SELECT * FROM transactions WHERE `Sender IBAN` = '" + userIBAN + "' OR `IBAN` = '" + userIBAN + "'";
    query->setQuery(queryString);
    transasctions_TV->setModel(query);
    transasctions_TV->setColumnHidden(0, true);
    transasctions_TV->setColumnWidth(1, 200);
    transasctions_TV->setColumnWidth(2, 220);
    transasctions_TV->setColumnWidth(3, 220);
    transasctions_TV->setColumnWidth(11, 170);

    // Second Query
    QSqlQueryModel* queryModel = new QSqlQueryModel();
    QString queryStringRecent = "SELECT * FROM transactions WHERE `Sender IBAN` = '" + userIBAN + "' OR `IBAN` = '" + userIBAN + "' ORDER BY Date DESC LIMIT 5";
    queryModel->setQuery(queryStringRecent);

    Recent_tr_TV->setModel(queryModel);
    Recent_tr_TV->hideColumn(0);
    Recent_tr_TV->hideColumn(3);
    Recent_tr_TV->hideColumn(4);
    Recent_tr_TV->hideColumn(5);
    Recent_tr_TV->hideColumn(8);
    Recent_tr_TV->hideColumn(11);
}


void MainWindow::on_cancel_mt_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::updateDashboard(QPieSeries* series, QChart* chart, QChartView* chartView)
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    qry.bindValue(":IBAN", m_IBAN);

    if (qry.exec() && qry.next())
    {
        m_clientFName = qry.value("First Name").toString();
        m_clientLName = qry.value("Last Name").toString();
        QString balance = qry.value("Balance").toString();

        ui->clientname_LA->setText("Hello Again, " + m_clientFName + " " + m_clientLName[0] + ".");
        ui->balance_LA_2->setText("BGN " + balance);

        updatepfp();
    }
    else
    {
        qDebug() << "Query failed or no record found.";
    }


    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", m_IBAN);

    if (query.exec() && query.next())
    {
        m_userExpenses = query.value("Expenses").toDouble();
        m_heir = query.value("Heir").toString();
        query.prepare("SELECT SUM(amount) AS totalIncome FROM transactions WHERE IBAN = :IBAN");
        query.bindValue(":IBAN", m_IBAN);

        if (query.exec() && query.next())
        {
            m_userIncome = query.value("totalIncome").toDouble();
        }

        if(m_heir == "")
        {
            ui->heir_detected->setText("A heir hasn't been detect! \n For the safety of the account select the heir of your assetts");
            ui->heir_detected->setStyleSheet("color: rgb(255, 0, 0);");
            ui->addHeir_PB->show();

        }
        else
        {
            ui->addHeir_PB->hide();
        }
    }
    series->clear();

    series->append("Income", m_userIncome);
    series->append("Expenses", m_userExpenses);

    chart->setBackgroundBrush(Qt::NoBrush);

    QPieSlice* slice0 = series->slices().at(0);
    slice0->setLabelVisible();

    QPieSlice* slice1 = series->slices().at(1);
    slice1->setLabelVisible();

    chart->addSeries(series);
    chart->setTitle("Total Balance");
    chart->backgroundBrush();
    chart->setTitleBrush(Qt::white);
    chart->legend()->hide();

    chartView->setRenderHint(QPainter::Antialiasing);

    ui->PieChart_LY->addWidget(chartView);
}

void MainWindow::on_calendar_PB_clicked()
{
    this->hide();
    m_calendar->show();
}

void MainWindow::UpdateSettings()
{
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    qry.bindValue(":IBAN", m_IBAN);

    if(qry.exec() && qry.next())
    {
        ui->FName_LE->setText(qry.value("First Name").toString());
        ui->LName_LE->setText(qry.value("Last Name").toString());
        ui->Birth_LE->setText(qry.value("Date of Birth").toString());
        ui->Gender_LE->setText(qry.value("Gender").toString());
        ui->SSN_LE->setText(qry.value("SSN").toString());
        ui->City_LE->setText(qry.value("City").toString());
        ui->State_LE->setText(qry.value("State/Province").toString());
        ui->PostalCode_LE->setText(qry.value("Postal Code").toString());
        ui->Street_LE->setText(qry.value("Street").toString());
        ui->Status_LE->setText(qry.value("Employment Status").toString());
        ui->AccType_LE->setText(qry.value("Type").toString());
        ui->Income_LE->setText(qry.value("Income").toString());
        ui->Expenses_LE->setText(qry.value("Expenses").toString());
        ui->Balance_LE->setText(qry.value("Balance").toString());
        ui->IBAN_LE->setText(qry.value("IBAN").toString());
        ui->Username_LE->setText(qry.value("Username").toString());
        ui->Password_LE->setText(qry.value("Password").toString());
        ui->SecurityQuestion_LE->setText(qry.value("Security question").toString());
        ui->SecurityAnswer_LE->setText(qry.value("Security answer").toString());
    }
}


void MainWindow::on_Send_qt_PB_clicked()
{
    QString receiverIBAN = ui->IBAN_qt_LE->text();
    QString amountStr = ui->Amount_SB->text();
    QString type = "transaction";

    QSqlQuery query;
    query.prepare("SELECT * FROM transactions WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", receiverIBAN);
    if(query.exec() && query.next())
    {
        QString FName = query.value("Receiver First Name").toString();
        QString LName = query.value("Receiver Last Name").toString();
        performTransaction(receiverIBAN, amountStr, type, FName, LName);
    }
}

void MainWindow::on_addHeir_PB_clicked()
{

    m_addHeir->show();
}


void MainWindow::on_signOut_PB_clicked()
{
    logIn* login = new logIn();
    login->show();
    this->hide();
}

