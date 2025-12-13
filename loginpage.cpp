#include "loginpage.h"
#include "ui_loginpage.h"
#include "userstorage.h"

#include <QMessageBox>

LogInPage::LogInPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LogInPage)
{
    ui->setupUi(this);

    // Connect tombol
    connect(ui->backButton, &QPushButton::clicked,
            this, &LogInPage::onBackClicked);

    connect(ui->loginButton, &QPushButton::clicked,
            this, &LogInPage::onLoginClicked);
}

LogInPage::~LogInPage()
{
    delete ui;
}

void LogInPage::resetPage()
{
    ui->usernameInput->clear();
    ui->passwordInput->clear();
}

void LogInPage::onBackClicked()
{
    resetPage();
    emit backRequested();
}

void LogInPage::onLoginClicked()
{
    QString username = ui->usernameInput->text().trimmed();
    QString password = ui->passwordInput->text().trimmed();

    // Validasi input kosong
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Username dan password harus diisi!");
        return;
    }

    // Cek apakah sudah ada akun
    if (!UserStorage::hasAccount()) {
        QMessageBox::warning(this, "Error",
                             "Belum ada akun yang terdaftar!\nSilakan Sign Up terlebih dahulu.");
        return;
    }

    // Cek kredensial
    if (!UserStorage::checkCredentials(username, password)) {
        QMessageBox::warning(this, "Error",
                             "Username atau password salah!");
        return;
    }

    // Login berhasil
    QMessageBox::information(this, "Success", "Login berhasil!");

    resetPage();
    emit loginSuccess();
}
