// https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/

class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        // Like assigning tasks to workers?
        int n = nums1.size();
        int inf = 2e8;
        vector<vector<int>> cost(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cost[i][j] = nums1[i] ^ nums2[j];
        
        // dp[i][mask] = min(dp[i-1][mask j bit off] + cost[i][j])   mask j off should have i-1 sb?
        // Recursively, dp[i][mask] = min(dp[i+1][mask j bit on] + cost[i][j])
        
        int ub = 1<<n;
        vector<vector<int>> dp(n, vector<int>(ub, inf));
        dp[0][0] = 0;
        for (int i = 0; i < n; i++) {
            for (int mask = 1; mask < ub; mask++) {
                for (int j = 0; j < n; j++) {
                    if (mask & (1<<j))
                        dp[i][mask] = min(dp[i][mask], cost[i][j] + ((i == 0) ? 0 : dp[i-1][mask ^ (1<<j)]) );
                }
            }
        }
        return dp[n-1][ub-1];
    }
};