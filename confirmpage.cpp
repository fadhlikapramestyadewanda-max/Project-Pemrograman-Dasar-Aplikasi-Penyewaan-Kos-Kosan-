#include "confirmpage.h"
#include "ui_confirmpage.h"

ConfirmPage::ConfirmPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConfirmPage)
    , qtyA(0), qtyB(0), qtyC(0), qtyD(0), qtyE(0)
    , duration(1), totalRooms(0), totalPrice(0)
{
    ui->setupUi(this);

    connect(ui->btnSave, &QPushButton::clicked, this, &ConfirmPage::onSaveClicked);
    connect(ui->btnEdit, &QPushButton::clicked, this, &ConfirmPage::onEditClicked);
}

ConfirmPage::~ConfirmPage()
{
    delete ui;
}

void ConfirmPage::resetPage()
{
    qtyA = qtyB = qtyC = qtyD = qtyE = 0;
    duration = 1;
    totalRooms = 0;
    totalPrice = 0;

    ui->labelReceiptContent->setText("Belum ada pesanan.");
}

void ConfirmPage::setOrderData(int a, int b, int c, int d, int e, int dur)
{
    qtyA = a;
    qtyB = b;
    qtyC = c;
    qtyD = d;
    qtyE = e;
    duration = dur;

    totalRooms = qtyA + qtyB + qtyC + qtyD + qtyE;

    // Harga dasar
    int priceA = 700000;
    int priceB = 1200000;
    int priceC = 950000;
    int priceD = 1400000;
    int priceE = 2000000;

    totalPrice =
        qtyA * priceA +
        qtyB * priceB +
        qtyC * priceC +
        qtyD * priceD +
        qtyE * priceE;

    totalPrice *= duration;

    updateReceipt();
}

void ConfirmPage::updateReceipt()
{
    QString text;

    text += "NOTA PEMESANAN\n";
    text += "----------------------------\n";
    text += QString("Durasi: %1 bulan\n\n").arg(duration);

    if (qtyA > 0) text += QString("Kamar Tipe A x%1\n").arg(qtyA);
    if (qtyB > 0) text += QString("Kamar Tipe B x%1\n").arg(qtyB);
    if (qtyC > 0) text += QString("Kamar Tipe C x%1\n").arg(qtyC);
    if (qtyD > 0) text += QString("Kamar Tipe D x%1\n").arg(qtyD);
    if (qtyE > 0) text += QString("Kamar Tipe E x%1\n").arg(qtyE);

    text += "----------------------------\n";
    text += QString("Total Kamar : %1\n").arg(totalRooms);
    text += QString("Total Harga : Rp%1\n").arg(totalPrice);

    ui->labelReceiptContent->setText(text);
}

/* ================== BUTTON SAVE ================== */
void ConfirmPage::onSaveClicked()
{
    emit goToPaymentPage(
        totalRooms,
        duration,
        totalPrice
        );
}

/* ================== BUTTON EDIT ================== */
void ConfirmPage::onEditClicked()
{
    emit goToEditPage();
}
