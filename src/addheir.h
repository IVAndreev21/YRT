#ifndef ADDHEIR_H
#define ADDHEIR_H

#include <QWidget>
#include <QSqlQuery>
#include <QCryptographicHash>
namespace Ui {
class AddHeir;
}

class AddHeir : public QWidget
{
    Q_OBJECT

public:
    explicit AddHeir(QString& username_ref, QWidget *parent = nullptr);
    ~AddHeir();

private slots:
    void on_heir_LE_editingFinished();

    void on_password_LE_editingFinished();

    void on_addHeir_PB_clicked();

private:
    Ui::AddHeir *ui;
    QString username;

    QString hash(const QString& toHash, const QString& salt);
};

#endif // ADDHEIR_H
