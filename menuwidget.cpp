#include "menuwidget.h"
#include "ui_menuwidget.h"
#include "List.h"
menuwidget::menuwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menuwidget)
{
    ui->setupUi(this);
}

menuwidget::~menuwidget()
{
    delete ui;
}
void menuwidget:: on_exitButton_clicked(){
    QApplication::exit();
}
void menuwidget:: on_calButton_clicked(){
    QString l = ui->leftlineEdit->text();
    QString r = ui->rightlineEdit->text();
    QString zf = "";//判断大小关系
    if(l == "" || r == "") QMessageBox::about(NULL, "报错啦", "存在空项");
    else{
        bool isDigital=l.contains(QRegExp("^\\d+$"));
        bool isDigital1=r.contains(QRegExp("^\\d+$"));
        if(!isDigital || !isDigital1) QMessageBox::about(NULL, "报错啦", "存在非法字符");
        else{
            QString z = ui->comboBox->currentText();
            QString j = ui->jcomboBox->currentText();
            l.remove(QRegExp("^(0+)"));
            r.remove(QRegExp("^(0+)"));
            if(j == "十进制"){
                //加法     未做：正+负(已经在输入排除掉)
                if(z == "+"){
                    QElapsedTimer timer;
                    timer.start();
                    List* left = new List(l);
                    List* right = new List(r);
                    List* answer = left->plus(right);
                    QString temp = answer->show();
                    ui->anslineEdit->setText("结果："+zf+temp);
                    ui->answeilabel->setText(QString::number(temp.length()));
                    ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                }
                //减法
                if(z == "-"){
                    QElapsedTimer timer;
                    timer.start();

                    if(l.length()<r.length()) zf = "-";
                    else if(l.length() == r.length()){
                         for(int i = 0;i<l.length();i++){
                             if(l[i]<r[i]){
                                 zf = "-";
                                 break;
                             }
                         }
                    }
                    if(zf == ""){
                        List* left = new List(l);
                        List* right = new List(r);
                        List* answer = left->minus(right);
                        QString temp = answer->show();
                        if(temp == "") temp = "0";
                        ui->anslineEdit->setText("结果："+zf+temp);
                        ui->answeilabel->setText(QString::number(temp.length()));
                        ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                    }
                    else{
                        List* left = new List(r);
                        List* right = new List(l);
                        List* answer = left->minus(right);
                        QString temp = answer->show();
                        if(temp == "") temp = "0";
                        ui->anslineEdit->setText("结果："+zf+temp);
                        ui->answeilabel->setText(QString::number(temp.length()));
                        ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                    }
                 }
                //乘法
                if(z == "*"){
                    QElapsedTimer timer;
                    timer.start();
                    List* left = new List(l);
                    List* right = new List(r);
                    List* answer = left->cheng(right);
                    QString temp = answer->show();
                    ui->anslineEdit->setText("结果："+zf+temp);
                    ui->answeilabel->setText(QString::number(temp.length()));
                    ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                }
                //除法
                if(z == "/"){
                    if(r == "0") QMessageBox::about(NULL, "报错啦", "被除数不能为0");
                    else{
                        if(r.length()<10){
                            QElapsedTimer timer;
                            timer.start();
                            List* left = new List(l,1);//1是为了反转
                            List* ri = new List(r,1);
                            if(left->cmp(ri)){
                                long long int right = r.toLongLong();
                                List* answer = left->chu(right);//报错，无法运行
                                QString temp = answer->show1();
                                ui->anslineEdit->setText("结果："+zf+temp);
                                ui->answeilabel->setText(QString::number(temp.length()));
                                ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                            }
                            else{
                                ui->anslineEdit->setText("结果："+zf+'0');
                                ui->answeilabel->setText(QString::number(1));
                                ui->timelabel->setText("0ms");
                            }

                        }
                        else{
                            QElapsedTimer timer;
                            timer.start();
                            List* left = new List(l,1);//1是为了反转
                            List* right = new List(r,1);
                            if(left->cmp(right)){
                                List* answer = left->chulist(right);
                                QString temp = answer->show1();
                                ui->anslineEdit->setText("结果："+zf+temp);
                                ui->answeilabel->setText(QString::number(temp.length()));
                                ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                            }
                            else{
                                ui->anslineEdit->setText("结果："+zf+'0');
                                ui->answeilabel->setText(QString::number(1));
                                ui->timelabel->setText("0ms");
                            }

                        }

                    }
                }
                //指数
                if(z == "^"){
                    if(r == "0"){
                        ui->anslineEdit->setText("结果："+zf+'1');
                        ui->answeilabel->setText(QString::number(1));
                        ui->timelabel->setText("0ms");
                    }
                    else if(r == "1"){
                        ui->anslineEdit->setText("结果："+zf+l);
                        ui->answeilabel->setText(QString::number(l.length()));
                        ui->timelabel->setText("0ms");
                    }
                    else if(l == "1"){
                        ui->anslineEdit->setText("结果："+zf+1);
                        ui->answeilabel->setText(QString::number(1));
                        ui->timelabel->setText("0ms");
                    }
                    else if(l == "0"){
                        ui->anslineEdit->setText("结果："+zf+ "0");
                        ui->answeilabel->setText(QString::number(0));
                        ui->timelabel->setText("0ms");
                    }
                    else{
                        QElapsedTimer timer;
                        timer.start();
                        List* left = new List(l);
                        long long int right = r.toLongLong();

                        if(r.length()<2){
                            List* answer = left->zhi(right);
                            QString temp = answer->show();
                            ui->anslineEdit->setText("结果："+zf+temp);
                            ui->answeilabel->setText(QString::number(temp.length()));
                            ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                        }
                        else{

                            List* ri = new List(r);
                            List* answer = left->zhii(ri);
                            QString temp = answer->show();
                            ui->anslineEdit->setText("结果："+zf+temp);
                            ui->answeilabel->setText(QString::number(temp.length()));
                            ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                        }

                    }


                }


            }
            if(j == "二进制"){
                bool istwoDigital=l.contains(QRegExp("^[0-1]+$"));//处理二进制，输入非二进制报错
                bool istwoDigital1=r.contains(QRegExp("^[0-1]+$"));
                if(!istwoDigital || !istwoDigital1) QMessageBox::about(NULL, "报错啦", "存在非法字符");
                else{
                    l.remove(QRegExp("^(0+)"));
                    r.remove(QRegExp("^(0+)"));
                    if(z == "+"){
                        QElapsedTimer timer;
                        timer.start();
                        List* left = new List(l);
                        List* right = new List(r);
                        List* answer = left->doubleplus(right);
                        QString temp = answer->show();
                        ui->anslineEdit->setText("结果："+zf+temp);
                        ui->answeilabel->setText(QString::number(temp.length()));
                        ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                    }
                    if(z == "-"){
                        QElapsedTimer timer;
                        timer.start();

                        if(l.length()<r.length()) zf = "-";
                        else if(l.length() == r.length()){
                             for(int i = 0;i<l.length();i++){
                                 if(l[i]<r[i]){
                                     zf = "-";
                                     break;
                                 }
                             }
                        }
                        if(zf == ""){
                            List* left = new List(l);
                            List* right = new List(r);
                            List* answer = left->doubleminus(right);
                            QString temp = answer->show();
                            ui->anslineEdit->setText("结果："+zf+temp);
                            ui->answeilabel->setText(QString::number(temp.length()));
                            ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                        }
                        else{
                            List* left = new List(r);
                            List* right = new List(l);
                            List* answer = left->doubleminus(right);
                            QString temp = answer->show();
                            ui->anslineEdit->setText("结果："+zf+temp);
                            ui->answeilabel->setText(QString::number(temp.length()));
                            ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                        }
                    }
                    if(z == "*"){
                        QElapsedTimer timer;
                        timer.start();
                        List* left = new List(l);
                        List* right = new List(r);
                        List* answer = left->doublecheng(right);
                        QString temp = answer->show();
                        ui->anslineEdit->setText("结果："+zf+temp);
                        ui->answeilabel->setText(QString::number(temp.length()));
                        ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                    }
                    if(z == "/"){
                        if(r == "0") QMessageBox::about(NULL, "报错啦", "被除数不能为0");
                        else{
                                QElapsedTimer timer;
                                timer.start();
                                List* left = new List(l,1);//1是为了反转
                                List* right = new List(r,1);
                                if(left->cmp(right)){
                                    List* answer = left->doublechu(right);
                                    QString temp = answer->show1();
                                    ui->anslineEdit->setText("结果："+zf+temp);
                                    ui->answeilabel->setText(QString::number(temp.length()));
                                    ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                                }
                                else{
                                    ui->anslineEdit->setText("结果："+zf+'0');
                                    ui->answeilabel->setText(QString::number(1));
                                    ui->timelabel->setText("0ms");
                                }

                        }
                    }
                    if(z == "^"){
                        if(r == "0"){
                            ui->anslineEdit->setText("结果："+zf+'1');
                            ui->answeilabel->setText(QString::number(1));
                            ui->timelabel->setText("0ms");
                        }
                        else if(r == "1"){
                            ui->anslineEdit->setText("结果："+zf+l);
                            ui->answeilabel->setText(QString::number(l.length()));
                            ui->timelabel->setText("0ms");
                        }
                        else if(l == "1"){
                            ui->anslineEdit->setText("结果："+zf+1);
                            ui->answeilabel->setText(QString::number(1));
                            ui->timelabel->setText("0ms");
                        }
                        else if(l == "0"){
                            ui->anslineEdit->setText("结果："+zf+ "0");
                            ui->answeilabel->setText(QString::number(0));
                            ui->timelabel->setText("0ms");
                        }
                        else{
                            QElapsedTimer timer;
                            timer.start();
                            List* left = new List(l);
                            long long int right = r.toLongLong();
                            if(r.length()<2){
                                long long int str=(QString::number(right,10)).toLongLong();
                                List* answer = left->zhi(str);
                                QString temp = answer->show();
                                ui->anslineEdit->setText("结果："+zf+temp);
                                ui->answeilabel->setText(QString::number(temp.length()));
                                ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                            }
                            else{

                                List* ri = new List(r);
                                List* answer = left->doublezhii(ri);
                                QString temp = answer->show();
                                ui->anslineEdit->setText("结果："+zf+temp);
                                ui->answeilabel->setText(QString::number(temp.length()));
                                ui->timelabel->setText(QString::number(timer.elapsed()/1.0,10,5)+ "ms");
                            }

                        }
                    }
                }

            }
           // if(z == "+")
        }
     }

}
void menuwidget:: on_duquButton_clicked(){
    QFile file("./data/cal.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!file.isOpen()){
            QMessageBox::about(NULL, "是bug耶", "    数据文件打开失败了捏         ");
            return;
    }
    QString a;
    QString b;
    QTextStream inp(&file);
    while(!inp.atEnd()){
        inp>>a>>b;      //仅加入文件尾部的数据
    }
    file.close();
    ui->leftlineEdit->setText(a);
    ui->rightlineEdit->setText(b);
}
void menuwidget:: on_cunButton_clicked(){
    QFile file("./data/anc.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);            //只写，文本形式，添加到末尾
    if(!file.isOpen()){
            QMessageBox::about(NULL, "是bug耶", "    数据文件打开失败了捏      ");
            return;
    }

    QTextStream out(&file);
    QString a =ui->anslineEdit->text();
    if(a != ""){
        out<< a <<endl;
        file.close();                                                                //关文件
        QMessageBox::about(NULL, "不是BUG耶", "     存入成功啦       ");
    }
    else QMessageBox::about(NULL, "是BUG耶", "     存入为空       ");

}
