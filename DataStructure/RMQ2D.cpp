/*
    usage:
    rmq.init(n, m);
    cin >> rmq[i][j]
    rmq.build();
*/

template <class num_t> struct RMQ2D {
  static const int maxn = 1e3 + 5;
  static const int maxm = 1e3 + 5;
  static const int logn = 10 + 1;
  static const int logm = 10 + 1;
  int n, m;
  num_t a[maxn][maxm];
  num_t f[logm][maxn][maxm];
  num_t g[logm][logn][maxm][maxn];

  inline num_t best(const num_t &a, const num_t &b) {
    return a < b ? a : b;
  }
  void init(int _n, int _m) { n = _n, m = _m; }
  num_t *operator[](int u) {
    assert(u < n);
    return a[u];
  }
  void build() {
    for (int k = 1; k <= n; k++) {
      for (int i = 1; i <= m; i++) {
        f[0][k][i] = a[k - 1][i - 1];
      }
      for (int j = 1; 1 << j <= m; j++) {
        for (int i = 0; i + (1 << j) - 1 <= m; i++) {
          f[j][k][i] = best(f[j - 1][k][i], f[j - 1][k][i + (1 << (j - 1))]);
        }
      }
    }
    for (int k = 1; k <= m; k++) {
      for (int l = 0; k + (1 << l) - 1 <= m; l++) {
        for (int i = 1; i <= n; i++) {
          g[l][0][k][i] = f[l][i][k];
        }
        for (int j = 1; 1 << j <= n; j++) {
          for (int i = 0; i + (1 << j) - 1 <= n; i++) {
            g[l][j][k][i] =
                best(g[l][j - 1][k][i], g[l][j - 1][k][i + (1 << (j - 1))]);
          }
        }
      }
    }
  }
  num_t query(int x, int y, int z, int t) {
    x++, y++, z++, t++;
    int a = z - x + 1, b = t - y + 1;
    int lga = __lg(a);
    int lgb = __lg(b);
    num_t res = g[lgb][lga][y][x];
    res = best(res, g[lgb][lga][y + b - (1 << (lgb))][x + a - (1 << (lga))]);
    res = best(res, g[lgb][lga][y][x + a - (1 << (lga))]);
    res = best(res, g[lgb][lga][y + b - (1 << (lgb))][x]);
    return res;
  }
};
RMQ2D<int> rmq;