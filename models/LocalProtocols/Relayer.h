#ifndef RELAYER_H_
#define RELAYER_H_

#include <memory>

class Node;
class Network;

class Relayer {
private:
    int clusterId;
    bool isActive;
    std::shared_ptr<Node> parentNode;
public:
    Relayer(std::shared_ptr<Node> _parentNode, int _clusterId);
    bool setActivity(bool _isActive);
    int getClusterId();
};

#endif /*RELAYER_H_*/