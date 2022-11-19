#pragma once

#include <vector>
#include "Graph.h"
#include "Simulation.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    //added
    vector<int> alreadyOffered;
    vector<int> mCoalitionMembers;
    void setCoalitionMandates(int mandates);
    vector<int> mRelevantNeighbors;
    void setRelevantNeighbors(vector<int>& relevantNeighbors);
    void addToRelevantNeighbors(int partyID);

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mCoalitionMandates;

    // A constructor to be used when cloning an agent to a new party.
    // we set the
    Agent(const Agent& otherAgent, int yourNewPartyID, int yourPartyMandates, int otherCoalitionMandates, int newID,SelectionPolicy* selectionPolicy );

};
