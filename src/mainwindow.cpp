#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "login.hpp"

// Constructor of MainWindow class
MainWindow::MainWindow(logIn* login, const QString& IBAN_ref, const QString& username_ref, QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize member variables
    m_IBAN = IBAN_ref;
    m_username = username_ref;

    // Initialize chart for dashboard
    series = new QPieSeries;
    chart = new QChart;
    chartView = new QChartView(chart);

    // Create AddHeir, Calendar objects
    m_addHeir = std::make_shared<AddHeir>(std::shared_ptr<MainWindow>(this), m_username);
    m_calendar = std::make_shared<Calendar>(std::shared_ptr<MainWindow>(this), m_username);

    // Update dashboard and UI elements
    UpdateDashboard();
    ui->card_holder_LA->setText(m_clientFName + " " + m_clientLName[0]);
    ui->securityAnswer_LE->setEchoMode(QLineEdit::Password);
    ui->IBAN_qt_LE->setPlaceholderText("BG00YRT00000000000000");

    // Set up transaction tables
    transactions_TV = ui->transactions_tr_TV;
    Recent_tr_TV = ui->recent_tr_TV;
    UpdateTransactions(transactions_TV, Recent_tr_TV);
    UpdateSettings();

    ui->password_LE->setEchoMode(QLineEdit::Password);
}

// Destructor of MainWindow class
MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
    delete chartView;
}

// Function to update the profile picture
void MainWindow::Updatepfp()
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
            // Set up circular mask and style for profile picture
            SetCircularMaskAndStyle(frame, imageLabel, userPixmap);
            SetCircularMaskAndStyle(frame2, imageLabel2, userPixmap);
        }
        else
        {
            qDebug() << "Invalid or empty image data.";
        }
    }
}

// Function to set a circular mask and style for a profile picture
void MainWindow::SetCircularMaskAndStyle(QFrame* frame, QLabel* imageLabel, const QPixmap& userPixmap)
{
    // Set up circular mask
    QBitmap mask(userPixmap.size());
    mask.fill(Qt::color0); // Transparent mask
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::color1); // Fill with opaque color
    painter.drawEllipse(QPointF(frame->width() / 2, frame->height() / 2), frame->width() / 2, frame->height() / 2);
    frame->setMask(mask);

    // Set circular style for the frame
    frame->setStyleSheet("background-color: white; border-radius: " + QString::number(frame->width() / 2) + "px;");

    // Set parent and geometry for the imageLabel
    imageLabel->setParent(frame);
    imageLabel->setGeometry(0, 0, frame->width(), frame->height());

    // Set the pixmap for the imageLabel
    imageLabel->setPixmap(userPixmap);
}

// Slot function called when the "Dashboard" button is clicked
void MainWindow::on_dashboard_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Slot function called when the "Transactions" button is clicked
void MainWindow::on_transactions_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_crypto_PB_clicked()
{
    DisplayCrypto();
}

void MainWindow::on_settings_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_make_tr_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pfp_acc_PB_clicked()
{
    // Open a file dialog to select an image
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
                // Save the image data in the appropriate format
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
    else
    {
        qDebug() << "invalid image";
    }
}

void MainWindow::on_crypto_PB_clicked()
{
    DisplayCrypto();
}

void MainWindow::on_settings_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_make_tr_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::PerformTransaction(const QString& receiverIBAN, const QString& amountStr, const QString& type, const QString& firstName, const QString& lastName)
{
    // Check sender's balance and perform the transaction
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
            // Retrieve receiver's information
            QSqlQuery receiverQuery;
            receiverQuery.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
            receiverQuery.bindValue(":IBAN", receiverIBAN);

            if (receiverQuery.exec() && receiverQuery.next())
            {
                double senderNewBalance = senderBalance - amount;
                double senderNewExpenseBalance = senderExpenseBalance + amount;
                double receiverBalance = receiverQuery.value("Balance").toDouble();
                double receiverNewBalance = receiverBalance + amount;

                // Update sender's balance
                QSqlQuery updateSenderQuery;
                updateSenderQuery.prepare("UPDATE users SET balance = :newBalance, expenses = :expense WHERE IBAN = :IBAN");
                updateSenderQuery.bindValue(":newBalance", senderNewBalance);
                updateSenderQuery.bindValue(":expense", senderNewExpenseBalance);
                updateSenderQuery.bindValue(":IBAN", m_IBAN);

                // Update receiver's balance
                QSqlQuery updateReceiverQuery;
                updateReceiverQuery.prepare("UPDATE users SET balance = :newBalance WHERE IBAN = :IBAN");
                updateReceiverQuery.bindValue(":newBalance", receiverNewBalance);
                updateReceiverQuery.bindValue(":IBAN", receiverIBAN);

                if (updateSenderQuery.exec() && updateReceiverQuery.exec())
                {
                    // Record the transaction details
                    RecordTransaction(receiverIBAN, amountStr, type, firstName, lastName, senderQuery);

                    // Show success message
                    QMessageBox::information(this, "Transaction success", "Transaction has been successful");
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

    // Update dashboard and transactions
    UpdateDashboard();
    UpdateTransactions(transactions_TV, Recent_tr_TV);
}

void MainWindow::on_confrim_mt_PB_clicked()
{
    // Retrieve transaction details from user input
    QString receiverIBAN = ui->IBAN_mt_LE->text();
    QString amountStr = ui->amount_mt_LE->text();
    QString type = ui->type_mt_CB->currentText();
    QString firstName = ui->first_name_mt_LE->text();
    QString lastName = ui->last_name_mt_LE->text();

    // Perform the transaction with the provided details
    PerformTransaction(receiverIBAN, amountStr, type, firstName, lastName);
}

void MainWindow::HeirVerified()
{
    // Hide heir detection elements
    ui->heir_detected->hide();
    ui->addHeir_PB->hide();
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
    // Go back to the dashboard
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::UpdateDashboard()
{
    // First query to get user information
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    qry.bindValue(":IBAN", m_IBAN);

    if (qry.exec() && qry.next())
    {
        // Update user information on the dashboard
        m_clientFName = qry.value("First Name").toString();
        m_clientLName = qry.value("Last Name").toString();
        double balance = qry.value("Balance").toDouble();
        balance = round(balance * 100) / 100;
        QString balanceStr = QString::number(balance, 'f', 2);

        ui->clientname_LA->setText("Hello Again, " + m_clientFName + " " + m_clientLName[0] + ".");
        ui->balance_LA_2->setText("BGN " + balanceStr);
        Updatepfp();
    }
    else
    {
        qDebug() << "Query failed or no record found.";
    }

    // Second query to get additional user information
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", m_IBAN);

    if (query.exec() && query.next())
    {
        m_userExpenses = query.value("Expenses").toDouble();
        m_heir = query.value("Heir").toString();

        // Third query to get the total income of the user
        query.prepare("SELECT SUM(amount) AS totalIncome FROM transactions WHERE IBAN = :IBAN");
        query.bindValue(":IBAN", m_IBAN);

        if (query.exec() && query.next())
        {
            m_userIncome = query.value("totalIncome").toDouble();
        }

        if (m_heir == "")
        {
            // Display a warning if no heir is detected
            ui->heir_detected->setText("A heir hasn't been detected!\nFor the safety of the account, select the heir of your assets");
            ui->heir_detected->setStyleSheet("color: rgb(255, 0, 0);");
            ui->addHeir_PB->show();
        }
        else
        {
            ui->addHeir_PB->hide();
        }
    }

    // Update the pie chart with income and expenses data
    series->clear();
    series->append("Income", m_userIncome);
    series->append("Expenses", m_userExpenses);

    QPieSlice* slice0 = series->slices().at(0);
    slice0->setLabelVisible();

    QPieSlice* slice1 = series->slices().at(1);
    slice1->setLabelVisible();

    chart->addSeries(series);
    chart->setTitle("Total Balance");

    // Set the background color of the chart to be transparent
    chart->setBackgroundBrush(QBrush(Qt::transparent));

    // Hide the legend
    chart->legend()->hide();

    // Set the title brush to be transparent
    chart->setTitleBrush(Qt::transparent);

    chartView->setRenderHint(QPainter::Antialiasing);

    // Set the background color of the chart view to be transparent
    chartView->setBackgroundBrush(QBrush(Qt::transparent));

    ui->PieChart_LY->addWidget(chartView);
}

void MainWindow::on_calendar_PB_clicked()
{
    // Switch to the calendar view
    this->hide();
    m_calendar->show();
}

void MainWindow::UpdateSettings()
{
    // Query to get user settings information
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
    qry.bindValue(":IBAN", m_IBAN);

    if (qry.exec() && qry.next())
    {
        // Update UI elements with user settings
        ui->fName_LE->setText(qry.value("First Name").toString());
        ui->lName_LE->setText(qry.value("Last Name").toString());
        ui->birth_LE->setText(qry.value("Date of Birth").toString());
        ui->gender_LE->setText(qry.value("Gender").toString());
        ui->SSN_LE->setText(qry.value("SSN").toString());
        ui->city_LE->setText(qry.value("City").toString());
        ui->state_LE->setText(qry.value("State/Province").toString());
        ui->postalCode_LE->setText(qry.value("Postal Code").toString());
        ui->street_LE->setText(qry.value("Street").toString());
        ui->status_LE->setText(qry.value("Employment Status").toString());
        ui->accType_LE->setText(qry.value("Type").toString());
        ui->income_LE->setText(qry.value("Income").toString());
        ui->expenses_LE->setText(qry.value("Expenses").toString());
        ui->balance_LE->setText(qry.value("Balance").toString());
        ui->IBAN_LE->setText(qry.value("IBAN").toString());
        ui->username_LE->setText(qry.value("Username").toString());
        ui->password_LE->setText(qry.value("Password").toString());
        ui->securityQuestion_LE->setText(qry.value("Security question").toString());
        ui->securityAnswer_LE->setText(qry.value("Security answer").toString());
    }
}



void MainWindow::on_send_qt_PB_clicked()
{
    // Get data from UI
    QString receiverIBAN = ui->IBAN_qt_LE->text();
    QString amountStr = ui->amount_SB->text();
    QString type = "transaction";

    // Query to check if the receiver exists in transactions
    QSqlQuery query;
    query.prepare("SELECT * FROM transactions WHERE IBAN = :IBAN");
    query.bindValue(":IBAN", receiverIBAN);

    if (query.exec() && query.next())
    {
        // Get receiver's name from the transactions data
        QString FName = query.value("Receiver First Name").toString();
        QString LName = query.value("Receiver Last Name").toString();

        // Perform the transaction
        PerformTransaction(receiverIBAN, amountStr, type, FName, LName);
    }
}

void MainWindow::on_addHeir_PB_clicked()
{
    // Show the add heir window
    m_addHeir->show();
}

void MainWindow::on_signOut_PB_clicked()
{
    // Show the login window and hide the main window
    logIn* login = new logIn();
    login->show();
    this->hide();
}

void MainWindow::DisplayCrypto()
{
    // Execute the Python crypto script
    QProcess process;
    QString executablePath = QCoreApplication::applicationDirPath();
    QFileInfo executableInfo(executablePath);
    QString sourceFolderPath = executableInfo.absolutePath() + "/../../../YRT/src";

    // Specify the working directory as an argument
    QStringList arguments;
    arguments << "crypto.py" << m_username;

    // Start the process detached with the specified working directory
    bool success = QProcess::startDetached("/usr/local/bin/python3.12", arguments, sourceFolderPath);

    if (!success) {
        qDebug() << "Error starting process: " << process.errorString();
    } else {
        qDebug() << "Process started successfully.";
        QByteArray outputData = process.readAllStandardOutput();
        QString outputString = QString::fromUtf8(outputData);

        qDebug() << "Output:" << outputString;
    }
}


