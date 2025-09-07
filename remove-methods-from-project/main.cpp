#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

void print_vector(vector<int>& vec) {
  printf("[");
  for (int el : vec)
    printf(" %i, ", el);
  printf("]\n");
}

class Solution {
public:
  vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
    /*
    I am given an adjacency list `invocations` describing a directed graph
    I have to compute 1) the reachable set of node k
    and 2) check that there are no predecessors of this set outside
    of the set
    if 2) is true, remove methods from graph, otherwise leave untouched
    */
    bool safe2remove = true;
    // Invocations is list of directed edges, convert to adjacency list
    vector<vector<int>> direct_successors(n);
    for (size_t j = 0; j < invocations.size(); ++j) {
      int O = invocations[j][0], D = invocations[j][1];
      direct_successors[O].push_back(D);
    }
    // Breadth-first search for direct and indirect successors of k
    bool* is_k_reachable = new bool[n];
    for (size_t j = 0; j < n; ++j) {
      is_k_reachable[j] = false;
    }
    vector<int> k_reachable = {k};
    k_reachable.reserve(n/2);
    queue<int> frontier;
    frontier.push(k);
    is_k_reachable[k] = true;
    while (not(frontier.empty())) {
      int node = frontier.front();
      frontier.pop();
      for (int successor : direct_successors[node]) {
        if (not(is_k_reachable[successor])) {
          frontier.push(successor);
          k_reachable.push_back(successor);
          is_k_reachable[successor] = true;
        }
      }
    }

    for (size_t j = 0; j < invocations.size(); ++j) {
      int O = invocations[j][0], D = invocations[j][1];
      if ((is_k_reachable[D]) and not(is_k_reachable[O])) {
        safe2remove = false;
        break;
      }
    }

    vector<int> methods;
    methods.reserve(n);
    for (size_t j = 0; j < n; ++j) {
      // condition to skip is safe2remove and kreachable
      if (not(safe2remove) || not(is_k_reachable[j])) {
        methods.push_back(j);
      }
    }

    delete[] is_k_reachable;
    return methods;
    }
};

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
    printf("==============================\n");
  }

  // Example 2:
  {
    int n = 5;
    int k = 0;
    vector<vector<int>> invocations = {{1,2},{0,2},{0,1},{3,4}};
    vector<int> output = {3,4};
    vector<int> result = sol.remainingMethods(n, k, invocations);
    printf("result = ");
    print_vector(result);
    printf("correct = ");
    print_vector(output);
    printf("==============================\n");
  }


  // Example 3:
  {
    int n = 3;
    int k = 2;
    vector<vector<int>> invocations = {{1,2},{0,1},{2,0}};
    vector<int> output = {};
    vector<int> result = sol.remainingMethods(n, k, invocations);
    printf("result = ");
    print_vector(result);
    printf("correct = ");
    print_vector(output);
    printf("==============================\n");
  }

  return 1;
}
