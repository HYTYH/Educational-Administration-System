/****************************************************************************
 * Copyright (c)2020, by Beijing University of Post and Telecommunications
 * All rights reserved.
 * FileName：		MyDatabase.h
 * System：          	Windows 10
 * Author：		Yanbo Liu
 * Date：		2020.12.03
 * Version：		1.1
 * Description：
        数据库类，提供简单化的进行数据库连接和数据库操作的方法。
 *
 * Last Modified:

    2020.11.20      By Yanbo Liu
                修改结构，InnerQuery变为公有函数，使得该类不与任何固定查询绑定。
    2020.11.01, 	By Yanbo Liu
                完成初始版本
****************************************************************************/

#pragma once
#ifndef MYDATABASE_H
#define MYDATABASE_H
#include <QString>
#include <QList>
#include <QQueue>
#include <QMutexLocker>
#include <stdio.h>
#include <iostream>
#include <QMutex>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QFile>

#define INFO_USER_NOT_EXISTS -1
#define INFO_PASSWORD_WRONG -2
#define INFO_DATABASE_WRONG -3
#define INFO_STUDENT_LOGIN_SUCC 1
#define INFO_ADMIN_LOGIN_SUCC 2
#define USER_STUDENT "student"
#define USER_STUDENT_NUM 0
#define USER_ADMIN "admin"
#define USER_ADMIN_NUM 1
class MyDatabase
{
private:

    QMutex SharedAreaLock;
    //维护查询过程线程安全的锁

    QMutexLocker SharedAreaLocker;
    //维护查询过程线程安全的高级锁（可以自动释放）

    bool Valid;
    //标识符，用于指示当前数据库是否可以执行操作

    QString DatabaseName, DatabaseAddr, DatabaseUsername, DatabasePassword;
    //数据库的名称，地址，用户名，密码

    QSqlDatabase DB;
    //数据库SQL对象

public:

    virtual QList<QString> InnerQuery(QString Operation, int Col);
    // ///////////////////////////////////////////////////////////////////
    // Function：		QList<QString> InnerQuery(QString Operation,int Col);
    // Description:     用于对当前数据库对象执行SQL语句并返回查询结果
    // Args：
    //      Operation   需要执行的SQL语句，注意根据数据库特性需要考虑末尾的分号";"
    //                  如Sqlite3的SQL语句末尾需要有";"
    //      Col         执行SQL语句查询的列数。如果不是查询语句此参数需设置为0.
    // Return Values:
    //      QList<QString>  查询的结果字符串构成的链表，以先行后列排序
    // ///////////////////////////////////////////////////////////////////

    void SetDataBase(QString Name, QString Addr, QString Username = "", QString Password = "");
    // ///////////////////////////////////////////////////////////////////
    // Function：		void SetDataBase(QString Name,QString Addr,
    //                       QString Username="",QString Password="");
    // Description:     用于对当前数据库对象设置基本配置信息
    // Args：
    //      Name        数据库名称
    //      Addr        数据库地址
    //      Username    数据库用户名
    //      Password    数据库密码
    // Return Values:
    //      QList<QString>  查询的结果字符串构成的链表，以先行后列排序
    // ///////////////////////////////////////////////////////////////////

    virtual int ConnectToServer();
    // ///////////////////////////////////////////////////////////////////
    // Function：		int ConnectToServer();
    // Description:     使数据库对象连接到数据库
    // Args：
    //      void
    // Return Values:
    //      int         数据库连接结果信息，-1为失败，1为成功。
    // ///////////////////////////////////////////////////////////////////

    virtual int DisConnectToServer();
    // ///////////////////////////////////////////////////////////////////
    // Function：		int DisConnectToServer();
    // Description:     使数据库对象和数据库断开连接
    // Args：
    //      void
    // Return Values:
    //      int         数据库断开连接结果信息。默认返回1。
    // ///////////////////////////////////////////////////////////////////

    MyDatabase(QString Name = "", QString Addr = "", QString Username = "", QString Password = "");
    // ///////////////////////////////////////////////////////////////////
    // Function：		MyDatabase(QString Name="",QString Addr="",
    //                             QString Username="",QString Password="");
    // Description:     数据库对象构造函数
    // Args：
    //      Name        数据库名称
    //      Addr        数据库地址
    //      Username    数据库用户名
    //      Password    数据库密码
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    ~MyDatabase();
    // ///////////////////////////////////////////////////////////////////
    // Function：		~MyDatabase();
    // Description:     数据库对象析构函数。断开连接，删除对象。
    // Args：
    //      void
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

};

#endif // MYDATABASE_H
