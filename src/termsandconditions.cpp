#include "termsandconditions.hpp"
#include "ui_termsandconditions.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
TermsAndConditions::TermsAndConditions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TermsAndConditions)
{
    ui->setupUi(this);

    QVBoxLayout* lay = new QVBoxLayout(this);
    QLabel* label = ui->termsAndConditions_LA;

    lay->addWidget(label);
    ui->scrollContents->setLayout(lay);
}

TermsAndConditions::~TermsAndConditions()
{
    delete ui;
}

void TermsAndConditions::on_agree_PB_clicked()
{
    m_accepted = true;
    this->hide();
}


void TermsAndConditions::on_cancel_PB_clicked()
{
    m_accepted = false;
    this->hide();

}

