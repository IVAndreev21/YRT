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

