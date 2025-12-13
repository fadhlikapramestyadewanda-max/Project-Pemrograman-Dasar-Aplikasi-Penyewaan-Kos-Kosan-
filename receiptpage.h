#ifndef RECEIPTPAGE_H
#define RECEIPTPAGE_H

#include <QWidget>

namespace Ui {
class ReceiptPage;
}

class ReceiptPage : public QWidget
{
    Q_OBJECT

public:
    explicit ReceiptPage(QWidget *parent = nullptr);
    ~ReceiptPage();

    // Untuk menerima data dari PaymentPage
    void setReceiptData(int rooms, int duration, const QString &method,
                        int totalPrice, const QString &fileName);

    // Reset halaman setelah finish
    void resetPage();

signals:
    void finishRequested();              // Tombol Finish ditekan
    void downloadPdfRequested(QString);  // Jika nanti ingin support external handling

private slots:
    void onFinishClicked();
    void onDownloadPdfClicked();

private:
    void generatePdf(const QString &filePath);  // Membuat file PDF ukuran A7

private:
    Ui::ReceiptPage *ui;

    QString uploadedFileName;  // Menyimpan nama file bukti pembayaran
};

#endif // RECEIPTPAGE_H
