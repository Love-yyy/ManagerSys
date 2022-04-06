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
		//���뵽������
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
		//д�������ۼ�¼.
		for (Node*it = pRecordList->Head.next; it != &pRecordList->Head; it = it->next)
		{
			Record*pRecord = (Record*)it;
			fwrite(&pRecord->ID, sizeof(Record) - ((char*)&pRecord->ID - (char*)pRecord), 1, fp);
		}
		fclose(fp);
	}
}

//���Ѿ����ص������в��Ҷ�Ӧ���ڵ����ۼ�¼.

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

//��ȡĳһ���Ӧ�����ۼ�¼.
SaleRecords* GetRecord(const char*szDate,ListContext*pSaleRecords,const char*path)
{
	//�ȿ����Ƿ��Ѿ�������һ������ۼ�¼
	SaleRecords*pSaleRecord = FindRecords(pSaleRecords, szDate);
	if (pSaleRecord == NULL)
	{
		//û���ҵ��Ļ��ͳ��Դ��ļ��м���.
		char szFileName[256] = { 0 };
		sprintf(szFileName, "%s\\%s", path,szDate);
		//û���ҵ�,���ļ��м���.
		ListContext*pRecord = ReadRecord(szFileName);

		pSaleRecord = (SaleRecords*)malloc(sizeof(SaleRecords));

		pSaleRecord->m_pRecordList = pRecord;
		strcpy(pSaleRecord->szDate, szDate);
		//���뵽������
		insertback(pSaleRecords, (Node*)pSaleRecord);
	}
	return pSaleRecord;
}

//��Ӽ�¼
void AddRecord(const char*szDate, ListContext*pSaleRecords,Record*pRecord,const char*Path)
{
	//�ҵ�ָ�����ڵ����ۼ�¼����
	SaleRecords*pSaleRecord = GetRecord(szDate, pSaleRecords,Path);
	
	Record*pNewRecord = (Record*)malloc(sizeof(Record));
	memcpy(pNewRecord, pRecord,sizeof(Record));

	//���뵽����ĩβ.
	insertback(pSaleRecord->m_pRecordList, (Node*)pNewRecord);
}

//�Ƚ� �ص�����
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