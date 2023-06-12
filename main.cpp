#include "menuwidget.h"

#include <QApplication>

int main(int argc, char *argv[])             //程序启动
{
    QApplication a(argc, argv);
    QFile qss("button.qss");
    if(qss.open(QFile::ReadOnly))
            a.setStyleSheet(qss.readAll());//创建应用程序对象
    else  QMessageBox::about(NULL, "是bug耶", "    qss文件打开失败了捏         ");
    menuwidget w;                            //对象
    w.setWindowTitle("大数计算器");             //标题
    w.show();                          //启动啦

    return a.exec();                    //交互不自动退出
}
