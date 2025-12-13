#include "receiptpage.h"
#include "ui_receiptpage.h"

#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>

ReceiptPage::ReceiptPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ReceiptPage)
{
    ui->setupUi(this);

    // Connect tombol
    connect(ui->btnFinish, &QPushButton::clicked,
            this, &ReceiptPage::onFinishClicked);

    connect(ui->btnDownloadPdf, &QPushButton::clicked,
            this, &ReceiptPage::onDownloadPdfClicked);

    uploadedFileName.clear();
}

ReceiptPage::~ReceiptPage()
{
    delete ui;
}

void ReceiptPage::resetPage()
{
    ui->labelRooms->setText("0");
    ui->labelDuration->setText("0 bulan");
    ui->labelPaymentMethod->setText("-");
    ui->labelTotalPrice->setText("Rp 0");
    ui->labelUploadedFile->setText("No file uploaded");

    uploadedFileName.clear();
}

void ReceiptPage::setReceiptData(int rooms, int duration, const QString &method,
                                 int totalPrice, const QString &fileName)
{
    uploadedFileName = fileName;

    ui->labelRooms->setText(QString::number(rooms));
    ui->labelDuration->setText(QString::number(duration) + " bulan");
    ui->labelPaymentMethod->setText(method);
    ui->labelTotalPrice->setText("Rp " + QString::number(totalPrice));

    if (fileName.isEmpty())
        ui->labelUploadedFile->setText("No file uploaded");
    else
        ui->labelUploadedFile->setText(fileName);
}

void ReceiptPage::onFinishClicked()
{
    emit finishRequested();
}

/* =====================================================
   ================ GENERATE PDF ========================
   ===================================================== */
void ReceiptPage::onDownloadPdfClicked()
{
    QString defaultName =
        QString("receipt_%1.pdf")
            .arg(QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss"));

    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save Receipt PDF",
        defaultName,
        "PDF Files (*.pdf)"
        );

    if (filePath.isEmpty())
        return;

    if (!filePath.endsWith(".pdf", Qt::CaseInsensitive))
        filePath += ".pdf";

    generatePdf(filePath);

    emit downloadPdfRequested(filePath);
}

void ReceiptPage::generatePdf(const QString &filePath)
{
    QPdfWriter writer(filePath);

    // Gunakan ukuran A7 built-in (74 x 105 mm)
    writer.setPageSize(QPageSize::A7);
    writer.setResolution(300);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        QMessageBox::warning(this, "Error", "Gagal membuat PDF.");
        return;
    }

    // Ambil data dari UI
    QString rooms   = ui->labelRooms->text();
    QString duration = ui->labelDuration->text();
    QString method   = ui->labelPaymentMethod->text();
    QString priceTxt = ui->labelTotalPrice->text();
    QString uploaded = uploadedFileName.isEmpty() ? "No file uploaded" : uploadedFileName;
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // PDF Layout manual
    int x = 20;
    int y = 30;
    int line = 50;

    QFont titleFont("Arial", 10, QFont::Bold);
    QFont bodyFont("Arial", 8);

    painter.setFont(titleFont);
    painter.drawText(x, y, "Order Receipt");
    y += 150;

    painter.setFont(bodyFont);
    painter.drawText(x, y, "Total Rooms: " + rooms);          y += line;
    painter.drawText(x, y, "Duration: " + duration);           y += line;
    painter.drawText(x, y, "Payment Method: " + method);       y += line;
    painter.drawText(x, y, "Total Price: " + priceTxt);        y += line;
    painter.drawText(x, y, "Uploaded File: " + uploaded);      y += 120;
    painter.drawText(x, y, "Generated: " + timestamp);

    painter.end();

    QMessageBox::information(
        this,
        "PDF Saved",
        QString("Receipt berhasil disimpan ke:\n%1").arg(filePath)
        );
}
