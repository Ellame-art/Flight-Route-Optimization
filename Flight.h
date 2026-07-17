#pragma once

struct Airport;

struct Flight {
    Airport* destination;
    double distance;
    double duration;
    double price;
    Flight(Airport* d, double dis, double dur, double pr) : destination(d), distance(dis), duration(dur), price(pr) {
        
    }
    void update(Airport* d, double dis, double dur, double pr){
        destination = d;
        distance = dis;
        duration = dur;
        price = pr;
    }
    
};