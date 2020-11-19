#include <bits/stdc++.h>

int N;
std::vector<std::vector<int>> adj;
std::vector<std::set<int>> links;
std::set<int> squares;

void reset(int n){
    N = n+1;
    squares = std::set<int>();
    adj = std::vector<std::vector<int>>(N, std::vector<int>(N));
    links = std::vector<std::set<int>>(N, std::set<int>());
}

void generateSquares(){
    int i = 0;
    int i2 = 0;
    while (i2 < 2*N){
        i++;
        i2 = i*i;
        squares.insert(i2);
    }
}

void makeGraph(){
    for (int i = 1; i < N; i++){
        for (int j = 1; j < i; j++){
            int s = i+j;
            if (squares.count(s)){
                adj[i][j] = 1;
                adj[j][i] = 1;
                links[i].insert(j);
                links[j].insert(i);
            } 
        }
    }
}

int countConnections(int origin, int node, std::vector<int> &visited){
    int cnt = 0;
    for (int i : links[node]){
        if (visited[i] != 1){
            if (node == origin){
                if (countConnections(origin, i, visited) == 1) cnt++;
            }
            else{
                cnt++;
            }
        }
    }
    return cnt;
}

bool dfs(int node, std::vector<std::vector<int>> &a, std::vector<int> &visited, std::stack<int> &path, int deadEnds){
    path.push(node);
    if (countConnections(-1, node, visited) == 1) deadEnds--;
    //printf("dead ends = %d\n", deadEnds);
    if ((int)path.size() == N-1) return true;
    if (deadEnds > 1) { path.pop(); return false; }

    for (int i = 1; i < N; i++){
        if (a[node][i] != 1) continue;
        if (visited[i] == 1) continue;
        visited[i] = 1;
        //a[node][i] = 0;
        //a[i][node] = 0;
        
        int numConn = countConnections(i, i, visited);

        if (dfs(i, a, visited, path, deadEnds + numConn)){
            return true;
        }
        
        //a[node][i] = 1;
        //a[i][node] = 1;
        visited[i] = 0;
    }
    path.pop();
    return false;
}

std::stack<int> dfsPathUtil(){
    std::stack<int> path;
    // Prioritize possible starts
    std::list<int> starts;
    int deadEnds = 0;
    for (int i = 1; i < N; i++){
        int numNeighbours = links[i].size();
        if (numNeighbours == 0){printf("Error\n"); return std::stack<int>(); }
        else if (numNeighbours == 1) starts.push_front(i);
    }
    deadEnds = starts.size();
    if (starts.empty()){
        for (int i = 1; i < N; i++){
            starts.push_back(i);
        }
    }
    
    if (deadEnds > 2) return std::stack<int>();
    for (auto it = starts.begin(); it != starts.end(); it++){
        printf("Solving with start at %d\n", *it);
        path = std::stack<int>();
        std::vector<int> visited(N);
        visited[*it] = 1;
        std::vector<std::vector<int>> a = adj;
        if (dfs(*it, a, visited, path, deadEnds)) return path;
    }
    return std::stack<int>();
}

std::vector<int> findHamiltonianPathDFS(){
    auto ps = dfsPathUtil();
    std::vector<int> ret;
    while (!ps.empty()){
        ret.push_back(ps.top());
        ps.pop();
    }
    return ret;
}

bool check_using_dp(){
    return false;
}

void printAdj(){
    for (const auto row : adj){
        for (const auto i : row){
            printf("%d ", i);
        }
        printf("\n");
    }
}

std::vector<int> square_sums_row(int n){
    printf("Solve for N = %d\n", n);
    reset(n);
    generateSquares();
    makeGraph();

    std::vector<int> solution = findHamiltonianPathDFS();

    for (const auto i : solution){
        printf("%d ", i);
    }
    printf("\n");

    return solution;
}

int main(){
    std::vector<int> result;
    
    for (int i = 1; i < 100; i++){
        auto start = std::chrono::high_resolution_clock::now();
        result = square_sums_row(i);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        printf("Took %ldu to complete\n\n", std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
    }//*/

    //result = square_sums_row(15);
}