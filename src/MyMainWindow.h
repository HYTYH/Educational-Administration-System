/****************************************************************************
 * Copyright (c)2020, by Beijing University of Post and Telecommunications
 * All rights reserved.
 * FileName：		MyMainWindow.h
 * System：          	Windows 10
 * Author：		Yanbo Liu | Yihong Tang
 * Date：		2020.12.03
 * Version：		1.1
 * Description：
        登录窗口类，用于连接数据库，输入、验证用户名密码，根据登录信息打开窗口
 *
 * Last Modified:

    2020.11.25      By Yanbo Liu | Yihong Tang
                修改UI
    2020.11.11, 	By Yanbo Liu
                完成初始版本
****************************************************************************/
#pragma once
#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H
#include "MyDatabase.h"
#include "ScheduleTable.h"
#include "SubThreadQuery.h"
#include <QMainWindow>
#include <QSet>
#include <QKeyEvent>
extern MyDatabase DatabaseInstance;
namespace Ui {
    class MyMainWindow;
}

class MyMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MyMainWindow(QWidget* parent = 0);
    // ///////////////////////////////////////////////////////////////////
    // Function：		MyMainWindow(QWidget *parent = 0);
    // Description:     登录窗口构造函数。初始化控件，连接槽函数。
    // Args：
    //      parent      父窗口的对象指针
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    ~MyMainWindow();
    // ///////////////////////////////////////////////////////////////////
    // Function：		~MyMainWindow();
    // Description:     登录窗口析构函数。
    // Args：
    //      void
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

public slots:

    void RecieveQueryResult(QList<QString> QueryResult, int QueryState, int QueryID);
    /*用于接收子查询结果并执行对应操作的槽函数*/

protected:

    void keyPressEvent(QKeyEvent *e);
    /*用于处理回车事件*/

    void closeEvent(QCloseEvent* Event);
    /*用于处理关闭事件*/

private slots:

    void UserConnectToServer();
    //点击重新连接数据库按钮对应的槽函数

    void UserLogin();
    //点击登录按钮对应的槽函数

private:

    Ui::MyMainWindow* ui;
    //对象的图形界面指针ui

    QSet<int> LoginApplyQueryID;
    //登录请求查询的ID集合
};

#endif // MYMAINWINDOW_H
