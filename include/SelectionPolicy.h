#pragma once
#include "Graph.h"


class SelectionPolicy { ;


public:
    virtual int select(Graph& graph, vector<int>& relevantNeighbors,int partyID){
        return -1;
    }
};

class MandatesSelectionPolicy: public SelectionPolicy{
    virtual int select(Graph& graph, vector<int>& relevantNeighbors,int partyID) override;


};

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    virtual int select(Graph& graph, vector<int>& relevantNeighbors,int partyID) override;

};