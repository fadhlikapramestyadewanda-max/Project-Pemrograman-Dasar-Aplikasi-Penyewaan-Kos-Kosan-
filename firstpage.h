#ifndef FIRSTPAGE_H
#define FIRSTPAGE_H

#include <QWidget>

namespace Ui {
class FirstPage;
}

class FirstPage : public QWidget
{
    Q_OBJECT

public:
    explicit FirstPage(QWidget *parent = nullptr);
    ~FirstPage();

    // Reset UI ke kondisi awal
    void resetPage();

signals:
    void loginRequested();      // pindah ke LogInPage
    void signupRequested();     // pindah ke SignUpPage

private slots:
    void onLogInClicked();
    void onSignUpClicked();

private:
    Ui::FirstPage *ui;
};

#endif // FIRSTPAGE_H
