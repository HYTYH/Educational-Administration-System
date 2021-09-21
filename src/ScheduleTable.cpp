#include "ScheduleTable.h"
#include "ui_ScheduleTable.h"
#include <QDebug>
#include <QPalette>
#include <QPaintEvent>
#include <QLabel>
#include <QPainter>
#include <QRectF>
#include <QFont>
#include <QTimer>
#include <qdatetime.h>




void ScheduleTable::RecieveQueryResult(QList<QString> QueryResult, int QueryState, int QueryID) {

    /*检查返回的状态是否为0,不为零说明出错*/
    if (QueryState != 0) {
        QMessageBox::information(NULL, "Alert", "在操作数据库时出错，请检查数据库和操作指令");
        return;
    }

    /*假如是课程详细信息查询*/
    if (ClassInfoApplyID.contains(QueryID)) {
        ClassInfoApplyID.remove(QueryID);
        DisplayClassInfo(QueryResult);
    }
    /*假如是学生全部课程信息查询*/
    else if (StudentAllClassesApplyID.contains(QueryID)) {
        StudentAllClassesApplyID.remove(QueryID);
        DisplaySchedule(QueryResult);
    }
    /*假如是学生详细信息查询*/
    else if (StudentInfoApplyID.contains(QueryID)) {
        StudentInfoApplyID.remove(QueryID);
        DisplayStudentInfo(QueryResult);
    }

}

ScheduleTable::ScheduleTable(QString User) :
    QWidget(NULL),
    ui(new Ui::ScheduleTable),
    Username(User),
    StudentAllClassesApplyID({}),
    StudentInfoApplyID({}),
    ClassInfoApplyID({})
{

    ui->setupUi(this);


    /*初始化QTimer，每秒钟在ui界面更新显示时间*/
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);

    /*导入图片到相应控件*/
    this->ui->Background->setPixmap(QPixmap(":/new/white.jpg"));
    this->ui->Background->setScaledContents(true);
    this->ui->SecOne->setPixmap(QPixmap(":/new/one.png"));
    this->ui->SecOne->setScaledContents(true);
    this->ui->SecTwo->setPixmap(QPixmap(":/new/two.png"));
    this->ui->SecTwo->setScaledContents(true);
    this->ui->SecThree->setPixmap(QPixmap(":/new/three.png"));
    this->ui->SecThree->setScaledContents(true);
    this->ui->SecFour->setPixmap(QPixmap(":/new/four.png"));
    this->ui->SecFour->setScaledContents(true);
    this->ui->SecFive->setPixmap(QPixmap(":/new/five.png"));
    this->ui->SecFive->setScaledContents(true);
    this->ui->SecSix->setPixmap(QPixmap(":/new/six.png"));
    this->ui->SecSix->setScaledContents(true);
    this->ui->SecSeven->setPixmap(QPixmap(":/new/seven.png"));
    this->ui->SecSeven->setScaledContents(true);
    this->ui->SecEight->setPixmap(QPixmap(":/new/eight.png"));
    this->ui->SecEight->setScaledContents(true);
    this->ui->Monday->setPixmap(QPixmap(":/new/mon.png"));
    this->ui->Monday->setScaledContents(true);
    this->ui->Tuesday->setPixmap(QPixmap(":/new/tue.png"));
    this->ui->Tuesday->setScaledContents(true);
    this->ui->Wednesday->setPixmap(QPixmap(":/new/wed.png"));
    this->ui->Wednesday->setScaledContents(true);
    this->ui->Thursday->setPixmap(QPixmap(":/new/thu.png"));
    this->ui->Thursday->setScaledContents(true);
    this->ui->Friday->setPixmap(QPixmap(":/new/fri.png"));
    this->ui->Friday->setScaledContents(true);
    this->ui->ReturnPic->setPixmap(QPixmap(":/new/return.png"));
    this->ui->ReturnPic->setScaledContents(true);
    this->ui->Girl->setPixmap(QPixmap(":/new/girl.png"));
    this->ui->Girl->setScaledContents(true);
    this->ui->Boy->setPixmap(QPixmap(":/new/boy.png"));
    this->ui->Boy->setScaledContents(true);
    this->ui->PersonalInfoPic->setPixmap(QPixmap(":/new/personal-information.png"));
    this->ui->PersonalInfoPic->setScaledContents(true);
    this->ui->ScheduleInfoPic->setPixmap(QPixmap(":/new/calendar_1.png"));
    this->ui->ScheduleInfoPic->setScaledContents(true);
    this->ui->HelpPic->setPixmap(QPixmap(":/new/help.png"));
    this->ui->HelpPic->setScaledContents(true);
    this->ui->ExitPic->setPixmap(QPixmap(":/new/exit.png"));
    this->ui->ExitPic->setScaledContents(true);
    this->ui->Rest->setPixmap(QPixmap(":/new/rest.jpg"));
    this->ui->Rest->setScaledContents(true);
    this->ui->Clock->setPixmap(QPixmap(":/new/Clock.png"));
    this->ui->Clock->setScaledContents(true);
    this->ui->SchedulePic->setPixmap(QPixmap(":/new/calendar.png"));
    this->ui->SchedulePic->setScaledContents(true);

    /*初始化按钮透明*/
    this->ui->MonSecOne->setFlat(true);
    this->ui->MonSecTwo->setFlat(true);
    this->ui->MonSecThree->setFlat(true);
    this->ui->MonSecFour->setFlat(true);
    this->ui->MonSecFive->setFlat(true);
    this->ui->MonSecSix->setFlat(true);
    this->ui->MonSecSeven->setFlat(true);
    this->ui->MonSecEight->setFlat(true);
    this->ui->TueSecOne->setFlat(true);
    this->ui->TueSecTwo->setFlat(true);
    this->ui->TueSecThree->setFlat(true);
    this->ui->TueSecFour->setFlat(true);
    this->ui->TueSecFive->setFlat(true);
    this->ui->TueSecSix->setFlat(true);
    this->ui->TueSecSeven->setFlat(true);
    this->ui->TueSecEight->setFlat(true);
    this->ui->WedSecOne->setFlat(true);
    this->ui->WedSecTwo->setFlat(true);
    this->ui->WedSecThree->setFlat(true);
    this->ui->WedSecFour->setFlat(true);
    this->ui->WedSecFive->setFlat(true);
    this->ui->WedSecSix->setFlat(true);
    this->ui->WedSecSeven->setFlat(true);
    this->ui->WedSecEight->setFlat(true);
    this->ui->ThurSecOne->setFlat(true);
    this->ui->ThurSecTwo->setFlat(true);
    this->ui->ThurSecThree->setFlat(true);
    this->ui->ThurSecFour->setFlat(true);
    this->ui->ThurSecFive->setFlat(true);
    this->ui->ThurSecSix->setFlat(true);
    this->ui->ThurSecSeven->setFlat(true);
    this->ui->ThurSecEight->setFlat(true);
    this->ui->FriSecOne->setFlat(true);
    this->ui->FriSecTwo->setFlat(true);
    this->ui->FriSecThree->setFlat(true);
    this->ui->FriSecFour->setFlat(true);
    this->ui->FriSecFive->setFlat(true);
    this->ui->FriSecSix->setFlat(true);
    this->ui->FriSecSeven->setFlat(true);
    this->ui->FriSecEight->setFlat(true);
    this->ui->Return->setFlat(true);
    this->ui->PersonalInfo->setFlat(true);
    this->ui->ClassInfo->setFlat(true);
    this->ui->Help->setFlat(true);
    this->ui->Exit->setFlat(true);

    /*画课表框架*/
    this->ui->Paint->installEventFilter(this);

    /*初始画面仅显示两个按钮 个人信息+课程信息*/
    this->ui->AlertLabel->setText("按住课程显示详细信息");
    this->ui->AlertLabel->setVisible(false);
    this->ui->Paint->setVisible(false);
    this->ui->MonSecOne->setVisible(false);
    this->ui->MonSecTwo->setVisible(false);
    this->ui->MonSecThree->setVisible(false);
    this->ui->MonSecFour->setVisible(false);
    this->ui->MonSecFive->setVisible(false);
    this->ui->MonSecSix->setVisible(false);
    this->ui->MonSecSeven->setVisible(false);
    this->ui->MonSecEight->setVisible(false);
    this->ui->TueSecOne->setVisible(false);
    this->ui->TueSecTwo->setVisible(false);
    this->ui->TueSecThree->setVisible(false);
    this->ui->TueSecFour->setVisible(false);
    this->ui->TueSecFive->setVisible(false);
    this->ui->TueSecSix->setVisible(false);
    this->ui->TueSecSeven->setVisible(false);
    this->ui->TueSecEight->setVisible(false);
    this->ui->WedSecOne->setVisible(false);
    this->ui->WedSecTwo->setVisible(false);
    this->ui->WedSecThree->setVisible(false);
    this->ui->WedSecFour->setVisible(false);
    this->ui->WedSecFive->setVisible(false);
    this->ui->WedSecSix->setVisible(false);
    this->ui->WedSecSeven->setVisible(false);
    this->ui->WedSecEight->setVisible(false);
    this->ui->ThurSecOne->setVisible(false);
    this->ui->ThurSecTwo->setVisible(false);
    this->ui->ThurSecThree->setVisible(false);
    this->ui->ThurSecFour->setVisible(false);
    this->ui->ThurSecFive->setVisible(false);
    this->ui->ThurSecSix->setVisible(false);
    this->ui->ThurSecSeven->setVisible(false);
    this->ui->ThurSecEight->setVisible(false);
    this->ui->FriSecOne->setVisible(false);
    this->ui->FriSecTwo->setVisible(false);
    this->ui->FriSecThree->setVisible(false);
    this->ui->FriSecFour->setVisible(false);
    this->ui->FriSecFive->setVisible(false);
    this->ui->FriSecSix->setVisible(false);
    this->ui->FriSecSeven->setVisible(false);
    this->ui->FriSecEight->setVisible(false);
    this->ui->Monday->setVisible(false);
    this->ui->Tuesday->setVisible(false);
    this->ui->Wednesday->setVisible(false);
    this->ui->Thursday->setVisible(false);
    this->ui->Friday->setVisible(false);
    this->ui->SecOne->setVisible(false);
    this->ui->SecTwo->setVisible(false);
    this->ui->SecThree->setVisible(false);
    this->ui->SecFour->setVisible(false);
    this->ui->SecFive->setVisible(false);
    this->ui->SecSix->setVisible(false);
    this->ui->SecSeven->setVisible(false);
    this->ui->SecEight->setVisible(false);
    this->ui->SchedulePic->setVisible(false);
    this->ui->Return->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Rest->setVisible(false);
    this->ui->StudentInfo->setVisible(false);
    this->ui->Girl->setVisible(false);
    this->ui->Boy->setVisible(false);
    this->ui->ReturnPic->setVisible(false);

    /*初始化控件字体类型及颜色*/
    this->ui->AlertLabel->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:18px");
    this->ui->HelpInfo->setStyleSheet("font-family:'娃娃体-简';color:rgb(0,104,139);font-size:28px");
    this->ui->PressToSeeHelp->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:28px");
    this->ui->PressToExit->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:28px");
    this->ui->PressToSeePersonal->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:28px");
    this->ui->PressToSeeSchedule->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:28px");
    this->ui->StudentInfo->setStyleSheet("font-family:'娃娃体-简';color:rgb(0,104,139);font-size:28px");
    this->ui->ClassSpecificInfo->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:20px");
    this->ui->Time->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,130,71);font-size:22px");
    this->ui->MonSecOne->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecTwo->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecThree->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecFour->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecFive->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecSix->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecSeven->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->MonSecEight->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecOne->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecTwo->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecThree->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecFour->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecFive->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecSix->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecSeven->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->TueSecEight->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecOne->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecTwo->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecThree->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecFour->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecFive->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecSix->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecSeven->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->WedSecEight->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecOne->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecTwo->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecThree->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecFour->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecFive->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecSix->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecSeven->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->ThurSecEight->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecOne->setStyleSheet("font:bold;font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecTwo->setStyleSheet("font:bold;font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecThree->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecFour->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecFive->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecSix->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecSeven->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");
    this->ui->FriSecEight->setStyleSheet("font-family:'娃娃体-简';color:rgb(255,250,250);font-size:18px");

    /*初始化控件文本显示内容*/
    this->ui->PressToSeePersonal->setText("点击查询个人信息");
    this->ui->PressToSeeSchedule->setText("点击查询课程信息");
    this->ui->PressToExit->setText("点击退出登陆");
    this->ui->PressToSeeHelp->setText("点击查看帮助");
}

ScheduleTable::~ScheduleTable() {
    delete ui;
}

bool ScheduleTable::eventFilter(QObject* watched, QEvent* event) {

    if (watched == ui->Paint && event->type() == QEvent::Paint) {
        /*使用QPainter绘制课表框架*/
        PaintTableStructure();
    }
    return QWidget::eventFilter(watched, event);
}

void ScheduleTable::PaintTableStructure() {

    /*填充颜色*/
    QBrush BrushRect;

    /*定位绘制目标对象*/
    QPainter PaintRect(ui->Paint);

    /*使用QPainter绘制表格外框*/
    BrushRect.setColor(QColor(255, 239, 219, 50));
    BrushRect.setStyle(Qt::SolidPattern);
    PaintRect.setPen(QPen(Qt::gray, 3));
    PaintRect.setBrush(BrushRect);
    PaintRect.drawRect(2, 2, 837, 628);


    QPainter PaintBrush(ui->Paint);
    QBrush BrushWeekdays;

    /*第一行颜色填充*/
    /*填充Monday表格项*/
    BrushWeekdays.setColor(QColor(130, 144, 255, 50));
    BrushWeekdays.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 3));
    PaintBrush.setBrush(BrushWeekdays);
    PaintBrush.drawRect(100, 2, 145, 68);

    /*填充Tuesday表格项*/
    BrushWeekdays.setColor(QColor(224, 255, 255));
    BrushWeekdays.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 3));
    PaintBrush.setBrush(BrushWeekdays);
    PaintBrush.drawRect(245, 2, 150, 68);

    /*填充Wednesday表格项*/
    BrushWeekdays.setColor(QColor(255, 255, 0, 50));
    BrushWeekdays.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushWeekdays);
    PaintBrush.drawRect(395, 2, 151, 68);

    /*填充Thursday表格项*/
    BrushWeekdays.setColor(QColor(255, 0, 0, 50));
    BrushWeekdays.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushWeekdays);
    PaintBrush.drawRect(545, 2, 152, 68);

    /*填充Friday表格项*/
    BrushWeekdays.setColor(QColor(245, 245, 220, 50));
    BrushWeekdays.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushWeekdays);
    PaintBrush.drawRect(695, 2, 153, 68);

    /*填充SecOne表格行*/
    QBrush BrushSec;
    BrushSec.setColor(QColor(139, 139, 131, 85));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 70, 839, 70);

    /*填充SecTwo表格行*/
    BrushSec.setColor(QColor(105, 105, 105, 99));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 140, 839, 70);

    /*填充SecThree表格行*/
    BrushSec.setColor(QColor(139, 139, 131, 85));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 210, 839, 70);

    /*填充SecFour表格行*/
    BrushSec.setColor(QColor(105, 105, 105, 99));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 280, 839, 70);

    /*填充SecFive表格行*/
    BrushSec.setColor(QColor(139, 139, 131, 85));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 350, 839, 70);

    /*填充SecSix表格行*/
    BrushSec.setColor(QColor(105, 105, 105, 99));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 420, 839, 70);

    /*填充SecSeven表格行*/
    BrushSec.setColor(QColor(139, 139, 131, 85));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 490, 839, 70);

    /*填充SecEight表格行*/
    BrushSec.setColor(QColor(105, 105, 105, 99));
    BrushSec.setStyle(Qt::SolidPattern);
    PaintBrush.setPen(QPen(Qt::gray, 1));
    PaintBrush.setBrush(BrushSec);
    PaintBrush.drawRect(2, 560, 839, 70);

    QPainter PaintLine(ui->Paint);

    /*表格竖线*/
    PaintLine.setPen(QPen(Qt::gray, 7));
    PaintLine.drawLine(0, 0, 0, 628);
    PaintLine.setPen(QPen(Qt::gray, 3));
    PaintLine.drawLine(100, 0, 100, 628);
    PaintLine.drawLine(245, 0, 245, 628);
    PaintLine.drawLine(395, 0, 395, 628);
    PaintLine.drawLine(545, 0, 545, 628);
    PaintLine.drawLine(695, 0, 695, 628);
    PaintLine.drawLine(839, 0, 839, 628);
    PaintLine.setPen(QPen(Qt::gray, 5));

    /*表格横线*/
    PaintLine.setPen(QPen(Qt::gray, 3));
    PaintLine.drawLine(0, 70, 841, 70);
    PaintLine.drawLine(0, 140, 841, 140);
    PaintLine.drawLine(0, 210, 841, 210);
    PaintLine.drawLine(0, 280, 841, 280);
    PaintLine.drawLine(0, 350, 841, 350);
    PaintLine.drawLine(0, 420, 841, 420);
    PaintLine.drawLine(0, 490, 841, 490);
    PaintLine.drawLine(0, 560, 841, 560);

}

void ScheduleTable::ApplyStudentClasses(QString User) {

    /*构造SQL查询语句用于查询学生的课表*/
    QString Operation =
        "select class_id,class_onweek,class_onday,class_name "
        "from (tb_userinfo natural join tb_student_classes)"
        "natural join tb_classesinfo where username=\""
        + User + QString("\";");

    /*反复生成随机数用于作为本次查询的查询ID，直到满足在当前ID在所有查询ID集合中都不存在，否则会产生二义性*/
    int ApplyId = 1 + qrand() % 100000000;
    while ((StudentAllClassesApplyID.contains(ApplyId) == true)
        || (StudentInfoApplyID.contains(ApplyId) == true)
        || (ClassInfoApplyID.contains(ApplyId) == true)) {

        ApplyId = 1 + qrand() % 100000000;
        qDebug() << "ID:" << ApplyId << "\n";
    }

    /*构建子线程查询对象，传入数据库实例，查询命令，查询行数，查询ID参数*/
    SubThreadQuery* nQuery = new SubThreadQuery(&DatabaseInstance, Operation, 4, ApplyId);

    /*将子线程查询中的查询结果信号 连接到 本对象的结果处理槽函数*/
    connect(nQuery, SIGNAL(SendQueryResult(QList<QString>, int, int)), this,
            SLOT(RecieveQueryResult(QList<QString>, int, int)));

    /*课表查询ID集合添加当前ID*/
    StudentAllClassesApplyID.insert(ApplyId);

    /*子线程查询开始执行*/
    nQuery->start();

}

void ScheduleTable::ApplyStudentInfo(QString User) {

    /*构造SQL查询语句用于查询学生的个人信息*/
    QString Operation =
        QString("select student_id,student_name,sex,school,major,year,age,gained_scores,avg_grades "
            "from tb_userinfo natural join tb_studentinfo "
            "where username=\"")
        + User + QString("\";");

    /*反复生成随机数用于作为本次查询的查询ID，需要满足在当前所有查询ID集合中都不存在，否则会产生二义性*/
    /*反复生成随机数用于作为本次查询的查询ID，直到满足在当前ID在所有查询ID集合中都不存在，否则会产生二义性*/
    int ApplyId = 1 + qrand() % 100000000;
    while ((StudentAllClassesApplyID.contains(ApplyId) == true)
        || (StudentInfoApplyID.contains(ApplyId) == true)
        || (ClassInfoApplyID.contains(ApplyId) == true)) {

        ApplyId = 1 + qrand() % 100000000;
        qDebug() << "ID:" << ApplyId << "\n";
    }

    /*构建子线程查询对象，传入数据库实例，查询命令，查询行数，查询ID参数*/
    SubThreadQuery* nQuery = new SubThreadQuery(&DatabaseInstance, Operation, 9, ApplyId);

    /*将子线程查询中的查询结果信号 连接到 本对象的结果处理槽函数*/
    connect(nQuery, SIGNAL(SendQueryResult(QList<QString>, int, int)), this,
            SLOT(RecieveQueryResult(QList<QString>, int, int)));

    /*学生信息查询ID集合添加当前ID*/
    StudentInfoApplyID.insert(ApplyId);

    /*子线程查询开始执行*/
    nQuery->start();

}

void ScheduleTable::ApplyClassInfo(QString ClassID) {

    /*构造SQL查询语句用于查询课程的详细信息*/
    QString Operation =
        QString("select class_id,class_name,teacher_name,"
            "school,class_scores,semester_weeks,test_pattern "
            "from tb_classesinfo where class_id=\"")
        + ClassID + QString("\";");


    /*反复生成随机数用于作为本次查询的查询ID，直到满足在当前ID在所有查询ID集合中都不存在，否则会产生二义性*/
    int ApplyId = 1 + qrand() % 100000000;
    while ((StudentAllClassesApplyID.contains(ApplyId) == true)
        || (StudentInfoApplyID.contains(ApplyId) == true)
        || (ClassInfoApplyID.contains(ApplyId) == true)) {

        ApplyId = 1 + qrand() % 100000000;
        qDebug() << "ID:" << ApplyId << "\n";
    }

    /*构建子线程查询对象，传入数据库实例，查询命令，查询行数，查询ID参数*/
    SubThreadQuery* nQuery = new SubThreadQuery(&DatabaseInstance, Operation, 7, ApplyId);

    /*将子线程查询中的查询结果信号 连接到 本对象的结果处理槽函数*/
    connect(nQuery, SIGNAL(SendQueryResult(QList<QString>, int, int)), this, SLOT(RecieveQueryResult(QList<QString>, int, int)));

    /*课程详细信息查询ID集合添加当前ID*/
    ClassInfoApplyID.insert(ApplyId);

    /*子线程查询开始执行*/
    nQuery->start();

}

void ScheduleTable::DisplaySchedule(QList<QString> UserClasses) {

    /*查询结果字符串个数不是4的倍数，说明查询出错*/
    if (UserClasses.size() % 4 != 0) {
        qDebug() << "课表查询结果不是4的倍数\n";
        return;
    }

    int UserClassInfoLen = 4;                                       /*每个用户课程信息字符串个数*/
    int ClassIdOffset = 0;                                          /*用户课程Id对应第一个字符串，下标为0*/
    int WeekdayOffset = 1;                                          /*用户课程每周上课日期对应第二个字符串，下标为1*/
    int SectionOffset = 2;                                          /*用户课程上课节次对应第三个字符串，下标为2*/
    int ClassNameOffset = 3;                                        /*用户课程名对应第四个字符串，下标为3*/
    int NumOfUserClasses = UserClasses.size() / UserClassInfoLen;   /*计算得出用户课程数*/

    /*根据查询的用户课程信息，设置对应控件文本，打印出课程表*/
    for (int i = 0; i < NumOfUserClasses; i++) {


        switch (UserClasses[i * UserClassInfoLen + WeekdayOffset].toInt()) {
        case 1:
            switch (UserClasses[i * UserClassInfoLen + SectionOffset].toInt()) {
            case 1: this->ui->MonSecOne->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 2: this->ui->MonSecTwo->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 3: this->ui->MonSecThree->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 4: this->ui->MonSecFour->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 5: this->ui->MonSecFive->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 6: this->ui->MonSecSix->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 7: this->ui->MonSecSeven->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 8: this->ui->MonSecEight->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            };
            break;
        case 2:
            switch (UserClasses[i * UserClassInfoLen + SectionOffset].toInt()) {
            case 1: this->ui->TueSecOne->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 2: this->ui->TueSecTwo->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 3: this->ui->TueSecThree->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 4: this->ui->TueSecFour->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 5: this->ui->TueSecFive->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 6: this->ui->TueSecSix->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 7: this->ui->TueSecSeven->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 8: this->ui->TueSecEight->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            };
            break;
        case 3:
            switch (UserClasses[i * UserClassInfoLen + SectionOffset].toInt()) {
            case 1: this->ui->WedSecOne->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 2: this->ui->WedSecTwo->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 3: this->ui->WedSecThree->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 4: this->ui->WedSecFour->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 5: this->ui->WedSecFive->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 6: this->ui->WedSecSix->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 7: this->ui->WedSecSeven->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 8: this->ui->WedSecEight->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            };
            break;
        case 4:
            switch (UserClasses[i * UserClassInfoLen + SectionOffset].toInt()) {
            case 1: this->ui->ThurSecOne->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 2: this->ui->ThurSecTwo->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 3: this->ui->ThurSecThree->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 4: this->ui->ThurSecFour->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 5: this->ui->ThurSecFive->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 6: this->ui->ThurSecSix->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 7: this->ui->ThurSecSeven->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 8: this->ui->ThurSecEight->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            };
            break;
        case 5:
            switch (UserClasses[i * UserClassInfoLen + SectionOffset].toInt()) {
            case 1: this->ui->FriSecOne->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 2: this->ui->FriSecTwo->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 3: this->ui->FriSecThree->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 4: this->ui->FriSecFour->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 5: this->ui->FriSecFive->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 6: this->ui->FriSecSix->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 7: this->ui->FriSecSeven->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            case 8: this->ui->FriSecEight->setText("ID: " + UserClasses[i * UserClassInfoLen + ClassIdOffset]
                        + "\n" + UserClasses[i * UserClassInfoLen + ClassNameOffset]); break;
            };
            break;
        default: qDebug() << "Wrong" << endl;
        }
    }
}

void ScheduleTable::DisplayStudentInfo(QList<QString> StudentInfo) {

    /*查询结果字符串个数不是9，说明查询出错*/
    if (StudentInfo.size() != 9) {
        qDebug() << "学生信息查询结果个数不是9\n";
        return;
    }

    /*根据学生信息中的学生性别，显示不同的图*/
    if (StudentInfo[2] == "男") {
        this->ui->Boy->setVisible(true);
        this->ui->Girl->setVisible(false);
    }
    else {
        this->ui->Girl->setVisible(true);
        this->ui->Boy->setVisible(false);
    }

    /*显示详细学生信息*/
    QString TextToSet;
    TextToSet.clear();
    TextToSet += "学号:    " + StudentInfo[0] + "\n";
    TextToSet += "姓名:    " + StudentInfo[1] + "\n";
    TextToSet += "性别:    " + StudentInfo[2] + "\n";
    TextToSet += "学院:    " + StudentInfo[3] + "\n";
    TextToSet += "专业:    " + StudentInfo[4] + "\n";
    TextToSet += "年级:    " + StudentInfo[5] + "\n";
    TextToSet += "年龄:    " + StudentInfo[6] + "\n";
    TextToSet += "已修学分:    " + StudentInfo[7] + "\n";
    TextToSet += "均绩:    " + StudentInfo[8];

    this->ui->StudentInfo->clear();
    this->ui->StudentInfo->setText(TextToSet);
    this->ui->StudentInfo->setVisible(true);
}

void ScheduleTable::DisplayClassInfo(QList<QString> ClassInfo) {

    /*ClassInfo --0 课程ID + 1 课程名 + 2 教师 + 3 开课学院 + 4 课程学分 + 5 上课周次 + 6 考核形式*/
    /*查询结果字符串个数不是7，说明查询出错*/
    if (ClassInfo.size() != 7) {
        qDebug() << "课程详细信息查询结果个数不是7\n";
        ClassInfo.clear();
        ClassInfo.push_back("Unknown");
        ClassInfo.push_back("Unknown");
        ClassInfo.push_back("Unknown");
        ClassInfo.push_back("Unknown");
        ClassInfo.push_back("Unknown");
        ClassInfo.push_back("Unknown");
        ClassInfo.push_back("Unknown");
    }

    /*显示详细信息*/
    QString TextToSet = "";
    TextToSet += "课程ID:     " + ClassInfo[0] + "\n";
    TextToSet += "课程名称:    " + ClassInfo[1] + "\n";
    TextToSet += "授课教师:    " + ClassInfo[2] + "\n";
    TextToSet += "所属学院:    " + ClassInfo[3] + "\n";
    TextToSet += "学分:     " + ClassInfo[4] + "\n";
    TextToSet += "上课周次:    " + ClassInfo[5] + "\n";
    TextToSet += "考核形式:    " + ClassInfo[6];
    this->ui->ClassSpecificInfo->setText(TextToSet);
}

void ScheduleTable::on_PersonalInfo_clicked() {

    /*申请子线程查询学生信息*/
    ApplyStudentInfo(Username);

    /*显示新界面，屏蔽原界面*/
    this->ui->Return->setVisible(true);
    this->ui->ClassSpecificInfo->setVisible(true);
    this->ui->ReturnPic->setVisible(true);
    this->ui->Help->setVisible(false);
    this->ui->HelpPic->setVisible(false);
    this->ui->PressToSeeHelp->setVisible(false);
    this->ui->Exit->setVisible(false);
    this->ui->ExitPic->setVisible(false);
    this->ui->PressToExit->setVisible(false);
    this->ui->ScheduleInfoPic->setVisible(false);
    this->ui->PressToSeePersonal->setVisible(false);
    this->ui->PressToSeeSchedule->setVisible(false);
    this->ui->PersonalInfo->setVisible(false);
    this->ui->ClassInfo->setVisible(false);
    this->ui->PersonalInfoPic->setVisible(false);
    QList<QString> StudentInfo;//0 学生ID + 1 姓名 + 2 性别 + 3 学院 + 4 专业 + 5 年级 + 6 年龄 + 7 已修学分 + 8 均绩
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");
    StudentInfo.push_back("Waiting");

    /*根据学生信息中的学生性别，显示不同的图*/
    if (StudentInfo[2] == "男") {
        this->ui->Boy->setVisible(true);
        this->ui->Girl->setVisible(false);
    }
    else {
        this->ui->Girl->setVisible(true);
        this->ui->Boy->setVisible(false);
    }

    /*显示学生信息*/
    QString TextToSet;
    TextToSet.clear();
    TextToSet += "学号:    " + StudentInfo[0] + "\n";
    TextToSet += "姓名:    " + StudentInfo[1] + "\n";
    TextToSet += "性别:    " + StudentInfo[2] + "\n";
    TextToSet += "学院:    " + StudentInfo[3] + "\n";
    TextToSet += "专业:    " + StudentInfo[4] + "\n";
    TextToSet += "年级:    " + StudentInfo[5] + "\n";
    TextToSet += "年龄:    " + StudentInfo[6] + "\n";
    TextToSet += "已修学分:    " + StudentInfo[7] + "\n";
    TextToSet += "均绩:    " + StudentInfo[8];

    this->ui->StudentInfo->clear();
    this->ui->StudentInfo->setText(TextToSet);
    this->ui->StudentInfo->setVisible(true);


}

void ScheduleTable::on_ClassInfo_clicked() {

    /*显示新界面，屏蔽原界面*/
    this->ui->AlertLabel->setVisible(true);
    this->ui->Help->setVisible(false);
    this->ui->HelpPic->setVisible(false);
    this->ui->PressToSeeHelp->setVisible(false);
    this->ui->Exit->setVisible(false);
    this->ui->ExitPic->setVisible(false);
    this->ui->PressToExit->setVisible(false);
    this->ui->PersonalInfoPic->setVisible(false);
    this->ui->PressToSeePersonal->setVisible(false);
    this->ui->PressToSeeSchedule->setVisible(false);
    this->ui->ScheduleInfoPic->setVisible(false);
    this->ui->ClassInfo->setVisible(false);
    this->ui->PersonalInfo->setVisible(false);
    this->ui->SchedulePic->setVisible(false);
    this->ui->ReturnPic->setVisible(true);
    this->ui->Return->setVisible(true);
    this->ui->Clock->setVisible(true);

    /*显示课表框架*/
    this->ui->Paint->setVisible(true);
    this->ui->MonSecOne->setVisible(true);
    this->ui->MonSecTwo->setVisible(true);
    this->ui->MonSecThree->setVisible(true);
    this->ui->MonSecFour->setVisible(true);
    this->ui->MonSecFive->setVisible(true);
    this->ui->MonSecSix->setVisible(true);
    this->ui->MonSecSeven->setVisible(true);
    this->ui->MonSecEight->setVisible(true);
    this->ui->TueSecOne->setVisible(true);
    this->ui->TueSecTwo->setVisible(true);
    this->ui->TueSecThree->setVisible(true);
    this->ui->TueSecFour->setVisible(true);
    this->ui->TueSecFive->setVisible(true);
    this->ui->TueSecSix->setVisible(true);
    this->ui->TueSecSeven->setVisible(true);
    this->ui->TueSecEight->setVisible(true);
    this->ui->WedSecOne->setVisible(true);
    this->ui->WedSecTwo->setVisible(true);
    this->ui->WedSecThree->setVisible(true);
    this->ui->WedSecFour->setVisible(true);
    this->ui->WedSecFive->setVisible(true);
    this->ui->WedSecSix->setVisible(true);
    this->ui->WedSecSeven->setVisible(true);
    this->ui->WedSecEight->setVisible(true);
    this->ui->ThurSecOne->setVisible(true);
    this->ui->ThurSecTwo->setVisible(true);
    this->ui->ThurSecThree->setVisible(true);
    this->ui->ThurSecFour->setVisible(true);
    this->ui->ThurSecFive->setVisible(true);
    this->ui->ThurSecSix->setVisible(true);
    this->ui->ThurSecSeven->setVisible(true);
    this->ui->ThurSecEight->setVisible(true);
    this->ui->FriSecOne->setVisible(true);
    this->ui->FriSecTwo->setVisible(true);
    this->ui->FriSecThree->setVisible(true);
    this->ui->FriSecFour->setVisible(true);
    this->ui->FriSecFive->setVisible(true);
    this->ui->FriSecSix->setVisible(true);
    this->ui->FriSecSeven->setVisible(true);
    this->ui->FriSecEight->setVisible(true);
    this->ui->Monday->setVisible(true);
    this->ui->Tuesday->setVisible(true);
    this->ui->Wednesday->setVisible(true);
    this->ui->Thursday->setVisible(true);
    this->ui->Friday->setVisible(true);
    this->ui->SecOne->setVisible(true);
    this->ui->SecTwo->setVisible(true);
    this->ui->SecThree->setVisible(true);
    this->ui->SecFour->setVisible(true);
    this->ui->SecFive->setVisible(true);
    this->ui->SecSix->setVisible(true);
    this->ui->SecSeven->setVisible(true);
    this->ui->SecEight->setVisible(true);
    this->ui->SchedulePic->setVisible(true);

    /*申请子线程查询学生的课表*/
    ApplyStudentClasses(Username);
}

void ScheduleTable::timerUpdate(void) {

    /*更新时间显示*/
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    this->ui->Time->setText(str);
}

void ScheduleTable::on_Return_clicked() {

    /*从当前界面返回初始界面*/
    this->ui->AlertLabel->setVisible(false);
    this->ui->HelpInfo->setVisible(false);
    this->ui->PressToSeePersonal->setVisible(true);
    this->ui->PressToSeeSchedule->setVisible(true);
    this->ui->PersonalInfo->setVisible(true);
    this->ui->ClassInfo->setVisible(true);
    this->ui->PersonalInfoPic->setVisible(true);
    this->ui->ScheduleInfoPic->setVisible(true);
    this->ui->Help->setVisible(true);
    this->ui->HelpPic->setVisible(true);
    this->ui->PressToSeeHelp->setVisible(true);
    this->ui->Exit->setVisible(true);
    this->ui->ExitPic->setVisible(true);
    this->ui->PressToExit->setVisible(true);
    this->ui->Return->setVisible(false);
    this->ui->ReturnPic->setVisible(false);
    this->ui->Boy->setVisible(false);
    this->ui->Girl->setVisible(false);
    this->ui->StudentInfo->setVisible(false);
    this->ui->Return->setVisible(false);
    this->ui->Paint->setVisible(false);
    this->ui->MonSecOne->setVisible(false);
    this->ui->MonSecTwo->setVisible(false);
    this->ui->MonSecThree->setVisible(false);
    this->ui->MonSecFour->setVisible(false);
    this->ui->MonSecFive->setVisible(false);
    this->ui->MonSecSix->setVisible(false);
    this->ui->MonSecSeven->setVisible(false);
    this->ui->MonSecEight->setVisible(false);
    this->ui->TueSecOne->setVisible(false);
    this->ui->TueSecTwo->setVisible(false);
    this->ui->TueSecThree->setVisible(false);
    this->ui->TueSecFour->setVisible(false);
    this->ui->TueSecFive->setVisible(false);
    this->ui->TueSecSix->setVisible(false);
    this->ui->TueSecSeven->setVisible(false);
    this->ui->TueSecEight->setVisible(false);
    this->ui->WedSecOne->setVisible(false);
    this->ui->WedSecTwo->setVisible(false);
    this->ui->WedSecThree->setVisible(false);
    this->ui->WedSecFour->setVisible(false);
    this->ui->WedSecFive->setVisible(false);
    this->ui->WedSecSix->setVisible(false);
    this->ui->WedSecSeven->setVisible(false);
    this->ui->WedSecEight->setVisible(false);
    this->ui->ThurSecOne->setVisible(false);
    this->ui->ThurSecTwo->setVisible(false);
    this->ui->ThurSecThree->setVisible(false);
    this->ui->ThurSecFour->setVisible(false);
    this->ui->ThurSecFive->setVisible(false);
    this->ui->ThurSecSix->setVisible(false);
    this->ui->ThurSecSeven->setVisible(false);
    this->ui->ThurSecEight->setVisible(false);
    this->ui->FriSecOne->setVisible(false);
    this->ui->FriSecTwo->setVisible(false);
    this->ui->FriSecThree->setVisible(false);
    this->ui->FriSecFour->setVisible(false);
    this->ui->FriSecFive->setVisible(false);
    this->ui->FriSecSix->setVisible(false);
    this->ui->FriSecSeven->setVisible(false);
    this->ui->FriSecEight->setVisible(false);
    this->ui->Monday->setVisible(false);
    this->ui->Tuesday->setVisible(false);
    this->ui->Wednesday->setVisible(false);
    this->ui->Thursday->setVisible(false);
    this->ui->Friday->setVisible(false);
    this->ui->SecOne->setVisible(false);
    this->ui->SecTwo->setVisible(false);
    this->ui->SecThree->setVisible(false);
    this->ui->SecFour->setVisible(false);
    this->ui->SecFive->setVisible(false);
    this->ui->SecSix->setVisible(false);
    this->ui->SecSeven->setVisible(false);
    this->ui->SecEight->setVisible(false);
    this->ui->SchedulePic->setVisible(false);
}

void ScheduleTable::on_Help_clicked() {

    /*显示新界面，屏蔽原界面*/
    this->ui->Return->setVisible(true);
    this->ui->ReturnPic->setVisible(true);
    this->ui->Help->setVisible(false);
    this->ui->HelpPic->setVisible(false);
    this->ui->PressToSeeHelp->setVisible(false);
    this->ui->PersonalInfo->setVisible(false);
    this->ui->PersonalInfoPic->setVisible(false);
    this->ui->PressToSeePersonal->setVisible(false);
    this->ui->ClassInfo->setVisible(false);
    this->ui->ScheduleInfoPic->setVisible(false);
    this->ui->PressToSeeSchedule->setVisible(false);
    this->ui->Exit->setVisible(false);
    this->ui->ExitPic->setVisible(false);
    this->ui->PressToExit->setVisible(false);

    /*显示帮助信息*/
    QString TextToSet;
    TextToSet.clear();
    TextToSet += "欢迎使用本课程表程序";
    TextToSet += "\n";
    TextToSet += "作者: 唐义泓(北邮) 刘彦博(北邮)";
    TextToSet += "\n";
    TextToSet += "在主界面点击相应图标可查询个人信息,课程信息和帮助信息";
    TextToSet += "\n";
    TextToSet += "在课程信息界面点击课程表对应表格内容可显示详细信息";
    TextToSet += "\n";
    TextToSet += "如有其他问题可通过以下联系方式联系作者:";
    TextToSet += "\n";
    TextToSet += "**********@**.com";

    this->ui->HelpInfo->setText(TextToSet);
    this->ui->HelpInfo->setVisible(true);
}

void ScheduleTable::on_Exit_clicked() {

    /*提示用户是否确认退出*/
    QMessageBox:: StandardButton result= QMessageBox::information(NULL, "提示", "确认登出？",QMessageBox::Yes|QMessageBox::No);

    //qDebug()<<"111"<<endl;
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

void ScheduleTable::on_MonSecOne_pressed() {

    /*关闭时间显示防止遮挡*/
    this->ui->Time->setVisible(false);

    /*获取点击的课程信息*/
    QString Text = this->ui->MonSecOne->text();

    /*如果没有课程，显示"REST"*/
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        /*有课程，则获取课程ID，发送查询请求，显示用于显示课程信息的控件ClassSpecificInfo*/
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecOne_released() {

    /*松开按键，显示时间，关闭其他，并把ClassSpecificInfo的内容清空*/
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

/*以下39个控件的逻辑与上述相似*/
void ScheduleTable::on_MonSecTwo_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecTwo->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecTwo_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_MonSecThree_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecThree->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecThree_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_MonSecFour_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecFour->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecFour_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_MonSecFive_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecFive->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecFive_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_MonSecSix_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecSix->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecSix_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_MonSecSeven_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecSeven->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecSeven_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_MonSecEight_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->MonSecEight->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_MonSecEight_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecOne_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecOne->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecOne_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecTwo_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecTwo->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecTwo_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecThree_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecThree->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecThree_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecFour_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecFour->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecFour_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecFive_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecFive->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecFive_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecSix_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecSix->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecSix_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecSeven_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecSeven->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecSeven_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_TueSecEight_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->TueSecEight->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_TueSecEight_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecOne_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecOne->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecOne_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecTwo_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecTwo->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecTwo_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecThree_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecThree->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecThree_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecFour_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecFour->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecFour_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecFive_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecFive->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecFive_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecSix_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecSix->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecSix_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecSeven_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecSeven->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecSeven_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_WedSecEight_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->WedSecEight->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_WedSecEight_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecOne_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecOne->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecOne_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecTwo_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecTwo->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecTwo_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecThree_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecThree->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecThree_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecFour_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecFour->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecFour_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecFive_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecFive->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecFive_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecSix_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecSix->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecSix_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecSeven_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecSeven->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecSeven_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_ThurSecEight_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->ThurSecEight->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_ThurSecEight_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecOne_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecOne->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecOne_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecTwo_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecTwo->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecTwo_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecThree_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecThree->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecThree_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecFour_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecFour->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecFour_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecFive_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecFive->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecFive_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecSix_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecSix->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecSix_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecSeven_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecSeven->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecSeven_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}

void ScheduleTable::on_FriSecEight_pressed()
{
    this->ui->Time->setVisible(false);
    QString Text = this->ui->FriSecEight->text();
    if (Text.isEmpty()) {
        this->ui->Rest->setVisible(true);
    }
    else {
        QStringList TextIDLine = Text.split("\n");
        QStringList TextID = TextIDLine[0].split(" ");
        QString ClassID = TextID[1];

        ApplyClassInfo(ClassID);
        this->ui->ClassSpecificInfo->setVisible(true);
    }
}

void ScheduleTable::on_FriSecEight_released()
{
    this->ui->Rest->setVisible(false);
    this->ui->ClassSpecificInfo->setVisible(false);
    this->ui->Time->setVisible(true);
    this->ui->ClassSpecificInfo->clear();
}
