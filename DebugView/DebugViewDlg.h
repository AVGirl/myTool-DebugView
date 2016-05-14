
// DebugViewDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h" 
#include "afxwin.h"
#include "Data.h" 
#include "CNewEdit.h"
#include "CFiltering.h"

#define SEND_SERVER 1
#define RECV_SERVER 2
#define SEND_HARDWARE 3 
#define RECV_HARDWARE 4 

// CDebugViewDlg �Ի���
class CDebugViewDlg : public CDialogEx
{
// ����
public:
	CDebugViewDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
    enum { IDD = IDD_DEBUGVIEW_DIALOG };
    CListCtrl m_listShow;
    CTabCtrl m_tabCtrl;
    CNewEdit m_Edit;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
    afx_msg void OnBnClickedRadio3();
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
    
    //�Ƿ��հ�
    afx_msg void OnBnClickedCheck1();
    
    //����б�
    afx_msg void OnBnClickedButton2();

    //ˢ����ʾ
    afx_msg void OnBnClickedButton4();

    //�����������
    afx_msg void OnBnClickedButton6();
     
    //�򿪹�����
    afx_msg void OnBnClickedButton3();
    
    //�й���Ϣ
    afx_msg void About();
	
    //ע��DLL
    afx_msg void OnBnClickedButton1();
    DECLARE_MESSAGE_MAP()

    void initList();
     
    void initTabCtrl();

    void showData(tagBuffer* buff);

    bool filteringPack(COPYDATASTRUCT* pCopyDataStruct); 
      
    void showByte(tagBuffer* pBuff);
      
    void showByte(std::map<int, tagBuffer*>* pItem);

    void showEditByte(CString str);

    void clearList();

private:
    bool m_pack;

    int m_showComm;

    int m_filteringState; 

    CData m_data;   

    CFilter m_filter; 
};
