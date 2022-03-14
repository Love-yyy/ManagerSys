#ifndef _SALE_RECORD_H
#define _SALE_RECORD_H
#include "list.h"

typedef struct _SaleRecords
{
	Node node;

	char szDate[64];			//日期
	ListContext	*m_pRecordList;	//当天记录.
}SaleRecords;

typedef struct _Record
{
	Node node;

	unsigned int ID;			//编号
	char szName[128];			//名称
	char szType[128];			//品种
	unsigned int Unit;			//单位
	
	double	Purchaseingprice;	//进价
	double  Sellingprice;		//售价
	double	Sell;				//出售数量.,购买数量.
	char	szTime[32];			//时间.

	char	szComment[128];		//备注.
	//
}Record;



void WriteRecord(const char*szFileName, ListContext*pRecordList);

ListContext* ReadRecord(const char*szFileName);

SaleRecords*FindRecords(ListContext*pSaleRecords, const char*szDate);

//获取某一天的记录.
SaleRecords* GetRecord(const char*szDate, ListContext*pSaleRecords, const char*path);
//添加某一天的销售记录.
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