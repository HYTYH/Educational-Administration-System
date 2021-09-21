/****************************************************************************
 * Copyright (c)2020, by Beijing University of Post and Telecommunications
 * All rights reserved.
 * FileName：		MyMainWindow.h
 * System：          	Windows 10
 * Author：		Yanbo Liu | Yihong Tang
 * Date：		2020.12.03
 * Version：		1.3
 * Description：
        课表类，用于提供和用户的界面交互。
 *
 * Last Modified:

    2020.12.3       By Yihong Tang
                UI改进
    2020.12.2       By Yanbo Liu
                修改同步查询为异步，即子线程查询方式。
    2020.11.25      By Yanbo Liu
                完善查询逻辑
    2020.11.11, 	By Yihong Tang
                完成初始版本
****************************************************************************/

#pragma once
#ifndef SCHEDULETABLE_H
#define SCHEDULETABLE_H

#include <QWidget>
#include <QList>
#include <QString>
#include <QMap>
#include <QSet>
#include <QTime>
#include <QMetaType>
#include <QEvent>
#include "MyDatabase.h"
#include "SubThreadQuery.h"
extern MyDatabase DatabaseInstance;
//全局的数据库

namespace Ui {
    class ScheduleTable;
}

class ScheduleTable : public QWidget
{
    Q_OBJECT

private:

    Ui::ScheduleTable* ui;
    //本类对应图形界面指针

    QString Username;
    //本课表对应学生的用户名

    QSet<int> StudentAllClassesApplyID;
    //存储“学生课表查询”的子线程查询ID

    QSet<int> StudentInfoApplyID;
    //存储“学生详细信息查询”的子线程查询ID

    QSet<int> ClassInfoApplyID;
    //存储“课程详细信息查询”的子线程查询ID

    bool eventFilter(QObject* watched, QEvent* event);
    // ///////////////////////////////////////////////////////////////////
    // Function：		bool eventFilter(QObject *watched, QEvent *event);
    // Description:     事件过滤器，接收拦截到的事件，用于实现QPainter绘图事件
    // Args：
    //      watched     QObject *    事件本应传递到的目标对象，用于定位绘图的对象
    //      event       QEvent *     QEvent类型事件，用于过滤选择QPainter事件
    // Return Values:
    //      bool
    //      返回一个bool值，false表示需继续处理事件，true表示停止处理事件
    // ///////////////////////////////////////////////////////////////////

    void PaintTableStructure(void);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void PaintTableStructure(void);
    // Description:     使用QPainter绘制课程表框架
    // Args：
    //      void
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    void ApplyStudentClasses(QString User);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void ApplyStudentClasses(QString User);
    // Description:     申请子线程异步并发查询学生的课表
    // Args：
    //      User        被查询的学生的用户名
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    void ApplyStudentInfo(QString User);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void ApplyStudentInfo(QString User);
    // Description:     申请子线程异步并发查询学生的详细信息
    // Args：
    //      User        被查询的学生的用户名
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    void ApplyClassInfo(QString ClassID);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void ApplyClassInfo(QString ClassID);
    // Description:     申请子线程异步并发查询课程的详细信息
    // Args：
    //      User        被查询课程的ID号码
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    void DisplaySchedule(QList<QString> UserClasses);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void DisplaySchedule(QList<QString> UserClasses);
    // Description:     根据参数显示课程表内容
    // Args：
    //      UserClasses 课表中全部课程的信息组成的链表，正常情况下个数为4的倍数
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    void DisplayStudentInfo(QList<QString> StudentInfo);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void DisplayStudentInfo(QList<QString> StudentInfo);
    // Description:     根据参数显示学生详细信息
    // Args：
    //      StudentInfo 学生的详细信息字符串组成的链表，正常情况下个数为9
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

    void DisplayClassInfo(QList<QString> ClassInfo);
    // ///////////////////////////////////////////////////////////////////
    // Function：		void DisplayClassInfo(QList<QString> ClassInfo);
    // Description:     根据参数显示单个课程详细信息
    // Args：
    //      ClassInfo   课程的详细信息字符串组成的链表，正常情况下个数为7
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////

public:

    explicit ScheduleTable(QString User);
    // ///////////////////////////////////////////////////////////////////
    // Function：		explicit ScheduleTable(QWidget *parent = nullptr);
    // Description:     ScheduleTable类构造函数, 用于初始化ui界面，控件
    // Args：
    //      parent1     QWidget*    继承QWidget
    // Return Values:
    //      ScheduleTable类对象
    //      返回一个ScheduleTable类对象，ui界面及控件已经初始化完毕
    // ///////////////////////////////////////////////////////////////////

    ~ScheduleTable();
    // ///////////////////////////////////////////////////////////////////
    // Function：		~ScheduleTable();
    // Description:     ScheduleTable类析构函数, 用于删除ui界面
    // Args：
    //      void
    // Return Values:
    //      void
    // ///////////////////////////////////////////////////////////////////


public slots:

    void RecieveQueryResult(QList<QString> QueryResult, int QueryState, int QueryID);
    /*用于接收子查询结果并执行对应操作的槽函数*/

private slots:
    void on_PersonalInfo_clicked();
    /*个人信息按钮点击的槽函数*/

    void on_ClassInfo_clicked();
    /*课程信息按钮点击的槽函数*/

    void on_Return_clicked();
    /*返回按钮点击的槽函数*/

    void on_Help_clicked();
    /*帮助按钮点击的槽函数*/

    void on_Exit_clicked();
    /*退出按钮点击的槽函数。销毁当前对象*/

    void timerUpdate(void);
    /*更新时间标签的槽函数*/

    void on_MonSecTwo_pressed();
    /*按钮点击的槽函数，下同*/

    void on_MonSecTwo_released();
    /*按钮释放的槽函数，下同*/

    void on_MonSecOne_pressed();

    void on_MonSecOne_released();

    void on_MonSecThree_pressed();

    void on_MonSecThree_released();

    void on_MonSecFour_pressed();

    void on_MonSecFour_released();

    void on_MonSecFive_pressed();

    void on_MonSecFive_released();

    void on_MonSecSix_pressed();

    void on_MonSecSix_released();

    void on_MonSecSeven_pressed();

    void on_MonSecSeven_released();

    void on_MonSecEight_pressed();

    void on_MonSecEight_released();

    void on_TueSecOne_pressed();

    void on_TueSecOne_released();

    void on_TueSecTwo_pressed();

    void on_TueSecTwo_released();

    void on_TueSecThree_pressed();

    void on_TueSecThree_released();

    void on_TueSecFour_pressed();

    void on_TueSecFour_released();

    void on_TueSecFive_pressed();

    void on_TueSecFive_released();

    void on_TueSecSix_pressed();

    void on_TueSecSix_released();

    void on_TueSecSeven_pressed();

    void on_TueSecSeven_released();

    void on_TueSecEight_pressed();

    void on_TueSecEight_released();

    void on_WedSecOne_pressed();

    void on_WedSecOne_released();

    void on_WedSecTwo_pressed();

    void on_WedSecTwo_released();

    void on_WedSecThree_pressed();

    void on_WedSecThree_released();

    void on_WedSecFour_pressed();

    void on_WedSecFour_released();

    void on_WedSecFive_pressed();

    void on_WedSecFive_released();

    void on_WedSecSix_pressed();

    void on_WedSecSix_released();

    void on_WedSecSeven_pressed();

    void on_WedSecSeven_released();

    void on_WedSecEight_pressed();

    void on_WedSecEight_released();

    void on_ThurSecOne_pressed();

    void on_ThurSecOne_released();

    void on_ThurSecTwo_pressed();

    void on_ThurSecTwo_released();

    void on_ThurSecThree_pressed();

    void on_ThurSecThree_released();

    void on_ThurSecFour_pressed();

    void on_ThurSecFour_released();

    void on_ThurSecFive_pressed();

    void on_ThurSecFive_released();

    void on_ThurSecSix_pressed();

    void on_ThurSecSix_released();

    void on_ThurSecSeven_pressed();

    void on_ThurSecSeven_released();

    void on_ThurSecEight_pressed();

    void on_ThurSecEight_released();

    void on_FriSecOne_pressed();

    void on_FriSecOne_released();

    void on_FriSecTwo_pressed();

    void on_FriSecTwo_released();

    void on_FriSecThree_pressed();

    void on_FriSecThree_released();

    void on_FriSecFour_pressed();

    void on_FriSecFour_released();

    void on_FriSecFive_pressed();

    void on_FriSecFive_released();

    void on_FriSecSix_pressed();

    void on_FriSecSix_released();

    void on_FriSecSeven_pressed();

    void on_FriSecSeven_released();

    void on_FriSecEight_pressed();

    void on_FriSecEight_released();

};

#endif // SCHEDULETABLE_H
