#include <algorithm>
#include <climits>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int networkDelayTime(vector<vector<int>> &times, int n, int k) {
  vector<vector<pair<int, int>>> graph(n + 1);
  for (auto &edge : times) {
    graph[edge[0]].push_back(pair<int, int>(edge[1], edge[2]));
  }
  vector<int> dist(n + 1, INT_MAX);
  vector<bool> visited(n + 1, false);
  dist[k] = 0;
  for (int i = 1; i <= n; ++i) {
    int ind;
    int min_dist = INT_MAX;
    for (int j = 1; j <= n; ++j) {
      if (!visited[j] && min_dist >= dist[j]) {
        ind = j;
        min_dist = dist[j];
      }
    }
    visited[ind] = true;
    for (auto edge : graph[ind]) {
      if (dist[edge.first] > dist[ind] + edge.second) {
        dist[edge.first] = dist[ind] + edge.second;
      }
    }
  }

  int max_time = *max_element(dist.begin() + 1, dist.end());
  if (max_time != INT_MAX) {
    return max_time;
  } else {
    return -1;
  }
}

int main() {
  vector<vector<int>> data1 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
  cout << "case 1 time: " << networkDelayTime(data1, 4, 2) << endl;
  vector<vector<int>> data2 = {{1, 2, 1}};
  cout << "case 2 time: " << networkDelayTime(data2, 2, 1) << endl;
  cout << "case 3 time: " << networkDelayTime(data2, 2, 2) << endl;
}