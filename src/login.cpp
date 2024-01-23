#include "login.hpp"
#include "ui_login.h"
#include <QDebug>
#include <QMessageBox>

// Constructor of logIn class
logIn::logIn(QWidget *parent) : QWidget(parent), ui(new Ui::logIn)
{
    ui->setupUi(this);
    ui->password_LE->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("Log In");

    // Initialize DatabaseManager and ResetCredentials objects
    m_databaseManager = std::make_shared<DatabaseManager>();
    m_databaseManager->OpenConnection();
    m_resetCredentials = std::make_shared<ResetCredentials>(std::shared_ptr<logIn>(this));
}

// Destructor of logIn class
logIn::~logIn()
{
    delete ui;
}

// Function to hash a given password with a provided salt
QString logIn::Hash(const QString &password, const QString &salt) {
    QByteArray passwordWithSalt = (password + salt).toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordWithSalt, QCryptographicHash::Sha256);
    return hashedPassword.toHex();
}

// Function called when the "Log In" button is clicked
void logIn::on_logIn_PB_clicked()
{
    // Retrieve username and password from the UI
    m_username = ui->username_LE->text();
    QString password = ui->password_LE->text();
    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", m_username);

    // Execute the query and check if the user exists
    if (qry.exec() && qry.next())
    {
        // Retrieve hashed password and salt from the database
        QString hashedPasswordFromDB = qry.value("Password").toString();
        QString saltFromDB = qry.value("Password Salt").toString();

        // Hash the entered password for comparison
        QString hashedPasswordToCheck = Hash(password, saltFromDB);

        // Check if the hashed passwords match
        if (hashedPasswordToCheck == hashedPasswordFromDB)
        {
            // Update the "Last Active" field in the database
            QString userIBAN = qry.value("IBAN").toString();
            QDate currentDate = QDate::currentDate();

            qry.prepare("UPDATE users SET `Last Active` = :currentDate WHERE Username = :username");
            qry.bindValue(":currentDate", currentDate);
            qry.bindValue(":username", m_username);

            // Execute the update query and proceed with the login
            if(qry.exec())
            {
                QMessageBox::information(this, "Login Successful", "Welcome to YRT Bank! \n\nYou have successfully logged in.");
                this->hide();
                m_mainWindow = std::make_shared<MainWindow>(this, userIBAN, m_username);
                m_mainWindow->show();
                DisplayEventsNotification();
            }
            else
            {
                // Handle the failure of the update query
                QMessageBox::critical(this, "Failure", "Application error, please contact us immediately");
                qDebug() << qry.lastError();
                qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
                qDebug() << qry.boundValues();  // Print the bound values for further inspection
            }
        }
        else
        {
            // Handle the case of incorrect password
            QMessageBox::critical(this, "Failure", "Wrong password or username");
            qDebug() << qry.lastError();
            qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
            qDebug() << qry.boundValues();  // Print the bound values for further inspection
        }
    }
    else
    {
        // Handle the case of incorrect username
        QMessageBox::critical(this, "Failure", "Wrong password or username");
        qDebug() << qry.lastError();
        qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
        qDebug() << qry.boundValues();  // Print the bound values for further inspection
    }
}

// Function called when the "Forgot Password" link is activated
void logIn::on_forgotenPassword_LA_linkActivated(const QString &link)
{
    // Hide the login window and show the ResetCredentials window
    this->hide();
    m_resetCredentials->show();
}

// Function to display notification events using a Python script
void logIn::DisplayEventsNotification()
{
    // Retrieve the path to the executable and the source folder
    QString executablePath = QCoreApplication::applicationDirPath();
    QProcess process;
    QFileInfo executableInfo(executablePath);
    QString sourceFolderPath = executableInfo.absolutePath() + "/../../../YRT/src";

    // Specify the Python script and username as arguments
    QStringList arguments;
    arguments << "AppleNotification.py" << m_username;

    // Start the Python script as a detached process with the specified working directory
    bool success = QProcess::startDetached("/usr/local/bin/python3.12", arguments, sourceFolderPath);

    // Check if the process started successfully
    if (!success) {
        qDebug() << "Error starting process: " << process.errorString();
    } else {
        qDebug() << "Process started successfully.";
    }
}
