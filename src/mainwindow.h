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
#include "addheir.h"

class logIn;
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(logIn* login, const QString& IBAN_ref, const QString& username_ref, QWidget *parent = nullptr);
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

    void on_addHeir_PB_clicked();

    void on_signOut_PB_clicked();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Calendar> m_calendar;
    std::shared_ptr<Crypto> m_crypto;
    std::shared_ptr<AddHeir> m_addHeir;
    void updatepfp();
    void UpdateTransactions(QTableView* transasctions_TV, QTableView* Recent_tr_TV);
    void performTransaction(const QString& receiverIBAN, const QString& amountStr, const QString& type, const QString& firstName, const QString& lastName);
    void UpdateSettings();
    double m_userExpenses;
    double m_userIncome;

    QString m_IBAN;
    QString m_username;
    QString m_clientFName;
    QString m_clientLName;
    void updateDashboard(QPieSeries* series, QChart* chart, QChartView* chartView);
    bool DetectedAccident();

    QPieSeries* series;
    QChart* chart;
    QChartView* chartView;

    QTableView* transactions_TV;
    QTableView* Recent_tr_TV;

    QString m_heir;
};

#endif // MAINWINDOW_H
