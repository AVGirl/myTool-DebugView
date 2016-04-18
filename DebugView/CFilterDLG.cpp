// CFilterDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DebugView.h"
#include "CFilterDLG.h"
#include "afxdialogex.h"


// CFilterDLG �Ի���

IMPLEMENT_DYNAMIC(CFilterDLG, CDialogEx)

CFilterDLG::CFilterDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFilterDLG::IDD, pParent)
{

}

CFilterDLG::~CFilterDLG()
{
}

void CFilterDLG::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_list);
    DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CFilterDLG, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON1, &CFilterDLG::OnBnClickedButton1)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CFilterDLG::OnNMDblclkList1)
    ON_EN_KILLFOCUS(IDC_EDIT1, &CFilterDLG::OnEnKillfocusEdit1)
    ON_BN_CLICKED(IDOK, &CFilterDLG::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON2, &CFilterDLG::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CFilterDLG::OnBnClickedButton3)
END_MESSAGE_MAP()


// CFilterDLG ��Ϣ�������


void CFilterDLG::setFilter(filterTab* tab)
{
    m_Tab = tab;
}

BOOL CFilterDLG::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    initList();

    initFilter();

    m_edit.ShowWindow(SW_HIDE);

    return TRUE;   
}

void CFilterDLG::initList()
{
    m_list.SetExtendedStyle(
        m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
     
    for (int i = 0; i < 0xFF; i++)
    {
        CString tmp;

        tmp.Format(L"%02X", i);

        m_list.InsertColumn(i, tmp, LVCFMT_LEFT, 25);
    }

    m_list.InsertItem(0, L"");
}

void CFilterDLG::initFilter()
{
    int count = getFilterCount();

    setTabRow(count);

    setFilterField();
}

int CFilterDLG::getFilterCount()
{
    int count = 0;

    filterTab::iterator it = m_Tab->begin();
    for (it; it != m_Tab->end(); it++)
    {
        if (count < it->first)
        {
            count = it->first;
        }
    }

    return count;
}

void CFilterDLG::setTabRow(int count)
{
    for (int i = 0; i < count; i++)
    {
        m_list.InsertItem(0, L"");
    }
}

void CFilterDLG::setFilterField()
{
    filterTab::iterator it = m_Tab->begin();
    for (it; it != m_Tab->end(); it++)
    {
        fillingField(it->first, it->second);
    }
}

void CFilterDLG::fillingField(int row, filterCol* data)
{ 
    WCHAR buff[] = L"0123456789ABCDEF ";

    CString tmp;
    filterCol::iterator it = data->begin();
    for (it; it != data->end(); it++)
    {
        if ((*it)->m_data > 0x10)
        {
            tmp.Format(L"%C%C", buff[(*it)->m_data / 0x10], buff[(*it)->m_data % 0x10]);
        }
        else
        {
            tmp.Format(L"%02C", buff[(*it)->m_data]);
        }
         
        m_list.SetItemText(row, (*it)->m_col, tmp);
    }
}

void CFilterDLG::OnBnClickedButton1()
{
    m_list.InsertItem(
        m_list.GetItemCount(), L"");
}


void CFilterDLG::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    
    CRect rc;
    m_Row = pNMItemActivate->iItem;//���ѡ�е���  
    m_Col = pNMItemActivate->iSubItem;//���ѡ����  


    if (pNMItemActivate->iSubItem != 0) //���ѡ���������;  
    {
        m_list.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//��������RECT��  
        m_edit.SetParent(&m_list);//ת������Ϊ�б���е�����  
        m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
        m_edit.SetWindowText(m_list.GetItemText(m_Row, m_Col));//���������е�ֵ����Edit�ؼ��У�  
        m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
        m_edit.SetFocus();//����Edit����  
        m_edit.ShowCaret();//��ʾ���  
        m_edit.SetSel(-1);//������ƶ������   
    }

    *pResult = 0;
}


void CFilterDLG::OnEnKillfocusEdit1()
{
    CString tem;
    m_edit.GetWindowText(tem);    //�õ��û�������µ�����  
    m_list.SetItemText(m_Row, m_Col, tem);   //���ñ༭���������  
    m_edit.ShowWindow(SW_HIDE);                //Ӧ�ر༭��  
}


void CFilterDLG::OnBnClickedOk()
{
    filterCol* tmp = nullptr;
    int n = m_list.GetItemCount();
    for (int i = 0; i < n; i++)
    {
        filterTab::iterator it = m_Tab->find(i);
        if (it == m_Tab->end())
        {
            filterCol* pCol = new filterCol;
            if (pCol == nullptr)
            {
                MessageBox(L"ϵͳ�ڴ治�㣬�޷���ӹ�������!");
                CDialogEx::OnOK();
            }

            m_Tab->insert(std::pair<int, filterCol*>(i, pCol));
            tmp = pCol;
        }
        else
        {
            tmp = (*it).second;
        }

        upFilter(i, tmp);
    }

    CDialogEx::OnOK();
}

void CFilterDLG::upFilter(int row, filterCol* data)
{
    CString ch; 

    for (int i = 0; i < 0xFF; i++)
    {
        ch = m_list.GetItemText(row, i);
        if (!ch.IsEmpty())
        {
            BYTE ch2 = wcstol((LPTSTR)(LPCTSTR)ch, nullptr, 16);

            if (isFilterData(data, i, ch2) == false)
            {
                if (newFilterData(data, i, ch2) == false)
                {
                    return;
                }
            }
        } 
    }
}

bool CFilterDLG::isFilterData(filterCol* data, int col, BYTE ch)
{
    filterCol::iterator it = data->begin();
    for (it; it != data->end(); it++)
    {
        if ((*it)->m_col == col)
        {
            (*it)->m_data = ch;
            return true;
        }
    }

    return false;
}

bool CFilterDLG::newFilterData(filterCol* data, int col, BYTE ch)
{
    filterData *p = new filterData;
    if (p == nullptr) return false;

    p->m_col = col;
    p->m_data = ch;

    data->push_back(p);

    return true;
}

void CFilterDLG::OnBnClickedButton2()
{
    int row = clearListRow();
    if (row == -1) return;

    clearTabRow(row);
}

int CFilterDLG::clearListRow()
{
    int row = m_list.GetSelectionMark();
    if (row == -1) return -1;

    for (int i = 0; i < 0xFF; i++)
    {
        m_list.SetItemText(row, i, L"");
    }

    m_list.SetSelectionMark(-1);

    return row;
}

void CFilterDLG::clearTabRow(int row)
{
    filterTab::iterator it = m_Tab->find(row);
    if (it == m_Tab->end()) return;

    filterCol::iterator cit = (*it).second->begin();
    for (cit; cit != (*it).second->end(); cit++)
    {
        delete (*cit); 
    }

    (*it).second->clear();
    m_Tab->erase(it);
}

void CFilterDLG::OnBnClickedButton3()
{
    int n = m_list.GetItemCount();
    for (int i = 0; i < n; i++)
    {
        m_list.SetSelectionMark(i);
        OnBnClickedButton2();
    }
}
