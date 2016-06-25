#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <mysql.h>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
using namespace std;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent  *keyEvent);
    void showEvent(QShowEvent *);
    //用于移动窗口
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    //用于移动窗口
    ~Login();

private:
    Ui::Login *ui;
    QPoint mLastMousePosition;//用于移动窗口
    bool mMoving;//用于移动窗口
signals:
    void  sendData(QString);//信号函数，登录成功后向主窗口传递用户名
private slots:
    void sign_up();//注册函数
    void log_in();//登录函数
    void exit();//退出
    void edit_text();//对用户名为空的验证，去除首尾空格
};

#endif // LOGIN_H
