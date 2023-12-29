#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QByteArray>
#include <QFileInfo>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QFileDialog>
#include "databasemanager.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& username_ref, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_transactions_PB_clicked();

    void on_pfp_acc_PB_clicked();

    void on_payments_PB_clicked();

    void on_cards_PB_clicked();

    void on_account_PB_clicked();

    void on_administration_PB_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<DatabaseManager> databaseManager;

    void updatepfp();

    QString username;
};

#endif // MAINWINDOW_H
