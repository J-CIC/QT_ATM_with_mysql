#include "mainwindow.h"
#include "login.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Login *login_dlg = new Login;
    login_dlg->setWindowFlags(Qt::FramelessWindowHint);//设置无边框窗口
    connect(login_dlg,SIGNAL(sendData(QString)),this,SLOT(receiveData(QString)));//连接用户名的发射接收函数
    login_dlg->exec();//运行登录窗口
    if(login_dlg->result()==0)
    {
        QTimer::singleShot(0,qApp,SLOT(quit()));//若选择退出登录，结束程序
    }
    setView();//设置视图
}

void MainWindow::setView()
{
    timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start(1000);
    QImage* img=new QImage;
    if(img->load("./src2.jpg"))
    {
        //qDebug()<<1;
    }
    else
    {
        //qDebug()<<0;
    }
    QImage* imgScaled = new QImage;
    *imgScaled=img->scaled(151,171);
    ui->img->setPixmap(QPixmap::fromImage(*imgScaled));
    hide_item();//隐藏不需要显示的控件
}

void MainWindow::hide_item()//隐藏不需要显示的控件
{
    ui->money_save->setVisible(false);
    ui->money_pull->setVisible(false);
    ui->money_transname->setVisible(false);
    ui->money_transmon->setVisible(false);
    ui->search_result->setVisible(false);
    ui->search_result->clearContents();
    ui->money_transname->setText("");
    ui->money_transmon->setText("");
    ui->money_save->setText("");
    ui->money_pull->setText("");
    ui->search_result->clearContents();
    ui->search_result->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->search_result->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->search_result->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->search_result->setSelectionMode(QAbstractItemView::NoSelection);
    ui->search_result->verticalHeader()->setVisible(false); //设置垂直头不可见
    ui->recent_record->setVisible(false);
    ui->user_record->setVisible(false);
    ui->my_record->setVisible(false);
    ui->tomy_record->setVisible(false);
    ui->calendar->setVisible(false);
    ui->day_record->setVisible(false);
    ui->amount->setVisible(false);
    ui->mon_status->setVisible(false);
}

void MainWindow::showTime()//显示系统时间
{
    QTime time = QTime::currentTime();
    QDate qdateObj = QDate::currentDate();
    QString text = qdateObj.toString("yyyy-M-d");
    text += " ";
    text += time.toString("hh:mm:ss");
    ui->time->setText(text);
}

void MainWindow::receiveData(QString data)//接收登录窗口的信息
{
    ui->label->setText(data);
    username=data;
    update_info();
}

void MainWindow::update_info()//更新余额和用户信息
{
    vector <Person> tmp = sql.select_person(username);
    ui->money->setText("￥"+QString::number(tmp[0].money,'f',2));
}

MainWindow::~MainWindow()
{
    delete ui;
}
//窗口移动
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->move(this->pos() + (event->globalPos() - mLastMousePosition));
        mLastMousePosition = event->globalPos();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void MainWindow::on_exit_clicked()
{
    QTimer::singleShot(0,qApp,SLOT(quit()));
}

void MainWindow::on_save_clicked()//存款
{
    hide_item();
    status = 1;
    ui->money_save->setVisible(true);
    ui->money_save->setFocus();
    ui->money_save->setValidator(new QDoubleValidator(0.00,INFINITY,2,this));
    ui->save->setStyleSheet("color:#6bae40;");
    ui->pull->setStyleSheet("color:white;");
    ui->transfer->setStyleSheet("color:white;");
    ui->inquiry->setStyleSheet("color:white;");
}

void MainWindow::on_pull_clicked()//取款
{
    hide_item();
    ui->money_pull->setVisible(true);
    ui->money_pull->setFocus();
    ui->money_pull->setValidator(new QDoubleValidator(0.00,INFINITY,2,this));
    status = 2;
    ui->save->setStyleSheet("color:white;");
    ui->pull->setStyleSheet("color:#6bae40;");
    ui->transfer->setStyleSheet("color:white;");
    ui->inquiry->setStyleSheet("color:white;");
}

void MainWindow::on_transfer_clicked()//转账
{
    hide_item();
    status = 3;
    ui->money_transname->setVisible(true);
    ui->money_transname->setFocus();
    ui->money_transmon->setVisible(true);
    ui->money_transmon->setValidator(new QDoubleValidator(0.00,INFINITY,2,this));
    ui->save->setStyleSheet("color:white;");
    ui->pull->setStyleSheet("color:white;");
    ui->transfer->setStyleSheet("color:#6bae40;");
    ui->inquiry->setStyleSheet("color:white;");
}

void MainWindow::on_inquiry_clicked()//查询
{
    hide_item();
    status = 4;
    ui->search_result->setHorizontalHeaderItem(0,new QTableWidgetItem("发起人"));
    ui->search_result->setHorizontalHeaderItem(1,new QTableWidgetItem("接收人"));
    ui->search_result->setHorizontalHeaderItem(2,new QTableWidgetItem("金额"));
    ui->search_result->setHorizontalHeaderItem(3,new QTableWidgetItem("状态"));
    ui->search_result->setHorizontalHeaderItem(4,new QTableWidgetItem("交易类型"));
    ui->search_result->setHorizontalHeaderItem(5,new QTableWidgetItem("交易时间"));
    inquiry_status = 0;//不必重复更新view
    ui->recent_record->setVisible(true);
    ui->user_record->setVisible(true);
    ui->my_record->setVisible(true);
    ui->tomy_record->setVisible(true);
    ui->day_record->setVisible(true);
    ui->amount->setVisible(true);
    ui->save->setStyleSheet("color:white;");
    ui->pull->setStyleSheet("color:white;");
    ui->transfer->setStyleSheet("color:white;");
    ui->inquiry->setStyleSheet("color:#6bae40;");
}

void MainWindow::on_confirm_clicked()//确认操作
{
    switch(status)//对操作状态进行判断
    {
        case 1:
        {
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
            double money = ui->money_save->text().toDouble();
            int res = sql.update_money(username, money);
            QString res_s;
            switch (res) {
            case 0:
                res_s="失败";
                break;
            case 1:
                res_s="成功";
                break;
            case 2:
                res_s="失败，余额不足";
            case 3:
                res_s="失败，不存在此用户";
                break;
            }
            QString type = "存款";
            Record tmp(username,username,money,res_s,type);
            sql.insert_record(tmp);
            if(res==1)
            {
                update_info();
                ui->status->append("你存入￥"+ui->money_save->text()+" <span style='color:#6bae40;'>成功！</span> "+time);
            }
            else
            {
                ui->status->append("你存入￥"+ui->money_save->text()+" <span style='color:#CD0000;'>失败！</span>原因：系统故障 "+time);
            }
        }
            break;
        case 2:
        {
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
            double money = ui->money_pull->text().toDouble();
            int res = sql.update_money(username, -money);
            QString res_s;
            switch (res) {
            case 0:
                res_s="失败";
                break;
            case 1:
                res_s="成功";
                break;
            case 2:
                res_s="失败，余额不足";
            case 3:
                res_s="失败，不存在此用户";
                break;
            }
            QString type = "取款";
            Record tmp(username,username,-money,res_s,type);
            sql.insert_record(tmp);
            if(res==1)
            {
                update_info();
                ui->status->append("你取出￥"+ui->money_pull->text()+" <span style='color:#6bae40;'>成功！</span> "+time);
            }
            else
            {
                if(res == 2)
                {
                    ui->status->append("你取出￥"+ui->money_pull->text()+" <span style='color:#CD0000;'>失败！</span>"
                                                                     "原因：<span style='color:#CD0000;'>余额不足</span> "+time);
                }
                else
                {
                    ui->status->append("你取出￥"+ui->money_pull->text()+" <span style='color:#CD0000;'>失败！</span>"
                                                                     "原因：<span style='color:#CD0000;'>系统故障</span> "+time);
                }
            }
        }
            break;
        case 3:
        {
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString time = current_date_time.toString("yyyy-MM-dd hh:mm:ss");
            QString transname = ui->money_transname->text();
            transname = transname.trimmed();
            if(username==transname)
            {
                QMessageBox::information(0,"提示","不能给自己转账哦(⊙o⊙)！");
                return ;
            }
            double money = ui->money_transmon->text().toDouble();
            int res = sql.transfer_money(username,transname,money);
            if(res == 1)//转账成功
            {
                update_info();
                ui->status->append("你向用户<span style='color:#6bae40;'>"+transname+"</span>转账￥"+ui->money_transmon->text()+" <span style='color:#6bae40;'>成功！</span> "+time);
            }
            if(res == 2)//余额不足
            {
                update_info();
                ui->status->append("你向用户<span style='color:#6bae40;'>"+transname+"</span>转账￥"+ui->money_transmon->text()+
                                   " <span style='color:#CD0000;'>失败！</span>原因：<span style='color:#CD0000;'>余额不足！</span> "+time);
            }
            if(res == 3)//不存在此用户
            {
                update_info();
                ui->status->append("你向用户<span style='color:#6bae40;'>"+transname+"</span>转账￥"+ui->money_transmon->text()+
                                   " <span style='color:#CD0000;'>失败！</span>原因：不存在此用户！ "+time);
            }
        }
    }
}

void MainWindow::on_cancel_clicked()
{
    hide_item();
    switch(status)
    {
        case 1:
        {
            ui->money_save->setVisible(true);
            ui->money_save->setFocus();
            ui->money_save->setValidator(new QDoubleValidator(0.00,INFINITY,2,this));
        }
        break;
        case 2:
        {
            ui->money_pull->setVisible(true);
            ui->money_pull->setFocus();
            ui->money_pull->setValidator(new QDoubleValidator(0.00,INFINITY,2,this));
        }
        break;
        case 3:
        {
            ui->money_transname->setVisible(true);
            ui->money_transname->setFocus();
            ui->money_transmon->setVisible(true);
            ui->money_transmon->setValidator(new QDoubleValidator(0.00,INFINITY,2,this));
        }
        break;
    }
}

void MainWindow::on_my_record_clicked()
{
//    QDateTime tmp2 = QDateTime::currentDateTime();
//    qDebug()<<"数据库开始"<<tmp2;
    vector <Record> tmp = sql.select_recordByfrom(username);
//    QDateTime tmp1 = QDateTime::currentDateTime();
//    qDebug()<<"数据库结束"<<tmp1;
    setTable(tmp.size());
    setData(tmp);
//    QDateTime tmp3 = QDateTime::currentDateTime();
//    qDebug()<<"全程结束"<<tmp3;
    inquiry_status = 0;//不必重复更新view
}

void MainWindow::on_tomy_record_clicked()
{
    vector <Record> tmp = sql.select_recordByto(username);
    setTable(tmp.size());
    setData(tmp);
    inquiry_status = 0;//不必重复更新view
}

void MainWindow::on_recent_record_clicked()
{
    vector <Record> tmp = sql.select_record(username);
    tmp = sql.orderbytime(tmp);
    setTable(tmp.size());
    setData(tmp);
    inquiry_status = 0;//不必重复更新view
}

void MainWindow::setTable(int size)
{
//    QDateTime tmp2 = QDateTime::currentDateTime();
//    qDebug()<<"setTable开始"<<tmp2;
    ui->search_result->setVisible(false);
    ui->search_result->setRowCount(size);
    ui->search_result->setColumnCount(6);
//    QDateTime tmp4 = QDateTime::currentDateTime();
//    qDebug()<<"setTable 断点1"<<tmp4;
    if(inquiry_status)
    {
        ui->search_result->setHorizontalHeaderItem(0,new QTableWidgetItem("发起人"));
        ui->search_result->setHorizontalHeaderItem(1,new QTableWidgetItem("接收人"));
        ui->search_result->setHorizontalHeaderItem(2,new QTableWidgetItem("金额"));
        ui->search_result->setHorizontalHeaderItem(3,new QTableWidgetItem("状态"));
        ui->search_result->setHorizontalHeaderItem(4,new QTableWidgetItem("交易类型"));
        ui->search_result->setHorizontalHeaderItem(5,new QTableWidgetItem("交易时间"));
    }
//    QDateTime tmp5 = QDateTime::currentDateTime();
//    qDebug()<<"setTable 断点2"<<tmp5;
    ui->search_result->setSelectionMode(QAbstractItemView::NoSelection);
    ui->calendar->setVisible(false);
    ui->mon_status->setVisible(false);
//    QDateTime tmp1 = QDateTime::currentDateTime();
//    qDebug()<<"setTable结束"<<tmp1;
}

void MainWindow::setData(vector <Record>& tmp)
{
//    QDateTime tmp2 = QDateTime::currentDateTime();
//    qDebug()<<"setData开始"<<tmp2;
    for(int i = 0;i<tmp.size();i++)
    {
        ui->search_result->setItem(i,0,new QTableWidgetItem(tmp[i].from_u));
        ui->search_result->setItem(i,1,new QTableWidgetItem(tmp[i].to_u));
        ui->search_result->setItem(i,2,new QTableWidgetItem(QString::number(tmp[i].money,'f',2)));
        ui->search_result->setItem(i,3,new QTableWidgetItem(tmp[i].status));
        ui->search_result->setItem(i,4,new QTableWidgetItem(tmp[i].type));
        ui->search_result->setItem(i,5,new QTableWidgetItem(tmp[i].time));
    }
    ui->search_result->setVisible(true);
//    QDateTime tmp1 = QDateTime::currentDateTime();
//    qDebug()<<"setData结束"<<tmp1;
}

bool compares(Assoc_person a,Assoc_person b)
{
    return a.username < b.username;
}

void MainWindow::on_user_record_clicked()
{
    setTable(0);
    vector <Assoc_person> tmp = sql.assoc_person(username);
    sort(tmp.begin(),tmp.end(),compares);
    ui->search_result->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->search_result->setColumnCount(2);
    ui->search_result->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
    ui->search_result->setHorizontalHeaderItem(0,new QTableWidgetItem("关系用户"));
    ui->search_result->setHorizontalHeaderItem(1,new QTableWidgetItem("交易次数"));
    ui->search_result->clearContents();
    ui->search_result->setRowCount(tmp.size());
    inquiry_status = 1;//下次需要更新表头
    for(int i=0;i<tmp.size();i++)
    {
        ui->search_result->setItem(i,0,new QTableWidgetItem(tmp[i].username));
        ui->search_result->setItem(i,1,new QTableWidgetItem(QString::number(tmp[i].record.size())));
    }
    ui->search_result->setVisible(true);
}

void MainWindow::on_search_result_doubleClicked(const QModelIndex &index)
{
    if(ui->search_result->selectionMode()!=QAbstractItemView::NoSelection)
    {
        QList <QTableWidgetItem*> items = ui->search_result->selectedItems();
        if(!items.isEmpty())
        {
            int row=ui->search_result->row(items.at(0));//获取选中的行
//            qDebug()<<row;
        }
        QTableWidgetItem *item= items.at(0);
        QString name = item->text();//获取内容
        setPerson(name);
        ui->search_result->clearSelection();
    }
}

void MainWindow::setPerson(QString name)
{
    vector <Record> tmp = sql.select_record(name,username);
    setTable(tmp.size());
    setData(tmp);
    inquiry_status = 0;//不必重复更新view
    tmp.clear();
}

void MainWindow::on_calendar_clicked(const QDate &date)
{
    QDateTime tmp(date);
    QString time = tmp.toString("yyyy-MM-dd hh:mm:ss");
    QString time_end = tmp.addDays(1).toString("yyyy-MM-dd hh:mm:ss");
    vector <Record> result = sql.select_record(username,time,time_end);
    setTable(result.size());
    setData(result);
    inquiry_status = 0;//不必重复更新view
    ui->calendar->setVisible(true);
    result.clear();
}

void MainWindow::on_day_record_clicked()
{
    setTable(0);
    ui->calendar->setVisible(true);
}

void MainWindow::on_amount_clicked()
{
    setTable(0);
    ui->mon_status->setVisible(true);
    vector <Person> tmp = sql.select_person(username);
    ui->mon_status->clear();
    ui->mon_status->append("您的账户余额为：<span style='color:#6bae40'>￥"+QString::number(tmp[0].money,'f',2)+"</span>");
    ui->mon_status->append("当前活期利率为：0.5%");
    ui->mon_status->append("您当月预期利息为：<span style='color:#6bae40'>￥"+QString::number(tmp[0].money*0.005,'f',2)+"</span>");
}
