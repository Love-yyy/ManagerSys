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
		//插入到链表尾端.
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

//从txt中导入记录,返回总记录条数和成功数量.
void ImportFromFile(ListContext*pStockList, const char*szFileName,int*pTotal,int*pSuccess)
{
	*pTotal = 0;
	*pSuccess = 0;
	FILE*fp = fopen(szFileName, "r");
	if (fp)
	{
		//
		while (true)
		{
			Goods goods = { 0 };
			//返回值: 整型，成功返回读入的参数的个数
			int nScanf = fscanf(fp, "%d%s%s%u%lf%lf%lf%lf", &goods.nID, goods.szName, goods.szType, &goods.nUnit,
				&goods.Purchaseprice, &goods.Sellingprice, &goods.Stock, &goods.Sell);
			//
			if (nScanf != 8)
				break;
			(*pTotal)++;
			//查找是否有重复的编号.
			Node*pNode = NULL;
			for (pNode = pStockList->Head.next; pNode != &pStockList->Head; pNode = pNode->next)
			{
				if (((Goods*)pNode)->nID == goods.nID)
					break;
			}
			//
			if (pNode == &pStockList->Head)
			{
				//没有找到重复编号.
				(*pSuccess)++;
				Goods* pGoods = (Goods*)malloc(sizeof(Goods));
				memcpy(pGoods, &goods, sizeof(Goods));
				//
				insertback(pStockList, (Node*)pGoods);
			}
		}
		fclose(fp);
	}
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