#ifndef PERSON_H
#define PERSON_H
#include <qstring.h>
class Person
{
public:
    Person(QString n1,double m1,QString p); //构造函数，参数分别表示用户名、余额、密码
    Person();
    QString username;//用户名
    double money;//余额
    QString pwd;//密码
    int type;//1为普通用户，2为关系用户
};


#endif // PERSON_H
