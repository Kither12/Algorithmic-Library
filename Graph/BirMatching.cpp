struct Matching {
    int n;
    vector<vector<int> > ke;
    vector<int> seen;
    vector<int> matchL, matchR;
    int iteration;

    Matching(int _n)
        : n(_n),
          ke(_n),
          seen(_n, false),
          matchL(_n, -1),
          matchR(_n, -1),
          iteration{0} {}

    void addEdge(int u, int v) { ke[u].push_back(v); }

    bool dfs(int u) {
        seen[u] = iteration;
        for (int v : ke[u]) {
            if (matchR[v] < 0) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        for (int v : ke[u]) {
            if (seen[matchR[v]] != iteration && dfs(matchR[v])) {
                matchR[v] = u;
                matchL[u] = v;
                return true;
            }
        }
        return false;
    }

    int match() {
        int res = 0;
        int newMatches = 0;
        do {
            iteration++;
            newMatches = 0;
            for (int u = 0; u < n; u++) {
                if (matchL[u] < 0 && dfs(u)) ++newMatches;
            }
            res += newMatches;
        } while (newMatches > 0);
        return res;
    }
};