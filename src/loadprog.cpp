#include "loadprog.h"
#include <QApplication>
#include <QDesktopServices>
#include <qDebug>
#include <QPainterPath>
#include <QClipboard>
#include <QPixmap>
#include <QScreen>
#include <QTime>
#include <QFileDialog>

MaskWidget::MaskWidget(QWidget *parent):QWidget(parent)
{
    // 去除边框
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    setGeometry(QApplication::primaryScreen()->geometry());

    x=y=w=h=0;

    m_menu = new QMenu(this);
    m_menu->addAction(_C("复制到剪贴板"),this,[&](){GetPixmap(CopyType::PART);Copy();});
    m_menu->addAction(_C("选中部分另存为"),this,[&](){GetPixmap(CopyType::PART);Save();});
    m_menu->addAction(_C("复制整个屏幕到剪贴板"),this,[&](){GetPixmap(CopyType::ALL);Copy();});
    m_menu->addAction(_C("整个屏幕另存为"),this,[&](){GetPixmap(CopyType::ALL);Save();});

    m_menu->setStyleSheet("background-color: rgba(30,30,30,100);color: rgb(255,255,255);"
                          "border-right:2px solid #aaaaaa; "
                          "border-bottom:2px solid #aaaaaa;"
                          "border-left:2px solid #aaaaaa;"
                          "border-top:2px solid #aaaaaa; "
                          "border-radius:5px;"
                          "font: 16pt ""黑体"";"
                          "selection-background-color: rgb(100,40,40);");
}

MaskWidget::~MaskWidget()
{
}

void MaskWidget::Copy()
{
    //保存到粘贴板
    QClipboard *pic=QApplication::clipboard();
    pic->setPixmap(screen);
    //关闭之后清空
    x=y=w=h=0;
    update();
    this->hide();
}

void MaskWidget::Save()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Image",
                                                    m_path.isEmpty()?QDir::currentPath():m_path,
                                                    "JPG Files (*.jpg)");

    if(!fileName.isEmpty())
        m_path = fileName.left(fileName.lastIndexOf("/"));
    if(!fileName.isEmpty())
    {
        screen.save(fileName);
    }
    //关闭之后清空
    x=y=w=h=0;
    update();
    this->hide();
}

void MaskWidget::GetPixmap(CopyType type)
{
    //截屏
    if(type == PART)
    {
        screen = QApplication::primaryScreen()->grabWindow(0,x,y,w,h);
    }
    else
        screen = QApplication::primaryScreen()->grabWindow(0);
}


void MaskWidget::mouseMoveEvent(QMouseEvent *t)
{
    // 鼠标移动事件
    end = t->globalPosition()-this->pos();   // 获取结束坐标
    if(end.x() > start.x())
    {
        x = start.x();
        w = end.x() - start.x();
    }
    else
    {
        x = end.x();
        w = start.x() - end.x();
    }

    if(end.y() > start.y())
    {
        y = start.y();
        h = end.y() - start.y();
    }
    else
    {
        y = end.y();
        h = start.y() - end.y();
    }
    // 根据坐标和大小绘制框选区域
    update();
}

void MaskWidget::mousePressEvent(QMouseEvent *t)
{
    // 鼠标点击事件
    // 点击左键记录起始位置
    if(t->button() == Qt::LeftButton)
    {
        update();
        start = t->globalPosition()-this->pos();
        qDebug()<<"start"<<start;
    }
    // 右键点击框选区域弹出菜单
    else if(t->button() == Qt::RightButton && t->pos().x() >= x && t->pos().x() <= x+w && t->pos().y() >= y && t->pos().y() <= y+h)
    {
        m_menu->exec(cursor().pos());
    }
}

void MaskWidget::mouseReleaseEvent(QMouseEvent *t)
{

}
void MaskWidget::paintEvent(QPaintEvent *)
{
    // 全局遮罩
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush brush(QColor(0,0,0,150));
    painter.setBrush(brush);
    QPainterPath path;
    // 画框选区域
    path.addRect(x,y,w,h);
    path.addRect(this->geometry());
    painter.drawPath(path);
    //框选遮罩
    QPainter painter1(this);
    brush.setColor(QColor(100,100,100,20));
    painter1.setBrush(brush);
    painter1.drawRect(x,y,w,h);
}

void MaskWidget::closeEvent(QCloseEvent *t)
{
    t->ignore();
}
void MaskWidget::hideEvent(QHideEvent *event)
{
    //关闭之后清空
    x=y=w=h=0;
    update();
    this->hide();
    qDebug()<<"hide";
}
