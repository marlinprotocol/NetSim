cmake_minimum_required(VERSION 2.9 FATAL_ERROR)
project(Project)

add_executable(simulation
        main.cpp
        core/Blockchain/Blockchain.cpp
        core/Blockchain/Block/PoSBlock.cpp
        core/Blockchain/Block/PoWBlock.cpp
        core/Blockchain/Block/Block.cpp
        core/Blockchain/Cache/BlockCache.cpp
        core/Simulator/Simulator.cpp
        core/EventManagement/Event/Event.cpp
        core/EventManagement/Event/AsyncEvent.cpp
        core/EventManagement/Event/EventTypes/MessageToNodeEvent.cpp
        core/EventManagement/EventManager/EventManager.cpp
        core/EventManagement/EventQueue/EventQueue.cpp
        core/Network/Network.cpp
        core/Network/Messages/Message.cpp
        core/Network/Messages/NewBlockIdMessage.cpp
        core/Network/Messages/NewBlockMinedMessage.cpp
        core/Network/Node/Node.cpp   
        core/Networking/Bandwidth.cpp
        core/Networking/BandwidthModels/gnp/AbstractGnpNetBandwidthManager.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthAllocation.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthManager.cpp
        core/Networking/NetworkLayer/IPv4Address.cpp
        core/Networking/NetworkLayer/IPv4Message.cpp
        core/Networking/NetworkLayer/NetworkMessage.cpp
        core/Networking/RoutingTable.cpp  
        core/Networking/Subnet.cpp        
        helpers/Logger/easylogging.cpp    
        models/BlockchainManagement/GlobalOrchestration/Bitcoin.cpp
        models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.cpp
        models/LocalProtocols/BitcoinMiner.cpp
        models/LocalProtocols/Protocol.cpp
        models/Networking/BitcoinRoutingTable.cpp       
)

add_executable(test
        tests/main.cpp
        tests/SubnetTest.cpp
        core/Blockchain/Blockchain.cpp
        core/Blockchain/Block/PoSBlock.cpp
        core/Blockchain/Block/PoWBlock.cpp
        core/Blockchain/Block/Block.cpp
        core/Blockchain/Cache/BlockCache.cpp
        core/Simulator/Simulator.cpp
        core/EventManagement/Event/Event.cpp
        core/EventManagement/Event/AsyncEvent.cpp
        core/EventManagement/Event/EventTypes/MessageToNodeEvent.cpp
        core/EventManagement/EventManager/EventManager.cpp
        core/EventManagement/EventQueue/EventQueue.cpp
        core/Network/Network.cpp
        core/Network/Messages/Message.cpp
        core/Network/Messages/NewBlockIdMessage.cpp
        core/Network/Messages/NewBlockMinedMessage.cpp
        core/Network/Node/Node.cpp   
        core/Networking/Bandwidth.cpp
        core/Networking/BandwidthModels/gnp/AbstractGnpNetBandwidthManager.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthAllocation.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthManager.cpp
        core/Networking/NetworkLayer/IPv4Address.cpp
        core/Networking/NetworkLayer/IPv4Message.cpp
        core/Networking/NetworkLayer/NetworkMessage.cpp
        core/Networking/RoutingTable.cpp  
        core/Networking/Subnet.cpp      
        helpers/Logger/easylogging.cpp      
        models/BlockchainManagement/GlobalOrchestration/Bitcoin.cpp
        models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.cpp
        models/LocalProtocols/BitcoinMiner.cpp
        models/LocalProtocols/Protocol.cpp
        models/Networking/BitcoinRoutingTable.cpp                       
)

add_definitions(-DELPP_DEFAULT_LOG_FILE="./logs/default.log")

set_property(TARGET simulation PROPERTY CXX_STANDARD 11)
set_property(TARGET test PROPERTY CXX_STANDARD 11)