    #include "../include/Party.h"
#include "../include/JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), timer(0)
{
    // You can change the implementation of the constructor, but not the signature!
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    // TODO: implement this method

    switch(mState){
        case Waiting:
            // do nothing, The simulation will change your state to collecting offers when you receive one.
            if(!offers.empty()){
                timer = 0 ; // BUG : Timer isn't always initialized
                mState = CollectingOffers;
                std::cout << "Party " << mId<<": I have offers from agents " ;
                for(int offer:offers){
                    std::cout << offer << " " ;
                }
                std::cout << std::endl;
            }
            break;
        case CollectingOffers:
            timer++;
            if(timer > 3){
                // choose using joinPolicy and change your state to joined.
                int agentToAccept = mJoinPolicy->select(s,offers);
                int agentToAcceptCoalition = s.getAgents().at(agentToAccept).mCoalitionNumber;
                std::cout << "---- Party " << mId <<": I'm accepting the offer of agent number " << agentToAccept <<std::endl;
                std::cout << "I have " <<mMandates << " mandates. The offering coalition has " << s.getAgents().at(agentToAccept).mCoalitionMandates <<" mandates. ";
                s.addAgent(s.getAgents().at(agentToAccept), mId);  // Clones Agent
                // add myself to the proper coalition vector
                s.coalitions.at(agentToAcceptCoalition).push_back(mId);

                // updates the offering agent's coalition mandates.
//                s.getAgents().at(agentToAccept).setCoalitionMandates(s.getAgents().at(agentToAccept).mCoalitionMandates + mMandates); //Optimize
//                s.addAgent(s.getAgents().at(agentToAccept),mId);
                // update my mandates


                //TODO : Initialize the new agents relevant neighbors!
                for(int i=0; i<s.getGraph().getNumVertices(); i++){
                    if(s.getGraph().getEdgeWeight(s.getAgents().at(s.getAgents().size()-1).getId(),i)>0 && !s.isPresent(s.getAgents().at(s.getAgents().size()-1).alreadyOffered,i)){
                        s.getAgents().at(s.getAgents().size()-1).mRelevantNeighbors.push_back(i);
                    }

                }
                std::cout << "Together we have " << s.getAgents().at(agentToAccept).mCoalitionMandates << " mandates" << std::endl;
                mState = Joined;



            }
            //increase your timer by 1, if it is equal to 4, you need to choose a coalition.
            // choose using JoinPolicy and update fields : mState = Joined.
            // clone the agent that made you the offer by invoking agent's copy constructor, and set him the following fields:
            // your ID, your mandates, your agents coalition mandates, find him the proper new ID via graphs agent vector (and add it to him!)
            // Remove yourself from all agents if JOINED, remove yourself from your offering agent (? maybe should be done on agent level)
            break;
        case Joined:
            
            //
            break;

            default:
            break;



    }
}

void Party::addToOffersList(int agentID) {
    offers.push_back(agentID);
}


//Ariel added

////Destructor
//    Party:: ~Party(){
//        if(mJoinPolicy) delete mJoinPolicy;
//
//
//    }
////Copy Constructor
//    Party::Party(const Party &other){
//        mId = other.mId;
//        mName = other.mName;
//        mMandates = other.mMandates;
//        mJoinPolicy = other.mJoinPolicy;
//        mState = other.mState;
//    }
////Moving Constructor
//    Party::Party(Party &&other){
//        mJoinPolicy = other.mJoinPolicy;
//        delete other.mJoinPolicy;
//    }
////Copy Operator
//    Party& Party::operator= (const Party& other){
//        (mJoinPolicy) = ((other.mJoinPolicy));
//        return *this;
//    }
////Move Operator
//    Party& Party::operator= (Party&& other){
//        if(mJoinPolicy) delete mJoinPolicy;
//        mJoinPolicy = other.mJoinPolicy;
//        other.mJoinPolicy = nullptr;
//        return *this;
//    }
//



