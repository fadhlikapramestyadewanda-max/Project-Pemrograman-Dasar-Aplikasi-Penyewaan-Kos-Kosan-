#include "userstorage.h"

// initialize static members
QString UserStorage::s_username = QString();
QString UserStorage::s_password = QString();
QMap<QString,int> UserStorage::s_roomQty = QMap<QString,int>();
int UserStorage::s_duration = 0;
QString UserStorage::s_paymentMethod = QString();
int UserStorage::s_totalPrice = 0;
QString UserStorage::s_uploadedFileName = QString();

// ---------------- Account ----------------
void UserStorage::setAccount(const QString &username, const QString &password)
{
    s_username = username;
    s_password = password;
}

void UserStorage::clearAccount()
{
    s_username.clear();
    s_password.clear();
}

bool UserStorage::hasAccount()
{
    return !s_username.isEmpty();
}

bool UserStorage::checkCredentials(const QString &username, const QString &password)
{
    // simple equality check
    return (!s_username.isEmpty()) && (username == s_username) && (password == s_password);
}

QString UserStorage::username()
{
    return s_username;
}

void UserStorage::setPassword(const QString &pwd)
{
    s_password = pwd;
}

// ---------------- Order ----------------
void UserStorage::setRoomQty(const QString &type, int qty)
{
    if (qty <= 0) {
        s_roomQty.remove(type);
    } else {
        s_roomQty[type] = qty;
    }
}

int UserStorage::roomQty(const QString &type)
{
    return s_roomQty.value(type, 0);
}

const QMap<QString,int> &UserStorage::allRoomQty()
{
    return s_roomQty;
}

void UserStorage::setAllRoomQty(const QMap<QString,int> &map)
{
    s_roomQty = map;
}

void UserStorage::setDuration(int months)
{
    if (months < 0) months = 0;
    s_duration = months;
}

int UserStorage::duration()
{
    return s_duration;
}

// ---------------- Payment ----------------
void UserStorage::setPaymentMethod(const QString &method)
{
    s_paymentMethod = method;
}

QString UserStorage::paymentMethod()
{
    return s_paymentMethod;
}

void UserStorage::setTotalPrice(int price)
{
    s_totalPrice = price;
}

int UserStorage::totalPrice()
{
    return s_totalPrice;
}

void UserStorage::setUploadedFileName(const QString &fileName)
{
    s_uploadedFileName = fileName;
}

QString UserStorage::uploadedFileName()
{
    return s_uploadedFileName;
}

// ---------------- Reset ----------------
void UserStorage::resetAll()
{
    // reset account? In your request you asked to reset "data yang tersimpan" after finish.
    // Usually we keep account (user) but remove order/payment data.
    // Here I'll clear order/payment but keep account by default.
    // If you want to clear account too, uncomment the two lines below.

    // clearAccount(); // <-- uncomment if you want sign-up data cleared on Finish

    s_roomQty.clear();
    s_duration = 0;
    s_paymentMethod.clear();
    s_totalPrice = 0;
    s_uploadedFileName.clear();
}
