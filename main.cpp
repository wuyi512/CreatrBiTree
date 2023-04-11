#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char ElemType;
typedef int State;

typedef struct BTree
{
	ElemType val;
	struct BTree *lChild, *rChild;
}*T;

T newNode(ElemType val);
State iniTree(T* root, char* preOrder, char* midOrder);
void visit(T node);
void preOrderTraverse(T root);

void preOrderTraverse(T root) 
{
	if (root)
	{
		visit(root);
		preOrderTraverse(root->lChild);
		preOrderTraverse(root->rChild);
	}
}

void visit(T node)
{
	printf("%c ", node->val);
}

T newNode(ElemType val)
{
	T node;
	node = (T)malloc(sizeof(BTree));
	if (node == NULL) return NULL;
	node->val = val;
	node->lChild = NULL;
	node->rChild = NULL;
	return node;
}

State iniTree(T* root, char* preOrder, char* midOrder)
{
	int len = strlen(preOrder);
	if (len == 1) return 1;
	int i = 0;
	for (; i < len; i++) if (preOrder[0] == midOrder[i]) break;
	char* preLeft, * midLeft, * preRight, * midRight;
	preLeft = (char*)malloc(sizeof(char) * (i + 1));
	midLeft = (char*)malloc(sizeof(char) * (i + 1));
	preRight = (char*)malloc(sizeof(char) * (len - i));
	midRight = (char*)malloc(sizeof(char) * (len - i));
	if (!midLeft || !midRight || !preLeft || !preRight)	return 0;
	preRight[len - i - 1] = '\0';
	midRight[len - i - 1] = '\0';
	midLeft[i] = '\0';
	preLeft[i] = '\0';
	/*
	* 用先序中第一个元素将中序的字符串和先序的字符串切割成两个子串
	* 两个子串即左右子树
	* 例如
	* 先序：adbce
	* 中序：bdcae
	* 则根节点为a
	* 将中序从a处切开即得到左右子树的中序遍历结果即
	* mR = bdc  mL = e
	* 也可将先序串切割成左右两子树的先序遍历结果即
	* pR = bdc  pL = e
	*/
	for (int j = 0; j < i; j++)
	{
		midLeft[j] = midOrder[j];
		preLeft[j] = preOrder[j + 1];
	}
	for (int j = 0; j < len - i; j++)
	{
		midRight[j] = midOrder[j + i + 1];
		preRight[j] = preOrder[j + i + 1];
	}
	T node;
	if (!(*root))
	{
		node = newNode(preOrder[0]);
		if (!node) return 0;
		*root = node;
	}
	/*
	* 先序第一个即为该根节点的孩子
	*/
	node = newNode(preLeft[0]);
	if (!node) return 0;
	(*root)->lChild = node;
	node = newNode(preRight[0]);
	if (!node) return 0;
	(*root)->rChild = node;
	if (!iniTree(&(*root)->lChild, preLeft, midLeft)) return 0;
	if (!iniTree(&(*root)->rChild, preRight, midRight)) return 0;
	return 1;
}

int main() 
{
	char preOrder[100];
	char midOrder[100];
	scanf_s("%s", preOrder, 100);
	scanf_s("%s", midOrder, 100);

	int len = strlen(preOrder);
	if (len != strlen(midOrder))
	{
		printf("ERROR: length of preOrder is not equal the midOrder");
		return 0;
	}
	T root = NULL;

	iniTree(&root, preOrder, midOrder);
	preOrderTraverse(root);

	return 0;
}
