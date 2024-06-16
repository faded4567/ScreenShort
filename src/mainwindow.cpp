#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/icon.ico"));
    // 注册
    hook.Install();
    qRegisterMetaType<Hook::Type>("Type");
    connect(&hook,&Hook::SendType,this,&MainWindow::SlotSignal);

    m_mask = new MaskWidget(this);
    m_mask->hide();

    QSystemTrayIcon* trayIcon=new QSystemTrayIcon(this);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(sysTragIconActived(QSystemTrayIcon::ActivationReason)));
    trayIcon->setIcon(QIcon(":/icon.png"));
    trayIcon->setToolTip("简易截屏");
    trayIcon->show();

    QMenu *trayIconMenu;
    QAction *helpAction;
    QAction *quitAction;
    //下面的构造函数中进行执行
    helpAction=new QAction("帮助",this);
    connect(helpAction,&QAction::triggered,this,[=](){
        QMessageBox::information(this,_C("帮助"),_C("1.按下键盘组合建ctrl alt + A 即可进入截图模式，可通过鼠标框选截图部分\n"
                                                     "2.按下ESC可退出截图模式\n"
                                                     "3.在框选部分中按下鼠标右键可选择将图片复制或另存为\n"
                                                     "4.在系统托盘中右键图标可退出本软件"));
    });
    quitAction=new QAction("退出",this);
    //connect(quitAction,&QAction::triggered,this,&Widget::close);    //关联窗口的close不太合适
    connect(quitAction,&QAction::triggered,this,&QCoreApplication::quit);   //应用程序的退出

    //创建菜单，添加菜单项
    trayIconMenu=new QMenu(this);
    trayIconMenu->addAction(helpAction);
    trayIconMenu->addSeparator();   //分割线
    trayIconMenu->addAction(quitAction);
    //给系统托盘添加右键菜单
    trayIcon->setContextMenu(trayIconMenu);

    QMessageBox::information(this,_C("提示"),_C("程序已启动，可通过系统托盘右键关闭\n"
                                                  "1.按下键盘组合建ctrl alt + A 即可进入截图模式，可通过鼠标框选截图部分\n"
                                                  "2.按下ESC可退出截图模式\n"
                                                  "3.在框选部分中按下鼠标右键可选择将图片复制或另存为\n"
                                                  "4.在系统托盘中右键图标可退出本软件"));
}

MainWindow::~MainWindow()
{
    hook.UnInstall();
}

void MainWindow::SlotSignal(Hook::Type type)
{
    switch(type)
    {
    case Hook::SHOT:
    {
        // 全屏遮罩
        qApp->beep();   // 蹦的一声
        m_mask->show();
        break;
    }
    case Hook::ESC:
    {
        m_mask->hide();
        break;
    }
    }
}

void MainWindow::sysTragIconActived(QSystemTrayIcon::ActivationReason acv)
{
    // 处理托盘处理
    switch(acv)
    {
    case QSystemTrayIcon::Trigger:  //点击
        break;
    case QSystemTrayIcon::DoubleClick:  //双击
        break;
    case QSystemTrayIcon::MiddleClick:  //中键点击
        break;
    case QSystemTrayIcon::Unknown:
        break;
    case QSystemTrayIcon::Context:
        break;
    }
}
