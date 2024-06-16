#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hook.h"
#include "loadprog.h"
#include <QSystemTrayIcon>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void SlotSignal(Hook::Type type);
    void sysTragIconActived(QSystemTrayIcon::ActivationReason acv);

private:
    Hook hook;
    MaskWidget *m_mask;
};

#endif // MAINWINDOW_H
