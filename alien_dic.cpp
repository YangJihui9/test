#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int max_len1;
  vector<bool> hasit;
  vector<set<int>> pre_chars;
  vector<set<int>> post_chars;
  string alienOrder(vector<string> &words) {

    int wlen = words.size();
    int max_len = 'z' - 'a' + 1;
    hasit = vector<bool>(max_len, false);
    pre_chars = vector<set<int>>(max_len, set<int>());
    post_chars = vector<set<int>>(max_len, set<int>());

    int startInd = 0;
    while (startInd < words.size() && words[startInd] == "") {
      ++startInd;
    }
    if (startInd == words.size()) {
      return "";
    }
    auto first = words[startInd][0] - 'a';
    cout << "111" << endl;
    for (int i = startInd; i < wlen - 1; i++) {
      cout << i << endl;
      for (int j = 0; j < words[i].size(); ++j) {
        hasit[words[i][j] - 'a'] = true;
      }
      cout << "3222" << endl;
      for (int ind = 0; ind < words[i].size(); ind++) {
        int next = i + 1;
        if (words[next].size() <= ind) {
          break;
        }
        if (words[i][ind] != words[next][ind]) {
          int pre_ind = words[i][ind] - 'a';
          int post_ind = words[next][ind] - 'a';
          pre_chars[post_ind].insert(pre_ind);
          post_chars[pre_ind].insert(post_ind);
          break;
        }
      }
      cout << "222" << endl;
    }
    cout << "2233" << endl;
    for (int j = 0; j < words[wlen - 1].size(); ++j) {
      hasit[words[wlen - 1][j] - 'a'] = true;
    }
    cout << "333" << endl;
    string res;
    if (add(first, res)) {
      for (int i = 0; i < hasit.size(); ++i) {
        if (hasit[i]) {
          return "";
        }
      }
      return res;
    } else {
      return "";
    }
  }
  bool add(int c, string &res) {
    cout << char(c + 'a') << endl;
    res.push_back(c + 'a');
    hasit[c] = false;
    for (auto it = post_chars[c].begin(); it != post_chars[c].end(); it++) {
      cout << char(*it + 'a') << "prelen: " << pre_chars[*it].size() << endl;

      if (!hasit[*it]) {
        return false;
      }
      pre_chars[*it].erase(c);
      if (pre_chars[*it].size() == 0) {
        add(*it, res);
      }
    }
    return true;
  }
};

int main() {
  vector<string> works{"asd", "basd", "bss", "dab", "sdd"};
  Solution sl;
  string res = sl.alienOrder(works);
  cout << res << endl;
}