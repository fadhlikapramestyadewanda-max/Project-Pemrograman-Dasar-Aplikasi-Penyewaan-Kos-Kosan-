#include "signuppage.h"
#include "ui_signuppage.h"
#include <QMessageBox>

SignUpPage::SignUpPage(UserStorage *storage, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUpPage)
    , userStorage(storage)
{
    ui->setupUi(this);

    // Connect tombol
    connect(ui->backButton, &QPushButton::clicked,
            this, &SignUpPage::onBackClicked);

    connect(ui->createButton, &QPushButton::clicked,
            this, &SignUpPage::onCreateClicked);
}

SignUpPage::~SignUpPage()
{
    delete ui;
}

void SignUpPage::resetPage()
{
    ui->usernameInput->clear();
    ui->passwordInput->clear();
}

void SignUpPage::onBackClicked()
{
    resetPage();
    emit backRequested();
}

void SignUpPage::onCreateClicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    // Validasi
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Semua field harus diisi!");
        return;
    }

    // Cek apakah akun sudah pernah dibuat sebelumnya (single user)
    if (UserStorage::hasAccount()) {
        QMessageBox::warning(this, "Warning",
                             "Akun telah dibuat sebelumnya!\nSilakan Log In.");
        return;
    }

    // Simpan akun ke UserStorage
    UserStorage::setAccount(username, password);

    QMessageBox::information(this, "Success",
                             "Akun berhasil dibuat!\nSilakan Log In.");

    resetPage();
    emit goToLoginPage();
}
