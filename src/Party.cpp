#include "../include/Party.h"
#include "../include/JoinPolicy.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) :
mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting)
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
                timer = 0 ;
                mState = CollectingOffers;
            }
            break;
        case CollectingOffers:
            timer++;
            if(timer == 4){
                // choose using joinPolicy and change your state to joined.
                int agentToAccept = mJoinPolicy->select(s,offers);
                s.addAgent(s.getAgents().at(agentToAccept), mId);
                // updates the offering agent's coalition mandates.
                s.getAgents().at(agentToAccept).setCoalitionMandates(s.getAgents().at(agentToAccept).mCoalitionMandates + mMandates); //Optimize
                s.addAgent(s.getAgents().at(agentToAccept),mId);
                mState = Joined;



            }
            //increase your timer by 1, if it is equal to 4, you need to choose a coalition.
            // choose using JoinPolicy and update fields : mState = Joined.
            // clone the agent that made you the offer by invoking agent's copy constructor, and set him the following fields:
            // your ID, your mandates, your agents coalition mandates, find him the proper new ID via graphs agent vector (and add it to him!)
            // Remove yourself from all agents if JOINED, remove yourself from your offering agent (? maybe should be done on agent level)
            break;
        case Joined:
            std::cout << "I have a boyfriend :)";
            //
            break;



    }
}

void Party::addToOffersList(int agentID) {
    offers.push_back(agentID);
}





