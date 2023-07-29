#include "solution.h"
#include <bits/stdc++.h>

geo::Vector2 start;
geo::Vector2 end;
std::vector<std::tuple<double, double, double>> circleData;

void reset(){
    circleData = std::vector<std::tuple<double, double, double>>();
}

void solve(){
    Solution solver = Solution();
    for (const auto cData : circleData){
        solver.addCircle(std::get<0>(cData), std::get<1>(cData), std::get<2>(cData));
    }

    solver.findIntersections();
    solver.makeCotangents();

    solver.addStartEnd(start, end);

    solver.linkCotangents();

    solver.infoDump(std::cout);

    solver.graph.performBfs(solver.startNode);
    std::clog << solver.startNode << " " << solver.endNode << std::endl;
    std::clog << solver.graph.nodes[solver.startNode].links.size() << std::endl;
    std::clog << solver.graph.nodes[solver.endNode].cost << std::endl;
}

int main(){
    reset();

    double startX, startY, endX, endY;
    std::cin >> startX >> startY >> endX >> endY;
    start = geo::Vector2(startX, startY);
    end = geo::Vector2(endX, endY);
    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++){
        double px, py, r;
        std::cin >> px >> py >> r;
        circleData.push_back(std::make_tuple(px, py, r));
    }

    solve();
}