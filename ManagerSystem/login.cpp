#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //将函数与信号函数连接
    connect(ui->regist,SIGNAL(clicked()),this,SLOT(sign_up()));
    connect(ui->login,SIGNAL(clicked()),this,SLOT(log_in()));
    connect(ui->exit,SIGNAL(clicked()),this,SLOT(exit()));
    connect(ui->username,SIGNAL(textEdited(QString)),this,SLOT(edit_text()));
}

void Login::showEvent(QShowEvent *)
{
    ui->username->setFocus();//设置焦点
    //绘制背景图片
    QImage* img=new QImage;
    if(img->load(":/src/UI/login.png"))
    {
        //qDebug()<<1;
    }
    else
    {
        //qDebug()<<0;
    }
    QImage* imgScaled = new QImage;
    *imgScaled=img->scaled(960,
                           523);
    ui->background->setPixmap(QPixmap::fromImage(*imgScaled));
}

void Login::log_in()
{
    QString username = ui->username->text();
    QString pwd = ui->password->text();
    if(username!=""&&pwd!="")
    {
        mysql sql;
        vector <Person> result = sql.select_person(username);
        if(result.size())
        {
            if(result[0].pwd==pwd)
            {
                emit sendData(username);//登录成功将用户名信息发给主窗口
                this->accept();//退出登录窗口
            }
            else
            {
                QMessageBox::critical(0, QObject::tr("提示"), "密码错误");
            }
        }
        else
        {
            QMessageBox::critical(0, QObject::tr("提示"), "用户名错误");
        }
    }
    else{
        QMessageBox::critical(0, QObject::tr("提示"), "用户名/密码不能为空");
    }
}

void Login::keyPressEvent(QKeyEvent  *keyEvent)
{
//    QPoint aaa = cursor().pos();
//    ui->username->setText(QString::number(aaa.rx())+" "+QString::number(aaa.ry()));
    if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
    {
        log_in();//回车登录
    }
}

void Login::sign_up()
{
    QString username = ui->username->text();
    QString pwd = ui->password->text();
    if(username!=""&&pwd!="")
    {
        mysql sql;
        vector <Person> tmp =sql.select_person(username);
        if (tmp.size()){
            QMessageBox::critical(0, QObject::tr("提示"),"已注册过改账户，请登录!");
            //如果查询到结果则表明注册过，注册失败
        }
        else{
            Person t(username,0.00,pwd);
            if(sql.insert_person(t))
            {
                QMessageBox::information(0,"提示","注册成功啦！你的密码是："+pwd);
            }
        }
    }
    else{
        QMessageBox::critical(0, QObject::tr("提示"), "用户名/密码不能为空");
    }
}

Login::~Login()
{
    delete ui;
}

//窗口移动
void Login::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = true;
        mLastMousePosition = event->globalPos();
    }
}

void Login::mouseMoveEvent(QMouseEvent* event)
{
    if( event->buttons().testFlag(Qt::LeftButton) && mMoving)
    {
        this->move(this->pos() + (event->globalPos() - mLastMousePosition));
        mLastMousePosition = event->globalPos();
    }
}

void Login::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        mMoving = false;
    }
}

void Login::exit()
{
    QTimer::singleShot(0,qApp,SLOT(quit()));
}

void Login::edit_text()
{
    QString tmp = ui->username->text();
    QString result;
    for(int i=0;i<tmp.length();i++)
    {
        if(tmp[i]!=' ')
        {
            result+=tmp[i];
            //qDebug()<<"1";
        }
    }
    ui->username->setText(result);
}
