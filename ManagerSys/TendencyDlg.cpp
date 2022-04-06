// TendencyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "TendencyDlg.h"
#include "afxdialogex.h"


// CTendencyDlg �Ի���

IMPLEMENT_DYNAMIC(CTendencyDlg, CDialogEx)

CTendencyDlg::CTendencyDlg(ListContext*pStockList, ListContext*pSaleRecords, CWnd* pParent /*=NULL*/)
	: CDialogEx(CTendencyDlg::IDD, pParent)
{
	m_pStockList = pStockList;
	m_pSaleRecords = pSaleRecords;
}

CTendencyDlg::~CTendencyDlg()
{
}

void CTendencyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_GoodsList);
}


BEGIN_MESSAGE_MAP(CTendencyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTendencyDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CTendencyDlg ��Ϣ��������


BOOL CTendencyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	
	//
	m_GoodsList.InsertString(m_GoodsList.GetCount(),L"ȫ��");
	m_GoodsList.SetItemData(0, (DWORD_PTR)0);
	//����ID��CommonBox��
	for (Node*pNode = m_pStockList->Head.next; pNode != &m_pStockList->Head; pNode = pNode->next)
	{
		Goods*pGoods = (Goods*)pNode;
		CString sItem;
		sItem.Format(L"[%d]  %s", pGoods->nID, CA2W(pGoods->szName).m_szBuffer);
		int idx = m_GoodsList.GetCount();
		m_GoodsList.InsertString(idx, sItem);
		m_GoodsList.SetItemData(idx,(DWORD_PTR)pGoods);
	}
	m_GoodsList.SetCurSel(0);


	//����
	CRect rect;
	GetClientRect(rect);
	InvalidateRect(rect, 1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
#define X_ORG 35
#define Y_ORG 540

#define X_WIDTH 760
#define Y_HEIGHT 450

#define LIST_X_ORG 815
#define LIST_Y_ORG 100

#include <limits.h>

double Arr[] = { 25, 50, 100, 250, 500, 1000, 2000,999999999 };
static int getidx(double size)
{
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		if (size < Arr[i])
			break;
	}
	return i;
}

void CTendencyDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CFont font;
	font.CreateFontW(12, 6, 0, 0, FW_THIN, FALSE, FALSE, 0, DEFAULT_CHARSET, DEFAULT_CHARSET,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SCRIPT, L"����");
	dc.SelectObject(font);

	// TODO:  �ڴ˴�������Ϣ�����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//��������ϵ.
	//dc.SetBkColor();
	//dc.SelectObject(GetStockObject(WHITE_PEN));
	m_DrawCount = 0;

	dc.MoveTo(X_ORG,Y_ORG);
	dc.LineTo(X_ORG, Y_ORG - Y_HEIGHT);

	dc.MoveTo(X_ORG, Y_ORG);
	dc.LineTo(X_ORG + X_WIDTH, Y_ORG);
	//��ͷ
	dc.MoveTo(X_ORG, Y_ORG - Y_HEIGHT);
	dc.LineTo(X_ORG - 5, Y_ORG - Y_HEIGHT + 5);
	dc.MoveTo(X_ORG, Y_ORG - Y_HEIGHT);
	dc.LineTo(X_ORG + 5, Y_ORG - Y_HEIGHT + 5);

	dc.MoveTo(X_ORG + X_WIDTH, Y_ORG);
	dc.LineTo(X_ORG + X_WIDTH - 5, Y_ORG + 5);
	dc.MoveTo(X_ORG + X_WIDTH, Y_ORG);
	dc.LineTo(X_ORG + X_WIDTH - 5, Y_ORG - 5);
	//
	int nID = 11111;

	dc.SetBkMode(TRANSPARENT);
	//Ѱ�����ֵ����Сֵ,ȷ����λ����.
	CTime time = CTime::GetCurrentTime();
	//6��ǰ��ʼ����.
	time -= 6 * 24 * 3600;
	//����x �� ����:
	for (int j = 1; j <= 7; j++)
	{
		CString Text = time.Format(L"%m-%d");
		for (int i = -3; i < 4; i++)
		{
			dc.SetPixel(X_ORG + 100 + (j-1)*100, Y_ORG + i, 0x0);
			dc.TextOutW(X_ORG + 100 + (j-1) * 100 - 20, Y_ORG + 4, Text);
		}
		for (int i = 1; i <= 4; i++)
		{
			dc.SetPixel(X_ORG + i, Y_ORG - j*((Y_HEIGHT - 60) / 7), 0x0);
		}
		Text.Format(L"% 4.0lf", Arr[j-1]);
		dc.TextOutW(X_ORG - 35, Y_ORG - j*((Y_HEIGHT - 60) / 7) - 8, Text);
		time += 24 * 3600;
	}
	//
	//
	time -= 7 * 24 * 3600;
	//�Ҳ��б�
	dc.MoveTo(LIST_X_ORG - 10, LIST_Y_ORG - 18);
	dc.LineTo(LIST_X_ORG - 10 + 200, LIST_Y_ORG-18);

	dc.MoveTo(LIST_X_ORG - 10, LIST_Y_ORG - 18);
	dc.LineTo(LIST_X_ORG - 10, LIST_Y_ORG - 18 + 800);
	Goods*pGoods = (Goods*)m_GoodsList.GetItemData(m_GoodsList.GetCurSel());
	if (pGoods)
	{
		Draw(&dc, pGoods, time);
		return;
	}
	for (Node*pNode = m_pStockList->Head.next; pNode != &m_pStockList->Head; pNode = pNode->next)
	{
		Draw(&dc, (Goods*)pNode, time);
	}
	//dc.LineTo()
}

void CTendencyDlg::Draw(CPaintDC*pDc,Goods*pGoods,CTime StartTime)
{
	ListContext*pList = createlist();

	Record Target;
	Target.ID = pGoods->nID;

	for (int i = 0; i < 7; i++)
	{
		CString sDate = StartTime.Format(L"%Y-%m-%d");
		Record*pTodayRecord = (Record*)malloc(sizeof(Record));
		pTodayRecord->Sell = 0;
		memset(pTodayRecord, 0, sizeof(Record));
		//��ȡ�����¼.
		SaleRecords*pRecordList = GetRecord(CW2A(sDate).m_szBuffer, m_pSaleRecords, "SaleRecords");
		//
		Record*pRecord = (Record*)search(pRecordList->m_pRecordList, pRecordList->m_pRecordList->Head.next, CompareByID2, (Node*)&Target);

		while (pRecord)
		{
			pTodayRecord->Sell += pRecord->Sell;
			//Ѱ����һ��
			pRecord = (Record*)search(pRecordList->m_pRecordList,pRecord->node.next, CompareByID2, (Node*)&Target);
		}
		insertback(pList, (Node*)pTodayRecord);
		//��һ��
		StartTime += 24 * 3600;
	}
	//����
	CPen Pen;
	COLORREF color = ((rand() % 256) << 16) | ((rand() % 256) << 8) | ((rand() % 256));
	Pen.CreatePen(PS_SOLID, 2, color);
	
	pDc->SetTextColor(color);
	pDc->SelectObject(Pen);

	double YUnit = 0;
	double XUnit = 100;
	
	//if (average > 0)
	//{
	//	int yidx = getidx()
	//	YUnit = ((Y_HEIGHT-40) / 2.0) / average;
	//}
	//��������
	int x = XUnit;

	for (Node*pNode = pList->Head.next; pNode != &pList->Head; pNode = pNode->next)
	{
		Record*pRecord = (Record*)pNode;
		YUnit = ((Y_HEIGHT - 60) / 7) / 25;
		int idx = getidx(pRecord->Sell);
		double deltaY = (pRecord->Sell * YUnit);

		if (idx)
		{
			YUnit = ((Y_HEIGHT - 60) / 7) / (Arr[idx]-Arr[idx-1]);
			deltaY = (pRecord->Sell - Arr[idx-1]) * YUnit;
		}
		unsigned int CurX = X_ORG + x;
		unsigned int CurY = Y_ORG -(idx*((Y_HEIGHT - 60) / 7) + deltaY);
		//
		pDc->SetPixel(CurX, CurY, 0xababab);
		if (pNode != pList->Head.next)
		{
			pDc->LineTo(CurX, CurY);
		}
		//
		pDc->MoveTo(CurX, CurY);
		//��ʾ����
		CString Text;
		Text.Format(L"%.2lf", pRecord->Sell);
		pDc->TextOutW(CurX - 10, CurY - 20, Text);


		x += XUnit;
	}

	dellist(pList);
	//���Ҳ�������ʾ.
	pDc->MoveTo(LIST_X_ORG, LIST_Y_ORG + m_DrawCount * 25 + 6);
	pDc->LineTo(LIST_X_ORG + 32, LIST_Y_ORG + m_DrawCount * 25 + 6);

	pDc->SelectObject(GetStockObject(BLACK_PEN));
	pDc->SetTextColor(0x0);

	CString Text;
	Text.Format(L"%s     ��λ:%s", CA2W(pGoods->szName).m_szBuffer, pGoods->nUnit ? L"��" : L"��");
	pDc->TextOutW(LIST_X_ORG + 36, LIST_Y_ORG + m_DrawCount * 25, Text);
	//
	m_DrawCount++;
	return;
	//GetRecord()
}


void CTendencyDlg::OnCbnSelchangeCombo1()
{
	CRect rect;
	GetClientRect(rect);
	InvalidateRect(rect, 1);
}