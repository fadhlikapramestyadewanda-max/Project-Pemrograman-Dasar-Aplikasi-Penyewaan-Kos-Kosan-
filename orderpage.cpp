#include "orderpage.h"
#include "ui_orderpage.h"

#include <QPushButton>

OrderPage::OrderPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderPage)
    , qtyA(0), qtyB(0), qtyC(0), qtyD(0), qtyE(0)
{
    ui->setupUi(this);

    // Connect tombol A
    connect(ui->btnMinusA, &QPushButton::clicked, this, &OrderPage::onMinusA);
    connect(ui->btnPlusA,  &QPushButton::clicked, this, &OrderPage::onPlusA);

    // Connect tombol B
    connect(ui->btnMinusB, &QPushButton::clicked, this, &OrderPage::onMinusB);
    connect(ui->btnPlusB,  &QPushButton::clicked, this, &OrderPage::onPlusB);

    // Connect tombol C
    connect(ui->btnMinusC, &QPushButton::clicked, this, &OrderPage::onMinusC);
    connect(ui->btnPlusC,  &QPushButton::clicked, this, &OrderPage::onPlusC);

    // Connect tombol D
    connect(ui->btnMinusD, &QPushButton::clicked, this, &OrderPage::onMinusD);
    connect(ui->btnPlusD,  &QPushButton::clicked, this, &OrderPage::onPlusD);

    // Connect tombol E
    connect(ui->btnMinusE, &QPushButton::clicked, this, &OrderPage::onMinusE);
    connect(ui->btnPlusE,  &QPushButton::clicked, this, &OrderPage::onPlusE);

    // Tombol Next
    connect(ui->btnNext, &QPushButton::clicked, this, &OrderPage::onNextClicked);

    updateLabels();
}

OrderPage::~OrderPage()
{
    delete ui;
}

void OrderPage::resetPage()
{
    qtyA = qtyB = qtyC = qtyD = qtyE = 0;
    ui->spinDuration->setValue(1);
    updateLabels();
}

void OrderPage::updateLabels()
{
    ui->labelQtyA->setText(QString::number(qtyA));
    ui->labelQtyB->setText(QString::number(qtyB));
    ui->labelQtyC->setText(QString::number(qtyC));
    ui->labelQtyD->setText(QString::number(qtyD));
    ui->labelQtyE->setText(QString::number(qtyE));
}

/* ======== SLOT KAMAR A ======== */
void OrderPage::onMinusA() { if (qtyA > 0) qtyA--; updateLabels(); }
void OrderPage::onPlusA()  { qtyA++; updateLabels(); }

/* ======== SLOT KAMAR B ======== */
void OrderPage::onMinusB() { if (qtyB > 0) qtyB--; updateLabels(); }
void OrderPage::onPlusB()  { qtyB++; updateLabels(); }

/* ======== SLOT KAMAR C ======== */
void OrderPage::onMinusC() { if (qtyC > 0) qtyC--; updateLabels(); }
void OrderPage::onPlusC()  { qtyC++; updateLabels(); }

/* ======== SLOT KAMAR D ======== */
void OrderPage::onMinusD() { if (qtyD > 0) qtyD--; updateLabels(); }
void OrderPage::onPlusD()  { qtyD++; updateLabels(); }

/* ======== SLOT KAMAR E ======== */
void OrderPage::onMinusE() { if (qtyE > 0) qtyE--; updateLabels(); }
void OrderPage::onPlusE()  { qtyE++; updateLabels(); }

/* ======== NEXT BUTTON ======== */
void OrderPage::onNextClicked()
{
    emit goToConfirmPage(
        qtyA, qtyB, qtyC, qtyD, qtyE,
        ui->spinDuration->value()
        );
}
