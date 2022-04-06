#ifndef LIST_H
#define LIST_H

/*双向环形链表*/
typedef struct Node
{
	struct Node*prev;
	struct Node*next;

}Node, *pNode;

typedef struct ListContext
{
	Node    Head;       //
	int     Len;        //长度
}ListContext, *pListContext;

//回调函数
typedef int(*docallback)(pListContext pList, pNode it);

//比较函数应该自己定义,返回正数,0,负数,代表大于,等于,小于
typedef int(*cmpfunc)(Node* it, Node* target);

//Create a empty list
pListContext createlist();
void dellist(pListContext plist);
void insertfront(pListContext plist, Node*pNewNode);
void insertback(pListContext plist, Node*pNewNode);
void delnode(pListContext plist, Node*pNode);
void sort(pListContext plist, cmpfunc cmp,int ascending);
Node* search(pListContext plist, Node*pStart, cmpfunc compare, void* target);

#endif