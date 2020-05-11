#ifndef WINDEBUGMONITOR_H
#define WINDEBUGMONITOR_H

#include <windows.h>
#include <string>

class WinDebugMonitor
{
public:
    WinDebugMonitor();
    ~WinDebugMonitor();

private:
    enum {
        TIMEOUT_WIN_DEBUG = 100,
    };

    struct dbwin_buffer
    {
        DWORD dwProcessId;
        char data[4096 - sizeof(DWORD)];
    };

private:
    HANDLE m_hDBWinMutex;
    HANDLE m_hDBMonBuffer;
    HANDLE m_hEventBufferReady;
    HANDLE m_hEventDataReady;

    HANDLE m_hWinDebugMonitorThread;
    BOOL m_bWinDebugMonStopped;
    struct dbwin_buffer *m_pDBBuffer;

private:
    DWORD Initialize();
    void Unintialize();
    DWORD WinDebugMonitorProcess();
    static DWORD WINAPI WinDebugMonitorThread(void *pData);

public:
    virtual void OutputWinDebugString(const char *str) {};
};

#endif // WINDEBUGMONITOR_H
