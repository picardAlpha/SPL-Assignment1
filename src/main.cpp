#include <iostream>
#include <iomanip>
#include "Parser.h"

using std::cout;
using std::endl;

void initializeAgents(const Graph& graph, const vector<Agent>& agents);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "usage: " << argv[0] << " <config_path>" << endl;
        return -1;
    }
    // read simulation from config file
    const string config_path = argv[1];
    Simulation simulation = Parser::readSimulation(argv[1]);

    // THINGS TO DO BEFORE SIMULATION STARTS -- INITIALIZATION
    initializeAgents(simulation.getGraph(), simulation.getAgents());





    // run simulation and store json state after each iteration
    vector<json> outPerIter = {Parser::makeJson(simulation)};
    while (!simulation.shouldTerminate())
    {
        simulation.step();
        outPerIter.push_back(Parser::makeJson(simulation));
    }

    // writing the outputs list to a file
    const string output_path = config_path.substr(0, config_path.find_last_of('.')) + ".out";
    std::ofstream outputFile(output_path);
    outputFile << std::setw(4) << json(outPerIter) << endl;


    // TESTS

        for(int i=0; i<simulation.getAgents().size();i++){
            cout << "The relevant neighbors of agent " << i <<" are:" << endl;
            for(int neighbor : simulation.getAgents().at(i).mRelevantNeighbors)
                cout << neighbor << endl;


        }






    return 0;
}

// set the coalition mandates of every agent equal to the number of mandates the party he belongs to have.
// and initialize relevant neighbors list.
void initializeAgents(Graph& graph, vector<Agent>& agents){

    for(Agent agent:agents){
        agent.setCoalitionMandates(graph.getParty(agent.getPartyId()).getMandates());
        int agentsPartyID = agent.getPartyId();

        for (int i=0; i<graph.getNumVertices(); i++){
            //if you are not my party
            if(agentsPartyID!=i &&
               // and you are my neighbor
               graph.getEdgeWeight(agentsPartyID, i) > 0 &&
               // and not in a coalition
               graph.getParty(i).getState()!=Joined){
                //add to my relevant neighbors vector
                agent.mRelevantNeighbors.push_back(i);
            }
        }

    }

}



