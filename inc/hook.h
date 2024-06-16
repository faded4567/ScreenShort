#ifndef HOOK
#define HOOK
#include <Windows.h>
#include <QObject>

// 创建钩子类
class Hook : public QObject
{
    Q_OBJECT
public:
    Hook();
    ~Hook();
    enum Type{SHOT,ESC};
    void Install();
    void UnInstall();
    void SendSignal(Type type);
    Q_ENUM(Type)
signals:
    void SendType(Type type);
};


#endif // HOOK

