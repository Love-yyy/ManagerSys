#ifndef _USER_H
#define _USER_H
#include "list.h"

typedef struct _UserData
{
	Node node;
	char szUserName[128];
	char szPassword[128];
}UserData;

//读取数据
ListContext* ReadUserData(const char*szFileName);
//写数据
bool WriteUserData(const char*szFileName, ListContext*pList);
//比较函数
int Compare(Node*it, Node*Target);
#endif