#pragma once
#include "../include/Graph.h"


class SelectionPolicy { ;


public:
    virtual int select(Graph& graph, vector<int>& relevantNeighbors,int partyID){
        return -1;
    }

    virtual ~SelectionPolicy() = default;
};

class MandatesSelectionPolicy: public SelectionPolicy{
    int select(Graph& graph, vector<int>& relevantNeighbors,int partyID) override;


};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    int select(Graph& graph, vector<int>& relevantNeighbors,int partyID) override;

};