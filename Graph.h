#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Airport.h"
#include "Flight.h"


class Graph{
    unordered_map<string, Airport*> airportMap;
    vector<Airport*> lastRoute;
    double lastDistance;
    double lastDuration;
    double lastPrice;
    int lastStops;
    Airport* lastSource = nullptr;
    Airport* lastDestination = nullptr;
    public:
    Graph();
    ~Graph();
    void ADD_AIRPORT(string& Code, string& Name, string& cty, string& cntry);
    void REMOVE_AIRPORT(string& code);
    void DISPLAY_AIRPORT(const string& airport_code);
    void ADD_FLIGHT(const string& Source, const string& Destination, double& Distance, double& Duration, double& Price);
    void REMOVE_FLIGHT(string& Source, string& Destination);
    void UPDATE_FLIGHT(string& Source, string& Destination, double& Distance, double& Duration, double& Price);
    void SHORTEST_DISTANCE(string& airport_code1, string& airport_code2);
    void FASTEST_ROUTE(string& Source, string& Destination);
    void CHEAPEST_ROUTE(string& Source, string& Destination);
    void MINIMUM_STOPS(string& Source, string& Destination);
    void DISPLAY_ROUTE();
};