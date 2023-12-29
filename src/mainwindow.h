#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "databasemanager.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& username, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_transactions_PB_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<DatabaseManager> databaseManager;

    void updatepfp();
};

#endif // MAINWINDOW_H
