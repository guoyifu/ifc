#pragma once

#include "ifc.h"
#include "CodeCountingAlgo.h"

///////////////////////////////////////////////////////////////////////////////

// ��ͳ����һ���ļ�
const int WM_CODECNT_FINISHED_FILE   = WM_USER + 101;
// ȫ��ͳ�����
const int WM_CODECNT_FINISHED_ALL    = WM_USER + 102;

///////////////////////////////////////////////////////////////////////////////

struct CCodeCountingParams
{
    CStrList FileExtList;   // �ļ���չ���б�(��: ".c", ".cpp" ...)
    CString strPath;        // ·��
    bool bRecurseSubDir;    // �Ƿ�ݹ������Ŀ¼
    HWND hMsgRecver;        // ��Ϣ���մ���
};

///////////////////////////////////////////////////////////////////////////////

class CCodeCountingThread : public CThread
{
private:
    CCodeCountingParams m_Params;
    CCodeCounter m_CodeCounter;
private:
    void ScanDir(LPCTSTR lpszPath);
    void AnalyzeFile(LPCTSTR lpszFileName);
    void NotifyFinishedFile();
    void NotifyFinishedAll();
protected:
    virtual void Execute();
    virtual void AfterExecute();
public:
    CCodeCountingThread(const CCodeCountingParams& Params);
    virtual ~CCodeCountingThread();
};
