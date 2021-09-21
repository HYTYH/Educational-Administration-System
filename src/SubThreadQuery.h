/****************************************************************************
 * Copyright (c)2020, by Beijing University of Post and Telecommunications
 * All rights reserved.
 * FileName：		MyMainWindow.h
 * System：          	Windows 10
 * Author：		Yanbo Liu
 * Date：		2020.12.03
 * Version：		1.0
 * Description：
        子线程查询类，用于在子线程里执行SQL语句并以信号形式将结果发出。
 *
 * Last Modified:

    2020.12.01, 	By Yanbo Liu
                完成初始版本
****************************************************************************/
#pragma once
#ifndef SUBTHREADQUERY_H
#define SUBTHREADQUERY_H
#include "MyDatabase.h"
#include "QThread"
#include <QString>
#include <QList>
#include <QMetaType>
class SubThreadQuery :public QThread
{
    Q_OBJECT

private:
    MyDatabase* DatabaseUsed;
    //子线程查询对象所用的数据库对象指针

    QString Command;
    //子线程查询对象所要执行的SQL语句

    int QueryCol;
    //子线程对象要执行的SQL语句查询列数（不是查询语句则应设置为0）

    int QueryId;
    //子线程对象的查询ID（外部设置和维护，查询结束会一并发出）

public:

    SubThreadQuery(MyDatabase* DatabaseUsedArgv, QString CommandArgv, int QueryColArgv, int QueryIdArgv);
    // ///////////////////////////////////////////////////////////////////
    // Function：		SubThreadQuery(MyDatabase* DatabaseUsedArgv,
    //                  QString CommandArgv,int QueryColArgv,int QueryIdArgv);
    // Description:     子线程查询对象的构造函数
    // Args：
    //      DatabaseUsedArgv  子线程查询对象所用的数据库对象指针
    //      CommandArgv       子线程查询对象所要执行的SQL语句
    //      QueryColArgv      子线程对象要执行的SQL语句查询列数（不是查询语句则应设置为0）
    //      QueryIdArgv       子线程对象的查询ID（外部设置和维护，查询结束会一并发出）
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

protected:

    virtual void run()override;
    // ///////////////////////////////////////////////////////////////////
    // Function：		void run();
    // Description:     重写的线程运行方法，用于执行查询操作
    // Args：
    //      void
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

signals:

    void SendQueryResult(QList<QString>, int, int);
    //信号，发送查询结果。参数分别为 查询结果，查询状态，查询ID

};

#endif // SUBTHREADQUERY_H
