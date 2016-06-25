#ifndef MYSQL_H
#define MYSQL_H
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <person.h>
#include <vector>
#include <qstring.h>
#include <record.h>
#include <assoc_person.h>
using namespace std;

class mysql
{
public:
    mysql();
    vector <Record> select_recordByfrom(QString name);//通过交易发起者查询记录，参数表示交易发起者用户名
    vector <Record> select_recordByto(QString name);//通过交易接受者查询记录，参数表示交易接收者用户名
    vector <Record> orderbytime(vector <Record> &re);//时间判断，5天内查询，参数表示要记录vector数组
    vector <Assoc_person> assoc_person(QString name);//查询与当前用户交易过的相关用户，参数表示当前用户名
    vector <Record> select_record(QString name);//查询与此用户名有关的所有记录，参数表示用户名
    vector <Record> select_record(QString name,QString user);//查询这两个用户之间所有的交易记录，参数表示用户名
    vector <Person> select_person(QString name);//通过用户名查询信息，参数表示用户名
    vector <Record> select_record(QString user,QString t1,QString t2);//通过给定起始时间和结束时间来查询此区间内的该用户交易记录，参数分别表示用户名、起始时间和结束时间
    int insert_person(Person &p);//注册用，插入用户，参数为插入的用户
    int update_money(QString name, double mon);//更新用户余额，参数为用户名和余额变化量
    int insert_record(Record &r);//插入记录，参数为单条记录
    int transfer_money(QString from_u,QString to_u,double money);
    //转账，参数为发起者用户名，接受者用户名，转账金额
private:
    QSqlDatabase db;//数据库对象
    int link_status;//用于判断数据库连接是否成功
};


#endif // MYSQL_H
