class DSU { // union by size
  public:
  // negative value in 'data' indicates the node is a root with component size -1*data[i]
  std::vector<int> data; // index of node's parent.
  DSU(int n) : data(n, -1) {}

  int root(int x) {
    if (data[x] < 0) return x; // root nodes have data = -1 * component size
    else return data[x] = root(data[x]);
  }

  bool is_same(int x, int y) {
    return root(x) == root(y);
  }

  int merge(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) return x;
    if (-data[x] < -data[y]) std::swap(x,y); // Let x be the larger group 
    data[x] += data[y]; // larger group is the leader
    data[y] = x; // smaller group's leader is now a pointer node
    return x;
  }

  int size(int x) {
    return -data[root(x)];
  }

  void change_size(int x, int v) {
    data[root(x)] -= v; // minus because negative of size is stored
  }

  // return the connected components: array of an array of nodes in the same component
  std::vector<std::vector<int>> groups() {
    std::vector<std::vector<int>> ans(data.size());
    for (int i=0; (uint64_t)i<data.size(); i++) {
      ans[root(i)].push_back(i);
    }
    return ans;
  }
};

