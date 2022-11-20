#pragma once
#include <vector>
#include "Simulation.h"

class JoinPolicy {

public:
    virtual int select(Simulation& simulation, vector<int>& offerList) {
        return -1;
    }
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    virtual int select(Simulation& simulation, vector<int>& offerList) override;

};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    virtual int select(Simulation& simulation, vector<int>& offerList) override;

};