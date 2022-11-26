
#include "../include/Agent.h"
#include "../include/Party.h"
#include "../include/SelectionPolicy.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mCoalitionNumber{agentId}, mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    //put myself as a coalition member
    mCoalitionMembers.push_back(partyId);
    // You can change the implementation of the constructor, but not the signature!
}

Agent::Agent(const Agent& otherAgent, int yourNewPartyID, int newID):
        mCoalitionMembers{otherAgent.mCoalitionMembers},
        mCoalitionNumber{otherAgent.mCoalitionNumber},
        mCoalitionMandates{otherAgent.mCoalitionMandates},
        alreadyOffered{otherAgent.alreadyOffered},
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
    std::cout << "Agent " << mAgentId << ": UPDATING. Already offered parties are : " ;
    for(int party : alreadyOffered){
        std::cout << party << " " ;
    }
    std::cout << std::endl;
    std::cout << "I'm agent no " << mAgentId << " (party  " << mPartyId << "). My relevant neighbors are : [" ;
    for(int i=0 ; i<mRelevantNeighbors.size(); i++){
        std::cout << mRelevantNeighbors.at(i) << " " ;
    }
    std::cout <<"]"<< std::endl;

    for(int i=0; i<mRelevantNeighbors.size(); i++){ // NOT ERASING ALREADY OFFERED PARTIES!
//         std::cout << "Relevant neighbor no " << i << " is " << mRelevantNeighbors.at(i) <<std::endl;

         if(sim.getParty(mRelevantNeighbors.at(i)).getState() == Joined ||
             isPresent(alreadyOffered, mRelevantNeighbors.at(i)) ) { //////REVISE!!!
             std::cout << "I need to remove party no. "<< mRelevantNeighbors.at(i) << " from my relevant neighbors list." <<std::endl;
                 mRelevantNeighbors.erase(mRelevantNeighbors.begin()+i);
                 i--;
         }
     }
    if(!mRelevantNeighbors.empty()) {
        std::cout << "I'm agent no " << mAgentId << " (party  " << mPartyId << "). My relevant neighbors are : [" ;
        for(int i=0 ; i<mRelevantNeighbors.size(); i++){
            std::cout << mRelevantNeighbors.at(i) << " " ;
        }
        std::cout <<"]"<< std::endl;


        int partyToOfferIndex = mSelectionPolicy->select(sim.getGraph(), mRelevantNeighbors, mPartyId);
        Party &partyToOffer = sim.getGraph().getParty(mRelevantNeighbors.at(partyToOfferIndex));
        switch (partyToOffer.getState()) {
            
            //Debate weather to give the agent control over party, or design her to maintain herself.
            case Waiting:
                // This could be changed to adding to the offers array in party, and the party herself checking each iteration if the array isn't empty and changing her status.
                partyToOffer.setState(CollectingOffers);
                partyToOffer.addToOffersList(mAgentId);
                addToAlreadyOffered(mRelevantNeighbors.at(partyToOfferIndex));
                std::cout << "Agent " << mAgentId<< "(party " << mPartyId<<"): I changed party "<< mRelevantNeighbors.at(partyToOfferIndex)<<" to CollectingOffers state and made the offer." <<std::endl;
                std::cout << "--------Agent " << mAgentId << "(party "<<mPartyId<<") offered party " << mRelevantNeighbors.at(partyToOfferIndex) <<"--------"<<std::endl;


                break;
            case CollectingOffers:
                partyToOffer.addToOffersList(mAgentId);
                addToAlreadyOffered(mRelevantNeighbors.at(partyToOfferIndex));
                std::cout << "Agent " << mAgentId<< "(party "<<mPartyId<<"): I made an offer to party "<< mRelevantNeighbors.at(partyToOfferIndex)<<". It was already in CollectingOrders state." <<std::endl;
                std::cout << "--------Agent " << mAgentId << "(party "<<mPartyId<<"): offered party " << mRelevantNeighbors.at(partyToOfferIndex) <<"--------"<<std::endl;




                break;
            case Joined:
                std::cout << "Something went wrong... Agent no." << mAgentId << " (party  " << mPartyId
                          << ") trying to add party no. " << mRelevantNeighbors.at(partyToOfferIndex)
                          << " to its coalition, but it's already in a Joined state." << std::endl;
                break;

            default :
                std::cout << "Unidentified Party State for party no." << partyToOffer.getPartyID() << std::endl;
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

bool Agent::isPresent(vector<int> &alreadyOffered, int num) {
    bool found = false;
    for(int i=0; i<alreadyOffered.size() && !found;i++){
        if(alreadyOffered.at(i) == num){
            found = true;
        }
    }

    return found;

}

void Agent::addToAlreadyOffered(int partyID) {
    alreadyOffered.push_back(partyID);

}

std::vector<int> Agent::getAlreadyOffered() {
    return alreadyOffered;
}




