#include <iostream>
#include <iomanip>
#include "Parser.h"

using std::cout;
using std::endl;


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

    // INITIALIZE AGENTS
//    for(Agent& agent:simulation.getAgents()){
//        agent.setCoalitionMandates(simulation.getParty(agent.getPartyId()).getMandates());
//        int agentsPartyID = agent.getPartyId();
//
//        for (int i=0; i<simulation.getGraph().getNumVertices(); i++){
//            //if you are not my party
//            if(agentsPartyID!=i &&
//               // and you are my neighbor
//               simulation.getGraph().getEdgeWeight(agentsPartyID, i) > 0 &&
//               // and not in a coalition
//               simulation.getParty(i).getState()!=Joined){
//                //add to my relevant neighbors vector
//                agent.addToRelevantNeighbors(i);
//            }
//        }


    // For each agents, add all relevant neighbors to its neighbor array.
    for(Agent& agent : simulation.getAgents()) {
        for (int j = 0; j < simulation.getGraph().getNumVertices();j++) {
            if(simulation.getGraph().getEdgeWeight(agent.getPartyId(),j)>0 &&
                simulation.getParty(j).getState() != Joined){
                agent.addToRelevantNeighbors(j);
            }
        }
    }


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
            cout << "The relevant neighbors of agent " << i <<" who belongs to party "<< simulation.getAgents().at(i).getPartyId() <<" are:" << endl;
            for(int j=0; j<simulation.getAgents().at(i).mRelevantNeighbors.size();j++)
                cout << simulation.getAgents().at(i).mRelevantNeighbors.at(j) << endl;


        }

    return 0;
}





// set the coalition mandates of every agent equal to the number of mandates the party he belongs to have.
// and initialize relevant neighbors list.





