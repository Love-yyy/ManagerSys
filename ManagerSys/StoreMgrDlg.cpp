// StoreMgrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "StoreMgrDlg.h"
#include "afxdialogex.h"
#include "SortDlg.h"
#include "MainFrame.h"
#include "AddGoodsDlg.h"

#include "PurcsDlg.h"
#include "SellDlg.h"
// CStoreMgrDlg �Ի���

IMPLEMENT_DYNAMIC(CStoreMgrDlg, CDialogEx)

CStoreMgrDlg::CStoreMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStoreMgrDlg::IDD, pParent)
	, m_Filter(_T(""))
{
	//��ȡ�����Ϣ.
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
END_MESSAGE_MAP()


// CStoreMgrDlg ��Ϣ�������


void CStoreMgrDlg::OnBnClickedOk()
{
}


void CStoreMgrDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CStoreMgrDlg::OnCbnSelchangeCombo1()
{
	UpdateStockListView();
}


BOOL CStoreMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ѡ��,������,һ��ѡ������.
	ModifyStyle(0, WS_CHILD);

	m_List.SetExtendedStyle(m_List.GetExStyle() | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	m_List.InsertColumn(0, L"���", LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, L"����", LVCFMT_LEFT, 100);
	m_List.InsertColumn(2, L"Ʒ��", LVCFMT_LEFT, 100);
	m_List.InsertColumn(3, L"��λ", LVCFMT_LEFT, 100);
	m_List.InsertColumn(4, L"����", LVCFMT_LEFT, 100);
	m_List.InsertColumn(5, L"�ۼ�", LVCFMT_LEFT, 100);
	m_List.InsertColumn(6, L"�����", LVCFMT_LEFT, 100);
	m_List.InsertColumn(7, L"������", LVCFMT_LEFT, 100);

	//����ѡ�
	m_DropList.InsertString(0, L"���");
	m_DropList.InsertString(1, L"����");
	m_DropList.InsertString(2, L"Ʒ��");
	m_DropList.InsertString(3, L"����");
	m_DropList.InsertString(4, L"�ۼ�");
	//
	m_DropList.SetCurSel(0);
	//��ʾ��Ʒ��Ϣ

	UpdateStockListView();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CStoreMgrDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		//�����Ƿ���������Ʒ��ͻ
		Node*it = NULL;
		for (it = m_pStockList->Head.next; it != &m_pStockList->Head; it = it->next)
		{
			Goods*pGoods = (Goods*)it;
			if (pGoods->nID == goods.nID)
				break;
		}
		if (it != &m_pStockList->Head)
		{
			MessageBox(L"��Ʒ��ų�ͻ", L"Error", MB_OK | MB_ICONASTERISK);
			return;
		}
		//��Ӽ�¼.
		Goods*pNewGoods = (Goods*)malloc(sizeof(Goods));
		memcpy(pNewGoods, &goods, sizeof(Goods));
		//
		insertback(m_pStockList, (Node*)pNewGoods);

		InsertGoods(goods);
	}
}


bool CStoreMgrDlg::Filter(Goods&goods)
{
	//������.
	CString Text;
	if (m_Filter.GetLength() == 0)
		return false;
	switch (m_DropList.GetCurSel())
	{
	case 0:													//���
		Text.Format(L"%d",goods.nID);	
		return 0 == wcsstr(Text, m_Filter);
	case 1:													//����
		return 0 == strstr(goods.szName, CW2A(m_Filter));
	case 2:													//Ʒ��
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
		//���뵽ListCtrl����
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
	//����
	m_List.SetItemText(0, 1, CA2W(goods.szName));
	//Ʒ��
	m_List.SetItemText(0, 2, CA2W(goods.szType));
	//��λ
	m_List.SetItemText(0, 3, goods.nUnit == 0 ? L"��" : L"��");
	//����
	Text.Format(L"%.2lf Ԫ", goods.Purchaseprice);
	m_List.SetItemText(0, 4, Text);
	//�ۼ�
	Text.Format(L"%.2lf Ԫ", goods.Sellingprice);
	m_List.SetItemText(0, 5, Text);
	//���
	Text.Format(L"%.2lf", goods.Stock);
	m_List.SetItemText(0, 6, Text);
	//����
	Text.Format(L"%.2lf", goods.Sell);
	m_List.SetItemText(0, 7, Text);
}

void CStoreMgrDlg::OnBnClickedButton2()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL || IDYES != MessageBox(L"ȷ��Ҫɾ��ѡ�м�¼��?(ɾ���󲻿ɻָ�)", L"Warning", MB_YESNO | MB_ICONWARNING))
	{
		return;
	}
	while (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		CString ID = m_List.GetItemText(idx, 0);
		m_List.DeleteItem(idx);

		for (Node*pIt = m_pStockList->Head.next; pIt != &m_pStockList->Head; pIt = pIt->next)
		{
			//���뵽ListCtrl����
			Goods* pGoods = (Goods*)pIt;
			CString GoodsId;
			GoodsId.Format(L"%d", pGoods->nID);
			//
			if (GoodsId == ID)
			{
				delnode(m_pStockList, pIt);
				break;
			}
		}
	}
}


void CStoreMgrDlg::OnEnChangeEdit1()
{
	UpdateStockListView();
}


void CStoreMgrDlg::OnOperation32776()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		int ID = atoi(CW2A(m_List.GetItemText(idx, 0)));

		//��������,�ҵ���Ӧ��Ʒ
		for (Node*p = m_pStockList->Head.next; p != &m_pStockList->Head; p = p->next)
		{
			Goods*pGoods = (Goods*)p;
			if (pGoods->nID == ID)
			{
				CSellDlg dlg(*pGoods);
				dlg.DoModal();
				//���ۼ�¼��Ϣ.
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
				//������ۼ�¼.
				ListContext*pSaleRecords = ((CMainFrame*)GetParent())->m_SaleDlg.m_pSaleRecords;

				AddRecord(CW2A(CTime::GetTickCount().Format(L"%Y-%m-%d")), pSaleRecords, &record,"SaleRecords");
				((CMainFrame*)GetParent())->m_SaleDlg.UpdateSaleRecordListView();
				//
				UpdateStockListView();
				break;
			}
		}
	}
}


void CStoreMgrDlg::OnOperation32777()
{
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_List.GetNextSelectedItem(pos);
		int ID = atoi(CW2A(m_List.GetItemText(idx, 0)));

		//��������,�ҵ���Ӧ��Ʒ
		for (Node*p = m_pStockList->Head.next; p != &m_pStockList->Head; p = p->next)
		{
			Goods*pGoods = (Goods*)p;
			if (pGoods->nID == ID)
			{
				//����.
				CPurcsDlg dlg(*pGoods);
				dlg.DoModal();
				////������¼��Ϣ.
				Record record = { 0 };
				record.ID = pGoods->nID;
				strcpy(record.szName, pGoods->szName);
				strcpy(record.szType, pGoods->szType);
				record.Sell = atof(CW2A(dlg.m_SellCount));		//����ʱ����ǽ�����
				record.Unit = pGoods->nUnit;
				record.Purchaseingprice = pGoods->Purchaseprice;
				record.Sellingprice = pGoods->Sellingprice;
				strcpy(record.szTime, CW2A(CTime::GetTickCount().Format(L"%H:%M:%S")));
				strcpy(record.szComment, CW2A(dlg.m_Comment));
				////������ۼ�¼.
				ListContext*pPurchaseRecord = ((CMainFrame*)GetParent())->m_PurchaseDlg.m_pPurchaseRecords;

				AddRecord(CW2A(CTime::GetTickCount().Format(L"%Y-%m-%d")), pPurchaseRecord, &record, "PurchaseRecords");
				((CMainFrame*)GetParent())->m_PurchaseDlg.UpdatePurchaseRecordListView();
				//
				UpdateStockListView();
				break;
			}
		}
	}
	
}
