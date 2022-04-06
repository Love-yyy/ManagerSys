#ifndef _SALE_RECORD_H
#define _SALE_RECORD_H
#include "list.h"

typedef struct
{
	Node node;

	char szDate[64];			//����
	ListContext	*m_pRecordList;	//�����¼.
}SaleRecords;

typedef struct
{
	Node node;

	unsigned int ID;			//���
	char szName[128];			//����
	char szType[128];			//Ʒ��
	unsigned int Unit;			//��λ
	
	double	Purchaseingprice;	//����
	double  Sellingprice;		//�ۼ�

	double	m_Rate;				//�ۿ�,ֻ�����ۼ�¼������Ч.
	
	double	Sell;				//��������.,��������.
	char	szTime[32];			//ʱ��.

	char	szComment[128];		//��ע.
	//
}Record;


void WriteRecord(const char*szFileName, ListContext*pRecordList);

ListContext* ReadRecord(const char*szFileName);

SaleRecords*FindRecords(ListContext*pSaleRecords, const char*szDate);

//��ȡĳһ��ļ�¼.
SaleRecords* GetRecord(const char*szDate, ListContext*pSaleRecords, const char*path);
//���ĳһ������ۼ�¼.
void AddRecord(const char*szDate, ListContext*pSaleRecords, Record*pRecord, const char*Path);

int CompareByID2(Node*it, Node*target);
int CompareByName2(Node*it, Node*target);
int CompareByType2(Node*it, Node*target);
int CompareBySellCount(Node*it, Node*target);
int CompareByPurchasingprice(Node*it, Node*target);
int CompareBySellingprice(Node*it, Node*target);
int CompareByProfit(Node*it, Node*target);

int CompareByTime(Node*it, Node*target);
#endif