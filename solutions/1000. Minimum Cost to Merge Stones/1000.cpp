class Solution {
 public:
  int mergeStones(vector<int>& stones, int K) {
    const int n = stones.size();
    this->K = K;

    // dp[i][j][k] := the minimum cost to merge stones[i..j] into k piles
    dp.resize(n, vector<vector<int>>(n, vector<int>(K + 1, kMax)));
    prefix.resize(n + 1);

    partial_sum(stones.begin(), stones.end(), prefix.begin() + 1);

    const int cost = mergeStones(stones, 0, n - 1, 1);
    return cost == kMax ? -1 : cost;
  }

 private:
  static constexpr int kMax = 1'000'000'000;
  int K;
  vector<vector<vector<int>>> dp;
  vector<int> prefix;

  int mergeStones(const vector<int>& stones, int i, int j, int k) {
    if ((j - i + 1 - k) % (K - 1))
      return kMax;
    if (i == j)
      return k == 1 ? 0 : kMax;
    if (dp[i][j][k] != kMax)
      return dp[i][j][k];
    if (k == 1)
      return mergeStones(stones, i, j, K) + prefix[j + 1] - prefix[i];

    for (int m = i; m < j; m += K - 1)
      dp[i][j][k] = min(dp[i][j][k], mergeStones(stones, i, m, 1) +
                                         mergeStones(stones, m + 1, j, k - 1));

    return dp[i][j][k];
  }
};
