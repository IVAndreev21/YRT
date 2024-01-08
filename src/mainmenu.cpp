#include "mainmenu.h"
#include "ui_mainmenu.h"
#include <QProcess>
#include <QProcessEnvironment>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent), ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    launchPythonScript();
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_LogIn_PB_clicked()
{
    logInWindow = new logIn(nullptr);
    this->hide();
    logInWindow->show();
}

void MainMenu::on_Register_PB_clicked()
{
    registerWindow = new Register(nullptr);
    this->hide();
    registerWindow->show();
}

void MainMenu::launchPythonScript()
{
    // Use QProcess to run the Python script
    QString path = "C:/Users/boyan/PycharmProjects/pythonProject1";
    QString  command("C:/Users/boyan/AppData/Local/Programs/Python/Python312/python.exe");
    QStringList params = QStringList() << "yrt.py";

    QProcess *process = new QProcess();
    process->startDetached(command, params, path);
    process->waitForFinished();
    process->close();
}
