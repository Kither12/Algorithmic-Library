while (l.size() < r.size()) {
    l = '0' + l;
}
int n = l.size();
dp[0][0][0][1] = 0;
for (int i = 0; i < n; ++i) {
    for (int x = 0; x <= 9; ++x) {
        for (int greater_l : {0, 1}) {
            for (int less_r : {0, 1}) {
                int dl = l[i] - '0';
                int dr = r[i] - '0';
                for (int leading_zeros : {0, 1}) {
                    if (!greater_l && x < dl) continue;
                    if (!less_r && x > dr) continue;
                    int new_leading_zeros = leading_zeros;

                    if (x != 0 && leading_zeros == 1) {
                        new_leading_zeros = 0;
                    }
                    int new_greater_l = greater_l;
                    int new_less_r = less_r;
                    if (x > dl && greater_l == 0) new_greater_l = 1;
                    if (x < dr && less_r == 0) new_less_r = 1;
                    dp[i + 1][new_greater_l][new_less_r][new_leading_zeros] +=
                        dp[i][greater_l][less_r][leading_zeros]
                }
            }
        }
    }
}