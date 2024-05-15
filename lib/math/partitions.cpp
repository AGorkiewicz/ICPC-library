vector<mint> solve(int n) {
  vector<mint> ans(n + 1);
  vector<pair<int, int>> gp; // (sign, generalized pentagonal numbers)
  gp.emplace_back(0, 0);
  for (int i = 1; gp.back().second <= n; i++) {
    gp.emplace_back(i % 2 ? 1 : -1, i * (3 * i - 1) / 2);
    gp.emplace_back(i % 2 ? 1 : -1, i * (3 * i + 1) / 2);
  }
  ans[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (auto it : gp) {
      if (i >= it.second) ans[i] += ans[i - it.second] * it.first;
      else break;
    } /* remember that ans[i] can be negative here */
  }
  return ans;
}
