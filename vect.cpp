#include "vect.h"
#include <QString>
#include <QStringList>
#include <QFile>



    Vect::Vect():size(10),last_index(-1),length(0)
    {
        arr = new Contact [size];
    }

    Vect::Vect(int l):size(l),last_index(-1),length(0)
    {
        arr = new Contact [size];
    }

    Vect::Vect(Vect &obj):size(obj.size),last_index(obj.last_index),length(obj.length)
    {
        for(int i = 0; i<length; i++){
            this->arr[i] = obj.arr[i];
        }
    }

    Vect::~Vect()
    {
        delete [] arr;
    }

    void Vect::doubling()
    {
        Contact *n_arr = new Contact[length];

                for(int i = 0; i<length; i++){
                    n_arr[i]=arr[i];
                }
                size *=2;

                arr = new Contact[size];

                for(int i = 0; i<length; i++){
                    arr[i]=n_arr[i];
                }

                delete [] n_arr;
    }

    void Vect::pushback(Contact obj)
    {
        try
        {
            if(size == length){
               throw 0;
            }
            arr[last_index+1] = obj;
            last_index++;
            length++;
        }
        catch(int err)
        {
            if(err==0){
            this->doubling();
            this->pushback(obj);
            }
        }
    }


    void Vect::del(int place)
    {
        try
        {
            if((place < 0)||(place>size))
            {
                throw 1;
            }
            else if(place == length)
            {
                throw 2;
            }
            for(int i = place-1; i<last_index; i++){
                arr[i]=arr[i+1];
            }
            last_index--;
            length--;
        }
        catch(int error)
        {
            switch(error){
                case(1): break;
                case(2): last_index--; length--; break;
            }

        }
    }


    void Vect::unite(Vect &obj)
    {
        if(obj.length+length<size){
            for(int i = 0; i<=obj.last_index; i++){
                this->arr[length+i]=obj.arr[i];
                last_index++;
            }
            length=last_index+1;
        }
        else
        {
            size = obj.length+length;
            Contact *n_arr = new Contact[size];
            for(int i = 0; i<length; i++){
                n_arr[i]=arr[i];
            }
            for(int i = length; i<size; i++){
                n_arr[i]=obj.arr[i-length];
            }
            this->arr = new Contact[size];
            length +=obj.length;
            last_index = length-1;

            for(int i = 0; i<size; i++){
                arr[i]=n_arr[i];
            }

            delete [] n_arr;
        }
    }

    void Vect::resize(int i)
    {
        arr = new Contact[i];
        size = i;
        last_index = -1;
        length = 0;
    }

    void Vect::readFromFile(QString filename)
    {
        QString str;
        QStringList list;
        QFile file(filename);
        int i = 0;
        file.open(QIODevice::ReadOnly |QIODevice::Text);
        while(!file.atEnd()){
            str = file.readLine();
            list = str.split(" ");
            if(list.length()==4){
                this->arr[i].setNumber(list[0]);
                this->arr[i].setSurname(list[1]);
                this->arr[i].setName(list[2]);
                this->arr[i].setDiller(list[3]);
                i++;
            }
            else
                continue;
        }
        file.close();
        length = i;
        last_index = length-1;
        arr[last_index].setDiller(arr[last_index].getDiller());
    }

    void Vect::setSize(int i)
    {
        size = i;
    }

    int Vect::getSize()
    {
        return size;
    }

    void Vect::setLength(int i)
    {
        this->length = i;
    }

    int Vect::getLength()
    {
        return length;
    }

    void Vect::setLastIndex(int i)
    {
        this->last_index = i;
    }

    int Vect::getLastIndex()
    {
        return last_index;
    }

    Contact* Vect::getArr()
    {
        return arr;
    }

    void Vect::setElem(int i, Contact obj)
    {
        arr[i] = obj;
    }

    Contact & Vect::operator[] (int i)
    {
        return this->arr[i];
    }


