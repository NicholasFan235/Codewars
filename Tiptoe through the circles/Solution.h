#include "Circle.h"
#include <iostream>
#include <set>

class Solution{
public:
    std::vector<geo::Circle*> circles;
    std::vector<std::pair<geo::Vector2, geo::Vector2>> cotangents;
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
            cotangents.push_back(std::make_pair(s, e));
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

    void infoDump(std::ostream &out){
        out << circles.size() << std::endl;
        for (const auto c : circles){
            c->infoDump(out);
        }

        out << cotangents.size() << std::endl;
        for (const auto c : cotangents){
            out << c.first.x << " " << c.first.y << " " << c.second.x << " " << c.second.y << std::endl;
        }

        graph.infoDump(out);
    }

    void linkCotangents(){
        for (const auto c : circles){
            c->linkCotangents(&graph);
        }
    }

private:
    int addTangents(const geo::Vector2 &p){
        int nodei = graph.addNode(p, -1);
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
                int n = graph.addNode(t1, i);
                c->addCotangent(n, fmod(phi+dphi, 2.0f*M_PI));
                cotangents.push_back(std::make_pair(t1, p));
                graph.addEdge(n, nodei, (p-t1).mag());
            }
            if (!lineIntersects(t2, p, true, {(int)i})){
                int n = graph.addNode(t2, i);
                c->addCotangent(n, fmod(phi-dphi+2.0f*M_PI, 2.0f*M_PI));
                cotangents.push_back(std::make_pair(t2, p));
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
            int ni = graph.addNode(outeri1, i);
            int nj = graph.addNode(outerj1, j);
            circles[i]->addCotangent(ni, fmod(offsetRotation + outerTheta, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation + outerTheta, 2.0f*M_PI));
            graph.addEdge(ni, nj, (outerj1-outeri1).mag());
            cotangents.push_back(std::make_pair(outeri1, outerj1));
        }
        if (!lineIntersects(outeri2, outerj2, true, {i, j})){
            int ni = graph.addNode(outeri2, i);
            int nj = graph.addNode(outerj2, j);
            circles[i]->addCotangent(ni, fmod(offsetRotation - outerTheta + 2.0f*M_PI, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation - outerTheta + 2.0f*M_PI, 2.0f*M_PI));
            graph.addEdge(ni, nj, (outerj2-outeri2).mag());
            cotangents.push_back(std::make_pair(outeri2, outerj2));
        }

        if (D<circles[i]->radius+circles[j]->radius) return;
        // Inner cotangents exist
        double innerTheta = acos((circles[i]->radius+circles[j]->radius)/D);
        geo::Vector2 inneri1 = circles[i]->position + rij.rotated(innerTheta)*circles[i]->radius;
        geo::Vector2 innerj1 = circles[j]->position - rij.rotated(innerTheta)*circles[j]->radius;
        geo::Vector2 inneri2 = circles[i]->position + rij.rotated(-innerTheta)*circles[i]->radius;
        geo::Vector2 innerj2 = circles[j]->position - rij.rotated(-innerTheta)*circles[j]->radius;
        if (!lineIntersects(inneri1, innerj1, true, {i, j})){
            int ni = graph.addNode(inneri1, i);
            int nj = graph.addNode(innerj1, j);
            circles[i]->addCotangent(ni, fmod(offsetRotation + innerTheta, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation + innerTheta + M_PI, 2.0f*M_PI));
            graph.addEdge(ni, nj, (innerj1-inneri1).mag());
            cotangents.push_back(std::make_pair(inneri1, innerj1));
        }
        if (!lineIntersects(inneri2, innerj2, true, {i, j})){
            int ni = graph.addNode(inneri2, i);
            int nj = graph.addNode(innerj2, j);
            circles[i]->addCotangent(ni, fmod(offsetRotation - innerTheta + 2.0f*M_PI, 2.0f*M_PI));
            circles[j]->addCotangent(nj, fmod(offsetRotation - innerTheta + 3.0f*M_PI, 2.0f*M_PI));
            graph.addEdge(ni, nj, (innerj2-inneri2).mag());
            cotangents.push_back(std::make_pair(inneri2, innerj2));
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
