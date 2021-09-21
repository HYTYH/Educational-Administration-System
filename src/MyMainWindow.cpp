#include "MyMainWindow.h"
#include "ui_MyMainWindow.h"

MyMainWindow::MyMainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MyMainWindow),
    LoginApplyQueryID({})
{
    /*设置UI*/
    ui->setupUi(this);

    /*设置图片背景，控件透明度，密码输入回显模式*/
    this->ui->LabelBackGround->setPixmap(QPixmap(":/new/MainWindowBackGround_School_2.png"));
    this->ui->LabelBackGround->setScaledContents(true);
    this->ui->UsernameLineEdit->setStyleSheet("border :1px ;background-color: rgba(200,200,200,200)");
    this->ui->PasswordLineEdit->setStyleSheet("border :1px ;background-color: rgba(200,200,200,200)");
    this->ui->LoginPushButton->setStyleSheet("border :1px ;background-color: rgba(200,200,200,200)");
    this->ui->PasswordLineEdit->setEchoMode(QLineEdit::Password);

    /*连接登录按钮和数据库连接按钮到槽函数*/
    connect(this->ui->ConnectPushButton, SIGNAL(clicked()), this, SLOT(UserConnectToServer()));
    connect(this->ui->LoginPushButton, SIGNAL(clicked()), this, SLOT(UserLogin()));

    /*启动窗口时默认尝试连接一次数据库*/
    UserConnectToServer();

}

MyMainWindow::~MyMainWindow()
{
    delete ui;
    this->deleteLater();
}

void MyMainWindow::RecieveQueryResult(QList<QString> QueryResult, int QueryState, int QueryID) {
    if (QueryState != 0) {

        /*查询状态不对*/
        qDebug() << "不正确的查询状态" << QueryState << endl;
        return;
    }

    if (LoginApplyQueryID.contains(QueryID) == false) {

        /*查询ID不对*/
        qDebug() << "未知登录查询ID?\n";
        return;
    }
    else {

        /*查询ID存在，将其删除*/
        LoginApplyQueryID.remove(QueryID);
    }

    /*开始后续操作*/
    QList<QString>& SqlResult = QueryResult;

    if (SqlResult.size() <= 1) {
        qDebug() << "size:" << SqlResult.size();
        QMessageBox::information(NULL, "登录失败", "用户名或密码错误");
    }
    else if (SqlResult[1] == USER_STUDENT) {

        /*学生登陆成功，提示，然后创建课程表窗口*/
        QMessageBox::information(NULL, "登陆成功", "学生登陆成功");

        QString Username = SqlResult[0];
        ScheduleTable* NewTable = new ScheduleTable(Username);
        NewTable->show();

    }
    else if (SqlResult[1] == USER_ADMIN) {
        QMessageBox::information(NULL, "登陆成功", "管理员登陆成功");
    }
    else {
        QMessageBox::information(NULL, "Alert", "登录返回信息错误，请检查数据库");
    }

}

void MyMainWindow::keyPressEvent(QKeyEvent *e){

    //qDebug()<<"hhh "<<e->key()<<endl;

    /*回车按钮则登录*/
    if(e->key()==Qt::Key_Return){
        UserLogin();
    }

}

void MyMainWindow::closeEvent(QCloseEvent* Event){

    /*提示用户是否确认退出*/
    QMessageBox:: StandardButton result= QMessageBox::information(NULL, "提示", "确认退出？",QMessageBox::Yes|QMessageBox::No);

    if(result==QMessageBox::No){

        /*不退出*/
        return;
    }
    else{

        /*退出程序界面*/
        this->close();
        //this->deleteLater();
    }

}

void MyMainWindow::UserConnectToServer() {

    /*重新设置、连接数据库*/
    DatabaseInstance.SetDataBase(this->ui->DatabaseInfoTextEdit->toPlainText(), "", "", "");
    if (DatabaseInstance.ConnectToServer() == 1) {

        QMessageBox::information(NULL, "Info", "连接数据库成功");
        this->ui->ConnectPushButton->close();
        this->ui->DatabaseInfoTextEdit->close();
    }
    else {

        QMessageBox::information(NULL, "Info", "连接数据库失败");
    }
}

void MyMainWindow::UserLogin() {

    /*取出用户名密码*/
    QString Username, Password;
    Username = this->ui->UsernameLineEdit->text();
    Password = this->ui->PasswordLineEdit->text();

    /*本地检查输入是否合法*/
    if (Username.length() <= 2) {
        QMessageBox::information(NULL, "Info", "用户名过短");
        return;
    }
    else if (Username.length() > 25) {
        QMessageBox::information(NULL, "Info", "用户名过长");
        return;
    }
    if (Password.length() <= 2) {
        QMessageBox::information(NULL, "Info", "密码过短");
        return;
    }
    else if (Password.length() > 25) {
        QMessageBox::information(NULL, "Info", "密码过长");
        return;
    }

    /*构造查询语句进行查询*/
    QString Operation = "select username,usertype from tb_userinfo where username=\""
        + Username + QString("\" and password=\"") + Password + QString("\" ;");

    /*生成独一无二的查询ID*/
    int QueryID = 1 + qrand() % 10000000;
    while (LoginApplyQueryID.contains(QueryID) == true) {
        QueryID = 1 + qrand() % 10000000;
    }

    /*开始查询*/
    SubThreadQuery* nQuery = new SubThreadQuery(&DatabaseInstance, Operation, 2, QueryID);
    LoginApplyQueryID.insert(QueryID);
    connect(nQuery, SIGNAL(SendQueryResult(QList<QString>, int, int)), this,
        SLOT(RecieveQueryResult(QList<QString>, int, int)));
    nQuery->start();

}
