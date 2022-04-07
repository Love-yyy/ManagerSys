#ifndef _STOCK_H
#define _STOCK_H

#include "list.h"

/*
	该结构体保存了与商品有关的信息
*/
typedef struct
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


/*
	函数说明 ： 该函数从给定的文件中读取出商品信息,并将商品信息保存在链表中,最后返回
	返回值	： 包含商品信息的链表
*/
ListContext* ReadStockData(const char*szFileName);

/*
	函数说明 ： 该函数将给定的商品信息链表中的所有信息写入到给定的文件中.
	返回值	： 无返回值
*/
void WriteStockData(const char*szFileName, ListContext*pStockList);


/*
	函数说明 ： 该函数从给定的文件中导入商品信息到某个商品信息链表中,
		pTotal保存总共发现的信息条数,pSuccess保存成功导入的信息条数 
	返回值	： 无返回值
*/
void ImportFromFile(ListContext*pStockList, const char*szFileName, int*pTotal, int*pSuccess);

/*
	函数说明 : 通过Id来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareById(Node*it, Node*target);

/*
	函数说明 : 通过Name来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByName(Node*it, Node*target);

/*
	函数说明 : 通过商品类型来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByType(Node*it, Node*target);

/*
	函数说明 : 通过进价来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByPurchaseprice(Node*it, Node*target);

/*
	函数说明 : 通过售价来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareBySellprice(Node*it, Node*target);

/*
	函数说明 : 通过库存量来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareByStock(Node*it, Node*target);
/*
	函数说明 : 通过销售量来比较两个商品的回调函数
	返回值   : 0相等,非0不同
*/
int CompareBySell(Node*it, Node*target);
#endif