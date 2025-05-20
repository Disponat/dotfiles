class Tree {
public:
  int n;
  vector<vector<int>> adj; // adjacency list
  vector<int> par;
  vector<int> sz; // sizes of subtree
  vector<int> ord; // order of exploration
  vector<int> centroids;
  // vector<bool> dead; // used to 'cut' the tree by marking dead nodes

  Tree(int _n) : n{_n} {
    adj.resize(n);
    par.resize(n);
    sz.resize(n);
    ord.resize(n);
    for (int i=0; i<n-1; i++) {
      int u,v; cin >> u >> v;
      u--;v--;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
  }

  Tree(vector<vector<int>>& _adj) {
    n = _adj.size();
    adj = _adj;
    sz.resize(n);
  }


  // get size of subtrees and exploration order starting at node i
  // also gets the tree's centroid
  void dfs_from(int i, int parent = -1) {
    ord.push_back(i);
    sz[i] = 1;
    bool is_centroid = true;
    for (auto& to: adj[i]) {
      if (to == parent) continue;
      par[to] = i;
      dfs_from(to, i);
      sz[i] += sz[to];
      if (sz[to] > n/2) is_centroid = false;
    }
    if (n - sz[i] > n / 2) is_centroid = false;
    if (is_centroid) centroids.push_back(i);
  }

  void get_centroids() {
    centroids.clear();
    ord.clear();
    dfs_from(0);
  }

};
