#ifndef Contact_H
#define Contact_H
#include <QString>

using namespace std;

class Contact
{
private:
    QString number;
    QString surname;
    QString name;
    QString diller;
public:
    Contact();
    Contact(QString number, QString surname,QString name,QString diller);
    Contact(Contact &object);
    ~Contact();
    QString getNumber();
    void setNumber(QString number);
    QString getSurname();
    void setSurname(QString surname);
    QString getName();
    void setName(QString name);
    QString getDiller();
    void setDiller(QString diller);
    QString output();
    Contact operator=(Contact &object);
};

#endif // Contact_H
