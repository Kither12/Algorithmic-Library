namespace BCC {
    int timer;
    vector<int> num;
    vector<int> low;
    vector<int> art;
    vector<pair<int, int>> bridges;
    vector<vector<int>> comps;
    vector<int> stk;

    void _dfs(const vector<vector<int>> &adj, int u, int p = -1) {
        num[u] = low[u] = ++timer;
        stk.push_back(u);
        for (int v : adj[u]) {
            if (!num[v]) {
            _dfs(adj, v, u);
            if (low[v] > num[u]) {
                bridges.push_back({u, v});
            }
            low[u] = min(low[u], low[v]);
            if (low[v] >= num[u]) {
                art[u] = num[u] > 1 || num[v] > 2;
                vector<int> comp = {u};
                comps.push_back(comp);
                while (comps.back().back() != v) {
                comps.back().push_back(stk.back()), stk.pop_back();
                }
            }
            } else if (v != p) {
            low[u] = min(low[u], num[v]);
            }
        }
    }

    tuple<vector<vector<int>>, vector<int>, vector<pair<int, int>>> build(const vector<vector<int>> &adj, int rt = 0) {
        int n = adj.size();
        timer = 0;
        num = vector<int>(n);
        low = vector<int>(n);
        art = vector<int>(n);
        bridges.clear();
        comps.clear();
        stk.clear();
        _dfs(adj, rt);
        return {comps, art, bridges};
    }
} // namespace BCC