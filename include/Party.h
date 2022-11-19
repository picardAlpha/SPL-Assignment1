#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;

    //added
    void addToOffersList(int agentID);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;

    //added

    // Saves the Agents IDs that made an offer to this party by chronological order.
    std::vector<int> offers;

    int getPartyID();
};
