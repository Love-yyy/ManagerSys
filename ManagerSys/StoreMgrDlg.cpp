// StoreMgrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "StoreMgrDlg.h"
#include "afxdialogex.h"
#include "SortDlg.h"
#include "MainFrame.h"
#include "AddGoodsDlg.h"
#include "ChangeGoodsDlg.h"

#include "PurcsDlg.h"
#include "SellDlg.h"
// CStoreMgrDlg 对话框

IMPLEMENT_DYNAMIC(CStoreMgrDlg, CDialogEx)

CStoreMgrDlg::CStoreMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreMgrDlg::IDD, pParent)
	, m_Filter(_T(""))
{
	//读取库存信息.
	m_pStockList = ReadStockData("stock.dat");
}

CStoreMgrDlg::~CStoreMgrDlg()
{
	WriteStockData("stock.dat", m_pStockList);
	dellist(m_pStockList);
}

void CStoreMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_COMBO1, m_DropList);
	DDX_Text(pDX, IDC_EDIT1, m_Filter);
}


BEGIN_MESSAGE_MAP(CStoreMgrDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStoreMgrDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CStoreMgrDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CStoreMgrDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CStoreMgrDlg::OnBnClickedButton3)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CStoreMgrDlg::OnNMRClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CStoreMgrDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStoreMgrDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CStoreMgrDlg::OnEnChangeEdit1)
	ON_COMMAND(ID_OPERATION_32776, &CStoreMgrDlg::OnOperation32776)
	ON_COMMAND(ID_OPERATION_32777, &CStoreMgrDlg::OnOperation32777)
	ON_BN_CLICKED(IDC_BUTTON4, &CStoreMgrDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CStoreMgrDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CStoreMgrDlg 消息处理程序


void CStoreMgrDlg::OnBnClickedOk()
{
}


void CStoreMgrDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CStoreMgrDlg::OnCbnSelchangeCombo1()
{
	UpdateStockListView();
}


BOOL CStoreMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//复选框,网格线,一次选中整行.
	ModifyStyle(0, WS_CHILD);

	m_List.SetExtendedStyle((~LVS_EX_CHECKBOXES)&(m_List.GetExStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES));
	
	m_List.InsertColumn(0, L"编号", LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, L"名称", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, L"品种", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, L"单位", LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, L"进价", LVCFMT_LEFT, 100);
	m_List.InsertColumn(5, L"售价", LVCFMT_LEFT, 100);
	m_List.InsertColumn(6, L"库存量", LVCFMT_LEFT, 100);
	m_List.InsertColumn(7, L"销售量", LVCFMT_LEFT, 100);

	//过滤选项。
	m_DropList.InsertString(0, L"编号");
	m_DropList.InsertString(1, L"名称");
	m_DropList.InsertString(2, L"品种");
	m_DropList.InsertString(3, L"进价");
	m_DropList.InsertString(4, L"售价");
	//
	m_DropList.SetCurSel(0);
	//显示商品信息

	UpdateStockListView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CStoreMgrDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	CSortDlg dlg(0);
	if (IDOK == dlg.DoModal())
	{
		unsigned int key = dlg.m_SortType >> 16;
		unsigned int ascending = dlg.m_SortType & 0xffff;
		switch (key)
		{
		case 0:
			sort(m_pStockList, CompareById, ascending);
			break;
		case 1:
			sort(m_pStockList, CompareByName, ascending);
			break;
		case 2:
			sort(m_pStockList, CompareByType, ascending);
			break;
		case 3:
			sort(m_pStockList, CompareByPurchaseprice, ascending);
			break;
		case 4:
			sort(m_pStockList, CompareBySellprice, ascending);
			break;
		case 5:
			sort(m_pStockList, CompareByStock, ascending);
			break;
		case 6:
			sort(m_pStockList, CompareBySell, ascending);
			break;
		default:
			return;
		}
		UpdateStockListView();
	}
}


void CStoreMgrDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;

	CMenu menu;
	POINT pt;
	GetCursorPos(&pt);
	menu.LoadMenuW(IDR_MENU1);
	menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
		pt.x, pt.y,this);
}


void CStoreMgrDlg::OnBnClickedButton1()
{
	Goods goods = { 0 };
	goods.Stock = 0;
	goods.Sell = 0;
	CAddGoodsDlg dlg(goods);
	if (IDOK == dlg.DoModal())
	{
		//查找是否与现有商品冲突
		Node*pExist = search(m_pStockList, m_pStockList->Head.next, CompareById, (void*)&goods);
		//
		if (pExist)
		{
			MessageBox(L"商品编号冲突", L"Error", MB_OK | MB_ICONASTERISK);
			return;
		}
		//添加记录.
		Goods*pNewGoods = (Goods*)malloc(sizeof(Goods));
		memcpy(pNewGoods, &goods, sizeof(Goods));
		//
		insertback(m_pStockList, (Node*)pNewGoods);
		InsertGoods(goods);
	}
}


bool CStoreMgrDlg::Filter(Goods&goods)
{
	//过滤器.
	CString Text;
	if (m_Filter.GetLength() == 0)
		return false;
	switch (m_DropList.GetCurSel())
	{
	case 0:													//编号
		Text.Format(L"%d",goods.nID);	
		return 0 == wcsstr(Text, m_Filter);
	case 1:													//名称
		return 0 == strstr(goods.szName, CW2A(m_Filter));
	case 2:													//品种
		return 0 == strstr(goods.szType, CW2A(m_Filter));
	case 3:
		Text.Format(L"%.2lf", goods.Purchaseprice);
		return 0 == wcsstr(Text, m_Filter);
	case 4:
		Text.Format(L"%.2lf", goods.Sellingprice);
		return 0 == wcsstr(Text, m_Filter);

	default:
		return false;
	}
}

void CStoreMgrDlg::UpdateStockListView()
{
	UpdateData();
	m_List.DeleteAllItems();
	m_List.SetRedraw(0);
	for (Node*pIt = m_pStockList->Head.next; pIt != &m_pStockList->Head; pIt = pIt->next)
	{
		//插入到ListCtrl里面
		Goods* pGoods = (Goods*)pIt;
		if (!Filter(*pGoods))
			InsertGoods(*pGoods);
	}
	m_List.SetRedraw(1);
}

void CStoreMgrDlg::InsertGoods(Goods&goods)
{
	CString  Text;
	Text.Format(L"%d", goods.nID);
	m_List.InsertItem(0, Text);
	//名称
	m_List.SetItemText(0, 1, CA2W(goods.szName));
	//品种
	m_List.SetItemText(0, 2, CA2W(goods.szType));
	//单位
	m_List.SetItemText(0, 3, goods.nUnit == 0 ? L"个" : L"斤");
	//进价
	Text.Format(L"%.2lf 元", goods.Purchaseprice);
	m_List.SetItemText(0, 4, Text);
	//售价
	Text.Format(L"%.2lf 元", goods.Sellingprice);
	m_List.SetItemText(0, 5, Text);
	//库存
	Text.Format(L"%.2lf", goods.Stock);
	m_List.SetItemText(0, 6, Text);
	//销量
	Text.Format(L"%.2lf", goods.Sell);
	m_List.SetItemText(0, 7, Text);
}

void CStoreMgrDlg::OnBnClickedButton2()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL || IDYES != MessageBox(L"确定要删除选中记录吗?(删除后不可恢复)", L"Warning", MB_YESNO | MB_ICONWARNING))
	{
		return;
	}
	while (pos)
	{
		//遍历选中项
		int idx = m_List.GetNextSelectedItem(pos);
		CString ID = m_List.GetItemText(idx, 0);
		m_List.DeleteItem(idx);
		//删除选中记录
		Goods Target;
		Target.nID = atoi(CW2A(ID));
		//
		Node*p = search(m_pStockList, m_pStockList->Head.next,CompareById,&Target);
		if (p)
		{
			delnode(m_pStockList, p);
		}
	}
}


void CStoreMgrDlg::OnEnChangeEdit1()
{
	UpdateStockListView();
}

//售出
void CStoreMgrDlg::OnOperation32776()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		int ID = atoi(CW2A(m_List.GetItemText(idx, 0)));

		Goods Target;
		Target.nID = ID;
		Node*p = search(m_pStockList, m_pStockList->Head.next, CompareById, (Node*)&Target);

		if (p)
		{
			Goods*pGoods = (Goods*)p;
			CSellDlg dlg(*pGoods);
			if (dlg.DoModal() == IDOK)
			{
				//销售记录信息.
				Record record = { 0 };
				record.ID = pGoods->nID;
				strcpy(record.szName, pGoods->szName);
				strcpy(record.szType, pGoods->szType);
				record.Sell = atof(CW2A(dlg.m_SellCount));
				record.Unit = pGoods->nUnit;
				record.Purchaseingprice = pGoods->Purchaseprice;
				record.Sellingprice = pGoods->Sellingprice;
				strcpy(record.szTime, CW2A(CTime::GetTickCount().Format(L"%H:%M:%S")));
				strcpy(record.szComment, CW2A(dlg.m_Comment));
				record.m_Rate = atof(CW2A(dlg.m_Rate));

				//添加销售记录.
				ListContext*pSaleRecords = ((CMainFrame*)GetParent())->m_SaleDlg.m_pSaleRecords;

				AddRecord(CW2A(CTime::GetTickCount().Format(L"%Y-%m-%d")), pSaleRecords, &record, "SaleRecords");
				((CMainFrame*)GetParent())->m_SaleDlg.UpdateSaleRecordListView();
				//
				UpdateStockListView();
			}
		}
	}
}

//进货
void CStoreMgrDlg::OnOperation32777()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		int ID = atoi(CW2A(m_List.GetItemText(idx, 0)));

		Goods Target;
		Target.nID = ID;
		Node*p = search(m_pStockList, m_pStockList->Head.next, CompareById, (Node*)&Target);

		if (p)
		{
			Goods*pGoods = (Goods*)p;
			//进货.
			CPurcsDlg dlg(*pGoods);
			if (IDOK == dlg.DoModal())
			{
				////进货记录信息.
				Record record = { 0 };
				record.ID = pGoods->nID;
				strcpy(record.szName, pGoods->szName);
				strcpy(record.szType, pGoods->szType);
				record.Sell = atof(CW2A(dlg.m_SellCount));		//进货时这个是进货量
				record.Unit = pGoods->nUnit;
				record.Purchaseingprice = pGoods->Purchaseprice;
				record.Sellingprice = pGoods->Sellingprice;
				strcpy(record.szTime, CW2A(CTime::GetTickCount().Format(L"%H:%M:%S")));
				strcpy(record.szComment, CW2A(dlg.m_Comment));
				////添加销售记录.
				ListContext*pPurchaseRecord = ((CMainFrame*)GetParent())->m_PurchaseDlg.m_pPurchaseRecords;

				AddRecord(CW2A(CTime::GetTickCount().Format(L"%Y-%m-%d")), pPurchaseRecord, &record, "PurchaseRecords");
				((CMainFrame*)GetParent())->m_PurchaseDlg.UpdatePurchaseRecordListView();
				//
				UpdateStockListView();
			}
		}
	}
	
}


void CStoreMgrDlg::OnBnClickedButton4()
{
	CFileDialog FileDlg(TRUE, L"*.txt", L"", NULL, L"文本文档(*.txt)|*.txt", this);

	if (IDOK == FileDlg.DoModal())
	{
		int nTotal = 0, nSuccess = 0;
		CString FileName = FileDlg.GetPathName();
		ImportFromFile(m_pStockList, CW2A(FileName), &nTotal, &nSuccess);
		//
		CString Text;
		Text.Format(L"读取完毕\r\n共找到:%d 条记录\r\n添加成功:%d 条记录\r\n", nTotal, nSuccess);
		MessageBox(Text);
		UpdateStockListView();
	}

}


void CStoreMgrDlg::OnBnClickedButton5()
{
	//
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	//
	int idx = m_List.GetNextSelectedItem(pos);
	Goods goods = { 0 };

	goods.nID = atoll(CW2A(m_List.GetItemText(idx, 0)));		//ID
	strcpy(goods.szName, CW2A(m_List.GetItemText(idx, 1)));		//Name
	strcpy(goods.szType, CW2A(m_List.GetItemText(idx, 2)));		//type
	goods.nUnit = m_List.GetItemText(idx, 3) == L"个" ? 0 : 1;	//unit
	goods.Purchaseprice = atof(CW2A(m_List.GetItemText(idx, 4)));//进价
	goods.Sellingprice = atof(CW2A(m_List.GetItemText(idx, 5)));

	CChangeGoodsDlg dlg(goods);
	if (IDOK == dlg.DoModal())
	{
		//修改控件上的显示
		CString  Text;
		m_List.SetItemText(idx, 1, CA2W(goods.szName));
		//品种
		m_List.SetItemText(idx, 2, CA2W(goods.szType));
		//单位
		m_List.SetItemText(idx, 3, goods.nUnit == 0 ? L"个" : L"斤");
		//进价
		Text.Format(L"%.2lf 元", goods.Purchaseprice);
		m_List.SetItemText(idx, 4, Text);
		//售价
		Text.Format(L"%.2lf 元", goods.Sellingprice);
		m_List.SetItemText(idx, 5, Text);
		//库存
		Text.Format(L"%.2lf", goods.Stock);
		m_List.SetItemText(idx, 6, Text);
		//销量
		Text.Format(L"%.2lf", goods.Sell);
		m_List.SetItemText(idx, 7, Text);
		//
		//修改链表里面的数据
		Node*pExist = search(m_pStockList, m_pStockList->Head.next, CompareById, (void*)&goods);
		if (pExist)
		{
			Goods*pGoods = (Goods*)pExist;
			strcpy(pGoods->szName, goods.szName);
			strcpy(pGoods->szType, goods.szType);
			//
			pGoods->nUnit = goods.nUnit;
			pGoods->Sellingprice = goods.Sellingprice;
			pGoods->Purchaseprice = goods.Purchaseprice;
		}
	}
}

