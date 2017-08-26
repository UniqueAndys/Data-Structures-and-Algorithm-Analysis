#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <set>

using namespace std;

/*
Dijkstra算法实现，具体使用案例参考算法导论
输入数据：
第一行：N 结点个数，M 边的个数
第2到M+1行：带方向的起点，终点，边的权值
第M+2行：原点
5 10
0 1 10
0 3 5
1 2 1
1 3 2
2 4 4
3 1 3
3 2 9
3 4 2
4 0 7
4 2 6
0
*/

struct Node {
	int index;
	int parent;
	int dis;
	Node() {	// 默认构造函数
		index = 0;
		parent = 0;
		dis = 0;
	}
	Node(int _index, int _parent, int _dis) :index(_index), parent(_parent), dis(_dis) {}
	friend bool operator<(Node a, Node b) {	// priority_queue默认是大顶堆，所以逻辑要反一下
		return a.dis > b.dis;
	}
};

// 松弛函数
void relax(int u, int v, int w, vector<Node> &G) {
	if (G[v].dis > G[u].dis + w) {
		G[v].dis = G[u].dis + w;
		G[v].parent = u;
	}
}

void Dijkstra(vector<Node> &G, vector<vector<pair<int, int>>> &Adj, int s) {
	G[s].dis = 0;
	G[s].parent = s;
	priority_queue<Node> pq;
	pq.push(G[s]);
	set<int> S;
	while (!pq.empty()) {
		Node tmp = pq.top();
		int cur = tmp.index;
		if (S.find(cur) == S.end()) {
			for (auto ele : Adj[cur]) {
				relax(cur, ele.first, ele.second, G);
				pq.push(G[ele.first]);
			}
		}
		S.insert(cur);
		pq.pop();
	}

}

int main() {
	int N, M;
	cin >> N >> M;
	vector<Node> G(N);
	for (int i = 0; i < N; ++i) {
		Node node = Node(i, 0, INT_MAX);
		G[i] = node;
	}
	priority_queue<Node> pq;
	for (int i = 0; i < N; ++i) {
		pq.push(G[i]);
	}

	vector<vector<pair<int, int>>> Adj(N);
	for (int i = 0; i < M; ++i) {
		int index1, index2, w;
		cin >> index1 >> index2 >> w;
		Adj[index1].push_back(make_pair(index2, w));
	}

	int s;
	cin >> s;

	Dijkstra(G, Adj, s);

	for (int i = 0; i < N; ++i) {	// 打印每个结点的信息
		cout << G[i].index << " " << G[i].parent << " " << G[i].dis << endl;
	}

	return 0;

}
