//
// Created by Lidor Nir Shalom on 20/11/2022.
//
#include "../include/JoinPolicy.h"


int MandatesJoinPolicy::select(Simulation& simulation, vector<int> &offeringAgentsIDList) {
    int maxMandates = -1;
    int maxMandatesIndex = -1;

    for(int i=0; i<offeringAgentsIDList.size(); i++){
        if(simulation.getAgents().at(offeringAgentsIDList.at(i)).mCoalitionMandates > maxMandates){
            maxMandates = simulation.getAgents().at(offeringAgentsIDList.at(i)).mCoalitionMandates; // ****optimize ** never used warning?
            maxMandatesIndex = i;
        }


    }
    return maxMandatesIndex;


}

int LastOfferJoinPolicy::select(Simulation& simulation, vector<int> &offerAgentsIDList) {

    return offerAgentsIDList.size()-1;
}




