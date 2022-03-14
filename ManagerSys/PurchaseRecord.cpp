#include "stdafx.h"
#include "PurchaseRecord.h"


int CompareByAmount(Node*it, Node*target)
{
	Record*pIt = (Record*)it;
	Record*pTarget = (Record*)target;

	return pIt->Sell*pIt->Purchaseingprice - pTarget->Sell*pTarget->Purchaseingprice;
}