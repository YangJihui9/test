#include <climits>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> memo;
vector<vector<int>> dist;
int gdst;
int inf = 1000;

int findCheap(int src, int k) {
  cout << "source: " << src << ", stops: " << k << endl;
  if (k < 0) {
    cout << "k < 0 src: " << src << ", k:" << k << ", price: " << inf << endl;
    return inf;
  }
  if (memo[src][k] != -1) {
    cout << "mem src: " << src << ", k:" << k << ", price: " << 0 << endl;
    return memo[src][k];
  }
  if (src == gdst) {
    cout << "dst src: " << src << ", k:" << k << ", price: " << 0 << endl;
    return 0;
  }

  int price = inf;
  if (dist[src][gdst] != -1) {
    price = dist[src][gdst];
  }

  for (int i = 0; i < dist.size(); ++i) {
    if (dist[src][i] != -1) {
      price = min(price, dist[src][i] + findCheap(i, k - 1));
    }
  }
  cout << "result src: " << src << ", k:" << k << ", price: " << price << endl;
  memo[src][k] = price;
  return price;
}

int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst,
                      int k) {
  dist.resize(n, vector<int>(n, -1));
  memo.resize(n, vector<int>(k + 2, -1));
  for (auto flight : flights) {
    dist[flight[0]][flight[1]] = flight[2];
  }

  gdst = dst;
  int price = findCheap(src, k);
  cout << "memo:" << endl;
  for (int i = 0; i < memo.size(); ++i) {
    for (int j = 0; j < memo[0].size(); ++j) {
      cout << memo[i][j] << ", ";
    }
    cout << endl;
  }
  cout << "dist:" << endl;
  for (int i = 0; i < dist.size(); ++i) {
    for (int j = 0; j < dist[0].size(); ++j) {
      cout << dist[i][j] << ", ";
    }
    cout << endl;
  }
  return price < inf ? price : -1;
}

int main() {
  vector<vector<int>> f1{{0, 1, 100}, {0, 2, 500}, {1, 2, 100}};
  int a1 = findCheapestPrice(3, f1, 0, 2, 0);
  cout << "case expect 500 : " << a1 << endl;
  int a2 = findCheapestPrice(3, f1, 0, 2, 1);
  cout << "case expect 200 : " << a2 << endl;
}