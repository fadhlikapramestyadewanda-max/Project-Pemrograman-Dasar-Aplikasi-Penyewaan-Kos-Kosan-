#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>
#include "userstorage.h"

namespace Ui {
class SignUpPage;
}

class SignUpPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpPage(UserStorage *storage, QWidget *parent = nullptr);
    ~SignUpPage();

    // Reset input ketika kembali dari halaman lain
    void resetPage();

signals:
    void backRequested();     // kembali ke FirstPage
    void goToLoginPage();     // setelah berhasil membuat akun → ke LogInPage

private slots:
    void onBackClicked();
    void onCreateClicked();

private:
    Ui::SignUpPage *ui;
    UserStorage *userStorage;
};

#endif // SIGNUPPAGE_H
