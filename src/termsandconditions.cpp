#include "termsandconditions.hpp"
#include "ui_termsandconditions.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

// Constructor
TermsAndConditions::TermsAndConditions(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::TermsAndConditions)
{
    ui->setupUi(this);

    // Create a vertical layout
    QVBoxLayout* lay = new QVBoxLayout(this);

    // Get the QLabel from the UI
    QLabel* label = ui->termsAndConditions_LA;

    // Add the QLabel to the layout
    lay->addWidget(label);

    // Set the layout for the scroll area
    ui->scrollContents->setLayout(lay);
}

// Destructor
TermsAndConditions::~TermsAndConditions()
{
    delete ui;
}

// Handle agree button clicked event
void TermsAndConditions::on_agree_PB_clicked()
{
    // Set the accepted flag to true
    m_accepted = true;

    // Hide the Terms and Conditions widget
    this->hide();
}

// Handle cancel button clicked event
void TermsAndConditions::on_cancel_PB_clicked()
{
    // Set the accepted flag to false
    m_accepted = false;

    // Hide the Terms and Conditions widget
    this->hide();
}
