
// DebugViewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DebugView.h"
#include "DebugViewDlg.h"
#include "afxdialogex.h" 
#include "CMyStatic.h" 
#include "CInjectionDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_USER_MY WM_USER + 1
#define WM_USER_MY2 WM_USER + 2
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
    enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg LRESULT OnMy(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnMy2(WPARAM wParam, LPARAM lParam);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    CMyStatic m_txt; 
    COLORREF m_colorText; 
    afx_msg void OnStnClickedadd();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_add, m_txt);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
    ON_MESSAGE(WM_USER_MY, OnMy)
    ON_MESSAGE(WM_USER_MY2, OnMy2)
    ON_WM_CTLCOLOR()
    ON_STN_CLICKED(IDC_add, &CAboutDlg::OnStnClickedadd)
END_MESSAGE_MAP()


// CDebugViewDlg �Ի���
BOOL CAboutDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_colorText = RGB(0, 0, 255);

    CFont *Font = new CFont;
    Font->CreateFont(14, 0, 0, 0, FALSE, FALSE, TRUE, 0
        , ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS
        , DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, NULL);

    GetDlgItem(IDC_add)->SetFont(Font);

    CString txt;
    txt.Format(
        L"DebugView��һ�������������Ӳ��ͨ�ź����ͨ�Ų鿴������Ϣ��һ��ߡ� \r\n\r\n"
        L"����������Ա��˳��(��)��˳�����̣���������������߻�ԭ�������̡� \r\n\r\n"
        L"���߲������ܵģ�����Ҫ�����ҵ����͵㲢���Լ�������HOOK�� \r\n\r\n"
        L"    HWND m_hwnd = ::FindWindow(NULL, \"DebugView\");  \r\n"
        L"    .... \r\n"
        L"    ::SendMessage(m_hwnd, WM_COPYDATA, NULL, (LPARAM)&data); \r\n\r\n"
        L"���\r\n"
        L"    send:      1 \r\n"
        L"    recve:     2 \r\n"
        L"    WriteFile: 3 \r\n"
        L"    ReadFile:  4 \r\n");

    SetDlgItemText(IDC_TXT, txt);
    return TRUE;
}
   
void CAboutDlg::OnStnClickedadd()
{
    ::ShellExecute(nullptr, L"open", L"www.xuwu.org", nullptr, nullptr, SW_SHOWNORMAL);
}

 
LRESULT CAboutDlg::OnMy(WPARAM wParam, LPARAM lParam)
{
    m_colorText = RGB(255, 0, 0);

    m_txt.GetDC()->SetTextColor(m_colorText);
    m_txt.Invalidate(FALSE);

    return FALSE;
}

LRESULT CAboutDlg::OnMy2(WPARAM wParam, LPARAM lParam)
{
    m_colorText = RGB(0, 0, 255);

    m_txt.GetDC()->SetTextColor(m_colorText);
    m_txt.Invalidate(FALSE);

    return FALSE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    if (pWnd->GetDlgCtrlID() == IDC_add)
    {
        pDC->SetTextColor(m_colorText);
    }

    return hbr;
}




CDebugViewDlg::CDebugViewDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDebugViewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
      
    m_pack = true;
}

void CDebugViewDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_listShow);
    DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
    DDX_Control(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CDebugViewDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_WM_COPYDATA()
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDebugViewDlg::OnTcnSelchangeTab1)
    ON_BN_CLICKED(IDC_RADIO1, &CDebugViewDlg::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &CDebugViewDlg::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &CDebugViewDlg::OnBnClickedRadio3)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDebugViewDlg::OnNMClickList1)
    ON_BN_CLICKED(IDC_CHECK1, &CDebugViewDlg::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_BUTTON2, &CDebugViewDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON4, &CDebugViewDlg::OnBnClickedButton4)
    ON_BN_CLICKED(IDC_BUTTON6, &CDebugViewDlg::OnBnClickedButton6)
    ON_BN_CLICKED(IDC_BUTTON3, &CDebugViewDlg::OnBnClickedButton3)
    ON_COMMAND(ID_32771, &CDebugViewDlg::About) 
    ON_BN_CLICKED(IDC_BUTTON1, &CDebugViewDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDebugViewDlg ��Ϣ�������

BOOL CDebugViewDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
       
    initTabCtrl();

    initList();

    m_filteringState = -1;

    ((CButton*)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);

    ((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(TRUE);
      
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDebugViewDlg::initTabCtrl()
{
    int inedx = 0; 
    m_tabCtrl.InsertItem(inedx++, L"All");
    m_tabCtrl.InsertItem(inedx++, L"srAll");
    m_tabCtrl.InsertItem(inedx++, L"send");
    m_tabCtrl.InsertItem(inedx++, L"recv");
    m_tabCtrl.InsertItem(inedx++, L"wrAll");
    m_tabCtrl.InsertItem(inedx++, L"writeFile");
    m_tabCtrl.InsertItem(inedx++, L"readFile"); 
}

void CDebugViewDlg::initList()
{
    m_listShow.SetExtendedStyle(
        m_listShow.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    int inedx = 0;
    m_listShow.InsertColumn(inedx++, L"type", LVCFMT_LEFT, 50);
    m_listShow.InsertColumn(inedx++, L"len", LVCFMT_LEFT, 50);
    m_listShow.InsertColumn(inedx++, L"dataBuff", LVCFMT_LEFT, 100000); 
}

void CDebugViewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDebugViewDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDebugViewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CDebugViewDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{  
    if (pCopyDataStruct->lpData != nullptr && m_pack == true)
    { 
        CString str;
        str = (LPSTR)pCopyDataStruct->lpData;
        int n = 0;

        if (m_filteringState != -1)
        {
            if (filteringPack(pCopyDataStruct) == false)
            {
                return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
            }
        } 

        tagBuffer* pBuff = m_data.addInfo(pCopyDataStruct);
        if (pBuff != nullptr)
        {
            showData(pBuff);
        } 
    }

    return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

void CDebugViewDlg::showData(tagBuffer* pBuff)
{  
    if (m_showComm == 0)
    {
        showByte(pBuff);
        return;
    }

    switch (pBuff->m_type)
    { 
    case SEND_SERVER:
    {
        if (m_showComm == 1 || m_showComm == 2 || m_showComm == 3)
        {
            showByte(pBuff);
        }
        break;
    }
    case RECV_SERVER:
    {
        if (m_showComm == 1 || m_showComm == 2 || m_showComm == 4)
        {
            showByte(pBuff);
        }
        break;
    }
    case SEND_HARDWARE:
    {
        if (m_showComm == 1 || m_showComm == 5 || m_showComm == 6)
        {
            showByte(pBuff);
        }
        break;
    }
    case RECV_HARDWARE:
    {
        if (m_showComm == 1 || m_showComm == 5 || m_showComm == 7)
        {
            showByte(pBuff);
        }
        break;
    }
    default:
        break;
    }
     
    return;
}

bool CDebugViewDlg::filteringPack(COPYDATASTRUCT* pCopyDataStruct)
{
    return m_filter.isFilter((BYTE*)pCopyDataStruct->lpData, pCopyDataStruct->cbData, m_filteringState);
} 

void CDebugViewDlg::showByte(tagBuffer* pBuff)
{
    WCHAR type[][20] = { 
        L"tmp",
        L"send",
        L"recv", 
        L"write",
        L"read"
    };
     
    m_listShow.InsertItem(m_listShow.GetItemCount(), type[pBuff->m_type]);
     
    CString str;
    str.Format(L"0x%X", pBuff->m_lenth);
    m_listShow.SetItemText(m_listShow.GetItemCount() - 1, 1, str);
     
    CString Int;
    for (int i = 0; i < pBuff->m_lenth; i++)
    { 
        Int.Format(L"%02X", pBuff->m_byte[i]);

        if (i == 0)
        { 
            str = CString(Int + L" ");
        } 
        else
        {
            str += CString(Int + L" ");
        }
    }
     
    m_listShow.SetItemText(m_listShow.GetItemCount() - 1, 2, str);
}

void CDebugViewDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
    m_showComm = m_tabCtrl.GetCurSel();
    switch (m_showComm)
    {
    case 0: 
    {
        showByte(m_data.getByteAll()); 
        break;
    }
    case 1:
    {
        showByte(m_data.getSR()); 
        break;
    }
    case 2:
    {
        showByte(m_data.getSend());
        break;
    }
    case 3:
    {
        showByte(m_data.getRecv());
        break;
    } 
    case 4:
    {
        showByte(m_data.getWR());
        break;
    }
    case 5:
    {
        showByte(m_data.getWeite());
        break;
    }
    case 6:
    {
        showByte(m_data.getRead());
        break;
    }
    default:
        break;
    } 
}


void CDebugViewDlg::OnBnClickedRadio1()
{
    m_filteringState = -1;
}


void CDebugViewDlg::OnBnClickedRadio2()
{
    m_filteringState = 1;
}


void CDebugViewDlg::OnBnClickedRadio3()
{
    m_filteringState = 0;
}
 

void CDebugViewDlg::showByte(std::map<int, tagBuffer*>* pItem)
{
    clearList(); 

    std::map<int, tagBuffer*>::iterator it = pItem->begin();
    for (it; it != pItem->end(); it++)
    {
        showByte((*it).second);
    }
}

void CDebugViewDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    
    int i = m_listShow.GetSelectionMark();
    if (i == -1)
        return;

    m_listShow.SetSelectionMark(-1);

    CString str = m_listShow.GetItemText(i, 2);
     
    m_Edit.showByte(str);

    *pResult = 0;
}


void CDebugViewDlg::showEditByte(CString str)
{
    int i = 0; 
    CString hex; 

    hex.Format(L"%08X: ", i);

    int count = str.GetLength();
    for (int inedx = 0, rn = 0; inedx < count; inedx++, rn++)
    { 
        hex += str[inedx];
         
        if (rn == 47)
        {
            rn = -1;  
            i+=0x10;

            CString tmp;
            tmp.Format(L"%08X: ", i);
            hex += CString(L"\r\n") + tmp; 
        }
    }

    SetDlgItemText(IDC_EDIT1, hex);
}

void CDebugViewDlg::OnBnClickedCheck1()
{
    m_pack = !m_pack;
}


void CDebugViewDlg::OnBnClickedButton2()
{
    m_data.deleteList(m_showComm); 
    clearList();
}

void CDebugViewDlg::clearList()
{
    SetDlgItemText(IDC_EDIT1, L"");
    m_listShow.DeleteAllItems();
} 

void CDebugViewDlg::OnBnClickedButton4()
{
    OnTcnSelchangeTab1(nullptr, nullptr);
}


void CDebugViewDlg::OnBnClickedButton6()
{
    m_data.deleteAllData(); 
    clearList();
}


void CDebugViewDlg::OnBnClickedButton3()
{
    m_filter.showFilterDlg();
}


void CDebugViewDlg::About()
{
    CAboutDlg about;

    about.DoModal();
}

void CDebugViewDlg::OnBnClickedButton1()
{
    CInjectionDLG dlg;

    dlg.DoModal();
}
