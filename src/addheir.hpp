#pragma once
#include <QWidget>
#include <QSqlQuery>
#include <QCryptographicHash>

class MainWindow;

namespace Ui {
class AddHeir;
}

class AddHeir : public QWidget
{
    Q_OBJECT

public:
    AddHeir(std::shared_ptr<MainWindow> mainwindow, QString& username_ref, QWidget* parent = nullptr);
    ~AddHeir();

private slots:
    void on_heir_LE_editingFinished();

    void on_password_LE_editingFinished();

    void on_addHeir_PB_clicked();

    void on_abort_PB_clicked();

private:
    Ui::AddHeir* ui;
    QString m_username;

    QString Hash(const QString& toHash, const QString& salt);

    std::shared_ptr<MainWindow> m_mainwindow;
};
