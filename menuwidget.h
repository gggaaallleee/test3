#ifndef MENUWIDGET_H
#define MENUWIDGET_H


#include <QWidget>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QElapsedTimer>
namespace Ui {
class menuwidget;
}

class menuwidget : public QWidget
{
    Q_OBJECT

public:
    explicit menuwidget(QWidget *parent = nullptr);
    ~menuwidget();

private:
    Ui::menuwidget *ui;
private slots:
    void on_calButton_clicked();
    void on_exitButton_clicked();
    void on_duquButton_clicked();
    void on_cunButton_clicked();
};

#endif // MENUWIDGET_H
