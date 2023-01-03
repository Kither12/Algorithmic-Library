template <typename num_t> struct RangeFenwick2D {
  int n, m;
  vector<vector<num_t>> fen[4];

  RangeFenwick2D(int n, int m) {
    this->n = n, this->m = m;
    for (int i = 0; i < 4; i++) {
      fen[i].resize(n + 1, vector<num_t>(m + 1));
    }
  }
  void upd(int x, int y, num_t val) {
    x++, y++;
    assert(0 < x && 0 < y);
    for (int xx = x; xx <= n; xx += xx & -xx) {
      for (int yy = y; yy <= m; yy += yy & -yy) {
        fen[0][xx][yy] += val;
        fen[1][xx][yy] += x * val;
        fen[2][xx][yy] += y * val;
        fen[3][xx][yy] += x * y * val;
      }
    }
  }
  void upd(int x, int y, int z, int t, num_t val) {
    upd(x, y, +val);
    upd(x, t + 1, -val);
    upd(z + 1, y, -val);
    upd(z + 1, t + 1, +val);
  }
  num_t query(int x, int y) {
    x++, y++;
    assert(x <= n && y <= m);
    num_t res = 0;
    for (int xx = x; xx > 0; xx -= xx & -xx) {
      for (int yy = y; yy > 0; yy -= yy & -yy) {
        res += (x + 1) * (y + 1) * fen[0][xx][yy];
        res -= (y + 1) * fen[1][xx][yy];
        res -= (x + 1) * fen[2][xx][yy];
        res += fen[3][xx][yy];
      }
    }
    return res;
  }
  num_t query(int x, int y, int z, int t) {
    return query(z, t) - query(x - 1, t) - query(z, y - 1) +
           query(x - 1, y - 1);
  }
};