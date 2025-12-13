#include "orderpopup.h"
#include "ui_orderpopup.h"   // HARUS sama dengan nama file hasil uic

#include <QPushButton>

OrderPopup::OrderPopup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrderPopupPage)   // WAJIB sesuai class UI
{
    ui->setupUi(this);

    // Hubungkan tombol orderButton ke slot
    connect(ui->orderButton, &QPushButton::clicked,
            this, &OrderPopup::onOrderClicked);
}

OrderPopup::~OrderPopup()
{
    delete ui;
}

void OrderPopup::onOrderClicked()
{
    emit goToOrderPage();
}
