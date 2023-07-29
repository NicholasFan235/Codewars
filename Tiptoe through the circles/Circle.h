
#include <math.h>
#include <vector>
#include <set>
#include <iostream>
#include "Vector2.h"
#include "Graph.h"

namespace geo
{

class Circle {
public:
    Vector2 position;
    double radius;

    Circle(const Vector2 &p, double r): position(p), radius(r),
        cotangents(std::vector<std::pair<int, double>>()),
        intersections(std::vector<std::pair<double, double>>()),
        links(std::vector<std::pair<double, double>>()) {}
private:
    std::vector<std::pair<int, double>> cotangents;
    std::vector<std::pair<double, double>> intersections;
    std::vector<std::pair<double, double>> links;
public:
    void addIntersection(double phi1, double phi2){
        intersections.push_back(std::make_pair(phi1, phi2));
    }

    void addCotangent(int n, double phi){
        cotangents.push_back(std::make_pair(n, phi));
    }

    void linkCotangents(Graph* graph){
        for (int i = 0; i < cotangents.size(); i++){
            for (int j = 0; j < i; j++){
                checkConnection(graph, i, j);
                checkConnection(graph, j, i);
            }
        }
    }

    void infoDump(std::ostream &out){
        out << position.x << " " << position.y << " " << radius << std::endl;
        out << intersections.size() << std::endl;
        for (const auto i : intersections){
            out << i.first << " " << i.second << std::endl;
        }
        out << links.size() << std::endl;
        for (const auto l : links){
            std::cout << l.first << " " << l.second << std::endl;
        }
    }

private:
    void checkConnection(Graph* graph, int i, int j){
        if (isConnected(cotangents[i].second, cotangents[j].second)){
            double cost = fmod(cotangents[j].second-cotangents[i].second + 2.0f*M_PI, 2.0f*M_PI) * radius;
            links.push_back(std::make_pair(cotangents[i].second, cotangents[j].second));
            graph->addEdge(cotangents[i].first, cotangents[j].first, cost);
            //if (cost < 0.01f) std::clog << i << " -> " << j << ": " << cost << std::endl;
        }
    }

    bool isConnected(double phi1, double phi2){
        std::pair<double, double> query = std::make_pair(phi1, phi2);
        for (const auto interval : intersections){
            if (overlaps(query, interval)) return false;
        }
        return true;
    }

    bool overlaps(const std::pair<double, double> &q, const std::pair<double, double> &i){
        return contains(q.first, i) || contains(q.second, i) ||
            contains(i.first, q) || contains(i.second, q);
    }

    bool contains(double phi, const std::pair<double, double> &interval){
        if (interval.second > interval.first){
            return phi>interval.first && phi<interval.second;
        }
        else{
            return phi>interval.first || phi<interval.second;
        }
    }
};


}