#include "termsandconditions.h"
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
    QLabel* label = ui->TermsAndConditions_LA;

    lay->addWidget(label);
    ui->scrollContents->setLayout(lay);
}

TermsAndConditions::~TermsAndConditions()
{
    delete ui;
}

void TermsAndConditions::on_Agree_PB_clicked()
{
    m_accepted = true;
    this->hide();
}


void TermsAndConditions::on_Cancel_PB_clicked()
{
    m_accepted = false;
    this->hide();

}

