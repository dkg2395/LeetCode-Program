class Solution {
  public boolean canIWin(int maxChoosableInteger, int desiredTotal) {
    if (desiredTotal <= 0)
      return true;

    final int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
    if (sum < desiredTotal)
      return false;

    return dp(desiredTotal, 0, maxChoosableInteger);
  }

  // true := can win, false := can't win
  private Map<Integer, Boolean> memo = new HashMap<>();

  private boolean dp(int total, int bitmask, int n) {
    if (total <= 0)
      return false;
    if (memo.containsKey(bitmask))
      return memo.get(bitmask);

    for (int i = 1; i <= n; ++i) {
      if ((bitmask & 1 << i) == 1) // Integer i is used.
        continue;
      if (!dp(total - i, bitmask | 1 << i, n))
        return true;
    }

    memo.put(bitmask, false);
    return false;
  }
}
