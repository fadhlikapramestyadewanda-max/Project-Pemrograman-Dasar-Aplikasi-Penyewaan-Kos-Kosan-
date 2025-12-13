#ifndef USERSTORAGE_H
#define USERSTORAGE_H

#include <QString>
#include <QMap>

/*
  UserStorage
  - Static storage untuk user/account + order + payment summary.
  - Dipanggil secara global tanpa perlu instance:
      UserStorage::setUsername("alia");
      if (UserStorage::checkCredentials("alia", "pwd")) { ... }
      UserStorage::resetAll(); // reset semua data ke default
*/

class UserStorage
{
public:
    // ------ Account (SignUp / Login) ------
    static void setAccount(const QString &username, const QString &password);
    static void clearAccount();
    static bool hasAccount();
    static bool checkCredentials(const QString &username, const QString &password);
    static QString username();
    // password getter intentionally omitted for safety (but available if you need);
    static void setPassword(const QString &pwd);

    // ------ Order data (room quantities + duration) ------
    // roomQty keys: "A","B","C","D","E"
    static void setRoomQty(const QString &type, int qty);
    static int roomQty(const QString &type); // returns 0 if not set
    static const QMap<QString,int> &allRoomQty();
    static void setDuration(int months);
    static int duration();

    // a convenience method to set whole map at once
    static void setAllRoomQty(const QMap<QString,int> &map);

    // ------ Payment summary ------
    static void setPaymentMethod(const QString &method);
    static QString paymentMethod();

    static void setTotalPrice(int price); // in IDR (integer)
    static int totalPrice();

    static void setUploadedFileName(const QString &fileName);
    static QString uploadedFileName();

    // ------ Reset everything to defaults ------
    static void resetAll();

private:
    // disallow construction
    UserStorage() = delete;
    ~UserStorage() = delete;
    UserStorage(const UserStorage&) = delete;
    UserStorage& operator=(const UserStorage&) = delete;

    // internal storage
    static QString s_username;
    static QString s_password; // stored here only for demo/simple app (not secure)
    static QMap<QString,int> s_roomQty;
    static int s_duration;
    static QString s_paymentMethod;
    static int s_totalPrice;
    static QString s_uploadedFileName;
};

#endif // USERSTORAGE_H
