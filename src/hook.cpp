#include "hook.h"
#include <QDebug>
#pragma comment(lib,"../lib/User32.Lib")
static HHOOK keyHook = nullptr; //钩子对象
static Hook *hook;
// 消息队列函数 系统消息队列会返回到此函数中
LRESULT CALLBACK keyProc(int nCode,WPARAM wParam,LPARAM lParam)
{
    // 判断按键类型
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *)lParam;
    // wParam判断事件类型
    if(wParam==WM_KEYDOWN)
    {
        // 按下ctrl + alt + a
        if(pkbhs->vkCode == 0x41 && GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_MENU))
        {
            hook->SendSignal(Hook::SHOT);
        }
        else if(GetAsyncKeyState(VK_ESCAPE))
        {
            hook->SendSignal(Hook::ESC);
        }
    }
    return CallNextHookEx(keyHook,nCode,wParam,lParam); //继续消息队列

}

Hook::Hook()
{

}

Hook::~Hook()
{

}

void Hook::Install()
{
    keyHook = SetWindowsHookEx(WH_KEYBOARD_LL,keyProc,nullptr,0);
    hook = this;
}

void Hook::UnInstall()
{
    UnhookWindowsHookEx(keyHook);
    keyHook = nullptr;
}

void Hook::SendSignal(Hook::Type type)
{
    emit SendType(type);
}
