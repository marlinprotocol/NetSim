#include <bits/stdc++.h>

#include "Protocol.h"

class DummyProtocol: public Protocol {
private:
    double difficulty;
public:
    DummyProtocol();
    double getDifficulty();
    double getLambda();
};