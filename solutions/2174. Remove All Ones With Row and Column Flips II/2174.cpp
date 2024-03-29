class Solution {
 public:
  int removeOnes(vector<vector<int>>& grid) {
    const int m = grid.size();
    const int n = grid[0].size();
    // dp[i] := the minimum number of operations to remove all 1s from the
    // grid, where bitmask i represents the state of the grid
    dp.resize(1 << m * n, INT_MAX);
    return dfs(encode(grid, m, n), m, n);
  }

 private:
  vector<int> dp;

  int dfs(int mask, int m, int n) {
    if (mask == 0)
      return 0;
    if (dp[mask] < INT_MAX)
      return dp[mask];

    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (mask >> i * n + j & 1) {  // grid[i][j] == 1
          int nextMask = mask;
          // Set the cells in the same row with 0.
          for (int k = 0; k < n; ++k)
            nextMask &= ~(1 << i * n + k);
          // Set the cells in the same column with 0.
          for (int k = 0; k < m; ++k)
            nextMask &= ~(1 << k * n + j);
          dp[mask] = min(dp[mask], 1 + dfs(nextMask, m, n));
        }

    return dp[mask];
  }

  int encode(const vector<vector<int>>& grid, int m, int n) {
    int encoded = 0;
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n; ++j)
        if (grid[i][j])
          encoded |= 1 << i * n + j;
    return encoded;
  }
};
