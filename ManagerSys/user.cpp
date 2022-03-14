#include "stdafx.h"
#include "list.h"
#include "LoginDlg.h"
#include "stdio.h"

//��ȡ�û��˺�������Ϣ
ListContext* ReadUserData(const char*szFileName)
{
	ListContext*pList = createlist();

	FILE*fp = fopen(szFileName, "rb");
	if (fp == NULL)
		return pList;

	while (1)
	{
		UserData Temp;
		int nRead = fread(Temp.szUserName, sizeof(UserData) - sizeof(Node), 1, fp);
		if (nRead <= 0)
			break;
		//��ӵ�����.
		UserData*pUserData = (UserData*)malloc(sizeof(UserData));
		memcpy(pUserData->szUserName, Temp.szUserName, sizeof(UserData) - sizeof(Node));

		insertback(pList, (Node*)pUserData);
	}
	fclose(fp);
	return pList;
}

//�����û��˺�������Ϣ
bool WriteUserData(const char*szFileName,ListContext*pList)
{
	FILE*fp = fopen(szFileName, "wb");
	if (fp == NULL)
		return false;
	//��������д�ļ�
	for (Node*pIt = pList->Head.next; pIt != &pList->Head; pIt = pIt->next)
	{
		UserData*pUserData = (UserData*)pIt;
		fwrite(pUserData->szUserName, sizeof(UserData) - sizeof(Node), 1, fp);
	}
	fclose(fp);
	return true;
}

//typedef int(*cmpfunc)(Node* it, Node* target);

int Compare(Node*it, Node*Target)
{
	UserData*pIt = (UserData*)it;
	UserData*pTarget = (UserData*)Target;
	//
	return strcmp(pIt->szUserName, pTarget->szUserName);
}