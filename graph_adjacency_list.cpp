//图的存储--邻接表
#include<iostream>
using namespace std;
typedef char ElemType;
#define MIXSIZE 100

//每个单链表中的结点
typedef struct ArcNode
{
	int headNum; //所在顶点表的下标;
	struct ArcNode* next; //和这个顶点相连的另一个结点的指针
}ArcNode;

//由每个结点作为表头组成的结构体数组
typedef struct Vertex
{
	ElemType data; //顶点信息
	struct ArcNode* first; //和这个顶点相连的一个结点的指针
}Vertex;

//最终图的结构体
typedef struct graph
{
	Vertex vertex[MIXSIZE];
	int nVer; //顶点数
	int nArc; //边数
}Graph;

//获取与顶点相连结点的下标
int getArc(Graph* p, ElemType a)
{
	for (int i = 0; i < p->nVer; i++)
	{
		if (p->vertex[i].data == a)
		{
			return i;
		}
	}
	return -1;
}

int creatGraph(Graph* p)
{
	cout << "请输入节点数和边数" << endl;
	cin >> p->nVer >> p->nArc;
	for (int i = 0; i < p->nVer; i++)
	{
		cout << "请依次输入每个结点的数据" << endl;
		cin >> p->vertex[i].data;
		p->vertex[i].first = NULL;
	}
	for (int i = 0; i < p->nArc; i++)
	{	
		ElemType m, n;
		cout << "请输入各边的两个结点数据" << endl;
		cin >> m >> n;
		int x = getArc(p, m);
		int y = getArc(p, n);
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

		ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
		if (q == NULL) {
			// 处理内存分配失败的情况
			return 1;
		}
		ArcNode* r = (ArcNode*)malloc(sizeof(ArcNode));
		if (r == NULL) {
			// 处理内存分配失败的情况
			return 1;
		}

		//头插法链接邻接表
		q->next = p->vertex[x].first;
		p->vertex[x].first = q;
		q->headNum = y;            
		
		r->next = p->vertex[y].first;
		p->vertex[y].first = r;
		r->headNum = x;
	}
	cout << "创建成功" << endl;
	return 0;
}

//释放链表
void freeList(Graph* p)
{
	for (int i = 0; i < p->nVer; i++)
	{
		ArcNode* q = p->vertex[i].first;
		ArcNode* L;
		while (q != NULL)
		{
			L = q->next;
			free(q);
			q = L;
		}
		p->vertex[i].first = NULL;
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
	cout << creatGraph(G);

	// 用完后释放堆内存
	freeList(G);
	free(G);
	
	return 0;
}
