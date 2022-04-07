#ifndef _SALE_RECORD_H
#define _SALE_RECORD_H
#include "list.h"

/*
	�ýṹ�����ڱ���ĳһ��������Լ���������ۼ�¼
*/
typedef struct
{
	Node node;

	char szDate[64];			//����
	ListContext	*m_pRecordList;	//�����¼.
}SaleRecords;


/*
	���ڼ�¼ĳһ��������Ʒ����Ϣ
*/
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

/*
	����˵�� : �ú�����ĳһ������ۼ�¼д�뵽ָ�����ļ���,pRecordList�б���ĳһ������ۼ�¼
	����ֵ   : �޷���ֵ
*/
void WriteRecord(const char*szFileName, ListContext*pRecordList);

/*
	����˵�� : �ú�����ָ�����ļ��ж�ȡĳһ������ۼ�¼,���������������Ϣ������������,��󷵻�
	����ֵ   : ����ĳһ��������Ϣ������
*/
ListContext* ReadRecord(const char*szFileName);

/*
	����˵��  : �ú������Ѿ����صĲ�ͬ���ڵ����ۼ�¼�У��ҵ�ָ�����ڵ����ۼ�¼��������һ��SaleRecordָ��
	����ֵ	 :SaleRecordsָ��,����SaleRecords�е�m_pRecordListΪ�����������Ϣ
*/
SaleRecords*FindRecords(ListContext*pSaleRecords, const char*szDate);

/*
	����˵��  : �ú����Ӹ�����pSaleRecords�У��ҵ�ָ�����ڵ����ۼ�¼��������һ��SaleRecordָ��
	����ֵ	 : SaleRecordsָ��,����SaleRecords�е�m_pRecordListΪ�����������Ϣ
*/
SaleRecords* GetRecord(const char*szDate, ListContext*pSaleRecords, const char*path);
//���ĳһ������ۼ�¼.

/*
	�ú�����ĳһ����¼���뵽ָ�����ڵ����ۼ�¼������.
		szDateָ��������,pRecordΪҪ��ӵļ�¼,
*/
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