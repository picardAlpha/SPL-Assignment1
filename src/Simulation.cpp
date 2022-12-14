#include "../include/Simulation.h"
#include "../include/Graph.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // You can change the implementation of the constructor, but not the signature!
}

void Simulation::step()
{
    std::cout<<std::endl;
    std::cout << "************************* Iteration " << ++iteration << " *************************" <<std::endl;
    // TODO: implement this method
    for(int i=0; i<mGraph.getNumVertices(); i++){
        getGraph().getParty(i).step(*this);
        if(shouldTerminate())
            break;
    }

    for(Agent& agent : mAgents){
        agent.step(*this);
    }

}

bool Simulation::shouldTerminate() const
{

    //Should add a check if all parties already joined a coalition!!
    bool result = false;
    bool allJoined = true;
    for(int i=0; i<mAgents.size() && !result; i++){
        if(getAgents().at(i).mCoalitionMandates>60) {
            result = true;
        }
    }
    for(int i=0; i<getGraph().getNumVertices()  && allJoined ;i++){
        if(getParty(i).getState()!=Joined){
            allJoined=false;
        }
        
    }
    return result || allJoined;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector< vector < int > > Simulation::getPartiesByCoalitions() const
{
    // TODO: you MUST implement this method for getting proper output, read the documentation above.

    // BUG: Coalitions are printed more than once!!!


    return coalitions;
    }


   // return vector<vector<int>>();



//added

Graph &Simulation::getGraph()
{
    return mGraph;
}

 vector<Agent> &Simulation::getAgents()
{
    return mAgents;
}

void Simulation::addAgent(Agent& agentToBeCopied, int newlyJoinedPartyID) {
    ///NEEDS TO BE IMPLEMENTED
    int newID = mAgents.size();
    Agent newAgent {agentToBeCopied,newlyJoinedPartyID,newID};
    // Add the new party mandates to the coalition
    newAgent.mCoalitionMandates = agentToBeCopied.mCoalitionMandates + getParty(newlyJoinedPartyID).getMandates();
    agentToBeCopied.mCoalitionMandates = newAgent.mCoalitionMandates;
    agentToBeCopied.mCoalitionMembers.push_back(newlyJoinedPartyID);
    newAgent.mCoalitionMembers = agentToBeCopied.mCoalitionMembers;
    newAgent.mRelevantNeighbors.clear();

    //initialize neighbors list.
//    for (int j = 0; j < getGraph().getNumVertices();j++) {
//        if(getGraph().getEdgeWeight(newAgent.getPartyId(),j)>0 &&
//           getParty(j).getState() != Joined){
//            newAgent.addToRelevantNeighbors(j);
//        }
//    }
    mAgents.push_back(newAgent);
    // Update all my coalition members I have joined!
    for(Agent& agent : getAgents()){
        if(agent.mCoalitionNumber == newAgent.mCoalitionNumber){
            agent.mCoalitionMembers.push_back(newAgent.getPartyId());
            agent.mCoalitionNumber = newAgent.mCoalitionNumber;
        }
    }



}

bool Simulation::isPresent(vector<int> &neighborsList, int num) {
    bool found = false;
    for (int i = 0; i < neighborsList.size() && !found; i++) {
        if (neighborsList.at(i) == num) {
            found = true;
        }
    }

    return found;

}
