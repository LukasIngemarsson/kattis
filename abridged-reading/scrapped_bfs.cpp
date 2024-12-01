// int bfs(vector<int>& adj_list, vector<int>& costs, int n, int start) {
//     vector<int> state(n, INT_MAX);
//     int min_cost = INT_MAX;
//     queue<pair<int, int>> q;
//     q.push({start, costs[start]});

//     while (!q.empty()) {
//         pair<int, int> p = q.front(); q.pop();
//         int curr = p.first, cost = p.second;            
//         if (cost > state[curr]) {
//             continue;
//         }
//         state[curr] = cost;
//         if (adj_list[curr] == 0) {
//             min_cost = min(min_cost, cost);
//             continue;
//         }
//         q.push({adj_list[curr], cost + costs[adj_list[curr]]});
//     }
//     return min_cost;
// }