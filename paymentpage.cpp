#include "paymentpage.h"
#include "ui_paymentpage.h"

#include <QFileDialog>
#include <QString>

PaymentPage::PaymentPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaymentPage),
    m_rooms(0),
    m_duration(0),
    m_totalPrice(0),
    m_selectedMethod(),
    m_fileName()
{
    ui->setupUi(this);

    // Radio button: Saat dipilih, update labelPaymentInfo
    connect(ui->radioQRIS, &QRadioButton::toggled, this, &PaymentPage::onPaymentMethodChanged);
    connect(ui->radioEwallet, &QRadioButton::toggled, this, &PaymentPage::onPaymentMethodChanged);
    connect(ui->radioTransfer, &QRadioButton::toggled, this, &PaymentPage::onPaymentMethodChanged);

    // Tombol pilih file
    connect(ui->btnChooseFile, &QPushButton::clicked,
            this, &PaymentPage::onChooseFileClicked);

    // Tombol Done
    connect(ui->btnDone, &QPushButton::clicked,
            this, &PaymentPage::onDoneClicked);

    ui->labelPaymentInfo->setText("Silakan pilih metode pembayaran.");
    ui->labelFileName->setText("No file chosen");
}

PaymentPage::~PaymentPage()
{
    delete ui;
}

// Terima data dari ConfirmPage
void PaymentPage::setPaymentData(int rooms, int duration, int totalPrice)
{
    m_rooms = rooms;
    m_duration = duration;
    m_totalPrice = totalPrice;

    ui->labelTotalRooms->setText(QString::number(rooms));
    ui->labelDuration->setText(QString::number(duration) + " bulan");
    ui->labelTotalPrice->setText("Rp " + QString::number(totalPrice));
}

// Slot saat radio button berubah
void PaymentPage::onPaymentMethodChanged()
{
    if (ui->radioQRIS->isChecked()) {
        m_selectedMethod = "QRIS";
        ui->labelPaymentInfo->setText("Scan QR code untuk melakukan pembayaran.");
    }
    else if (ui->radioEwallet->isChecked()) {
        m_selectedMethod = "E-Wallet";
        ui->labelPaymentInfo->setText("Silakan transfer via OVO/DANA/GoPay ke nomor 0812-XXX-XXX.");
    }
    else if (ui->radioTransfer->isChecked()) {
        m_selectedMethod = "Transfer Bank";
        ui->labelPaymentInfo->setText("Silakan transfer ke Bank BCA: 1234567890 a.n Kost Simple Stay.");
    }
}

// Pilih file bukti pembayaran
void PaymentPage::onChooseFileClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose Payment Proof");

    if (!file.isEmpty()) {
        // simpan hanya nama file (bukan path) seperti implementasimu sebelumnya
        m_fileName = file.section('/', -1); // atau file.split("/").last()
        ui->labelFileName->setText(m_fileName);
    }
}

// Tombol DONE -> lanjut ke ReceiptPage
void PaymentPage::onDoneClicked()
{
    if (m_selectedMethod.isEmpty()) {
        ui->labelPaymentInfo->setText("⚠ Pilih metode pembayaran terlebih dahulu.");
        return;
    }

    // Emit dengan 5 argumen sesuai deklarasi di header
    emit goToReceiptPage(
        m_rooms,
        m_duration,
        m_selectedMethod,
        m_totalPrice,
        m_fileName
        );
}

// Reset page (dipanggil ketika user klik FINISH di ReceiptPage)
void PaymentPage::resetPage()
{
    m_rooms = 0;
    m_duration = 0;
    m_totalPrice = 0;
    m_selectedMethod.clear();
    m_fileName.clear();

    ui->labelTotalRooms->setText("-");
    ui->labelDuration->setText("-");
    ui->labelTotalPrice->setText("-");

    // Reset pilihan radio buttons
    ui->radioQRIS->setAutoExclusive(false);
    ui->radioEwallet->setAutoExclusive(false);
    ui->radioTransfer->setAutoExclusive(false);

    ui->radioQRIS->setChecked(false);
    ui->radioEwallet->setChecked(false);
    ui->radioTransfer->setChecked(false);

    ui->radioQRIS->setAutoExclusive(true);
    ui->radioEwallet->setAutoExclusive(true);
    ui->radioTransfer->setAutoExclusive(true);

    ui->labelPaymentInfo->setText("Silakan pilih metode pembayaran.");
    ui->labelFileName->setText("No file chosen");
}

// Getter nama file
QString PaymentPage::selectedFileName() const
{
    return m_fileName;
}
