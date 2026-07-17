#include<iostream>
#include <string>
#include "Flight.h"
#include "Airport.h"
#include "Graph.h"
using namespace std;


int main(){
    int testcase;
    cin>>testcase;
    for(int i = 0; i < testcase; i++){
        int operations;
        cin>>operations;
        Graph network;
        for(int j = 0; j < operations; j++){
            string a;
            if (!(cin >> a)) {
                cout << "Unexpected end of input.\n";
                break;
            }
            if(a == "ADD_AIRPORT"){
                string code, name, city, country;
                cin>>code>>name>>city>>country;
                network.ADD_AIRPORT(code, name, city, country);
            }
            else if(a == "REMOVE_AIRPORT"){
                string code;
                cin>>code;
                network.REMOVE_AIRPORT(code);
            }
            else if(a == "DISPLAY_AIRPORT"){
                string code;
                cin>>code;
                network.DISPLAY_AIRPORT(code);
            }
            else if(a == "ADD_FLIGHT"){
                string source, destination;
                double distance, duration, price;
                cin>>source>>destination>>distance>>duration>>price;
                network.ADD_FLIGHT(source, destination, distance, duration, price);
            }
            else if(a == "REMOVE_FLIGHT"){
                string source, destination;
                cin>>source>>destination;
                network.REMOVE_FLIGHT(source, destination);
            }
            else if(a == "UPDATE_FLIGHT"){
                string source, destination;
                double distance, duration, price;
                cin>>source>>destination>>distance>>duration>>price;
                network.UPDATE_FLIGHT(source, destination, distance, duration, price); 
            }
            else if(a == "SHORTEST_DISTANCE"){
                string source, destination;
                cin>>source>>destination;
                network.SHORTEST_DISTANCE(source, destination);
                cout << '\n';
            }
            else if(a == "FASTEST_ROUTE"){
                string source, destination;
                cin>>source>>destination;
                network.FASTEST_ROUTE(source, destination);
                cout << '\n';
            }
            else if(a == "CHEAPEST_ROUTE"){
                string source, destination;
                cin>>source>>destination;
                network.CHEAPEST_ROUTE(source, destination);
                cout << '\n';
            }
            else if(a == "MINIMUM_STOPS"){
                string source, destination;
                cin>>source>>destination;
                network.MINIMUM_STOPS(source, destination);
                cout << '\n';
            }
            else if(a == "DISPLAY_ROUTE"){
                network.DISPLAY_ROUTE();
            }
            else{
                cout<<"INVALID INPUT\n";
            }
        }
    }
    return 0;
}