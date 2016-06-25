#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <algorithm>
#include <QDebug>
#include <QMessageBox>
#include <qtimer.h>
#include <QMouseEvent>
#include <QDate>
#include <mysql.h>
#include <assoc_person.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
explicit MainWindow(QWidget *parent = 0);
mysql sql;//重用一个数据库类对象，节省资源
    //下面3行用于移动窗口
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    //上面3行用于移动窗口
    void setView();//设置窗口布局
    void update_info();//更新窗口部分信息
    void hide_item();//初始窗口隐藏部分控件
    void setData(vector <Record> &tmp);//表格填充数据函数，参数表示要填充的记录数组
    void setTable(int size);//设置表格，参数表示表格长度
    void setPerson(QString name);//查询关联用户时更改表格，参数表示用户名
    ~MainWindow();

private:
    QPoint mLastMousePosition;//用于窗口移动
    bool mMoving;//用于窗口移动
    QString username;//当前用户名
    Ui::MainWindow *ui;
    int status=0;//区分用户操作，1为存款，2为取款，3为转账，4为查询
    int inquiry_status = 1;//防止重复操作view消耗时间
    QTimer * timer;//定时器
public slots:
    void receiveData(const QString data);
    //槽函数，用于接收Login窗口发射的数据——用户名
private slots:
    void showTime();//动态更新时间
    void on_exit_clicked();//退出按钮单击函数
    void on_save_clicked();//存款按钮单击函数
    void on_pull_clicked();//取款按钮单击函数
    void on_transfer_clicked();//转账按钮单击函数
    void on_inquiry_clicked();//查询按钮单击函数
    void on_confirm_clicked();//确认按钮单击函数
    void on_cancel_clicked();//取消按钮单击函数
    /*各种查询按钮对应的响应函数*/
    void on_my_record_clicked();
    void on_tomy_record_clicked();
    void on_recent_record_clicked();
    void on_user_record_clicked();
    void on_search_result_doubleClicked(const QModelIndex &index);
    //双击关联用户修改表格内容，参数为单击的单元格
    void on_calendar_clicked(const QDate &date);
    //根据日历单击的特定日期查询记录，参数为日期
    void on_day_record_clicked();
    void on_amount_clicked();
    /*各种查询按钮对应的响应函数*/
};


#endif // MAINWINDOW_H
