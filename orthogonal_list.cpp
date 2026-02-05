//图的存储--十字链表
/*
	这个代码的所用的headNum和headNext是箭头指出的结点，tailNum和tailNext是箭头指入的结点，和图里面定义的弧头和弧尾相反
*/
#include<iostream>
using namespace std;
typedef char ElemType;
#define MIXSIZE 100

//每个单链表中的结点
typedef struct ArcNode
{
	int headNum; //头所在顶点表的下标;
	int tailNun; //尾所在顶点表的下标;
	struct ArcNode* headNext; //和这个顶点相连的另一个结点的指针---由该结点指出
	struct ArcNode* tailNext; //和这个顶点相连的另一个结点的指针---指向该结点
}ArcNode;

//由每个结点作为表头组成的结构体数组
typedef struct Vertex
{
	ElemType data; //顶点信息
	struct ArcNode* firstIn; //和这个顶点相连的一个结点的指针---由该结点指出
	struct ArcNode* firstOut; //和这个顶点相连的一个结点的指针---指向该结点
}Vertex;

//最终图的结构体
typedef struct graph
{
	Vertex vertex[MIXSIZE];
	int nVer; //顶点数
	int nArc; //边数---出边和入边
}Graph;

//获取与顶点相连结点的下标
int getArc(Graph* G, ElemType a)
{
	for (int i = 0; i < G->nVer; i++)
	{
		if (G->vertex[i].data == a)
		{
			return i;
		}
	}
	return -1;
}

//连成框架
int creatGraph(Graph* G)
{
	cout << "请输入节点数和边数" << endl;
	cin >> G->nVer >> G->nArc;
	for (int i = 0; i < G->nVer; i++)
	{
		cout << "请依次输入每个结点的数据" << endl;
		cin >> G->vertex[i].data;
		G->vertex[i].firstIn = NULL;
		G->vertex[i].firstOut = NULL;
	}
	for (int i = 0; i < G->nArc; i++)
	{
		ElemType m, n;
		cout << "请输入各边的两个结点数据" << endl;
		cin >> m >> n;
		int x = getArc(G, m);
		int y = getArc(G, n);
		if (x == -1 || y == -1)
		{
			cout << "顶点不存在！" << endl;
			return 1;
		}
		if (x == y)
		{
			cout << "顶点重复！" << endl;
			return 1;
		}

		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		if (p == NULL) {
			// 处理内存分配失败的情况
			return 1;
		}
		
		//头插法链接邻接表
		p->headNext = G->vertex[x].firstOut;
		G->vertex[x].firstOut = p;
		p->headNum = x;
		p->tailNun = y;
	}
	cout << "创建成功" << endl;

	return 0;
}

//构建十字链表
int CrossLink(Graph* G)
{
	for (int i = 0; i < G->nVer; i++)
	{
		ArcNode* p = G->vertex[i].firstOut;
		while (p != NULL)
		{
			if (p->tailNun == i)
			{
				p->tailNext = G->vertex[i].firstIn;
				G->vertex[i].firstIn = p;
			}
			p = p->headNext;
		}
	}
	
	return 0;
}

//释放链表
void freeList(Graph* G)
{
	for (int i = 0; i < G->nVer; i++)
	{
		ArcNode* p = G->vertex[i].firstOut;
		ArcNode* q;
		while (p != NULL)
		{
			q = p->headNext;
			free(p);
			p = q;
		}
		G->vertex[i].firstIn = NULL;
		G->vertex[i].firstOut = NULL;
	}
}

int main()
{
	// 从栈分配改为堆分配
	Graph* G = (Graph*)malloc(sizeof(Graph));
	if (G == NULL) {
		// 处理内存分配失败的情况
		return 1;
	}
	creatGraph(G);
	cout << CrossLink(G);
	// 用完后释放堆内存
	freeList(G);
	free(G);

	return 0;
}
