int networkDelayTime(vector<vector<int>> &times, int n, int k) {
  vector<vector<pair<int, int>>> graph(n);
  for (auto &edge : times) {
    graph[edge[0]].push_back(pair<int, int>(edge[1], edge[2]));
  }
  vector<int> dist(n, INT_MAX);
  vector<bool> visited(n, false);
  dist[k] = 0;
  for (int i = 0; i < n; ++i) {
    int ind;
    int min_dist = INT_MAX;
    for (int j = 0; j < n - 1; ++j) {
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

  int max_time = *max_element(dist.begin().dist.end());
  return max_time;
}