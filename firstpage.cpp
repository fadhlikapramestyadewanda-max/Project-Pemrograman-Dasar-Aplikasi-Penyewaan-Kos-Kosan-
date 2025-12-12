#include "firstpage.h"
#include "ui_firstpage.h"

FirstPage::FirstPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FirstPage)
{
    ui->setupUi(this);

    // Connect tombol sesuai nama widget asli
    connect(ui->logInButton, &QPushButton::clicked,
            this, &FirstPage::onLogInClicked);

    connect(ui->signUpButton, &QPushButton::clicked,
            this, &FirstPage::onSignUpClicked);
}

FirstPage::~FirstPage()
{
    delete ui;
}

void FirstPage::resetPage()
{
    // FirstPage tidak memiliki input field
    // jadi hanya placeholder
}

// Tombol Log In diklik → pindah ke LogInPage
void FirstPage::onLogInClicked()
{
    emit loginRequested();
}

// Tombol Sign Up diklik → pindah ke SignUpPage
void FirstPage::onSignUpClicked()
{
    emit signupRequested();
}
