#ifndef ORDERPOPUP_H
#define ORDERPOPUP_H

#include <QWidget>

namespace Ui {
class OrderPopupPage;   // Cocok dengan <class>OrderPopupPage</class>
}

class OrderPopup : public QWidget
{
    Q_OBJECT

public:
    explicit OrderPopup(QWidget *parent = nullptr);
    ~OrderPopup();

signals:
    void goToOrderPage();

private slots:
    void onOrderClicked();

private:
    Ui::OrderPopupPage *ui;  // WAJIB sama dengan nama class di .ui
};

#endif // ORDERPOPUP_H
