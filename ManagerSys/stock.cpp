#include "stdafx.h"
#include "stock.h"


ListContext* ReadStockData(const char*szFileName)
{
	ListContext*pStockList = createlist();
	FILE*fp = fopen(szFileName, "rb");
	if (fp == NULL)
		return pStockList;
	//
	while (true)
	{
		Goods temp = { 0 };
		int nRead = fread(&temp.nID, sizeof(Goods) - ((char*)&temp.nID - (char*)&temp), 1, fp);
		if (nRead <= 0)
			break;

		Goods*pNewGoods = (Goods*)malloc(sizeof(Goods));
		memcpy(pNewGoods, &temp, sizeof(Goods));
		//²åÈëµ½Á´±íÎ²¶Ë.
		insertback(pStockList, (Node*)pNewGoods);
	}
	//
	fclose(fp);
	return pStockList;
}

void WriteStockData(const char*szFileName, ListContext*pStockList)
{
	FILE*fp = fopen(szFileName, "wb");
	if (fp == NULL)
		return ;
	
	for (Node*pIt = pStockList->Head.next; pIt != &pStockList->Head; pIt = pIt->next)
	{
		Goods*pGoods = (Goods*)pIt;
		fwrite(&pGoods->nID, sizeof(Goods) - ((char*)&pGoods->nID - (char*)pGoods), 1, fp);
	}
	//
	fclose(fp);
	return ;
}

//typedef int(*cmpfunc)(Node* it, Node* target);

int CompareById(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;

	return pGoods->nID - pTarget->nID;
}

int CompareByName(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;

	return strcmp(pGoods->szName,pTarget->szName);
}

int CompareByType(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	return strcmp(pGoods->szType, pTarget->szType);
}

int CompareByPurchaseprice(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	return pGoods->Purchaseprice - pTarget->Purchaseprice;
}
int CompareBySellprice(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	return pGoods->Sellingprice - pTarget->Sellingprice;
}

int CompareByStock(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	return pGoods->Stock - pTarget->Stock;
}
int CompareBySell(Node*it, Node*target)
{
	Goods*pGoods = (Goods*)it;
	Goods*pTarget = (Goods*)target;
	return pGoods->Sell - pTarget->Sell;
}