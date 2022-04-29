#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
  vector<vector<int>> memo;
  vector<vector<int>> dist;
  int gdst;
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                        int k) {
    dist.resize(n, vector<int>(n, -1));
    memo.resize(n, vector<int>(k + 2, -1));
    for (auto flight : flights) {
      dist[flight[0]][flight[1]] = flight[2];
    }

    gdst = dst;
    int price = findCheap(src, k);
    return price < INT_MAX ? price : -1;
  }
  int findCheap(int src, int k) {
    if (memo[src][k] != -1) {
      return memo[src][k];
    }
    if (src == gdst) {
      return 0;
    }
    if (k < 0) {
      return INT_MAX;
    }
    int price = INT_MAX;
    for (int i = 0; i < dist.size(); ++i) {
      if (dist[src][i] != -1) {
        price = min(price, dist[src][i] + findCheap(i, k - 1));
      }
    }
    memo[src][k] = price;
    return price;
  }
};