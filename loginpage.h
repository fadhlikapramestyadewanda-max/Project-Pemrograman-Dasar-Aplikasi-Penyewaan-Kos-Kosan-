#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

namespace Ui {
class LogInPage;
}

class LogInPage : public QWidget
{
    Q_OBJECT

public:
    explicit LogInPage(QWidget *parent = nullptr);
    ~LogInPage();

    // Reset input ketika user kembali ke halaman ini
    void resetPage();

signals:
    void backRequested();      // kembali ke FirstPage
    void loginSuccess();       // menuju OrderPopupPage setelah login sukses

private slots:
    void onBackClicked();
    void onLoginClicked();

private:
    Ui::LogInPage *ui;
};

#endif // LOGINPAGE_H
