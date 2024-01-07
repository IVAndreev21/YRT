#ifndef CALENDARPOPUP_H
#define CALENDARPOPUP_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class CalendarPopUp;
}

class CalendarPopUp : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarPopUp(const QString& username_ref, QWidget *parent = nullptr);
    ~CalendarPopUp();

private slots:
    void on_Save_PB_clicked();

    void on_Abort_PB_clicked();

private:
    Ui::CalendarPopUp *ui;
    QString username;
};

#endif // CALENDARPOPUP_H
