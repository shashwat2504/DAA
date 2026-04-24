#include <iostream>
using namespace std;

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int wt[n+1], bi[n+1];   // wt = weight, bi = profit

    cout << "Enter weights:\n";
    for(int i = 1; i <= n; i++) {
        cin >> wt[i];
    }

    cout << "Enter profits:\n";
    for(int i = 1; i <= n; i++) {
        cin >> bi[i];
    }

    
    cout << "Enter capacity: ";
    cin >> W;

    int dp[n+1][W+1];

    // Initialize
    for(int i = 0; i <= n; i++) {
        for(int w = 0; w <= W; w++) {
            if(i == 0 || w == 0)
                dp[i][w] = 0;
        }
    }

    // DP logic
    for(int i = 1; i <= n; i++) {
        for(int w = 1; w <= W; w++) {

            if(wt[i] <= w) {
                dp[i][w] = max(
                    bi[i] + dp[i-1][w - wt[i]],  // take item
                    dp[i-1][w]                   // skip item
                );
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    cout << "Maximum profit = " << dp[n][W];

    return 0;
}