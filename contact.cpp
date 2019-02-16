#include "contact.h"

Contact::Contact():number(""),surname(""),name(""),diller("")
{
}

Contact::Contact(QString number, QString surname,QString name,QString diller):number(number),surname(surname),name(name),diller(diller)
{
}

Contact::Contact(Contact &object):number(object.number),surname(object.surname),name(object.name),diller(object.diller)
{
}

Contact::~ Contact()
{
}

QString Contact::getNumber()
{
    return this->number;
}

void Contact::setNumber(QString number)
{
    this->number = number;
}

QString Contact::getSurname()
{
    return this->surname;
}

void Contact::setSurname(QString surname)
{
    this->surname = surname;
}

QString Contact::getName()
{
    return this->name;
}

void Contact::setName(QString name)
{
    this->name = name;
}


QString Contact::getDiller()
{
    return this->diller;
}

void Contact::setDiller(QString diller)
{
    this->diller = diller;
}

QString Contact::output()
{
    if(number.isEmpty()||surname.isEmpty()||name.isEmpty()||diller.isEmpty()){
        return "";
    }
    QString s = number+" "+surname+" "+name+" "+diller+" ";
    return s.simplified();
}


Contact Contact::operator =(Contact &object){
    if (&object == this)
        return *this;
    setNumber(object.number);
    setSurname(object.surname);
    setName(object.name);
    setDiller(object.diller);
    return *this;
}
