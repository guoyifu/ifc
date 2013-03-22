#pragma once

#include "ifc.h"
#include "CodeCountingResult.h"

///////////////////////////////////////////////////////////////////////////////
// classes:

class CCodeCounter;
class CBaseCodeCntAlgo;
class CCppCodeCntAlgo;
class CPascalCodeCntAlgo;
class CJavaCodeCntAlgo;
class CCsCodeCntAlgo;

///////////////////////////////////////////////////////////////////////////////
// class CCodeCounter

class CCodeCounter
{
private:
    CStrList m_CppFileExtList;
    CStrList m_PascalFileExtList;
    CStrList m_JavaFileExtList;
    CStrList m_CsFileExtList;
private:
    void InitFileExtList();
public:
    CCodeCounter();
    ~CCodeCounter();

    void GetCppFileExtList(CStrList& List) { List = m_CppFileExtList; }
    void GetPascalFileExtList(CStrList& List) { List = m_PascalFileExtList; }
    void GetJavaFileExtList(CStrList& List) { List = m_JavaFileExtList; }
    void GetCsFileExtList(CStrList& List) { List = m_CsFileExtList; }

    bool Perform(LPCTSTR lpszFileName, CCodeCntResultVals& Result);
};

///////////////////////////////////////////////////////////////////////////////
// class CBaseCodeCntAlgo - Դ��ͳ���㷨 ����

class CBaseCodeCntAlgo
{
public:
    // ע���ַ�����
    enum COMMENTS_CHAR_TYPE 
    {
        CCT_LINE_CMT_SINGLE_CHAR      = 0,   // ��ע�͵��ַ�����VB�ġ�'��
        CCT_LINE_CMT_DOUBLE_CHAR      = 1,   // ��ע��˫�ַ����硰//��
        CCT_SEG_CMT_BEGIN_SINGLE_CHAR = 2,   // ��ע����ʼ���ַ�����Delphi�ġ�{��
        CCT_SEG_CMT_END_SINGLE_CHAR   = 3,   // ��ע����ֹ���ַ�����Delphi�ġ�}��
        CCT_SEG_CMT_BEGIN_DOUBLE_CHAR = 4,   // ��ע����ʼ˫�ַ����硰/*��
        CCT_SEG_CMT_END_DOUBLE_CHAR   = 5,   // ��ע����ֹ˫�ַ����硰*/��
        CCT_TYPE_COUNT                = 6
    };

private:
    WCHAR m_chCmtChars[CCT_TYPE_COUNT][2];
private:
    void InitCommentsChars();
protected:
    bool IsLineBreakChar(WCHAR ch) { return (ch == 10 || ch == 13);  }
    bool IsBlankLine(LPCWSTR pStart, LPCWSTR pEnd);
    bool IsLineBreakStart(LPCWSTR pStr) { return IsLineBreakChar(pStr[0]); }
    void ScanLineBreak(LPCWSTR& pStr);
    bool CheckScanLineBreak(LPCWSTR& pStr);
    bool IsCommentsStart(LPCWSTR pStr);
    void ScanComments(LPCWSTR& pStr, int& nLines);
protected:
    virtual bool GetCommentsChars(COMMENTS_CHAR_TYPE nType, WCHAR chChars[2]) { return false; }
    virtual bool IsLiteralConstStart(LPCWSTR pStr) { return false; }
    virtual void ScanLiteralConst(LPCWSTR& pStr, int& nLines) {}
public:
    CBaseCodeCntAlgo();
    virtual ~CBaseCodeCntAlgo() {}
    void Execute(LPCWSTR lpszSource, CCodeCntResultVals& Result);
};

///////////////////////////////////////////////////////////////////////////////
// class CCppCodeCntAlgo - C/C++ Դ��ͳ���㷨

class CCppCodeCntAlgo : public CBaseCodeCntAlgo
{
protected:
    virtual bool GetCommentsChars(COMMENTS_CHAR_TYPE nType, WCHAR chChars[2]);
    virtual bool IsLiteralConstStart(LPCWSTR pStr);
    virtual void ScanLiteralConst(LPCWSTR& pStr, int& nLines);
};

///////////////////////////////////////////////////////////////////////////////
// class CPascalCodeCntAlgo - Pascal Դ��ͳ���㷨

class CPascalCodeCntAlgo : public CBaseCodeCntAlgo
{
protected:
    virtual bool GetCommentsChars(COMMENTS_CHAR_TYPE nType, WCHAR chChars[2]);
    virtual bool IsLiteralConstStart(LPCWSTR pStr);
    virtual void ScanLiteralConst(LPCWSTR& pStr, int& nLines);
};

///////////////////////////////////////////////////////////////////////////////
// class CJavaCodeCntAlgo - Java Դ��ͳ���㷨

class CJavaCodeCntAlgo : public CCppCodeCntAlgo {};

///////////////////////////////////////////////////////////////////////////////
// class CCsCodeCntAlgo - C# Դ��ͳ���㷨

class CCsCodeCntAlgo : public CCppCodeCntAlgo {};

///////////////////////////////////////////////////////////////////////////////
