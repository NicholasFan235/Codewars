#include <bits/stdc++.h>

int liftDirection = 1;
int currFloor = 0;
std::set<int> floorQueue;
std::vector<std::vector<int>> queues;
std::vector<std::queue<int>> upQueues, downQueues;
std::vector<int> passengers;
int numPassengers;
int capacity;
std::vector<int> stops;
int totalCustomers;

void addRequestsAhead(int startFloor){
    if (liftDirection == 1){
        for (int i = startFloor; i < queues.size(); i++){
            if (upQueues[i].size() > 0){
                floorQueue.insert(i);
            }
        }
    }
    else{
        for (int i = startFloor; i >= 0; i--){
            if (downQueues[i].size() > 0){
                floorQueue.insert(i);
            }
        }
    }
}

void tryDrop(int floor){
    if (passengers[floor] > 0){
        numPassengers -= passengers[floor];
        totalCustomers -= passengers[floor];
        passengers[floor] = 0;
    }
}

void tryLoad(int floor){
    if (liftDirection == 1){
        while (numPassengers < capacity && !upQueues[floor].empty()){
            numPassengers++;
            int p = upQueues[floor].front();
            upQueues[floor].pop();
            passengers[p]++;
            floorQueue.insert(p);
        }
    }
    if (liftDirection == -1){
        while (numPassengers < capacity && !downQueues[floor].empty()){
            numPassengers++;
            int p = downQueues[floor].front();
            downQueues[floor].pop();
            passengers[p]++;
            floorQueue.insert(p);
        }
    }
}

void tryAdd(int floor){
    if (stops.back() != floor) stops.push_back(floor);
}

void doStop(int floor){
    tryDrop(floor);
    tryLoad(floor);
    tryAdd(floor);
}

void calcUpDownQueues(){
    upQueues = std::vector<std::queue<int>>(queues.size(), std::queue<int>());
    downQueues = std::vector<std::queue<int>>(queues.size(), std::queue<int>());

    for (int i = 0; i < queues.size(); i++){
        for (int j = 0; j < queues[i].size(); j++){
            totalCustomers++;
            if (queues[i][j] > i){
                upQueues[i].push(queues[i][j]);
            }
            else{
                downQueues[i].push(queues[i][j]);
            }
        }
    }
}

std::vector<int> the_lift(std::vector<std::vector<int>> q, int c) {
    capacity = c;
    queues = q;
    passengers = std::vector<int>(q.size());
    stops = {0};

    liftDirection = 1;
    calcUpDownQueues();
    
    while (1){
        if (totalCustomers == 0) break;
        if (liftDirection == -1){
            addRequestsAhead(queues.size()-1);
            while (!floorQueue.empty()){
                doStop(*prev(floorQueue.end()));
                floorQueue.erase(prev(floorQueue.end()));
            }
            liftDirection = 1;
            continue;
        }
        if (liftDirection == 1){
            addRequestsAhead(0);
            while (!floorQueue.empty()){
                doStop(*floorQueue.begin());
                floorQueue.erase(floorQueue.begin());
            }
            liftDirection = -1;
            continue;
        }
    }
    
    tryAdd(0);
    return stops;
}


int main(){
    std::vector<std::vector<int>> queues;
    std::vector<int> result;
    queues = { {}, {}, {1,1}, {}, {}, {}, {} };
    result = the_lift(queues, 5);
    
    for (const int i : result){
        printf("%d ", i);
    }
    std::cout << std::endl;
}