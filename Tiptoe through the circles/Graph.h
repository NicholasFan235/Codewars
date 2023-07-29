
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>
#include <iostream>

class Node{
public:
    std::unordered_map<int, double> links;
    
    geo::Vector2 pos;
    int circleOwner;

    double cost;

    Node(geo::Vector2 p, int c):
        pos(p), circleOwner(c),
        links(std::unordered_map<int, double>()) {}

    void addLink(int n, double cost){
        if (links.find(n)==links.end()) links.insert(std::make_pair(n, cost));
        else links[n] = fmin(links[n], cost);
        //if (links[n] < 0.01f) std::clog << n << ": " << links[n] << std::endl;
    }
};


class Graph{
public:
    std::vector<Node> nodes;

    Graph(): nodes(std::vector<Node>()) {}

    int addNode(geo::Vector2 pos, int c){
        nodes.push_back(Node(pos, c));
        return nodes.size()-1;
    }

    void addEdge(int n1, int n2, double cost, bool directed = false){
        nodes[n1].addLink(n2, cost);
        if (!directed) nodes[n2].addLink(n1, cost);
    }

    void resetNodes(){
        for (int i = 0; i < nodes.size(); i++){
            nodes[i].cost = INFINITY;
        }
    }

    void performBfs(int startNode){
        resetNodes();
        nodes[startNode].cost = 0.0f;
        std::queue<int> checkQueue;
        checkQueue.push(startNode);
        while (!checkQueue.empty()){
            int currNode = checkQueue.front();
            checkQueue.pop();
            for (const auto l : nodes[currNode].links){
                if (nodes[l.first].cost > nodes[currNode].cost + l.second){
                    nodes[l.first].cost = nodes[currNode].cost + l.second;
                    //std::clog << currNode << " -> " << l.first << ": " << nodes[l.first].cost << std::endl;
                    checkQueue.push(l.first);
                }
            }
        }
    }

    void infoDump(std::ostream &out){
        out << nodes.size() << std::endl;
        for (int i = 0 ; i < nodes.size(); i++){
            out << i << std::endl;
            out << nodes[i].pos.x << " " << nodes[i].pos.y << std::endl;
            out << nodes[i].links.size() << std::endl;
            for (const auto l : nodes[i].links){
                out << l.first << " " << l.second << std::endl;
            }
            out << nodes[i].cost << std::endl;
            //if (nodes[i].cost < 0.01f) std::clog << i << ": " << nodes[i].cost << std::endl;
        }
    }
};
