#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
  int minCostConnectPoints(vector<vector<int>> &points) {
    int n = points.size();

    // Min-heap to store minimum weight edge at top.
    priority_queue<pair<int, int>, vector<pair<int, int>>,
                   greater<pair<int, int>>>
        heap;

    // Track nodes which are included in MST.
    vector<bool> inMST(n);

    heap.push({0, 0});
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

          heap.push({nextWeight, nextNode});
        }
      }
    }

    return mstCost;
  }
};

int minCostConnectPoints(vector<vector<int>> &points) {
  vector<vector<int>> edges;
  int len = points.size();
  edges.reserve(len * (len - 1) / 2);

  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; ++j) {
      int dist = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
                 (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
      vector<int> edge{i, j, dist};
      edges.push_back(move(edge));
    }
  }

  sort(edges.begin(), edges.end(),
       [](vector<int> a, vector<int> b) { return a[2] < b[2]; });

  vector<int> parent(len, -1);
  vector<vector<int>> children(len);
  int count = 0;
  int cost = 0;
  for (auto edge : edges) {
    if (count == len - 1) {
      break;
    }
    int i = edge[0];
    int j = edge[1];
    if (parent[i] == -1 || parent[i] != parent[j]) {
      cost += edge[2];
      ++count;
      if (parent[i] == -1 && parent[j] == -1) {
        parent[i] = i;
        parent[j] = i;
        children[i].push_back(j);
      } else if (parent[i] == -1) {
        parent[i] = parent[j];
        children[parent[j]].push_back(i);
      } else if (parent[j] == -1) {
        parent[j] = parent[i];
        children[parent[i]].push_back(j);
      } else {
        int a_ind = parent[i];
        int s_ind = parent[j];
        if (children[a_ind].size() < children[s_ind].size()) {
          int temp = a_ind;
          a_ind = s_ind;
          s_ind = temp;
        }
        parent[s_ind] = a_ind;
        for (int child : children[s_ind]) {
          parent[child] = a_ind;
        }
        children[a_ind].reserve(children[a_ind].size() +
                                children[s_ind].size());
        children[a_ind].insert(children[a_ind].end(), children[s_ind].begin(),
                               children[s_ind].end());
        children[s_ind].clear();
      }
    }
  }

  if (count == len - 1) {
    return cost;
  } else {
    return -1;
  }
}

using EdgeT = pair<int, int>;
int minCostConnect(vector<vector<int>> &points) {
  if (points.size() == 0) {
    return 0;
  }

  int len = points.size();
  vector<vector<EdgeT>> graph(len);
  for (int i = 0; i < len; ++i) {
    graph[i].reserve(len - 1);
  }

  for (int i = 0; i < len; ++i) {
    for (int j = i + 1; j < len; ++j) {
      int dis = (points[i][0] - points[j][0]) * (points[i][0] - points[j][0]) +
                (points[i][1] - points[j][1]) * (points[i][1] - points[j][1]);
      graph[i].push_back(EdgeT(j, dis));
      graph[j].push_back(EdgeT(i, dis));
    }
  }
  for (int i = 0; i < len; ++i) {
    sort(graph[i].begin(), graph[i].end(),
         [](EdgeT a, EdgeT b) { return a.second < b.second; });
  }
  vector<bool> conn(len, false);
  int cost;
  int count = 1;
  conn[0] = true;

  vector<EdgeT> aEdge = move(graph[0]);
  while (count < len) {
    EdgeT &now = aEdge[0];
    conn[now.first] = true;
    cost += now.second;
    count++;
    if (count == len) {
      break;
    }

    vector<EdgeT> temp;
    vector<EdgeT> &bEdge = graph[now.first];
    temp.reserve(aEdge.size() - 1 + bEdge.size() - 1);
    int i = 1;
    int j = 0;
    while (1) {
      while (conn[aEdge[i].first] && i < aEdge.size()) {
        ++i;
      }

      while (conn[bEdge[j].first] && i < bEdge.size()) {
        ++j;
      }

      if (i < len - 1 && j < len - 1) {
        if (aEdge[i].second < bEdge[j].second) {
          temp.push_back(aEdge[i]);
          ++i;
        } else {
          temp.push_back(bEdge[j]);
          ++j;
        }
      } else {
        break;
      }
    }

    while (i < len - 1) {
      if (!conn[aEdge[i].first]) {
        temp.push_back(aEdge[i]);
      }
      ++i;
    }

    while (j < len - 1) {
      if (!conn[bEdge[j].first]) {
        temp.push_back(bEdge[j]);
      }
      ++i;
    }

    aEdge = move(temp);
  }

  return cost;
}

class Solution {
public
  int findCheapestPrice(int n, int[][] flights, int src, int dst, int K) {
    // Build the adjacency matrix
    int adjMatrix[][] = new int[n][n];
    for (int[] flight : flights) {
      adjMatrix[flight[0]][flight[1]] = flight[2];
    }
    // Shortest distances array
    int[] distances = new int[n];
    // Shortest steps array
    int[] currentStops = new int[n];
    Arrays.fill(distances, Integer.MAX_VALUE);
    Arrays.fill(currentStops, Integer.MAX_VALUE);
    distances[src] = 0;
    currentStops[src] = 0;
    // The priority queue would contain (node, cost, stops)
    PriorityQueue<int[]> minHeap =
        new PriorityQueue<int[]>((a, b)->a[1] - b[1]);
    minHeap.offer(new int[]{src, 0, 0});
    while (!minHeap.isEmpty()) {
      int[] info = minHeap.poll();
      int node = info[0], stops = info[2], cost = info[1];
      // If destination is reached, return the cost to get here
      if (node == dst) {
        return cost;
      }
      // If there are no more steps left, continue
      if (stops == K + 1) {
        continue;
      }
      // Examine and relax all neighboring edges if possible
      for (int nei = 0; nei < n; nei++) {
        if (adjMatrix[node][nei] > 0) {
          int dU = cost, dV = distances[nei], wUV = adjMatrix[node][nei];
          // Better cost?
          if (dU + wUV < dV) {
            minHeap.offer(new int[]{nei, dU + wUV, stops + 1});
            distances[nei] = dU + wUV;
          } else if (stops < currentStops[nei]) {
            // Better steps?
            minHeap.offer(new int[]{nei, dU + wUV, stops + 1});
          }
          currentStops[nei] = stops;
        }
      }
    }
    return distances[dst] == Integer.MAX_VALUE ? -1 : distances[dst];
  }
}
