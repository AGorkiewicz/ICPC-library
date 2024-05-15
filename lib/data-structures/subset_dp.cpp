vector <int> solve(int W, vector <int> coins) {
    int n = coins.size(), all_sum = 0;
    if (n == 0) { return 0; }
    vector <int> dp[2];
    for (auto v: coins) { all_sum += v; }
    int goal = all_sum / 2, start_idx = 0, cur_sum = 0;
    while (cur_sum + coins[start_idx] <= goal) {
        cur_sum += coins[start_idx++];
    }
    start_idx--;
    for (int i = 0; i < 2; ++i) { dp[i].assign(W + W + 1, -1); }
    auto update = [&](const int id) {
        for (int i = W + W; i >= 0; --i) {
            for (int j = max(0, dp[id ^ 1][i]); j < dp[id][i]; ++j) {
                if (i - coins[j] >= 0) {
                    dp[id][i - coins[j]] = max(dp[id][i - coins[j]], j);
                }
            }
        }
    };
    dp[start_idx & 1][cur_sum + W - goal] = start_idx + 1;
    update(start_idx & 1);
    for (int i = start_idx + 1; i < n; ++i) {
        const int id = i & 1;
        dp[id].assign(W + W + 1, -1);
        for (int j = 0; j + coins[i] <= W + W; ++j) {
            dp[id][j] = max(dp[id][j], dp[id ^ 1][j]);
            dp[id][j + coins[i]] = max(dp[id][j + coins[i]], dp[id ^ 1][j]);
        }
        update(id);
    }
    return dp[(n - 1) & 1];
}