#ifndef LIST_H
#define LIST_H

/*˫��������*/
typedef struct Node
{
	struct Node*prev;
	struct Node*next;

}Node, *pNode;

typedef struct ListContext
{
	Node    Head;       //
	int     Len;        //����
}ListContext, *pListContext;

//�ص�����
typedef int(*docallback)(pListContext pList, pNode it);

//�ȽϺ���Ӧ���Լ�����,��������,0,����,�������,����,С��
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