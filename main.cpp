#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

// ==============================
// 邊的資料結構
// ==============================
struct Edge {
    int to;
    int weight;
};

// ==============================
// 回復路徑用
// ==============================
void printPath(const vector<int>& parent, int v, const vector<string>& name) {
    // 基礎情況：如果沒有前驅節點，代表走到起點了，直接印出節點名稱
    if (parent[v] == -1) {
        cout << name[v];
        return;
    }
    // 遞迴尋找前驅節點，先印出前面的路徑
    printPath(parent, parent[v], name);
    // 加上箭頭並印出當前節點
    cout << " -> " << name[v];
}

// ==============================
// 最短路徑 DP
// ==============================
void shortestPathDP(const vector<vector<Edge>>& graph,
                    const vector<int>& topo,
                    int source,
                    int target,
                    const vector<string>& name) {
    const int INF = numeric_limits<int>::max() / 2;
    int n = graph.size();

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);

    // Step 1. 初始化
    dist[source] = 0;

    // Step 2. 依照 topo 順序做 DP
    for (int u : topo) {
        if (dist[u] != INF) {
            for (const auto& edge : graph[u]) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }

    cout << "Shortest Path DP\n";
    cout << "Distance = ";

    if (dist[target] >= INF / 2) {
        cout << "INF\n";
        cout << "Path: No path\n\n";
    } else {
        cout << dist[target] << "\n";
        cout << "Path: ";
        printPath(parent, target, name);
        cout << "\n\n";
    }
}

// ==============================
// 最長路徑 DP
// DAG 中可直接用 DP 解
// ==============================
void longestPathDP(const vector<vector<Edge>>& graph,
                   const vector<int>& topo,
                   int source,
                   int target,
                   const vector<string>& name) {
    const int NEG_INF = numeric_limits<int>::min() / 2;
    int n = graph.size();

    vector<int> dist(n, NEG_INF);
    vector<int> parent(n, -1);

    // Step 1. 初始化
    dist[source] = 0;

    // Step 2. 依照 topo 順序做 DP
    for (int u : topo) {
        if (dist[u] != NEG_INF) {
            for (const auto& edge : graph[u]) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight > dist[v]) {
                    dist
