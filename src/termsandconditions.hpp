#pragma once

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
    void on_agree_PB_clicked();

    void on_cancel_PB_clicked();

private:
    Ui::TermsAndConditions *ui;

    bool m_accepted;
};
