// SaleRecordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "SaleRecordDlg.h"
#include "afxdialogex.h"
#include "SortDlg.h"

// CSaleRecordDlg 对话框

IMPLEMENT_DYNAMIC(CSaleRecordDlg, CDialogEx)

CSaleRecordDlg::CSaleRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSaleRecordDlg::IDD, pParent)
	, m_Filter(_T(""))
{
	m_pSaleRecords = createlist();
	m_pCurRecord = NULL;
}

CSaleRecordDlg::~CSaleRecordDlg()
{
	//
	for (Node*it = m_pSaleRecords->Head.next; it != &m_pSaleRecords->Head; it = it->next)
	{
		//保存每一天的记录
		SaleRecords*pSaleRecord = (SaleRecords*)it;
		char szFileName[256];
		sprintf(szFileName, "SaleRecords\\%s", pSaleRecord->szDate);
		WriteRecord(szFileName, pSaleRecord->m_pRecordList);
		//删除每一天的记录
		dellist(pSaleRecord->m_pRecordList);
	}
	//删除链表
	dellist(m_pSaleRecords);
}

void CSaleRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, m_SaleDlg);
	DDX_Control(pDX, IDC_LIST1, m_SaleRecordList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_FilterList);
	DDX_Text(pDX, IDC_EDIT1, m_Filter);
}


BEGIN_MESSAGE_MAP(CSaleRecordDlg, CDialogEx)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CSaleRecordDlg::OnDtnDatetimechangeDatetimepicker1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSaleRecordDlg::OnCbnSelchangeCombo1)
	ON_EN_CHANGE(IDC_EDIT1, &CSaleRecordDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSaleRecordDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSaleRecordDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSaleRecordDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSaleRecordDlg 消息处理程序


BOOL CSaleRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ModifyStyle(0, WS_CHILD);
	//
	CreateDirectory(L"SaleRecords", NULL);
	//
	

	//
	m_FilterList.AddString(L"编号");
	m_FilterList.AddString(L"名称");
	m_FilterList.AddString(L"品种");
	m_FilterList.AddString(L"时间");
	m_FilterList.SetCurSel(0);

	
	//
	m_SaleRecordList.InsertColumn(0, L"编号",LVCFMT_LEFT,120);
	m_SaleRecordList.InsertColumn(1, L"名称", LVCFMT_LEFT, 120);
	m_SaleRecordList.InsertColumn(2, L"品种", LVCFMT_LEFT, 120);
	m_SaleRecordList.InsertColumn(3, L"单位", LVCFMT_LEFT, 75);
	m_SaleRecordList.InsertColumn(4, L"数量", LVCFMT_LEFT, 75);
	m_SaleRecordList.InsertColumn(5, L"进价", LVCFMT_LEFT, 80);
	m_SaleRecordList.InsertColumn(6, L"售价", LVCFMT_LEFT, 80);
	m_SaleRecordList.InsertColumn(7, L"利润", LVCFMT_LEFT, 100);
	m_SaleRecordList.InsertColumn(8, L"时间", LVCFMT_LEFT, 100);
	m_SaleRecordList.InsertColumn(9, L"备注", LVCFMT_LEFT, 100);
	m_SaleRecordList.SetExtendedStyle(m_SaleRecordList.GetExStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//加载列表.
	CTime time;
	m_DateCtrl.GetTime(time);
	//在已经加载的链表中查找当天的记录
	//当刚开启对话框的时候,就把当天的记录读取出来.
	m_pCurRecord = GetRecord(CW2A(time.Format(L"%Y-%m-%d")), m_pSaleRecords,"SaleRecords");
	UpdateSaleRecordListView();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//日期改变
void CSaleRecordDlg::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	//
	CTime time;
	m_DateCtrl.GetTime(time);
	//日期改变时刷新链表.
	m_pCurRecord = GetRecord(CW2A(time.Format(L"%Y-%m-%d")).m_szBuffer, m_pSaleRecords,"SaleRecords");
	UpdateSaleRecordListView();
}


void CSaleRecordDlg::OnOK()
{
	
}

void CSaleRecordDlg::InsertRecord(Record&record)
{
	CString Text;
	Text.Format(L"%d", record.ID);

	m_SaleRecordList.InsertItem(0, Text);
	m_SaleRecordList.SetItemText(0, 1, CA2W(record.szName));
	m_SaleRecordList.SetItemText(0, 2, CA2W(record.szType));
	m_SaleRecordList.SetItemText(0, 3, record.Unit?L"斤":L"个");

	Text.Format(L"%.2lf", record.Sell);
	m_SaleRecordList.SetItemText(0, 4, Text);
	//进价
	Text.Format(L"%.2lf 元", record.Purchaseingprice);
	m_SaleRecordList.SetItemText(0, 5, Text);
	//售价
	Text.Format(L"%.2lf 元", record.Sellingprice);
	m_SaleRecordList.SetItemText(0, 6, Text);
	//利润
	double m = record.Sell * (record.Sellingprice - record.Purchaseingprice);
	Text.Format(L"%.2lf 元", m);
	m_SaleRecordList.SetItemText(0, 7, Text);
	//
	m_SaleRecordList.SetItemText(0, 8, CA2W(record.szTime));

	m_SaleRecordList.SetItemText(0, 9, CA2W(record.szComment));
}
void CSaleRecordDlg::UpdateSaleRecordListView()
{
	UpdateData();
	m_SaleRecordList.DeleteAllItems();
	m_SaleRecordList.SetRedraw(0);
	ListContext*pList = m_pCurRecord->m_pRecordList;

	for (Node*pIt = pList->Head.next; pIt != &pList->Head; pIt = pIt->next)
	{
		//插入到ListCtrl里面
		Record*pRecord = (Record*)pIt;

		if (!Filter(*pRecord))
			InsertRecord(*pRecord);
	}
	m_SaleRecordList.SetRedraw(1);
}

bool CSaleRecordDlg::Filter(Record&record)
{
	CString Text;
	switch (m_FilterList.GetCurSel())
	{
	case 0:
		Text.Format(L"%d", record.ID);
		return 0 == wcsstr(Text, m_Filter);
	case 1:
		return 0 == strstr(record.szName, CW2A(m_Filter));
	case 2:
		return 0 == strstr(record.szType, CW2A(m_Filter));
	case 3:
		return 0 == strstr(record.szTime, CW2A(m_Filter));
	}
	return false;
}

void CSaleRecordDlg::OnCbnSelchangeCombo1()
{
	UpdateSaleRecordListView();
}


void CSaleRecordDlg::OnEnChangeEdit1()
{
	UpdateSaleRecordListView();
}


void CSaleRecordDlg::OnBnClickedButton2()
{
	if (IDYES != MessageBox(L"确定要删除选中记录吗?(删除后不可恢复)", L"Warning", MB_YESNO | MB_ICONWARNING))
		return;
	ListContext*pList = m_pCurRecord->m_pRecordList;
	//删除当天的记录
	while (pList->Head.next != &pList->Head)
	{
		//删除所有节点
		delnode(pList, pList->Head.next);
	}
	//
	UpdateSaleRecordListView();
}


void CSaleRecordDlg::OnBnClickedButton1()
{
	POSITION pos = m_SaleRecordList.GetFirstSelectedItemPosition();
	if (pos == NULL || IDYES != MessageBox(L"确定删除该天记录吗?(删除后不可恢复)", L"Warning", MB_YESNO | MB_ICONWARNING))
		return;

	while (pos)
	{
		int idx = m_SaleRecordList.GetNextSelectedItem(pos);
		//emmmmm将就一下,链表太慢了.
		ListContext*pList = m_pCurRecord->m_pRecordList;
		for (Node*p = pList->Head.next; p != &pList->Head; p = p->next)
		{
			Record*pRecord = (Record*)p;
			if (!strcmp(pRecord->szTime, CW2A(m_SaleRecordList.GetItemText(idx, 8))))
			{
				delnode(pList, p);
				break;
			}
		}
	}
	//刷新显示.
	UpdateSaleRecordListView();
}


void CSaleRecordDlg::OnBnClickedButton3()
{
	CSortDlg dlg(1);
	if (dlg.DoModal() == IDOK)
	{
		unsigned int key = dlg.m_SortType >> 16;
		unsigned int ascending = dlg.m_SortType & 0xffff;
		switch (key)
		{
		case 0:
			sort(m_pCurRecord->m_pRecordList, CompareByID2,ascending);
			break;
		case 1:
			sort(m_pCurRecord->m_pRecordList, CompareByName2, ascending);
			break;
		case 2:
			sort(m_pCurRecord->m_pRecordList, CompareByType2, ascending);
			break;
		case 3:
			sort(m_pCurRecord->m_pRecordList, CompareBySellCount, ascending);
			break;
		case 4:
			sort(m_pCurRecord->m_pRecordList, CompareByPurchasingprice, ascending);
			break;
		case 5:
			sort(m_pCurRecord->m_pRecordList, CompareBySellingprice, ascending);
			break;
		case 6:
			sort(m_pCurRecord->m_pRecordList, CompareByProfit, ascending);
			break;
		case 7:
			sort(m_pCurRecord->m_pRecordList, CompareByTime, ascending);
			break;
		default:
			return;
		}
		UpdateSaleRecordListView();
	}
}
