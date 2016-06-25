#include "record.h"

Record::Record(QString f_u,QString t_u,double mon,QString stu,QString ty)
{
    //不包含时间的构造函数，用于产生记录时构建，参数分别表示交易发起者、交易接收者、交易金额、交易状态、交易类型
    from_u=f_u;
    to_u=t_u;
    money=mon;
    status=stu;
    type=ty;
    QDateTime current_date_time = QDateTime::currentDateTime();
    time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
}

Record::Record(QString f_u,QString t_u,double mon,QString stu,QString ty,QString ti)
{
    //包含时间的构造函数，用于从数据库中取出数据时使用，参数分别表示交易发起者、交易接收者、交易金额、交易状态、交易类型、交易时间
    from_u=f_u;
    to_u=t_u;
    money=mon;
    status=stu;
    type=ty;
    time = ti;
}
