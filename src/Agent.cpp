
#include "Agent.h"
#include "party.h"
#include "SelectionPolicy.h"
#include <iostream>

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

Agent::Agent(const Agent& otherAgent, int yourNewPartyID, int yourPartyMandates, int otherCoalitionMandates, int newID,SelectionPolicy* selectionPolicy ):
        alreadyOffered{otherAgent.alreadyOffered},
        mCoalitionMembers{otherAgent.mCoalitionMembers},
        mAgentId{newID},
        mPartyId{yourNewPartyID},
        mSelectionPolicy{selectionPolicy},
        mCoalitionMandates{yourPartyMandates+otherCoalitionMandates}
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
    for(int i=0; i<mRelevantNeighbors.size(); i++){
        if(sim.getParty(mRelevantNeighbors.at(i)).getState() == Joined ||
                std::count(alreadyOffered.begin(), alreadyOffered.end(),mRelevantNeighbors.at(i)) ) { //////REVISE!!!
            mRelevantNeighbors.erase(mRelevantNeighbors.begin()+i);
        }
    }
    if(!mRelevantNeighbors.empty()) {
        int partyToOfferID = mSelectionPolicy->select(sim.getGraph(), mRelevantNeighbors, mPartyId);

        Party &partyToOffer = sim.getGraph().getParty(partyToOfferID);
        switch (partyToOffer.getState()) {
            //Debate weather to give the agent control over party, or design her to maintain herself.
            case Waiting:
                // This could be changed to adding to the offers array in party, and the party herself checking each iteration if the array isn't empty and changing her status.
                partyToOffer.setState(CollectingOffers);
                partyToOffer.addToOffersList(mAgentId);
                alreadyOffered.push_back(partyToOfferID);


                break;
            case CollectingOffers:
                partyToOffer.addToOffersList(mAgentId);
                alreadyOffered.push_back(partyToOfferID);


                break;
            case Joined:
                std::cout << "Something went wrong... Agent no. " << mAgentId << "who belongs to party " << mPartyId
                          << " trying to add party no. " << partyToOfferID
                          << "to its coalition, but it's already in a Joined state.";

            default :
                std::cout << "Unidentified Party State.";
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





