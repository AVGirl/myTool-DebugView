#pragma once
#include "afxcmn.h"
#include "CProcessInfo.h"


// CInjectionDLG �Ի���

class CInjectionDLG : public CDialogEx
{
	DECLARE_DYNAMIC(CInjectionDLG)

public:
	CInjectionDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInjectionDLG();

// �Ի�������
    enum { IDD = IDD_DIALOG1 };
    CListCtrl m_list1;
    CListCtrl m_list2;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    virtual BOOL OnInitDialog();
     
    //ע��
    afx_msg void OnBnClickedOk();
	 
    afx_msg void OnBnClickedButton1();

    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
     
    afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);

    //ж��
    afx_msg void OnBnClickedButton2();
    DECLARE_MESSAGE_MAP()

    void initList(); 
    
    void showProcess(); 

    void showMoudle();

private: 
    CProcessInfo m_pi;

    const processInfo* m_process;
    
    const moduleInfo* m_moudle;

    DWORD m_injectionID;

    CStringA m_dll;  

    DWORD m_removeBase;
};
