#include "SubThreadQuery.h"

SubThreadQuery::SubThreadQuery(MyDatabase* DatabaseUsedArgv, QString CommandArgv, int QueryColArgv, int QueryIdArgv) :
    DatabaseUsed(DatabaseUsedArgv), Command(CommandArgv), QueryCol(QueryColArgv), QueryId(QueryIdArgv)
{

    /*纠正并提示行数错误*/
    if (QueryCol < 0) {

        qDebug() << "查询行数小于0?" << endl;
        QueryCol = 0;
    }

    /*注册信息，这样QList<QString>就可以作为信号的参数在不同线程间传递了*/
    qRegisterMetaType<QList<QString> >("QList<QString>");

    /*线程查询对象在查询完成后销毁*/
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

}

void SubThreadQuery::run() {

    /*在新线程里查询*/
    QList<QString> result = {};
    result = this->DatabaseUsed->InnerQuery(Command, QueryCol);

    /*以信号形式发送查询结果并退出*/
    emit SendQueryResult(result, 0, QueryId);
    this->exit(0);
}
