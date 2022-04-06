#include "stdafx.h"
#include "SaleRecord.h"
/*
	
*/

ListContext* ReadRecord(const char*szFileName)
{
	ListContext*pRecords = createlist();
	FILE*fp = fopen(szFileName, "rb");
	if (!fp)
		return pRecords;

	while (true)
	{
		Record temp = { 0 };
		int nRead = fread(&temp.ID,sizeof(Record) - ((char*)&temp.ID - (char*)&temp) , 1, fp);
		if (nRead <= 0)
			break;
		//插入到链表中
		Record*pNewRecord = (Record*)malloc(sizeof(Record));
		memcpy(pNewRecord, &temp, sizeof(Record));

		insertback(pRecords, (Node*)pNewRecord);
	}
	fclose(fp);
	return pRecords;
}

void WriteRecord(const char*szFileName, ListContext*pRecordList)
{
	FILE*fp = fopen(szFileName, "wb");
	if (fp)
	{
		//写当天销售记录.
		for (Node*it = pRecordList->Head.next; it != &pRecordList->Head; it = it->next)
		{
			Record*pRecord = (Record*)it;
			fwrite(&pRecord->ID, sizeof(Record) - ((char*)&pRecord->ID - (char*)pRecord), 1, fp);
		}
		fclose(fp);
	}
}

//从已经加载的链表中查找对应日期的销售记录.

SaleRecords*FindRecords(ListContext*pSaleRecords,const char*szDate)
{
	for (Node*it = pSaleRecords->Head.next; it != &pSaleRecords->Head; it = it->next)
	{
		SaleRecords*pRecord = (SaleRecords*)it;
		if (!strcmp(pRecord->szDate, szDate))
		{
			return pRecord;
		}
	}
	return NULL;
}

//获取某一天对应的销售记录.
SaleRecords* GetRecord(const char*szDate,ListContext*pSaleRecords,const char*path)
{
	//先看看是否已经加载这一天的销售记录
	SaleRecords*pSaleRecord = FindRecords(pSaleRecords, szDate);
	if (pSaleRecord == NULL)
	{
		//没有找到的话就尝试从文件中加载.
		char szFileName[256] = { 0 };
		sprintf(szFileName, "%s\\%s", path,szDate);
		//没有找到,从文件中加载.
		ListContext*pRecord = ReadRecord(szFileName);

		pSaleRecord = (SaleRecords*)malloc(sizeof(SaleRecords));

		pSaleRecord->m_pRecordList = pRecord;
		strcpy(pSaleRecord->szDate, szDate);
		//插入到链表中
		insertback(pSaleRecords, (Node*)pSaleRecord);
	}
	return pSaleRecord;
}

//添加记录
void AddRecord(const char*szDate, ListContext*pSaleRecords,Record*pRecord,const char*Path)
{
	//找到指定日期的销售记录链表
	SaleRecords*pSaleRecord = GetRecord(szDate, pSaleRecords,Path);
	
	Record*pNewRecord = (Record*)malloc(sizeof(Record));
	memcpy(pNewRecord, pRecord,sizeof(Record));

	//加入到链表末尾.
	insertback(pSaleRecord->m_pRecordList, (Node*)pNewRecord);
}

//比较 回调函数
int CompareByID2(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return pIt->ID - pTarget->ID;
}

int CompareByName2(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return strcmp(pIt->szName,pTarget->szName);
}

int CompareByType2(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return strcmp(pIt->szType, pTarget->szType);
}
int CompareBySellCount(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return pIt->Sell-pTarget->Sell;
}

int CompareByPurchasingprice(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return pIt->Purchaseingprice - pTarget->Purchaseingprice;
}
int CompareBySellingprice(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return pIt->Sellingprice - pTarget->Sellingprice;
}

int CompareByProfit(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return  (pIt->Sellingprice - pIt->Purchaseingprice)*pIt->Sell - (pTarget->Sellingprice - pTarget->Purchaseingprice)*pTarget->Sell;
}

int CompareByTime(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return strcmp(pIt->szTime, pTarget->szTime);
}