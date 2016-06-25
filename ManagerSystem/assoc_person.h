#ifndef ASSOC_PERSON_H
#define ASSOC_PERSON_H
#include <person.h>
#include <vector>
#include <record.h>
using namespace std;
class Assoc_person : public Person
{
public:
    Assoc_person(QString n1,vector <Record> &re);//构造函数，参数分别表示用户名，和所有当前用户与他有关的记录
    vector <Record> record;//相关的记录，用Vector容器存储
};


#endif // ASSOC_PERSON_H
