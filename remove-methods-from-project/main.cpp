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
    I have to compute:
    1. The reachable set of node k
    2. The predecessor set of the reachable set
    The reachable set is marked for removal
    If the predecessor set is a subset of the reachable set, I can remove the reachable set from the graph
    Otherwise, I have to leave the graph intact
    */
    // Invocations is list of directed edges, convert to adjacency lists
    vector<vector<int>> direct_successors(n), direct_predecessors(n);
    for (size_t j = 0; j < invocations.size(); ++j) {
      int O = invocations[j][0], D = invocations[j][1];
      direct_successors[O].push_back(D);
      direct_predecessors[D].push_back(O);
    }
    // Breadth-first search for direct and indirect successors of k
    bool* mark_visited = new bool[n];
    for (size_t j = 0; j < n; ++j)
      mark_visited[j] = false;
    std::vector<int> k_reachable = {k};
    queue<int> frontier;
    frontier.push(k);
    mark_visited[k] = true;
    while (not(frontier.empty())) {
      int node = frontier.front();
      frontier.pop();
      for (int successor : direct_successors[node]) {
        if (not(mark_visited[successor])) {
          frontier.push(successor);
          k_reachable.push_back(successor);
          mark_visited[successor] = true;
        }
      }
    }

    // Breadth-first search for direct and indirect predecessors of
    // `k_reachable` that are NOT in `k_reachable`
    bool* is_k_reachable = new bool[n];
    for (size_t j = 0; j < n; ++j) {
      mark_visited[j] = false;
      is_k_reachable[j] = false;
    }
    for (int kreachable : k_reachable) {
      is_k_reachable[kreachable] = true;
      frontier.push(kreachable);
      mark_visited[kreachable] = true;
    }

    bool safe2remove = true;
    while (not(frontier.empty())) {
      int node = frontier.front();
      frontier.pop();
      for (int predecessor : direct_predecessors[node]) {
        if (not(is_k_reachable[predecessor])) {
          safe2remove = false;
          break;
        }
        if (not(mark_visited[predecessor])) {
          frontier.push(predecessor);
          mark_visited[predecessor] = true;
        }
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

    delete[] mark_visited, is_k_reachable;
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
