#ifndef _USER_H
#define _USER_H
#include "list.h"

typedef struct _UserData
{
	Node node;
	char szUserName[128];
	char szPassword[128];
}UserData;

//��ȡ����
ListContext* ReadUserData(const char*szFileName);
//д����
bool WriteUserData(const char*szFileName, ListContext*pList);
//�ȽϺ���
int Compare(Node*it, Node*Target);
#endif