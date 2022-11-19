#include "Agent.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
    // You can change the implementation of the constructor, but not the signature!
}

Agent::Agent(const Agent& otherAgent, int yourNewPartyID, int yourPartyMandates, int otherCoalitionMandates, int newID,SelectionPolicy* selectionPolicy ):
        offered{otherAgent.offered},
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
    // then use SelectionPolicy to find the next party you should offer to.
    // if the party you offer to in collecting offers state, just add you offer to her offers list.
    // if the party you offer to in Waiting state, change her state to collecting offers and add your offer to her offers list. *****This should be revised.
    // if your relevant neighbors list is empty, do nothing.
}


//added

void Agent::setRelevantNeighbors(vector<int>& relevantNeighbors){
 mRelevantNeighbors=relevantNeighbors;
}





