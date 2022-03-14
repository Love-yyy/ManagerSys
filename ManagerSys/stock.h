#ifndef _STOCK_H
#define _STOCK_H

#include "list.h"

typedef struct _Goods
{
	Node node;

	unsigned int nID;		//商品编号
	char szName[64];		//名称
	char szType[64];		//品种
	unsigned int nUnit;		//销售单位.
	double Purchaseprice;	//进价
	double Sellingprice;	//售价
	double Stock;			//库存
	double Sell;			//已销售

}Goods;

//
ListContext* ReadStockData(const char*szFileName);
void WriteStockData(const char*szFileName, ListContext*pStockList);

//排序函数compare函数
int CompareById(Node*it, Node*target);
int CompareByName(Node*it, Node*target);
int CompareByType(Node*it, Node*target);
int CompareByPurchaseprice(Node*it, Node*target);
int CompareBySellprice(Node*it, Node*target);

int CompareByStock(Node*it, Node*target);
int CompareBySell(Node*it, Node*target);
#endif