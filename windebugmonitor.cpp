#include "windebugmonitor.h"

WinDebugMonitor::WinDebugMonitor()
{
    if (Initialize() != 0) {
        std::wstring str = L"WinDebugMonitor::Initialize() failed.\n";
        ::OutputDebugStringW(str.c_str());
    }
}

WinDebugMonitor::~WinDebugMonitor()
{
    Unintialize();
}

DWORD WinDebugMonitor::Initialize()
{
    DWORD errorCode = 0;
    BOOL bSuccessful = FALSE;

    SetLastError(0);

    std::wstring DBWinMutex = L"DBWinMutex";
    m_hDBWinMutex = ::OpenMutex(
                MUTEX_ALL_ACCESS,
                FALSE,
                DBWinMutex.c_str()
                );

    if (m_hDBWinMutex == NULL) {
        errorCode = GetLastError();
        return errorCode;
    }

    std::wstring DBWIN_BUFFER_READY = L"DBWIN_BUFFER_READY";
    m_hEventBufferReady = ::OpenEvent(
                EVENT_ALL_ACCESS,
                FALSE,
                DBWIN_BUFFER_READY.c_str()
                );

    if (m_hEventBufferReady == NULL) {
        m_hEventBufferReady = ::CreateEvent(
                    NULL,
                    FALSE,	// auto-reset
                    TRUE,	// initial state: signaled
                    DBWIN_BUFFER_READY.c_str()
                    );

        if (m_hEventBufferReady == NULL) {
            errorCode = GetLastError();
            return errorCode;
        }
    }

    std::wstring DBWIN_DATA_READY = L"DBWIN_DATA_READY";
    m_hEventDataReady = ::OpenEvent(
                SYNCHRONIZE,
                FALSE,
                DBWIN_DATA_READY.c_str()
                );

    if (m_hEventDataReady == NULL) {
        m_hEventDataReady = ::CreateEvent(
                    NULL,
                    FALSE,	// auto-reset
                    FALSE,	// initial state: nonsignaled
                    DBWIN_DATA_READY.c_str()
                    );

        if (m_hEventDataReady == NULL) {
            errorCode = GetLastError();
            return errorCode;
        }
    }

    std::wstring DBWIN_BUFFER = L"DBWIN_BUFFER";
    m_hDBMonBuffer = ::OpenFileMapping(
                FILE_MAP_READ,
                FALSE,
                DBWIN_BUFFER.c_str()
                );

    if (m_hDBMonBuffer == NULL) {
        m_hDBMonBuffer = ::CreateFileMapping(
                    INVALID_HANDLE_VALUE,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    sizeof(struct dbwin_buffer),
                    DBWIN_BUFFER.c_str()
                    );

        if (m_hDBMonBuffer == NULL) {
            errorCode = GetLastError();
            return errorCode;
        }
    }

    m_pDBBuffer = (struct dbwin_buffer *)::MapViewOfFile(
                m_hDBMonBuffer,
                SECTION_MAP_READ,
                0,
                0,
                0
                );

    if (m_pDBBuffer == NULL) {
        errorCode = GetLastError();
        return errorCode;
    }

    m_bWinDebugMonStopped = FALSE;

    m_hWinDebugMonitorThread = ::CreateThread(
                NULL,
                0,
                WinDebugMonitorThread,
                this,
                0,
                NULL
                );

    if (m_hWinDebugMonitorThread == NULL) {
        m_bWinDebugMonStopped = TRUE;
        errorCode = GetLastError();
        return errorCode;
    }

    bSuccessful = ::SetPriorityClass(
                ::GetCurrentProcess(),
                REALTIME_PRIORITY_CLASS
                );

    bSuccessful = ::SetThreadPriority(
                m_hWinDebugMonitorThread,
                THREAD_PRIORITY_TIME_CRITICAL
                );

    return errorCode;
}

void WinDebugMonitor::Unintialize()
{
    if (m_hWinDebugMonitorThread != NULL) {
        m_bWinDebugMonStopped = TRUE;
        ::WaitForSingleObject(m_hWinDebugMonitorThread, INFINITE);
    }

    if (m_hDBWinMutex != NULL) {
        CloseHandle(m_hDBWinMutex);
        m_hDBWinMutex = NULL;
    }

    if (m_hDBMonBuffer != NULL) {
        ::UnmapViewOfFile(m_pDBBuffer);
        CloseHandle(m_hDBMonBuffer);
        m_hDBMonBuffer = NULL;
    }

    if (m_hEventBufferReady != NULL) {
        CloseHandle(m_hEventBufferReady);
        m_hEventBufferReady = NULL;
    }

    if (m_hEventDataReady != NULL) {
        CloseHandle(m_hEventDataReady);
        m_hEventDataReady = NULL;
    }

    m_pDBBuffer = NULL;
}

DWORD WinDebugMonitor::WinDebugMonitorProcess()
{
    DWORD ret = 0;

    // wait for data ready
    ret = ::WaitForSingleObject(m_hEventDataReady, TIMEOUT_WIN_DEBUG);

    if (ret == WAIT_OBJECT_0) {
        OutputWinDebugString(m_pDBBuffer->data);

        // signal buffer ready
        SetEvent(m_hEventBufferReady);
    }

    return ret;
}

DWORD WINAPI WinDebugMonitor::WinDebugMonitorThread(void *pData)
{
    WinDebugMonitor *_this = (WinDebugMonitor *)pData;

    if (_this != NULL) {
        while (!_this->m_bWinDebugMonStopped) {
            _this->WinDebugMonitorProcess();
        }
    }

    return 0;
}
