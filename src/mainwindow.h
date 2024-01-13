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
#include <QSqlQuery>
#include <QBuffer>
#include <QSqlQueryModel>
#include "calendar.h"
#include "crypto.h"
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

    void on_calendar_PB_clicked();

    void on_Send_qt_PB_clicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<Calendar> calendar;
    std::unique_ptr<Crypto> crypto;
    void updatepfp();
    void UpdateTransactions(QTableView* transasctions_TV, QTableView* Recent_tr_TV);
    void performTransaction(const QString& receiverIBAN, const QString& amountStr, const QString& type, const QString& firstName, const QString& lastName);
    void UpdateSettings();
    double userExpenses;
    double userIncome;

    QString IBAN;
    QString username;
    QString clientFName;
    QString clientLName;
    void updateDashboard(QPieSeries* series, QChart* chart, QChartView* chartView);
    bool DetectedAccident();

    QPieSeries* series;
    QChart* chart;
    QChartView* chartView;

    QTableView* transactions_TV;
    QTableView* Recent_tr_TV;

    QString heir;
};

#endif // MAINWINDOW_H
