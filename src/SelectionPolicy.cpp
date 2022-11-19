//
// Created by Lidor Nir Shalom on 19/11/2022.
//


// Will receive graph as reference and vector of relevant neighbors from agent and return the max value according to the type.

#include "SelectionPolicy.h"

//SHOULD I ADD SELECTIONPOLICY:: ??

// ASSUMES RelevantNeighbors vector ISN'T EMPTY!!!
int MandatesSelectionPolicy::select(Graph &graph, vector<int> &relevantNeighbors, int partyID) {
    int max = 0;
    int maxIndex = -1 ;

    for(int i=0; i<relevantNeighbors.size(); i++){
        if(graph.getMandates(relevantNeighbors.at(i))>max){
            max=graph.getMandates(relevantNeighbors.at(i));
            maxIndex = i ;
        }
    }

    return maxIndex;

}



// ASSUMES RelevantNeighbors vector ISN'T EMPTY!!!
int EdgeWeightSelectionPolicy::select(Graph &graph, vector<int> &relevantNeighbors,int partyID) {

    int max = 0;
    int maxIndex = -1 ;

    for(int i=0; i<relevantNeighbors.size(); i++){
        if(graph.getEdgeWeight(partyID,relevantNeighbors.at(i)) > max){
            max = graph.getEdgeWeight(partyID,relevantNeighbors.at(i));
            maxIndex = i;
        }

    }
    return maxIndex;
}


