#ifndef PAYMENTPAGE_H
#define PAYMENTPAGE_H

#include <QWidget>

namespace Ui {
class PaymentPage;
}

class PaymentPage : public QWidget
{
    Q_OBJECT

public:
    explicit PaymentPage(QWidget *parent = nullptr);
    ~PaymentPage();

    // Menerima data dari ConfirmPage
    void setPaymentData(int totalRooms, int duration, int totalPrice);

    // Getter fileName untuk dipakai main.cpp bila perlu
    QString selectedFileName() const;

    // Reset semua data setelah tombol FINISH ditekan (dipanggil dari main.cpp)
    void resetPage();

signals:
    // Tambahkan fileName agar dikirim ke ReceiptPage
    void goToReceiptPage(int rooms,
                         int duration,
                         QString method,
                         int totalPrice,
                         QString fileName);

private slots:
    void onPaymentMethodChanged();
    void onChooseFileClicked();
    void onDoneClicked();

private:
    Ui::PaymentPage *ui;

    // Data pembayaran
    int m_rooms;
    int m_duration;
    int m_totalPrice;

    // Pilihan user
    QString m_selectedMethod;
    QString m_fileName;   // nama file bukti pembayaran
};

#endif // PAYMENTPAGE_H
