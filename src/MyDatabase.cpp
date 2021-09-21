#include "MyDatabase.h"
QList<QString> MyDatabase::InnerQuery(QString Operation, int Col) {
    QSqlQuery QueryHandle(DB);
    if (Valid == false) {
        QMessageBox::information(NULL, "Alert", "数据库未连接");
        return {};
    }

    QList<QString> Ret = {};

    this->SharedAreaLocker.relock();
    if (QueryHandle.exec(Operation) == false)
    {
        qDebug() << "Error: Fail to exec.error:" << QueryHandle.lastError() << endl;
    }
    else {
        if (Col > 0) {
            int counter = 0;
            while (QueryHandle.next() == true) {
                for (counter = 0; counter < Col; counter++) {
                    //qDebug()<<QueryHandle.value(counter)<<endl;
                    Ret.push_back(QueryHandle.value(counter).toString());
                }
            }

        }
    }
    this->SharedAreaLocker.unlock();
    return Ret;
}

MyDatabase::MyDatabase(QString Name, QString Addr, QString Username, QString Password) :
    SharedAreaLocker(&SharedAreaLock),
    Valid(true), DatabaseName(Name), DatabaseAddr(Addr),
    DatabaseUsername(Username), DatabasePassword(Password)
{}

void MyDatabase::SetDataBase(QString Name, QString Addr, QString Username, QString Password) {

    /*进行相应赋值操作*/
    DatabaseName = Name;
    DatabaseAddr = Addr;
    DatabaseUsername = Username;
    DatabasePassword = Password;
}

int MyDatabase::ConnectToServer() {

    /*本地数据库，没有地址信息*/
    if (DatabaseAddr == "") {
        /*查找文件是否存在*/
        QFile file(this->DatabaseName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
            qDebug() << "Error: Failed to connect database.File not exists.";
            Valid = false;
            return -1;
        }
        else {
            file.close();
        }

    }

    /*捕获以前的连接*/
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        DB = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        DB = QSqlDatabase::addDatabase("QSQLITE");
        DB.setDatabaseName(DatabaseName);
    }

    /*根据打开的状态设置Valid标识*/
    if (DB.open() == false)
    {
        qDebug() << "Error: Failed to connect database." << DB.lastError();
    }
    else
    {
        std::cout << "Connect Succ" << std::endl;
        this->Valid = true;
    }

    /*根据Valid标识返回是否成功的信息*/
    if (Valid == true) {
        return 1;
    }
    else {
        return -1;
    }

}

int MyDatabase::DisConnectToServer() {

    /*关闭数据库，设置标识*/
    DB.close();
    Valid = false;
    return 1;
}

MyDatabase::~MyDatabase() {

    /*析构函数，断开数据库连接*/
    this->DisConnectToServer();
    std::cout << "DataBase closed" << std::endl;
}
