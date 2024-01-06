#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QByteArray>
#include <QFileInfo>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QFileDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QLegend>
#include <QtCharts/QChartGlobal>
#include <QTableView>
#include <QTreeWidget>
#include <QPen>
#include "databasemanager.hpp"
#include "calendar.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& IBAN_ref, const QString& username_ref, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dashboard_PB_clicked();

    void on_pfp_acc_PB_clicked();

    void on_transactions_PB_clicked();

    void on_payments_PB_clicked();

    void on_crypto_PB_clicked();

    void on_settings_PB_clicked();

    void on_make_tr_PB_clicked();

    void on_confrim_mt_PB_clicked();

    void on_cancel_mt_PB_clicked();

    void on_Send_QT_PB_clicked();

    void on_calendar_PB_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<DatabaseManager> databaseManager;
    std::unique_ptr<Calendar> calendar;
    QSqlDatabase db;
    void updatepfp();
    void UpdateTransactions(QTableView* transasctions_TV, QTableView* Recent_tr_TV);
    void updatePieChart();
    void performTransaction(const QString& receiverIBAN, const QString& amountStr, const QString& type, const QString& firstName, const QString& lastName);

    double userExpenses;
    double userIncome;

    QString IBAN;
    QString username;
    QString clientFName;
    QString clientLName;
    void updateDashboard(QPieSeries* series, QChart* chart, QChartView* chartView);

    QPieSeries* series;
    QChart* chart;
    QChartView* chartView;

    QTableView* transactions_TV;
    QTableView* Recent_tr_TV;
};

#endif // MAINWINDOW_H
