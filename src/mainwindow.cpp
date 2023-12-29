#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const QString &username_ref, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    username = username_ref;
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
    QLabel* imageLabel = ui->pfp_acc_LA;
    QLabel* imageLabel2 = ui->pfp_acc_LA_2;
    QFrame* frame = ui->frame;
    QFrame* frame2 = ui->frame_2;

    if (databaseManager->openConnection())
    {
        QSqlDatabase db = databaseManager->getDatabase();
        if (db.isValid() && db.isOpen())
        {
            QSqlQuery query;
            query.prepare("SELECT pfp FROM users WHERE Username = :username");
            query.bindValue(":username", username);

            if (query.exec() && query.first()) // Assuming there's only one user with the given username
            {
                QByteArray imageData = query.value(0).toByteArray();
                QPixmap userPixmap;
                userPixmap.loadFromData(QByteArray::fromBase64(imageData));

                if (!userPixmap.isNull()) {
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
                } else {
                    qDebug() << "Invalid or empty image data.";
                }
            }
            else
            {
                QMessageBox::critical(this, "Database Error", "Failed to retrieve user data from the database." + query.lastError().text());
            }
        }
    }
    else
    {
        QMessageBox::critical(this, "Database Error", "Failed to open database connection.");
    }
}
void MainWindow::on_transactions_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pfp_acc_PB_clicked()
{
    QString ImagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), QCoreApplication::applicationDirPath(), tr("Image Files (*.jpg *.png)"), 0, QFileDialog::DontUseNativeDialog);

    if (!ImagePath.isEmpty()) {
        QPixmap Image(ImagePath);
        QBuffer ImageBufferData;

        if (ImageBufferData.open(QIODevice::ReadWrite))
        {
            QString fileExtension = QFileInfo(ImagePath).suffix().toLower();
            if (fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png")
            {
                // Determine the image format based on the file extension
                if (fileExtension == "jpg" || fileExtension == "jpeg")
                    Image.save(&ImageBufferData, "JPG");
                else if (fileExtension == "png")
                    Image.save(&ImageBufferData, "PNG");

                ImageBufferData.close();
                QByteArray FinalDataToSave = ImageBufferData.buffer().toBase64();

                if (databaseManager->openConnection())
                {
                    QSqlDatabase db = databaseManager->getDatabase();
                    if (db.isValid() && db.isOpen())
                    {
                        QSqlQuery qry;
                        qry.prepare("UPDATE users SET pfp = :pfp WHERE Username = :username");
                        qry.bindValue(":pfp", FinalDataToSave);
                        qry.bindValue(":username", username);
                        if(qry.exec())
                        {
                            QSqlDatabase::database().commit();
                            ui->pfp_acc_LA->setPixmap(Image);
                            ui->pfp_acc_LA_2->setPixmap(Image);
                        }
                    }
                }
            }
            else
            {
                // Handle unsupported file format here
                QMessageBox::warning(this, tr("Unsupported Format"), tr("Only JPG and PNG files are supported."));
            }
        }
    }
}


void MainWindow::on_payments_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_cards_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_account_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_administration_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}



void MainWindow::on_make_tr_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_confrim_mt_PB_clicked()
{
    QString receiverIBAN = ui->IBAN_mt_LE->text(); // Assuming you have an input field for the receiver's username
    QString amountStr = ui->amount_mt_LE->text();
    QString type = ui->type_mt_CB->currentText();
    QString firstName = ui->first_name_mt_LE->text();
    QString lastName = ui->last_name_mt_LE->text();

    if (databaseManager->openConnection())
    {
        QSqlDatabase db = databaseManager->getDatabase();
        if (db.isValid() && db.isOpen())
        {
            QSqlQuery receiverQuery;
            receiverQuery.prepare("SELECT * FROM users WHERE IBAN = :IBAN");
            receiverQuery.bindValue(":IBAN", receiverIBAN);
            if (receiverQuery.exec() && receiverQuery.next())
            {
                QString receiverUsername = receiverQuery.value(15).toString();
                QSqlQuery senderQuery;
                senderQuery.prepare("SELECT * FROM users WHERE Username = :username");
                senderQuery.bindValue(":username", username);

                if (senderQuery.exec() && senderQuery.next())
                {
                    double senderBalance = senderQuery.value(19).toDouble();
                    bool conversionOK;
                    double amount = amountStr.toDouble(&conversionOK);

                    if (conversionOK && senderBalance >= amount)
                    {
                        QSqlQuery receiverQuery;
                        receiverQuery.prepare("SELECT * FROM users WHERE Username = :username");
                        receiverQuery.bindValue(":username", receiverUsername);

                        if (receiverQuery.exec() && receiverQuery.next())
                        {
                            double senderNewBalance = senderBalance - amount;
                            double receiverBalance = receiverQuery.value(19).toDouble();
                            double receiverNewBalance = receiverBalance + amount;

                            // Update sender's balance
                            QSqlQuery updateSenderQuery;
                            updateSenderQuery.prepare("UPDATE users SET balance = :newBalance WHERE Username = :username");
                            updateSenderQuery.bindValue(":newBalance", senderNewBalance);
                            updateSenderQuery.bindValue(":username", username);

                            // Update receiver's balance
                            QSqlQuery updateReceiverQuery;
                            updateReceiverQuery.prepare("UPDATE users SET balance = :newBalance WHERE Username = :username");
                            updateReceiverQuery.bindValue(":newBalance", receiverNewBalance);
                            updateReceiverQuery.bindValue(":username", receiverUsername);

                            if (updateSenderQuery.exec() && updateReceiverQuery.exec())
                            {
                                // Insert the transaction record
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
                                insertQuery.bindValue(":Description", "Transfer to " + receiverUsername);

                                if (insertQuery.exec())
                                {
                                    QTreeWidgetItem* item = new QTreeWidgetItem(ui->Transactions_tr_TW);
                                    item->setText(0, QDateTime::currentDateTime().toString()); // Assuming the first column is for the date and time
                                    item->setText(1, receiverIBAN);
                                    item->setText(2, senderQuery.value(1).toString() + senderQuery.value(2).toString());
                                    item->setText(3, firstName + lastName);
                                    item->setText(4, type);
                                    item->setText(5, amountStr);
                                    item->setText(6, "Transfer to " + receiverUsername);

                                    // Add the item to the QTreeWidget
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
    }
}

