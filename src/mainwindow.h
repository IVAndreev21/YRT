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
#include <QPen>
#include "databasemanager.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(const QString& IBAN_ref, QWidget *parent = nullptr);
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

private:
    Ui::MainWindow *ui;
    std::unique_ptr<DatabaseManager> databaseManager;
    QSqlDatabase db;
    void updatepfp();
    void populateTransactionTreeWidget();
    void updatePieChart();

    double userExpenses;
    double userIncome;

    QString IBAN;

    void updateDashboard();
};

#endif // MAINWINDOW_H
