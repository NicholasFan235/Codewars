#include <bits/stdc++.h>

namespace geo // Vector2
{

class Vector2{
    public:
        double x, y;
    private:
    public:
        Vector2() : x(0), y(0) {}
        Vector2(double _x, double _y) : x(_x), y(_y) {}
        Vector2(const Vector2 &v) : x(v.x), y(v.y) {}
        ~Vector2() = default;
    public:
        double mag() const { return sqrt(x*x+y*y); }
        double mag2() const { return x*x + y*y; }
        double angle() const { return std::fmod(atan2(y, x) + 2.0f * M_PI, 2.0f * M_PI); }
        Vector2& normalize() { *this/=mag(); return *this;};
        Vector2 normalized() const { return *this/mag(); };
 
        Vector2 rotated(double angle) { return Vector2(cos(angle)*x-sin(angle)*y, sin(angle)*x+cos(angle)*y); }

        Vector2 operator+(const Vector2 &v) const{ return Vector2(x+v.x, y+v.y); }
        Vector2 operator-(const Vector2 &v) const{ return Vector2(x-v.x, y-v.y); }
        Vector2 operator+(const double &i) const{ return Vector2(x+i, y+i); }
        Vector2 operator-(const double &i) const { return Vector2(x-i, y-i); }
        Vector2 operator*(const double &i) const { return Vector2(x*i, y*i); }
        Vector2 operator/(const double &i) const { return Vector2(x/i, y/i); }

        Vector2& operator+=(const Vector2 &v) { x+=v.x; y+=v.y; return *this; }
        Vector2& operator-=(const Vector2 &v) { x-=v.x; y-=v.y; return *this; }
        Vector2& operator+=(const double &i) { x+=i; y+=i; return *this; }
        Vector2& operator-=(const double &i) { x-=i; y-=i; return *this; }
        Vector2& operator*=(const double &i) { x*=i; y*=i; return *this; }
        Vector2& operator/=(const double &i) { x/=i; y/=i; return *this; }

        double dot(const Vector2 &v) const{ return x*v.x + y*v.y; }
        double cross(const Vector2 &v) const{ return x*v.x - y*v.y; }

        friend bool operator==(const Vector2 &l, const Vector2 &r) { return l.x==r.x && l.y==r.y; }
        friend bool operator!=(const Vector2 &l, const Vector2 &r) { return l.x!=r.x || l.y!=r.y; }

    private:
        void initialise();
};

double dot(const Vector2& u, const Vector2& v){ return u.dot(v); };
double cross(const Vector2& u, const Vector2& v){ return u.cross(v); };
double mag(const Vector2& v){ return v.mag(); }
double mag2(const Vector2& v){ return v.mag2(); }

const Vector2 operator+(const double &i, const Vector2 &v) { return v+i; }
const Vector2 operator-(const double &i, const Vector2 &v) { return Vector2(i-v.x, i-v.y); }
const Vector2 operator*(const double &i, const Vector2 &v) { return v*i; }

}

class Node{
public:
    std::unordered_map<int, double> links;

    double cost;

    Node():
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

    int addNode(){
        nodes.push_back(Node());
        return nodes.size()-1;
    }

    void addEdge(int n1, int n2, double cost, bool directed = false){
        nodes[n1].addLink(n2, cost);
        if (!directed) nodes[n2].addLink(n1, cost);
    }

    void resetNodes(){
        for (unsigned int i = 0; i < nodes.size(); i++){
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
};


namespace geo // Circle
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
        for (unsigned int i = 0; i < cotangents.size(); i++){
            for (unsigned int j = 0; j < i; j++){
                checkConnection(graph, i, j);
                checkConnection(graph, j, i);
            }
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



class Solution{
public:
    std::vector<geo::Circle*> circles;
    //std::vector<std::pair<geo::Vector2, geo::Vector2>> cotangents;
    Graph graph;
    int startNode; int endNode;

    Solution(): 
        circles(std::vector<geo::Circle*>()),
        graph(Graph()) {}
    ~Solution(){
        for (const auto c : circles) delete c;
    }

    void addStartEnd(const geo::Vector2 &s, const geo::Vector2 &e){
        startNode = addTangents(s);
        endNode = addTangents(e);
        if (!lineIntersects(s, e)){
            graph.addEdge(startNode, endNode, (e-s).mag());
            //cotangents.push_back(std::make_pair(s, e));
        }
    }
    
    void addCircle(double x, double y, double radius) { addCircle(geo::Vector2(x, y), radius); }
    void addCircle(const geo::Vector2 &p, double r){
        geo::Circle* nCircle = new geo::Circle(p, r);
        circles.push_back(nCircle);
    }
    
    void findIntersections(){
        for (unsigned int i = 0; i < circles.size(); i++){
            for (unsigned int j = 0; j < i; j++){
                geo::Vector2 rij = circles[j]->position - circles[i]->position;
                double d2 = rij.mag2();
                double d = sqrt(d2);
                if (d2 > pow(circles[i]->radius + circles[j]->radius, 2.0f)) continue;

                double phii = rij.angle();
                double phij = fmod(phii + M_PI, M_PI*2.0f);
                double dphii = acos((pow(circles[i]->radius, 2.0f)+d2-pow(circles[j]->radius, 2.0f))/(2.0f*circles[i]->radius*d));
                double dphij = acos((pow(circles[j]->radius, 2.0f)+d2-pow(circles[i]->radius, 2.0f))/(2.0f*circles[j]->radius*d));

                circles[i]->addIntersection(fmod(phii-dphii + 2.0f*M_PI, 2.0f*M_PI), fmod(phii+dphii, 2.0f*M_PI));
                circles[j]->addIntersection(fmod(phij-dphij + 2.0f*M_PI, 2.0f*M_PI), fmod(phij+dphij, 2.0f*M_PI));
            }
        }
    }

    void makeCotangents(){
        for (unsigned int i = 0; i < circles.size(); i++){
            for (unsigned int j = 0; j < i; j++){
                makeCotangents(i, j);
            }
        }
    }

    void linkCotangents(){
        for (const auto c : circles){
            c->linkCotangents(&graph);
        }
    }

private:
    int addTangents(const geo::Vector2 &p){
        int nodei = graph.addNode();
        for (unsigned int i = 0; i < circles.size(); i++){
            auto c = circles[i];
            geo::Vector2 r = p-c->position;
            double D = r.mag();
            if (D < c->radius) continue;
            double phi = r.angle();
            double dphi = acos(c->radius/D);

            r.normalize();
            geo::Vector2 t1 = c->position + r.rotated(dphi)*c->radius;
            geo::Vector2 t2 = c->position + r.rotated(-dphi)*c->radius;
            if (!lineIntersects(t1, p, true, {(int)i})){
                int n = graph.addNode();
                c->addCotangent(n, fmod(phi+dphi, 2.0f*M_PI));
                //cotangents.push_back(std::make_pair(t1, p));
                graph.addEdge(n, nodei, (p-t1).mag());
            }
            if (!lineIntersects(t2, p, true, {(int)i})){
                int n = graph.addNode();
                c->addCotangent(n, fmod(phi-dphi+2.0f*M_PI, 2.0f*M_PI));
                //cotangents.push_back(std::make_pair(t2, p));
                graph.addEdge(n, nodei, (p-t2).mag());
            }
        }
        return nodei;
    }

    void makeCotangents(int i, int j){
        double D = (circles[i]->position - circles[j]->position).mag();
        if (D<fabs(circles[i]->radius-circles[j]->radius)) return;
        // Outer cotangents exist
        double outerTheta = acos((circles[i]->radius-circles[j]->radius)/D);
        geo::Vector2 rij = (circles[j]->position - circles[i]->position).normalized();
        double offsetRotation = fmod(atan2(rij.y, rij.x)+2.0f*M_PI, 2.0f*M_PI);
        geo::Vector2 outeri1 = circles[i]->position + rij.rotated(outerTheta)*circles[i]->radius;
        geo::Vector2 outerj1 = circles[j]->position + rij.rotated(outerTheta)*circles[j]->radius;
        geo::Vector2 outeri2 = circles[i]->position + rij.rotated(-outerTheta)*circles[i]->radius;
        geo::Vector2 outerj2 = circles[j]->position + rij.rotated(-outerTheta)*circles[j]->radius;
        if (!lineIntersects(outeri1, outerj1, true, {i, j})){
            int ni = graph.addNode();
            int nj = graph.addNode();
            circles[i]->addCotangent(ni, fmod(offsetRotation + outerTheta, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation + outerTheta, 2.0f*M_PI));
            graph.addEdge(ni, nj, (outerj1-outeri1).mag());
            //cotangents.push_back(std::make_pair(outeri1, outerj1));
        }
        if (!lineIntersects(outeri2, outerj2, true, {i, j})){
            int ni = graph.addNode();
            int nj = graph.addNode();
            circles[i]->addCotangent(ni, fmod(offsetRotation - outerTheta + 2.0f*M_PI, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation - outerTheta + 2.0f*M_PI, 2.0f*M_PI));
            graph.addEdge(ni, nj, (outerj2-outeri2).mag());
            //cotangents.push_back(std::make_pair(outeri2, outerj2));
        }

        if (D<circles[i]->radius+circles[j]->radius) return;
        // Inner cotangents exist
        double innerTheta = acos((circles[i]->radius+circles[j]->radius)/D);
        geo::Vector2 inneri1 = circles[i]->position + rij.rotated(innerTheta)*circles[i]->radius;
        geo::Vector2 innerj1 = circles[j]->position - rij.rotated(innerTheta)*circles[j]->radius;
        geo::Vector2 inneri2 = circles[i]->position + rij.rotated(-innerTheta)*circles[i]->radius;
        geo::Vector2 innerj2 = circles[j]->position - rij.rotated(-innerTheta)*circles[j]->radius;
        if (!lineIntersects(inneri1, innerj1, true, {i, j})){
            int ni = graph.addNode();
            int nj = graph.addNode();
            circles[i]->addCotangent(ni, fmod(offsetRotation + innerTheta, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation + innerTheta + M_PI, 2.0f*M_PI));
            graph.addEdge(ni, nj, (innerj1-inneri1).mag());
            //cotangents.push_back(std::make_pair(inneri1, innerj1));
        }
        if (!lineIntersects(inneri2, innerj2, true, {i, j})){
            int ni = graph.addNode();
            int nj = graph.addNode();
            circles[i]->addCotangent(ni, fmod(offsetRotation - innerTheta + 2.0f*M_PI, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation - innerTheta + 3.0f*M_PI, 2.0f*M_PI));
            graph.addEdge(ni, nj, (innerj2-inneri2).mag());
            //cotangents.push_back(std::make_pair(inneri2, innerj2));
        }
    }

    float closestPoint(const geo::Vector2 &origin, const geo::Vector2 &dir, const geo::Vector2 &target){
        return geo::dot(target-origin, dir.normalized());
    }

    bool lineIntersects(geo::Vector2 p, geo::Vector2 q, bool excluding = false, std::set<int> excludes = {}){
        for (unsigned int i = 0; i < circles.size(); i++){
            if (excluding && excludes.find(i) != excludes.end()) continue;
            auto c = circles[i];
            float dist = (q-p).mag();
            geo::Vector2 dir = (q-p).normalized();
            float t = closestPoint(p, dir, c->position);
            if (t<0) t = 0;
            if (t>dist) t = dist;
            geo::Vector2 closestPoint = p + dir*t;
            float closestApproach = (c->position - closestPoint).mag();
            if (closestApproach < c->radius){
                return true;
            }
        }
        return false;
    }
};



double shortest_path_length(Point a, Point b, const vector<Circle> &c)
{
  Solution solver = Solution();
  
  printf("%f %f %f %f\n", a.x, a.y, b.x, b.y);
  
  printf("%d\n", c.size());
  for (const Circle& cData : c){
    printf("%f %f %f\n", cData.ctr.x, cData.ctr.y, cData.r);
    solver.addCircle(cData.ctr.x, cData.ctr.y, cData.r);
  }
  
  solver.findIntersections();
  solver.makeCotangents();
  solver.addStartEnd(geo::Vector2(a.x, a.y), geo::Vector2(b.x, b.y));
  solver.linkCotangents();
  
  solver.graph.performBfs(solver.startNode);
  double cost = solver.graph.nodes[solver.endNode].cost;
  
  return cost == INFINITY ? -1 : cost;
 
}