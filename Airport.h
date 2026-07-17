#pragma once

#include <string>
#include <vector>
using namespace std;

struct Flight;
struct Airport {
    string airportCode;
    string airportName;
    string city;
    string country;
    vector<Flight*> outgoingFlights;
    Airport(string Code, string Name, string cty, string cntry) : airportCode(Code), airportName(Name), city(cty), country(cntry){
    }
};