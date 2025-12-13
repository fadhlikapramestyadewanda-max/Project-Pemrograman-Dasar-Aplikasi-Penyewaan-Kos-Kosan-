#ifndef CONFIRMPAGE_H
#define CONFIRMPAGE_H

#include <QWidget>

namespace Ui {
class ConfirmPage;
}

class ConfirmPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConfirmPage(QWidget *parent = nullptr);
    ~ConfirmPage();

    // Menerima data dari OrderPage
    void setOrderData(int a, int b, int c, int d, int e, int duration);

    // Untuk reset jika user kembali ke orderpage
    void resetPage();

signals:
    void goToEditPage();     // kembali ke OrderPage
    void goToPaymentPage(    // ke PaymentPage dengan data final
        int totalRooms,
        int duration,
        int totalPrice
        );

private slots:
    void onSaveClicked();
    void onEditClicked();

private:
    Ui::ConfirmPage *ui;

    int qtyA;
    int qtyB;
    int qtyC;
    int qtyD;
    int qtyE;
    int duration;

    int totalRooms;
    int totalPrice;

    void updateReceipt();
};

#endif // CONFIRMPAGE_H
