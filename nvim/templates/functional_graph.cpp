struct FunctionalGraph {
    int n = 0;
    vector<int> F;
    vector<bool> in_cycle;
    vector<int> which_cycle; //used to index cycles
    vector<vector<int>> cycles;
    vector<int> depth; // Distance from a cycle
    vector<int> cycle_root; // first cycle node reachable from i
    vector<int> cycle_position;
    vector<vector<int>> children;
    vector<int> jump, jump_dist; // Not sure

    FunctionalGraph(const vector<int> &f = {}) {
       if (!f.empty()){
          F = f;
          build();
       }
    }

    FunctionalGraph(vector<int>&& f) {
      F = std::move(f);
      build();
    }

    void build() {
        n = int(F.size());
        in_cycle.assign(n, false);
        which_cycle.assign(n, -1);
        cycle_root.assign(n, -1);
        cycle_position.assign(n, -1);
        depth.assign(n, -1);
        children.assign(n, {}); // reachable nodes that are not in a cycle
        cycles.clear();

        vector<int> seen(n, -1);

        for (int i = 0; i < n; i++) {
            if (seen[i] >= 0)
                continue;

            int x = i;

            do {
                seen[x] = i;
                x = F[x];
            } while (seen[x] < 0);

            if (seen[x] != i)
                continue;

            vector<int> cycle;
            int y = x;

            do {
                in_cycle[y] = true;
                cycle_position[y] = int(cycle.size());
                which_cycle[y] = int(cycles.size());
                cycle.push_back(y);
                y = F[y];
            } while (y != x);

            cycles.push_back(cycle);
        }

        seen.assign(n, 0);

        for (int i = 0; i < n; i++)
            seen[F[i]] += !in_cycle[i];

        for (int i = 0; i < n; i++)
            children[i].reserve(seen[i]);

        seen.clear();

        for (int i = 0; i < n; i++)
            if (!in_cycle[i])
                children[F[i]].push_back(i);

        jump.assign(n, -1);
        jump_dist.assign(n, -1);
        int cyc_root = -1, which_cyc = -1;

        function<void(int,int)> dfs;
        dfs = [&](int node, int parent) {
            depth[node] = parent < 0 ? 0 : depth[parent] + 1;
            cycle_root[node] = cyc_root;
            which_cycle[node] = which_cyc;
            jump[node] = parent < 0 ? node : jump_dist[parent] == jump_dist[jump[parent]] ? jump[jump[parent]] : parent;
            jump_dist[node] = depth[node] - depth[jump[node]];

            for (int child : children[node])
                dfs(child, node);
        };

        for (int i = 0; i < n; i++)
            if (in_cycle[i]) {
                cyc_root = i;
                which_cyc = which_cycle[i];
                dfs(i, -1);
            }
    }

    int cycle_length(int node) const {
        return int(cycles[which_cycle[node]].size());
    }

    int go_forward(int v, int64_t k) const {
        if (k >= depth[v]) {
            int root = cycle_root[v];
            k -= depth[v];
            int cyc = which_cycle[root];
            int64_t position = (cycle_position[root] + k) % cycles[cyc].size();
            return cycles[cyc][position];
        }

        while (k > 0)
            if (jump_dist[v] <= k) {
                k -= jump_dist[v];
                v = jump[v];
            } else {
                k--;
                v = F[v];
            }

        return v;
    }
};

