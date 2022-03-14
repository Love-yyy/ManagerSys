#ifndef _STOCK_H
#define _STOCK_H

#include "list.h"

typedef struct _Goods
{
	Node node;

	unsigned int nID;		//��Ʒ���
	char szName[64];		//����
	char szType[64];		//Ʒ��
	unsigned int nUnit;		//���۵�λ.
	double Purchaseprice;	//����
	double Sellingprice;	//�ۼ�
	double Stock;			//���
	double Sell;			//������

}Goods;

//
ListContext* ReadStockData(const char*szFileName);
void WriteStockData(const char*szFileName, ListContext*pStockList);

//������compare����
int CompareById(Node*it, Node*target);
int CompareByName(Node*it, Node*target);
int CompareByType(Node*it, Node*target);
int CompareByPurchaseprice(Node*it, Node*target);
int CompareBySellprice(Node*it, Node*target);

int CompareByStock(Node*it, Node*target);
int CompareBySell(Node*it, Node*target);
#endif