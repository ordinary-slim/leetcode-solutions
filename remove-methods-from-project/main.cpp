#include <vector>
#include <cstdio>

using namespace std;

class Solution {
public:
  vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
    /*
    I am given an adjacency list `invocations` describing a directed graph
    I have to compute:
    1. The reachable set of node k
    2. The predecessor set of the reachable set
    The reachable set is marked for removal
    If the predecessor set is a subset of the reachable set, I can remove the reachable set from the graph
    Otherwise, I have to leave the graph intact
    */
    for (vector<int>& pair : invocations) {
    }
    return vector<int>();
    }
};

void print_vector(vector<int>& vec) {
  printf("[");
  for (int el : vec)
    printf(" %i, ", el);
  printf("]\n");
}

int main() {
  Solution sol;
  // Example 1:
  {
    int n = 4;
    int k = 1;
    vector<int> output = {0,1,2,3};
    vector<vector<int>> invocations = {{1,2},{0,1},{3,2}};
    vector<int> result = sol.remainingMethods(n, k, invocations);
    printf("result = ");
    print_vector(result);
    printf("correct = ");
    print_vector(output);
  }

  // Example 2:
  {
    int n = 5;
    int k = 0;
    vector<vector<int>> invocations = {{1,2},{0,2},{0,1},{3,4}};
    vector<int> output = {3,4};
  }


  // Example 3:
  {
    int n = 3;
    int k = 2;
    vector<vector<int>> invocations = {{1,2},{0,1},{2,0}};
    vector<int> output = {};
  }

  return 1;
}
