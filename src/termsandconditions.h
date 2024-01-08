#ifndef TERMSANDCONDITIONS_H
#define TERMSANDCONDITIONS_H

#include <QWidget>

namespace Ui {
class TermsAndConditions;
}

class TermsAndConditions : public QWidget
{
    Q_OBJECT

public:
    explicit TermsAndConditions(QWidget *parent = nullptr);
    ~TermsAndConditions();

    bool getStatus();

private slots:
    void on_Agree_PB_clicked();

    void on_Cancel_PB_clicked();

private:
    Ui::TermsAndConditions *ui;

    bool m_accepted;
};

#endif // TERMSANDCONDITIONS_H
