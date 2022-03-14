#include "stdafx.h"
#include "PurcsDlg.h"

CPurcsDlg::CPurcsDlg(Goods&goods) :
CSellDlg(goods)
{
}


CPurcsDlg::~CPurcsDlg()
{
}


BOOL CPurcsDlg::OnInitDialog()
{
	CSellDlg::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(L"进货");
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CPurcsDlg::OnEnChangeEdit4()
{
	UpdateData();
	CString Text;
	double Total = atof(CW2A(m_SellCount)) * m_goods.Purchaseprice;
	Text.Format(L"%.2lf 元", Total);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(Text);
}

void CPurcsDlg::OnOK()
{
	// TODO:  UpdateData();
	double SellCount = atof(CW2A(m_SellCount));
	m_goods.Stock += atof(CW2A(m_SellCount));
	CDialogEx::OnOK();
}
