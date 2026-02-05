//图的邻接矩阵存储
#include<iostream>
using namespace std;
typedef char ElemType;
#define MIXSIZE 100
#define MIXINT 999999

typedef struct graph
{
	ElemType vertex[MIXSIZE];//存储顶点的数组
	int edge[MIXSIZE][MIXSIZE];//存储边的矩阵
	int nVer, nEgde;//顶点数，边数
}Graph;

int getEdge(Graph* q, ElemType a)
{
	for (int i = 0; i < q->nVer; i++)
	{
		if (q->vertex[i] == a)
		{
			return i;
		}
	}
	return 0;
}
int creatGraph(Graph* p)
{
	cout << "请输入节点数和边数" << endl;
	cin >> p->nVer >> p->nEgde;
	for (int i = 0; i < p->nVer; i++)
	{
		cout << "请依次输入每个结点的数据" << endl;
		cin >> p->vertex[i];
	}
	for (int i = 0; i < p->nEgde; i++)
	{
		for (int j = 0; j < p->nEgde; j++)
		{
			p->edge[i][j] = MIXINT;
		}
	}
	for (int i = 0; i < p->nEgde; i++)
	{
		ElemType m, n, w;
		cout << "请输入各边的两个结点数据和权值" << endl;
		cin >> m >> n >> w;
		int x = getEdge(p, m);
		int y = getEdge(p, n);
		p->edge[x][y] = w;
		p->edge[y][x] = p->edge[x][y];
	}
	return 0;
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
	free(G);
	return 0;
}
