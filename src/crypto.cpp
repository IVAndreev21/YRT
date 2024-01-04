#include "crypto.h"
#include "ui_crypto.h"

Crypto::Crypto(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Crypto)
{
    ui->setupUi(this);
}

Crypto::~Crypto()
{
    delete ui;
}
