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


class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        
        // Min-heap to store minimum weight edge at top.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        
        // Track nodes which are included in MST.
        vector<bool> inMST(n);
        
        heap.push({ 0, 0 });
        int mstCost = 0;
        int edgesUsed = 0;
        
        while (edgesUsed < n) {
            pair<int, int> topElement = heap.top();
            heap.pop();
            
            int weight = topElement.first;
            int currNode = topElement.second;
            
            // If node was already included in MST we will discard this edge.
            if (inMST[currNode]) {
                continue;
            }
            
            inMST[currNode] = true;
            mstCost += weight;
            edgesUsed++;
            
            for (int nextNode = 0; nextNode < n; ++nextNode) {
                // If next node is not in MST, then edge from curr node
                // to next node can be pushed in the priority queue.
                if (!inMST[nextNode]) {
                    int nextWeight = abs(points[currNode][0] - points[nextNode][0]) + 
                                     abs(points[currNode][1] - points[nextNode][1]);
                    
                    heap.push({ nextWeight, nextNode });
                }
            }
        }
        
        return mstCost;
    }
};