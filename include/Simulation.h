#pragma once

#include <vector>

#include "../include/Graph.h"
#include "../include/Agent.h"

class Agent;
using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int> > getPartiesByCoalitions() const;

    Graph &getGraph();

    vector<Agent> &getAgents();
    void addAgent(Agent &agentToBeCopied, int newlyJoinedPartyID);
    static bool isPresent(vector<int> &neighborsList, int num);


private:
    Graph mGraph;
    vector<Agent> mAgents;

};
