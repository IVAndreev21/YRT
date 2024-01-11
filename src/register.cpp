#include "register.h"
#include "ui_register.h"

Register::Register(QWidget *parent)
    : QWidget(parent), ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->password_LE->setEchoMode(QLineEdit::Password);
    LogIn = std::make_unique<logIn>();
    this->setWindowTitle("Register");
    databaseManager = std::make_unique<DatabaseManager>();
    databaseManager->openConnection();
    db = databaseManager->getDatabase();

    termsAndConditions = std::make_unique<TermsAndConditions>();
    termsAndConditions->setParent(this);
    termsAndConditions->hide();
    m_accepted = false;
}

Register::~Register()
{
    delete ui;
}

void Register::on_next1_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Register::on_previous1_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Register::on_next2_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Register::on_previous2_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Register::on_next3_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void Register::on_previous3_PB_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void Register::on_submit_PB_clicked()
{
    bool usernameTaken = false;
    bool ssnTaken = false;
    bool phoneTaken = false;

    QString firstName = ui->first_name_LE->text();
    QString lastName = ui->last_name_LE->text();
    QString DateOfBirth = ui->date_of_birth_DE->text();
    QString gender = ui->gender_CB->currentText();
    QString SSN = ui->SSN_LE->text();
    QString SSNToCheck = ui->SSN_LE->text();
    QString street = ui->street_LE->text();
    QString city = ui->city_LE->text();
    QString stateProvince = ui->state_province_LE->text();
    QString postalCode = ui->postal_code_LE->text();
    QString phone = ui->phone_LE->text();
    QString phoneToCheck = ui->phone_LE->text();
    QString email = ui->email_LE->text();
    QString status = ui->status_CB->currentText();
    QString income = ui->income_LE->text();
    QString type = ui->type_CB->currentText();
    QString username = ui->username_LE->text();
    QString usernameToCheck = ui->username_LE->text();
    QString password = ui->password_LE->text();
    QString securityQuestion = ui->security_question_CB->currentText();
    QString securityAnswer = ui->security_question_LE->text();
    QList<int> randomNumbers;

    for (int i = 0; i < 10; ++i) {
        int randomNumber = QRandomGenerator::global()->bounded(10);
        randomNumbers.append(randomNumber);
    }

    QString randomNumbersString;
    for (int number : randomNumbers) {
        randomNumbersString.append(QString::number(number));
    }


    QString passwordSalt = generateSalt();
    QString securityAnswerSalt = generateSalt();

    QString hashedPassword = hashPassword(password, passwordSalt);
    QString hashedSecurityAnswer = hashPassword(securityAnswer, securityAnswerSalt);

    QString IBAN = "BG" + QString::number(QRandomGenerator::global()->bounded(10, 100)) + "YRT9661" + randomNumbersString;

    QSqlQuery qry;
    qry.prepare("SELECT * FROM users WHERE Username = :username");
    qry.bindValue(":username", usernameToCheck);
    if (qry.exec() && qry.next()) {
        usernameTaken = true;
    }

    qry.prepare("SELECT * FROM users WHERE SSN = :ssn");
    qry.bindValue(":ssn", SSNToCheck);
    if (qry.exec() && qry.next()) {
        ssnTaken = true;
    }

    qry.prepare("SELECT * FROM users WHERE Phone = :phone");
    qry.bindValue(":phone", phoneToCheck);
    if (qry.exec() && qry.next()) {
        phoneTaken = true;
    }

    if (usernameTaken) {
        QMessageBox::critical(this, "Error", "Username is already taken.");
    }

    if (ssnTaken) {
        QMessageBox::critical(this, "Error", "SSN is already taken.");
    }

    if (phoneTaken) {
        QMessageBox::critical(this, "Error", "Phone number is already taken.");
    }
    if(!m_accepted)
    {
        QMessageBox::critical(this, "Error", "Please agree to our terms and conditions before registrating an account");

    }


    if (!usernameTaken && !ssnTaken && !phoneTaken && m_accepted) {
        qry.prepare("INSERT INTO users (`First Name`, `Last Name`, `Date of birth`, Gender, SSN, Street, City, `State/Province`, `Postal code`, Phone, Email, `Employment Status`, Income, Type, Username, Password, `Security question`, `Security answer`, IBAN, `Password Salt`, `Security Answer Salt`)"
                    "VALUES (:First_Name, :Last_Name, :Date_of_birth, :Gender, :SSN, :Street, :City, :State_Province, :Postal_code, :Phone, :Email, :Employment_Status, :Income, :Type, :Username, :Password, :Security_question, :Security_answer, :IBAN, :passwordSalt, :SQSalt)");

        qry.bindValue(":First_Name", firstName);
        qry.bindValue(":Last_Name", lastName);
        qry.bindValue(":Date_of_birth", DateOfBirth);
        qry.bindValue(":Gender", gender);
        qry.bindValue(":SSN", SSN);
        qry.bindValue(":Street", street);
        qry.bindValue(":City", city);
        qry.bindValue(":State_Province", stateProvince);
        qry.bindValue(":Postal_code", postalCode);
        qry.bindValue(":Phone", phone);
        qry.bindValue(":Email", email);
        qry.bindValue(":Employment_Status", status);
        qry.bindValue(":Income", income);
        qry.bindValue(":Type", type);
        qry.bindValue(":Username", username);
        qry.bindValue(":Password", hashedPassword);
        qry.bindValue(":Security_question", securityQuestion);
        qry.bindValue(":Security_answer", hashedSecurityAnswer);
        qry.bindValue(":IBAN", IBAN);
        qry.bindValue(":passwordSalt", passwordSalt);
        qry.bindValue(":SQSalt", securityAnswerSalt);

        if (qry.exec()) {
            QMessageBox::information(this, "Success", "Your registration to trawma bank has been successful. \n\nRedirecting to the login page..");
            this->hide();
            LogIn->show();
        } else {
            QMessageBox::critical(this, "Failure", "Data has not been inserted successfully. Try again or contact us ");
            qDebug() << qry.lastError().text();
            qDebug() << qry.lastQuery();  // Print the last executed query for further inspection
            qDebug() << qry.boundValues();  // Print the bound values for further inspection
        }
    }
}


QString Register::generateSalt() {
    // Generate a random salt
    QByteArray salt;
    for (int i = 0; i < 16; ++i) {
        salt.append(QRandomGenerator::global()->generate());
    }
    return salt.toHex();
}

QString Register::hashPassword(const QString& password, const QString& salt) {
    QByteArray passwordWithSalt = (password + salt).toUtf8();
    QByteArray hashedPassword = QCryptographicHash::hash(passwordWithSalt, QCryptographicHash::Sha256);
    return hashedPassword.toHex();
}

void Register::on_Terns_and_conditions_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked)
    {
        termsAndConditions->move(QPoint(ui->Terns_and_conditions->pos().x() - 400, ui->Terns_and_conditions->pos().y() - 300));
        termsAndConditions->show();
        m_accepted = true;
    }
    else if(arg1 == Qt::Unchecked)
    {
        termsAndConditions->hide();
        m_accepted = false;
    }
}

