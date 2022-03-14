#ifndef _PURCHASE_RECORD_H
#define _PURCHASE_RECORD_H
#include "SaleRecord.h"

typedef SaleRecords PurchaseRecords;

//通过进价总金额比较.
int CompareByAmount(Node*it, Node*target);

#endif