/*******************************************************************************************
 * FileProperties: 
 *     FileName: loadprog.h
 *     SvnProperties: 
 *         $URL: http://192.168.0.155/svn/HQP2263/DEVELOP/P2/5_Software/51_Host/inc/FastUI/loadprog.h $
 *         $Author: yangshuai $
 *         $Revision: 235 $
 *         $Date: 2024-02-02 13:22:05 $
*******************************************************************************************/
#ifndef LOADPROG_H
#define LOADPROG_H

#include <QWidget>
#include <QPainter>
#include <QRegion>
#include <QCloseEvent>
#include <QMenu>
#include <QMimeData>
#define _C(X) QString::fromUtf8(X)
namespace Ui {
class LoadProg;
}
enum CopyType
{
    PART,
    ALL,
};
// 遮罩图层
class MaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MaskWidget(QWidget *parent = 0);
    ~MaskWidget();
    void Copy();
    void Save();
    void GetPixmap(CopyType type);
protected:
    virtual void mouseMoveEvent(QMouseEvent *t);
    virtual void mousePressEvent(QMouseEvent *t);
    virtual void mouseReleaseEvent(QMouseEvent *t);
    virtual void paintEvent(QPaintEvent *);
    virtual void closeEvent(QCloseEvent *t);
    virtual void hideEvent(QHideEvent *event);
signals:

private:
    QPixmap screen; //截屏图片
    QPointF start,end;
    int x,y,w,h;
    QMenu *m_menu;
    QString m_path;

};
#endif // LOADPROG_H
