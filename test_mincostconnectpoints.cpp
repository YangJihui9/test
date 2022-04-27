#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int minCostConnectPoints(vector<vector<int>> &points) {
  int n = points.size();
  if (n == 0) {
    return 0;
  }
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  vector<bool> ing(n, false);
  int cost = 0;
  int incount = 0;
  pq.push(pair<int, int>(0, 0));
  while (!pq.empty()) {
    auto now = pq.top();
    pq.pop();
    int cur_ind = now.second;
    if (ing[cur_ind]) {
      continue;
    }
    ing[cur_ind] = true;
    cout << "in:" << cur_ind << endl;
    cost += now.first;
    ++incount;
    if (incount == n) {
      break;
    }

    for (int i = 1; i < n; ++i) {
      if (ing[i]) {
        continue;
      }
      pq.push(pair<int, int>(abs(points[cur_ind][0] - points[i][0]) +
                                 abs(points[cur_ind][1] - points[i][1]),
                             i));
    }
  }
  return cost;
}

int main() {
  vector<vector<int>> data = {{3, 12}, {-2, 5}, {-4, 1}};

  cout << "case 1 cost: " << minCostConnectPoints(data) << endl;

  vector<vector<int>> data2 = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};

  cout << "case 2  cost: " << minCostConnectPoints(data2) << endl;
}