#pragma once

#include <vector>
#include "../include/Graph.h"
#include "../include/Simulation.h"

class SelectionPolicy;

class Agent {
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;

    int getId() const;

    void step(Simulation &);

    //added
    std::vector<int> mCoalitionMembers;
    int mCoalitionNumber;

    void setCoalitionMandates(int mandates);

    std::vector<int> mRelevantNeighbors;

    void setRelevantNeighbors(std::vector<int> &relevantNeighbors);

    void addToRelevantNeighbors(int partyID);

    int mCoalitionMandates;

    // A constructor to be used when cloning an agent to a new party.
    Agent(const Agent &otherAgent, int yourNewPartyID, int newID);

    bool isPresent(vector<int> &neighborsList, int num);

    int getCoalitionMandates();

    void addToAlreadyOffered(int partyID);

    std::vector<int> getAlreadyOffered();
    std::vector<int> alreadyOffered;


//    virtual ~Agent(); //Destructor
    Agent(const Agent& other); // Copy Constructor
//    Agent(Agent&& other); //Move Constructur  BAD!!
    Agent& operator = (const Agent& other); //Copy Operator
    Agent& operator = (Agent&& other); //Move Operator



private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;

    //added

};
    //Ariel Added
