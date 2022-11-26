#pragma once
#include <vector>
#include "../include/Simulation.h"

class JoinPolicy {

public:
    virtual int select(Simulation& simulation, vector<int>& offerList) {
        return -1;
    }

    virtual ~JoinPolicy()= default;


};

class MandatesJoinPolicy : public JoinPolicy {
public:
    int select(Simulation& simulation, vector<int>& offerList) override;

};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    int select(Simulation& simulation, vector<int>& offerList) override;

};