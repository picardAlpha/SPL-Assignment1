
#include "../include/Agent.h"
#include "../include/Party.h"
#include "../include/SelectionPolicy.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mCoalitionNumber{agentId}, mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    //put myself as a coalition member
    mCoalitionMembers.push_back(agentId);
    // You can change the implementation of the constructor, but not the signature!
}

Agent::Agent(const Agent& otherAgent, int yourNewPartyID, int newID):
        alreadyOffered{otherAgent.alreadyOffered},
        mCoalitionMembers{otherAgent.mCoalitionMembers},
        mCoalitionNumber{otherAgent.mCoalitionNumber},
        mCoalitionMandates{otherAgent.mCoalitionMandates},
        mAgentId{newID},
        mPartyId{yourNewPartyID},
        mSelectionPolicy{otherAgent.mSelectionPolicy}
        {

        }

void Agent::setCoalitionMandates(int mandates){
    mCoalitionMandates=mandates;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // TODO: implement this method
    // First update you relevant neighbors list. It can only shrink, so you only need to check its members.
    // for(int i=0; i<mRelevantNeighbors.size(); i++){
    //     std::cout << "relevant neighboor no " << i << " is " << mRelevantNeighbors.at(i) <<std::endl; 
    //     if(sim.getParty(mRelevantNeighbors.at(i)).getState() == Joined ||
    //         isPresent(alreadyOffered, mRelevantNeighbors.at(i)) ) { //////REVISE!!!
    //             mRelevantNeighbors.erase(mRelevantNeighbors.begin()+i);
    //     }
    // }
    if(!mRelevantNeighbors.empty()) {
        int partyToOfferIndex = mSelectionPolicy->select(sim.getGraph(), mRelevantNeighbors, mPartyId);

        Party &partyToOffer = sim.getGraph().getParty(mRelevantNeighbors.at(partyToOfferIndex));
        switch (partyToOffer.getState()) {
            
            //Debate weather to give the agent control over party, or design her to maintain herself.
            case Waiting:
                // This could be changed to adding to the offers array in party, and the party herself checking each iteration if the array isn't empty and changing her status.
                partyToOffer.setState(CollectingOffers);
                partyToOffer.addToOffersList(mAgentId);
                alreadyOffered.push_back(mRelevantNeighbors.at(partyToOfferIndex));


                break;
            case CollectingOffers:
                partyToOffer.addToOffersList(mAgentId);
                alreadyOffered.push_back(mRelevantNeighbors.at(partyToOfferIndex));


                break;
            case Joined:
                std::cout << "Something went wrong... Agent no." << mAgentId << " who belongs to party " << mPartyId
                          << " trying to add party no. " << mRelevantNeighbors.at(partyToOfferIndex)
                          << "to its coalition, but it's already in a Joined state." << std::endl;

            default :
                std::cout << "Unidentified Party State." << std::endl;
                break;

        }
    }


    // then use SelectionPolicy to find the next party you should offer to.


    // if the party you offer to in collecting offers state, just add you offer to her offers list.
    // if the party you offer to in Waiting state, change her state to collecting offers and add your offer to her offers list. *****This should be revised.
    // if your relevant neighbors list is empty, do nothing.
}


//added

void Agent::setRelevantNeighbors(vector<int>& relevantNeighbors){
 mRelevantNeighbors=relevantNeighbors;
}

void Agent::addToRelevantNeighbors(int partyID){
    mRelevantNeighbors.push_back(partyID);

}

bool Agent::isPresent(vector<int> &neighborsList, int num) {
    bool found = false;
    for(int i=0; i<neighborsList.size() && !found;i++){
        if(neighborsList.at(i) == num){
            found = true;
        }
    }

    return found;

}




