// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_User(_T("admin"))
{
	m_pUserData = ReadUserData("user.dat");//��ȡ�û�����
}

CLoginDlg::~CLoginDlg()
{
	//��������.
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


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedOk()
{
	Node*p = NULL;
	//�����˺�Ĭ������
	char Password[128] = "123456789";

	UpdateData();
	if (m_User.GetLength() == 0 || m_Password.GetLength() == 0)
	{
		MessageBox(L"�˺Ż�����Ϊ��",L"tips",MB_OK|MB_ICONASTERISK);
		return;
	}
	//�����û�
	
	for (p = m_pUserData->Head.next; p != &m_pUserData->Head; p = p->next)
	{
		UserData*pUser = (UserData*)p;
		if (strcmp(pUser->szUserName, CW2A(m_User).m_szBuffer) == 0)
		{
			strcpy(Password, pUser->szPassword);
			break;
		}
	}
	//û���ҵ��û�
	if (p == &m_pUserData->Head && m_User != L"admin")
	{
		MessageBox(L"�û������������!", L"tips", MB_OK | MB_ICONASTERISK);
		return;
	}
	//�ҵ���Ӧ���û������ǹ���Ա�˺�.
	if (strcmp(Password, CW2A(m_Password)))
	{
		MessageBox(L"�û������������!", L"tips", MB_OK | MB_ICONASTERISK);
		return;
	}
	//��¼�ɹ�


	CDialogEx::OnOK();
}
