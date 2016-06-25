#include "mysql.h"
#include <qdebug.h>
mysql::mysql()
{
    db = QSqlDatabase::addDatabase("QMYSQL"); // 使用mysql数据库驱动
    db.setHostName("localhost");
    db.setDatabaseName("test"); // 数据库名称
    db.setPort(3306);
    db.setUserName("root"); // 用户名
    db.setPassword("root"); // 密码
    link_status = db.open(); // 尝试连接数据库
    if(!link_status)
    {
        qDebug()<<"Open Database Fail! Information:"<<db.lastError().databaseText();
    }
}
vector <Person> mysql::select_person(QString name)
{
    vector <Person> result;
    QSqlQuery query;
    if(name=="")
    {
        return result;
    }
    else
    {
        query.prepare("SELECT * FROM user where name = :name");
        query.bindValue(":name", name);   //在绑定要插入的值
        if (!query.exec()){
            qDebug()<<"执行失败:"<<query.lastError().text();
            return result;
        }
        else{
            QSqlRecord rec = query.record();
            if(query.next())//将数据存储到数组里准备返回
            {
                int pwd_num = rec.indexOf("pwd");
                int money_num = rec.indexOf("money");
                //int size = query.size();
                QString pwd_get = query.value(pwd_num).toString();
                double money = query.value(money_num).toDouble();
                // qDebug()<<QString::number(fieldNo)+":"+QString::number(columnNum);
                Person tmp(name,money,pwd_get);
                result.push_back(tmp);
            }
            return result;
        }
    }
}
int mysql::insert_person(Person &p)
{
    QSqlQuery query;
    query.prepare("INSERT INTO user (name,pwd) VALUES (:name,:pwd)"); //准备执行SQL查询
    query.bindValue(":name", p.username);   //在绑定要插入的值
    query.bindValue(":pwd", p.pwd);
    if (!query.exec()){
        qDebug()<<"插入失败:"<<query.lastError().text();
        return false;
    }
    else{
        return true;
    }
}

int mysql::update_money(QString name,double mon)
{
    vector <Person> tmp = select_person(name);
    if(tmp.size()==0)
    {
        return 3;//用户不存在
    }
    double money = tmp[0].money + mon;
    if(money<0)
    {
        return 2;//2表示余额不足
    }
    QSqlQuery query;
    query.prepare("Update user set money = :money where name = :name"); //准备执行SQL查询
    query.bindValue(":money", money);
    query.bindValue(":name", name);   //在绑定要插入的值
    if(!query.exec())
    {
        qDebug()<<"更新失败:"<<query.lastError().text();
        return 0;
    }
    else
    {
        return 1;
    }
}

int mysql::insert_record(Record &r)
{
    QSqlQuery query;
    query.prepare("INSERT INTO record (from_u,to_u,money,time,status,type) VALUES (:from_u,:to_u,:money,:time,:status,:type)");
    query.bindValue(":from_u", r.from_u);
    query.bindValue(":to_u", r.to_u);
    query.bindValue(":money", r.money);
    query.bindValue(":time", r.time);
    query.bindValue(":status", r.status);
    query.bindValue(":type", r.type);
    if (!query.exec()){
        qDebug()<<"插入失败:"<<query.lastError().text();
        return 0;
    }
    else{
        return 1;
    }
}

int mysql::transfer_money(QString from_u,QString to_u,double money)
{
    int result1=update_money(from_u,-money);
    int result2=update_money(to_u,money);
    QString type = "转账";
    if(result1==1&&result2==1)
    {
        Record tmp(from_u,to_u,money,"成功",type);
        insert_record(tmp);
        return 1;
    }
    else if(result1==2)//用户余额不足
    {
        Record tmp(from_u,to_u,money,"失败，余额不足",type);
        insert_record(tmp);
        update_money(to_u,-money);
        return 2;
    }
    else if(result2==3)//不存在此用户
    {
        Record tmp(from_u,to_u,money,"失败，不存在此用户",type);
        insert_record(tmp);
        update_money(from_u,money);
        return 3;
    }
    return 0;
}

vector <Record> mysql::select_recordByfrom(QString name)
{
    vector <Record> result;
    QSqlQuery query;
    if(name=="")
    {
        return result;
    }
    else
    {
        query.prepare("SELECT * FROM record where from_u = :name order by time desc");
        query.bindValue(":name", name);   //在绑定要插入的值
        if (!query.exec()){
            qDebug()<<"执行失败:"<<query.lastError().text();
            return result;
        }
        else{
            QSqlRecord rec = query.record();
            while(query.next())//将数据存储到数组里准备返回
            {
                int fu_num = rec.indexOf("from_u");
                int tu_num = rec.indexOf("to_u");
                int mo_num = rec.indexOf("money");
                int ti_num = rec.indexOf("time");
                int st_num = rec.indexOf("status");
                int ty_num = rec.indexOf("type");
                QString from_u = query.value(fu_num).toString();
                QString to_u = query.value(tu_num).toString();
                double money = query.value(mo_num).toDouble();
                QString time = query.value(ti_num).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString status = query.value(st_num).toString();//0失败,1成功,2余额不足,3不存在用户
                QString type = query.value(ty_num).toString();
                Record tmp(from_u,to_u,money,status,type,time);
                result.push_back(tmp);
            }
            return result;
        }
    }
}
vector <Record> mysql::select_recordByto(QString name)
{
    vector <Record> result;
    QSqlQuery query;
    if(name=="")
    {
        return result;
    }
    else
    {
        query.prepare("SELECT * FROM record where to_u = :name order by time desc");
        query.bindValue(":name", name);   //在绑定要插入的值
        if (!query.exec()){
            qDebug()<<"执行失败:"<<query.lastError().text();
            return result;
        }
        else{
            QSqlRecord rec = query.record();
            while(query.next())//将数据存储到数组里准备返回
            {
                int fu_num = rec.indexOf("from_u");
                int tu_num = rec.indexOf("to_u");
                int mo_num = rec.indexOf("money");
                int ti_num = rec.indexOf("time");
                int st_num = rec.indexOf("status");
                int ty_num = rec.indexOf("type");
                QString from_u = query.value(fu_num).toString();
                QString to_u = query.value(tu_num).toString();
                double money = query.value(mo_num).toDouble();
                QString time = query.value(ti_num).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString status = query.value(st_num).toString();//0失败,1成功,2余额不足,3不存在用户
                QString type = query.value(ty_num).toString();
                Record tmp(from_u,to_u,money,status,type,time);
                result.push_back(tmp);
            }
            return result;
        }
    }
}

vector <Record> mysql::select_record(QString name)
{
    vector <Record> result;
    QSqlQuery query;
    if(name=="")
    {
        return result;
    }
    else
    {
        query.prepare("SELECT * FROM record where to_u = :name or from_u = :name order by time desc");
        query.bindValue(":name", name);   //在绑定要插入的值
        if (!query.exec()){
            qDebug()<<"执行失败:"<<query.lastError().text();
            return result;
        }
        else{
            QSqlRecord rec = query.record();
            while(query.next())//将数据存储到数组里准备返回
            {
                int fu_num = rec.indexOf("from_u");
                int tu_num = rec.indexOf("to_u");
                int mo_num = rec.indexOf("money");
                int ti_num = rec.indexOf("time");
                int st_num = rec.indexOf("status");
                int ty_num = rec.indexOf("type");
                QString from_u = query.value(fu_num).toString();
                QString to_u = query.value(tu_num).toString();
                double money = query.value(mo_num).toDouble();
                QString time = query.value(ti_num).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString status = query.value(st_num).toString();//0失败,1成功,2余额不足,3不存在用户
                QString type = query.value(ty_num).toString();
                Record tmp(from_u,to_u,money,status,type,time);
                result.push_back(tmp);
            }
            return result;
        }
    }
}

vector <Record> mysql::select_record(QString name,QString user)
{
    vector <Record> result;
    QSqlQuery query;
    if(name=="")
    {
        return result;
    }
    else
    {
        query.prepare("SELECT * FROM record where to_u = :name && from_u = :name1 order by time desc");
        query.bindValue(":name", name);   //在绑定要插入的值
        query.bindValue(":name1", user);   //在绑定要插入的值
        if (!query.exec()){
            qDebug()<<"执行失败:"<<query.lastError().text();
            return result;
        }
        else{
            QSqlRecord rec = query.record();
            while(query.next())//将数据存储到数组里准备返回
            {
                int fu_num = rec.indexOf("from_u");
                int tu_num = rec.indexOf("to_u");
                int mo_num = rec.indexOf("money");
                int ti_num = rec.indexOf("time");
                int st_num = rec.indexOf("status");
                int ty_num = rec.indexOf("type");
                QString from_u = query.value(fu_num).toString();
                QString to_u = query.value(tu_num).toString();
                double money = query.value(mo_num).toDouble();
                QString time = query.value(ti_num).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
                QString status = query.value(st_num).toString();//0失败,1成功,2余额不足,3不存在用户
                QString type = query.value(ty_num).toString();
                Record tmp(from_u,to_u,money,status,type,time);
                result.push_back(tmp);
            }
            query.prepare("SELECT * FROM record where from_u = :name && to_u = :name1 order by time desc");//准备执行数据库操作
            query.bindValue(":name", name);   //在绑定要插入的值
            query.bindValue(":name1", user);   //在绑定要插入的值
            if (!query.exec()){
                qDebug()<<"执行失败:"<<query.lastError().text();
                return result;
            }
            else{
                QSqlRecord rec = query.record();
                while(query.next())
                {
                    int fu_num = rec.indexOf("from_u");
                    int tu_num = rec.indexOf("to_u");
                    int mo_num = rec.indexOf("money");
                    int ti_num = rec.indexOf("time");
                    int st_num = rec.indexOf("status");
                    int ty_num = rec.indexOf("type");
                    QString from_u = query.value(fu_num).toString();
                    QString to_u = query.value(tu_num).toString();
                    double money = query.value(mo_num).toDouble();
                    QString time = query.value(ti_num).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
                    QString status = query.value(st_num).toString();//0失败,1成功,2余额不足,3不存在用户
                    QString type = query.value(ty_num).toString();
                    Record tmp(from_u,to_u,money,status,type,time);
                    result.push_back(tmp);
                }
            }
            return result;
        }
    }
}

vector <Record> mysql::orderbytime(vector <Record> &re)//根据时间查询
{
    vector <Record> result;
    QDateTime cur_time(QDate::currentDate());
    cur_time = cur_time.addDays(-4);
    for(int i=0;i<re.size();i++)
    {
        QDateTime tmp = QDateTime::fromString(re[i].time,"yyyy-MM-dd hh:mm:ss");
        if(tmp>=cur_time)
        {
            result.push_back(re[i]);
        }
    }
    return result;
}

vector <Assoc_person> mysql::assoc_person(QString name)
{
    vector <QString> result;
    vector <Assoc_person> final_result;
    QSqlQuery query;
    if(name=="")
    {
        return final_result;
    }
    else
    {
        query.prepare("SELECT distinct from_u FROM record where to_u = :name");//准备执行数据库操作
        query.bindValue(":name", name);   //在绑定要插入的值
        if (!query.exec()){
            qDebug()<<"执行失败:"<<query.lastError().text();
            return final_result;
        }
        else{
            QSqlRecord rec = query.record();
            while(query.next())//将数据存储到数组里准备返回
            {
                int fu_num = rec.indexOf("from_u");
                QString from_u = query.value(fu_num).toString();
                result.push_back(from_u);
            }
            query.prepare("SELECT distinct to_u FROM record where from_u = :name && to_u not in "
                          "(SELECT distinct from_u FROM record where to_u = :name)");//准备执行数据库操作
            query.bindValue(":name", name);   //在绑定要插入的值
            if (!query.exec()){
                qDebug()<<"执行失败:"<<query.lastError().text();
                return final_result;
            }
            else{
                QSqlRecord rec1 = query.record();
                while(query.next())
                {
                    int tu_num = rec1.indexOf("to_u");
                    QString to_u = query.value(tu_num).toString();
                    result.push_back(to_u);
                }
            }
        }
        for(int i=0;i<result.size();i++)
        {
            vector <Record> tmp = select_record(result[i],name);
            if(result[i] != name)
            {
                Assoc_person person(result[i],tmp);
                final_result.push_back(person);
            }
        }
        return final_result;
    }
}

bool comp(Record a,Record b)
{
    QDateTime t1= QDateTime::fromString(a.time);
    QDateTime t2= QDateTime::fromString(b.time);
    return t1 > t2;
}

vector <Record> mysql::select_record(QString user,QString t1,QString t2)
{
    vector <Record> result;
    QSqlQuery query;
    query.prepare("SELECT * FROM record where ( to_u = :name or from_u = :name) "
                  "&& time >= :time && time < :time1 order by time desc");//准备执行数据库操作
    query.bindValue(":name", user);   //在绑定要插入的值
    query.bindValue(":time", t1);   //在绑定要插入的值
    query.bindValue(":time1", t2);   //在绑定要插入的值
    if (!query.exec()){
        qDebug()<<"执行失败:"<<query.lastError().text();
        return result;
    }
    else{
        QSqlRecord rec = query.record();
        while(query.next())//将数据存储到数组里准备返回
        {
            int fu_num = rec.indexOf("from_u");
            int tu_num = rec.indexOf("to_u");
            int mo_num = rec.indexOf("money");
            int ti_num = rec.indexOf("time");
            int st_num = rec.indexOf("status");
            int ty_num = rec.indexOf("type");
            QString from_u = query.value(fu_num).toString();
            QString to_u = query.value(tu_num).toString();
            double money = query.value(mo_num).toDouble();
            QString time = query.value(ti_num).toDateTime().toString("yyyy-MM-dd hh:mm:ss");
            QString status = query.value(st_num).toString();//0失败,1成功,2余额不足,3不存在用户
            QString type = query.value(ty_num).toString();
            Record tmp(from_u,to_u,money,status,type,time);
            result.push_back(tmp);
        }
        sort(result.begin(),result.end(),comp);//利用sort函数进行排序
        return result;
    }
}
