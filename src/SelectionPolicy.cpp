//
// Created by Lidor Nir Shalom on 19/11/2022.
//


// Will receive graph as reference and vector of relevant neighbors from agent and return the max value according to the type.

#include "../include/SelectionPolicy.h"

//SHOULD I ADD SELECTIONPOLICY:: ??

// ASSUMES RelevantNeighbors vector ISN'T EMPTY!!!
int MandatesSelectionPolicy::select(Graph &graph, vector<int> &relevantNeighbors, int partyID) {
    int max = 0;
    int maxIndex = -1 ;

    for(int i=0; i<relevantNeighbors.size(); i++){
        if(graph.getMandates(relevantNeighbors.at(i))>max){
            max = graph.getMandates(relevantNeighbors.at(i));
            maxIndex = i ;
        }
    }
    // std::cout << "Selection Policy returned party number " << relevantNeighbors.
    return maxIndex;

}

// ASSUMES RelevantNeighbors vector ISN'T EMPTY!!!
int EdgeWeightSelectionPolicy::select(Graph &graph, vector<int> &relevantNeighbors,int partyID) {

    int max = 0;
    int maxIndex = -1 ;

    for(int i=0; i<relevantNeighbors.size(); i++){
        int currEdgeWeight = graph.getEdgeWeight(partyID,relevantNeighbors.at(i));
        if(currEdgeWeight > max){
            max = currEdgeWeight;
            maxIndex = i;
        }

    }
    return maxIndex;
}


