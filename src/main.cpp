#include "MyMainWindow.h"
#include "MyDatabase.h"
#include <QApplication>

MyDatabase DatabaseInstance("LocalDatabase.db");

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);

    MyMainWindow w;

    w.show();

    return a.exec();

}

