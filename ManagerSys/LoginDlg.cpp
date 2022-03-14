// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_User(_T("admin"))
{
	m_pUserData = ReadUserData("user.dat");//读取用户密码
}

CLoginDlg::~CLoginDlg()
{
	//保存数据.
	WriteUserData("user.dat", m_pUserData);
	dellist(m_pUserData);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_User);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	Node*p = NULL;
	//所有账号默认密码
	char Password[128] = "123456789";

	UpdateData();
	if (m_User.GetLength() == 0 || m_Password.GetLength() == 0)
	{
		MessageBox(L"账号或密码为空",L"tips",MB_OK|MB_ICONASTERISK);
		return;
	}
	//查找用户
	
	for (p = m_pUserData->Head.next; p != &m_pUserData->Head; p = p->next)
	{
		UserData*pUser = (UserData*)p;
		if (strcmp(pUser->szUserName, CW2A(m_User).m_szBuffer) == 0)
		{
			strcpy(Password, pUser->szPassword);
			break;
		}
	}
	//没有找到用户
	if (p == &m_pUserData->Head && m_User != L"admin")
	{
		MessageBox(L"用户名或密码错误!", L"tips", MB_OK | MB_ICONASTERISK);
		return;
	}
	//找到对应的用户或者是管理员账号.
	if (strcmp(Password, CW2A(m_Password)))
	{
		MessageBox(L"用户名或密码错误!", L"tips", MB_OK | MB_ICONASTERISK);
		return;
	}
	//登录成功


	CDialogEx::OnOK();
}
