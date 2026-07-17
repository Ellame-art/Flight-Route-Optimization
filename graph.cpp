#include<iostream>
#include<vector>
#include <cfloat>
#include <queue>
#include <algorithm>
#include "Flight.h"
#include "Airport.h"
#include "Graph.h"
using namespace std;


Graph :: Graph(){

}

Graph :: ~Graph(){
    for (auto &entry : airportMap) {
        auto &flights = entry.second->outgoingFlights;
        for (auto fit : flights ) {
            delete fit;
        }
        delete entry.second;
    }
}

void Graph :: ADD_AIRPORT(string& Code, string& Name, string& cty, string& cntry){
    if (airportMap.find(Code) != airportMap.end()) {
        cout << "Airport already exists.\n";
        return;
    }
    airportMap[Code] = new Airport(Code, Name, cty, cntry);
    cout<<"Airport added Successfully\n";
}

void Graph :: REMOVE_AIRPORT(string& code){ // need changes
    auto it = airportMap.find(code);
    if (it == airportMap.end()){
        cout<<"Airport doesn't exist.\n";
        return;
    }
    for(auto f : it->second->outgoingFlights){
        delete f;
    }
    for (auto &entry : airportMap) {
        if(entry.second == it->second) continue;
        auto &flights = entry.second->outgoingFlights;
        for (auto fit = flights.begin(); fit != flights.end(); ) {
            if ((*fit)->destination == it->second) {
                delete *fit;
                fit = flights.erase(fit);
            } 
            else ++fit;
        }
    }
    delete it->second;
    airportMap.erase(code);
    cout<<"Airport removed successflly\n";
}

void Graph :: DISPLAY_AIRPORT(const string& airport_code){
    auto ite = airportMap.find(airport_code);
    if(ite == airportMap.end()) {
        cout<<"Airport doesn't exist"<<endl;
        return;
    }
    Airport* node = ite->second;
    cout<<"Airport: "<<node->airportCode<<" ("<<node->airportName<<")\n";
    cout<<"City: "<<node->city<<endl;
    cout<<"Country: "<<node->country<<endl;
    if (node->outgoingFlights.empty()) {
        cout << "No outgoing flights.\n";
        return;
    }
    else cout << "Outgoing Flights:\n";
    for(auto it : node->outgoingFlights){
        // To: BOM | Distance: 1148 km | Time: 2.1 h | Price: 5200
        cout<<"To: "<<it->destination->airportCode<<" | Distance: "<<it->distance<<" km | Time: "<<it->duration<<" h | Price: "<<it->price<<endl;
    }
}

void Graph :: ADD_FLIGHT(const string& Source, const string& Destination, double& Distance, double& Duration, double& Price){
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    for (Flight* flight : src->second->outgoingFlights) {
        if (flight->destination == des->second) {
            cout << "Flight already exists.\n";
            return;
        }
    }
    Flight* new_f = new Flight(des->second, Distance, Duration, Price);
    src->second->outgoingFlights.push_back(new_f);
    cout << "Flight added successfully.\n";
}

void Graph :: REMOVE_FLIGHT(string& Source, string& Destination){ 
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    bool found = false;
    auto& flights = src->second->outgoingFlights;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        if ((*it)->destination == des->second) {
            delete *it;
            flights.erase(it);
            found = true;
            break;   // iterator is invalid after erase
        }
    }
    if(!found) cout<<"flight doesn't exist";
    else cout << "Flight removed successfully.\n";
}

void Graph :: UPDATE_FLIGHT(string& Source, string& Destination, double& Distance, double& Duration, double& Price){
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    bool found = false;
    for(auto it : src->second->outgoingFlights){
        if(it->destination == des->second){
            it->distance = Distance;
            it->duration = Duration;
            it->price = Price;
            found = true;
            break;
        }
    }
    if(!found) cout<<"flight doesn't exist";
    else cout << "Flight updated successfully.\n";
}

void Graph :: SHORTEST_DISTANCE(string& Source, string& Destination){
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    lastSource = src->second;
    lastDestination = des->second;
    priority_queue<pair<double, Airport*>, vector<pair<double, Airport*>>, greater<pair<double, Airport*>>> pq;
    pq.push({0,src->second});
    unordered_map<Airport*, double> dist;
    unordered_map<Airport*, double> durt;
    unordered_map<Airport*, double> prc;
    unordered_map<Airport*, Airport*> parent;
    for(auto it : airportMap){
        dist[it.second] = DBL_MAX;
    }
    dist[src->second] = 0;
    while(!pq.empty()){
        auto current = pq.top();
        double dis = current.first;
        Airport* airport = current.second;
        pq.pop();
        if(dis > dist[airport]) continue;
        if(airport == des->second){
            lastDistance = dis;
            break;
        }
        for(auto it : airport->outgoingFlights){
            double newdis = dis + it->distance;
            auto newair = it->destination;
            if(newdis < dist[newair]){
                dist[newair] = newdis;
                parent[newair] = airport;
                durt[newair] = it->duration;
                prc[newair] = it->price;
                pq.emplace(newdis, newair);
            }
        }
    }
    lastRoute.clear();
    lastDuration = 0, lastPrice = 0, lastStops = 0;
    Airport* temp = des->second;
    if(dist[des->second] == DBL_MAX){
        cout << "No route exists\n";
        return;
    }
    while(temp!= src->second){
        lastRoute.push_back(temp);
        lastDuration += durt[temp], lastPrice += prc[temp];
        temp = parent[temp];
    }
    lastRoute.push_back(src->second);
    lastStops = max(0, (int)lastRoute.size()-2);
    reverse(lastRoute.begin(), lastRoute.end());
}

void Graph :: FASTEST_ROUTE(string& Source, string& Destination){
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    lastSource = src->second;
    lastDestination = des->second;
    priority_queue<pair<double, Airport*>, vector<pair<double, Airport*>>, greater<pair<double, Airport*>>> pq;
    pq.push({0,src->second});
    unordered_map<Airport*, double> dist;
    unordered_map<Airport*, double> durt;
    unordered_map<Airport*, double> prc;
    unordered_map<Airport*, Airport*> parent;
    for(auto it : airportMap){
        durt[it.second] = DBL_MAX;
    }
    durt[src->second] = 0;
    dist[src->second] = 0;
    prc[src->second] = 0;
    while(!pq.empty()){
        auto current = pq.top();
        double dur = current.first;
        Airport* airport = current.second;
        pq.pop();
        if(dur > durt[airport]) continue;
        if(airport == des->second){
            break;
        }
        for(auto it : airport->outgoingFlights){
            double newdur = dur + it->duration;
            auto newair = it->destination;
            if(newdur < durt[newair]){
                durt[newair] = newdur;
                parent[newair] = airport;
                dist[newair] = it->distance;
                prc[newair] = it->price;
                pq.emplace(newdur, newair);
            }
        }
    }
    lastRoute.clear();
    lastDistance = 0, lastPrice = 0, lastStops = 0, lastDuration = 0;
    Airport* temp = des->second;
    if(durt[des->second] == DBL_MAX){
        cout << "No route exists\n";
        return;
    }
    lastDuration = durt[des->second];
    while(temp!= src->second){
        lastRoute.push_back(temp);
        lastDistance += dist[temp], lastPrice += prc[temp];
        temp = parent[temp];
    }
    lastRoute.push_back(src->second);
    lastStops = max(0, (int)lastRoute.size()-2);
    reverse(lastRoute.begin(), lastRoute.end());
}

void Graph :: CHEAPEST_ROUTE(string& Source, string& Destination){
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    lastSource = src->second;
    lastDestination = des->second;
    priority_queue<pair<double, Airport*>, vector<pair<double, Airport*>>, greater<pair<double, Airport*>>> pq;
    pq.push({0,src->second});
    unordered_map<Airport*, double> dist;
    unordered_map<Airport*, double> durt;
    unordered_map<Airport*, double> prc;
    unordered_map<Airport*, Airport*> parent;
    for(auto it : airportMap){
        prc[it.second] = DBL_MAX;
    }
    durt[src->second] = 0;
    dist[src->second] = 0;
    prc[src->second] = 0;
    while(!pq.empty()){
        auto current = pq.top();
        double price = current.first;
        Airport* airport = current.second;
        pq.pop();
        if(price > prc[airport]) continue;
        if(airport == des->second){
            break;
        }
        for(auto it : airport->outgoingFlights){
            double newprc = price + it->price;
            auto newair = it->destination;
            if(newprc < prc[newair]){
                prc[newair] = newprc;
                parent[newair] = airport;
                dist[newair] = it->distance;
                durt[newair] = it->duration;
                pq.emplace(newprc, newair);
            }
        }
    }
    lastRoute.clear();
    lastDistance = 0, lastPrice = 0, lastStops = 0, lastDuration = 0;
    Airport* temp = des->second;
    if(prc[des->second] == DBL_MAX){
        cout << "No route exists\n";
        return;
    }
    lastPrice = prc[des->second];
    while(temp!= src->second){
        lastRoute.push_back(temp);
        lastDistance += dist[temp], lastDuration += durt[temp];
        temp = parent[temp];
    }
    lastRoute.push_back(src->second);
    lastStops = max(0, (int)lastRoute.size()-2);
    reverse(lastRoute.begin(), lastRoute.end());
}

void Graph :: MINIMUM_STOPS(string& Source, string& Destination){
    auto src = airportMap.find(Source);
    auto des = airportMap.find(Destination);
    if(src == airportMap.end() || des == airportMap.end()){
        cout<<"Source/ Destination doesn't exist\n";
        return;
    }
    lastSource = src->second;
    lastDestination = des->second;
    
    unordered_map<Airport*, double> dist;
    unordered_map<Airport*, double> durt;
    unordered_map<Airport*, double> prc;
    unordered_map<Airport*, Airport*> parent;
    unordered_map<Airport*, bool> visited;
    queue<Airport*> q;
    visited[src->second] = true;
    q.push(src->second);
    durt[src->second] = 0;
    dist[src->second] = 0;
    prc[src->second] = 0;
    while(!q.empty()){
        Airport* airport = q.front();
        q.pop();
        if(airport == des->second){
            break;
        }
        for(auto it : airport->outgoingFlights){
            auto newair = it->destination;
            if(!visited[newair]){
                prc[newair] = it->price;
                parent[newair] = airport;
                dist[newair] = it->distance;
                durt[newair] = it->duration;
                q.push(newair);
                visited[newair] = true;
            }
        }
    }
    lastRoute.clear();
    lastDistance = 0, lastPrice = 0, lastStops = 0, lastDuration = 0;
    Airport* temp = des->second;
    if(!visited[des->second]){
        cout << "No route exists\n";
        return;
    }
    while(temp!= src->second){
        lastRoute.push_back(temp);
        lastDistance += dist[temp], lastDuration += durt[temp];
        lastPrice += prc[temp];
        temp = parent[temp];
    }
    lastRoute.push_back(src->second);
    lastStops = max(0, (int)lastRoute.size()-2);
    reverse(lastRoute.begin(), lastRoute.end());
}

void Graph :: DISPLAY_ROUTE(){
    if(lastRoute.empty()){
        cout<<"Last route wasn't successful\n";
        return;
    }
    cout << "Source      : " << lastSource->airportCode << '\n';
    cout << "Destination : " << lastDestination->airportCode << '\n';
    cout << "Route       : ";
    for (size_t i = 0; i < lastRoute.size(); i++) {
        cout << lastRoute[i]->airportCode;
        if (i != lastRoute.size() - 1)
            cout << " -> ";
    }
    cout << '\n';
    cout << "Distance    : " << lastDistance << " km\n";
    cout << "Duration    : " << lastDuration << " hours\n";
    cout << "Price       : Rs. " << lastPrice << '\n';
    cout << "Stops       : " << lastStops << '\n'; 
}