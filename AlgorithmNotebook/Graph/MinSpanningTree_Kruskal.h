
//												MST by Kruskal
//			O(E*log(V))
const int MAXV = 1e6 + 1;
int V, E;
vector<int> e[MAXV];
vector<int> wei[MAXV];
/*------------------------------------------------------------ Fast code --------------------------------------------------------------------*/
// init range: [1, n]
#define MAXN 20
int par_[MAXN];
int size_[MAXN];	// size of the corresponding set
void init(int n) {
	for(int i = 1; i <= n; ++i)
		par_[i] = i;
	fill(size_ + 1, size_ + n + 1, 1);
}
int find(int x) {
	while(x != par_[x])
		x = par_[x];
	return x;
}
void merge(int a, int b) {
	a = find(a);
	b = find(b);
	if(size_[a] < size_[b])
		swap(a,b);
	size_[a] += size_[b];
	par_[b] = a;
}

vector<int> pathwei;
int Kruskal() {
	int totalW = 0;
	init(V);

	priority_queue< pair<int, pair<int, int>>> pq;
	for (int v = 1; v <= V; ++v)
		for (int i = 0; i < e[v].size(); ++i)
			pq.push({ -wei[v][i],{ v, e[v][i] } });

	while(!pq.empty()) {
		int we = -pq.top().first;
		int a = pq.top().second.first;
		int b = pq.top().second.second;
		pq.pop();

		if(find(a) != find(b)) {
			//Update
			totalW += we;
			pathwei.push_back(we);
			merge(a,b);
		}
	}
	return totalW;
}


/*-------------------------------------------------------- Struct ------------------------------------------------------------------------*/
struct disjointSet {
public:
	vector<int> parent_;
	vector<int> rank_;
public:
	disjointSet(int n) {
		parent_.assign(n, 0);
		rank_.assign(n, 0);
	}
	void MakeSet(int i) {
		parent_[i] = i;
		rank_[i] = 0;
	}
	int Find(int x) {
		if (x != parent_[x])
			parent_[x] = Find(parent_[x]);
		return parent_[x];
	}
	void Merge(int a, int b) {
		int a_id = Find(a);
		int b_id = Find(b);
		if (a_id == b_id)
			return;

		if (rank_[a_id] > rank_[b_id])
			parent_[b_id] = a_id;
		else {
			parent_[a_id] = b_id;
			if (rank_[a_id] == rank_[b_id])
				++rank_[b_id];
		}
	}
};

vector<int> pathwei;
int Kruskal() {
	int totalTreeWeight = 0;

	disjointSet S(V + 1);
	for (int v = 1; v <= V; ++v)
		S.MakeSet(v);

	priority_queue< pair<int, pair<int, int>>> pq;
	for (int v = 1; v <= V; ++v)
		for (int i = 0; i < e[v].size(); ++i)
			pq.push({ -wei[v][i],{ v, e[v][i] } });

	while (!pq.empty()) {
		int we = -pq.top().first;
		int a = pq.top().second.first;
		int b = pq.top().second.second;
		pq.pop();

		if (S.Find(a) != S.Find(b)) {

			//Update
			totalTreeWeight += we;
			pathwei.push_back(we);
			S.Merge(a, b);
		}
	}
	return totalTreeWeight;
}
