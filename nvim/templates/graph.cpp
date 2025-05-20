struct Edge {
  int to;
  i64 w;
  Edge (int to, i64 w) : to(to), w(w) {};
  bool operator>(const Edge& other) const {
    return w > other.w;
  }
};

class Graph {
public:
  using AdjList = std::vector<std::vector<Edge>>;
  using MinHeap = std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>; // smallest value at top of queue
 
  int N; // # Vertices
  AdjList adj_list;

  Graph() {}

  // assume input of size M, where each line is 'from to weight' and is 1-indexed
  Graph(int _N, int _M, bool undirected, bool weighted = true) {
    init(_N, _M, undirected, weighted);
  }

  void init(int _N, int _M, bool undirected, bool weighted) {
    N = _N;
    adj_list.resize(N);

    for (int i=0; i<_M; i++) {
      int a,b; cin >> a >> b;
      a--; b--; // IMPORTANT: ASSUMES INPUT IS 1-INDEXED
      if (weighted) {
         i64 c; cin >> c;
         adj_list[a].emplace_back(b,c);
         if (undirected) { adj_list[b].emplace_back(a,c); }
      }
      else {
        adj_list[a].emplace_back(b,1);
        if (undirected) { adj_list[b].emplace_back(a,1); }
      }
    }
  }

  std::vector<Edge> operator[] (int i) {
    return adj_list[i];
  }

  Graph(AdjList& adj_list) : adj_list(adj_list) {
    N = adj_list.size();
  }

  Graph(AdjList&& adj_list) : adj_list(std::move(adj_list)) {
    N = adj_list.size();
  }

  // ans[i] is an edge giving the distance from src to node i and the previous node on the path to node i.
  vector<Edge> shortest_paths_from (int src) { // Bellman-Ford
    vector<Edge> ans(N, {-1, LLONG_MAX});
    ans[src] = {-1,0};
    for (int i=0; i<N-1; i++) { // do relaxation N-1 times
      for (int from=0; from<N; from++) {
        for (auto& [to, w] : adj_list[from]) {
          if (ans[from].w < ans[to].w - w) { // avoid overflow
            ans[to] = {from, ans[from].w + w};
          }
        }
      }
    }
    return ans;
    // optional: check for negatiive cycles by running the loop one more time. and seeing if update happens
  }


  // Assume prev is already computed (from daijkstra or Ford)
  std::vector<int> shortest_path_from_prev(int dest, std::vector<int>& prev) {
    if (prev[dest] == -1) return std::vector<int>(); // indicates no path exists
    vector<int> path;
    int cur = dest;
    while (cur != -1) {
      path.push_back(cur);
      cur = prev[cur];
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

  // fails if there are negative edge weights
  // ans[i] is an edge giving the distance from src to node i and the previous node on the path to node i.
  std::vector<Edge> shortest_paths_from_dijkstra (int src) {
    std::vector<Edge> ans(N, {-1, LLONG_MAX});
    MinHeap Q; // priority queue  
    ans[src] = {-1,0};
    Q.push( {src,0} );
    std::vector<bool>visited(N,false);
    while (!Q.empty()) {
      auto [from, _] = Q.top(); Q.pop();
      if (visited[from]) continue; 
      visited[from] = true;
      for (auto& [to, w] : adj_list[from]) {
        if (ans[from].w < ans[to].w - w) { // Structured this way to avoid overflow
          ans[to] = {from, ans[from].w + w};
          Q.push( {to, ans[to].w} );
        }
      }
    }
    return ans;
  }

  // same as shortest_path_from, but invert the edges first
  std::vector<Edge> shortest_path_to(int dest) {
    AdjList adj_list2(N);
    for (int from=0; from<N; from++) for (auto& [to, w] : adj_list[from]) adj_list2[to].push_back({from, w});
    Graph G2(adj_list2);
    return G2.shortest_paths_from_dijkstra(dest);
  }

  // floyd-warshall. O(V^3)
  // doesn't work if there are negative cycles
  vector<vector<Edge>> all_shortest_paths_dense () { 
    vector ans(N, vector<Edge>(N, {-1, LLONG_MAX}));

    for (int from=0; from<N; from++) {
      ans[from][from] = {-1, 0};
      for (auto& [to, w] : adj_list[from]) {
        ans[from][to] = {from,w};
      }
    }

    for (int k=0; k<N; k++) {
      for (int i=0; i<N; i++) for (int j=0; j<N; j++) {
        if (ans[i][k].w < ans[i][j].w - ans[k][j].w) { // avoid overflow 
            ans[i][j] = {ans[k][j].to, ans[i][k].w + ans[k][j].w};
        }
      }
    }
    return ans;
  }

  void all_shortest_paths_sparse() { // Johnson's: O(V^2 log(V) + V*E)
  }

  void min_span_tree() { // kruskal
  }

};

