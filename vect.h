#ifndef VECT_H
#define VECT_H
#include <QString>
#include "contact.h"


class Vect
{
private:
    int size;
    int last_index;
    int length;
    Contact *arr;
public:
    Vect();
    Vect(int l);
    Vect(Vect &obj);
    ~Vect();
    void doubling();
    void pushback(Contact obj);
    void del(int place);
    void unite(Vect &obj);
    void readFromFile(QString filename);
    void resize(int size);
    void setSize(int i);
    int getSize();
    int getLength();
    void setLength(int i);
    void setLastIndex(int i);
    int getLastIndex();
    Contact *getArr();
    void setElem(int i, Contact obj);
    Contact &operator[] (int i);
};





#endif // VECT_H
