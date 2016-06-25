#include "assoc_person.h"

Assoc_person::Assoc_person(QString n1,vector <Record> &re)
{
    //通过构造函数对类进行初始化
    username=n1;
    record = re;
}
