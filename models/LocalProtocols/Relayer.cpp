#include "Relayer.h"
#include "core/Network/Node/Node.h"
#include "core/Network/Network.h"

Relayer::Relayer(std::shared_ptr<Node> _parentNode, int _clusterId): parentNode(_parentNode), clusterId(_clusterId), isActive(true) {
    
}

bool Relayer::setActivity(bool _isActive) {
    isActive = _isActive;
    return true;
}

int Relayer::getClusterId() {
    return clusterId;
}