#ifndef RECORD_H
#define RECORD_H
#include <QString>
#include <QDateTime>

class Record
{
public:
    Record(QString f_u,QString t_u,double mon,QString stu,QString ty);
    //不包含时间的构造函数，用于产生记录时构建，参数分别表示交易发起者、交易接收者、交易金额、交易状态、交易类型
    Record(QString f_u,QString t_u,double mon,QString stu,QString ty,QString ti);
    //包含时间的构造函数，用于从数据库中取出数据时使用，参数分别表示交易发起者、交易接收者、交易金额、交易状态、交易类型、交易时间
    QString from_u;//交易的发起者
    QString to_u;//交易的接受者
    double money;//交易数额
    QString time;//交易时间
    QString status;//交易状况：成功、失败（余额不足，转账用户不存在）
    QString type;//交易类型：存款，取款，转账
};


#endif // RECORD_H
