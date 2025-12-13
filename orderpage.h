#ifndef ORDERPAGE_H
#define ORDERPAGE_H

#include <QWidget>

namespace Ui {
class OrderPage;
}

class OrderPage : public QWidget
{
    Q_OBJECT

public:
    explicit OrderPage(QWidget *parent = nullptr);
    ~OrderPage();

    // Reset saat kembali dari halaman lain
    void resetPage();

signals:
    void goToConfirmPage(
        int qtyA, int qtyB, int qtyC, int qtyD, int qtyE, int duration);

private slots:
    // A
    void onMinusA();
    void onPlusA();
    // B
    void onMinusB();
    void onPlusB();
    // C
    void onMinusC();
    void onPlusC();
    // D
    void onMinusD();
    void onPlusD();
    // E
    void onMinusE();
    void onPlusE();

    void onNextClicked();

private:
    Ui::OrderPage *ui;

    int qtyA;
    int qtyB;
    int qtyC;
    int qtyD;
    int qtyE;

    void updateLabels();
};

#endif // ORDERPAGE_H
