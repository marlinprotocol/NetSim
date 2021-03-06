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
        core/Network/Messages/SubnetMessage.cpp
        core/Network/Node/Node.cpp   
        core/Networking/Bandwidth.cpp
        core/Networking/RoutingTable.cpp  
        core/Networking/Subnet.cpp   
        core/Networking/BandwidthModels/TransferProgress.cpp        
        core/Networking/BandwidthModels/gnp/AbstractGnpNetBandwidthManager.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthAllocation.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthManager.cpp
        core/Networking/Isolation/IsolationManager.cpp
        core/Networking/Isolation/IsolationModel.cpp
        core/Networking/Isolation/Events/PartitionEvent.cpp
        core/Networking/LatencyModels/City.cpp
        core/Networking/LatencyModels/GnpLatencyModel.cpp
        core/Networking/LatencyModels/LatencyModel.cpp
        core/Networking/LatencyModels/LinkMetrics.cpp
        core/Networking/LatencyModels/PingER.cpp
        core/Networking/LatencyModels/RandomLatencyModel.cpp
        core/Networking/LatencyModels/StaticLatencyModel.cpp
        core/Networking/LatencyModels/WonderNetwork.cpp
        core/Networking/NetworkLayer/IPv4Address.cpp
        core/Networking/NetworkLayer/IPv4Message.cpp
        core/Networking/NetworkLayer/L3Address.cpp
        core/Networking/NetworkLayer/NetworkLayer.cpp
        core/Networking/NetworkLayer/NetworkMessage.cpp
        core/Networking/TransportLayer/L4Address.cpp
        core/Networking/TransportLayer/L4Message.cpp
        core/Networking/TransportLayer/L4Protocol.cpp
        core/Networking/TransportLayer/TCPMessage.cpp
        core/Networking/TransportLayer/TransportLayer.cpp
        core/Networking/TransportLayer/UDPMessage.cpp     
        helpers/Logger/easylogging.cpp      
        helpers/Random.cpp
        lib/jsoncpp/jsoncpp.cpp
        models/BlockchainManagement/GlobalOrchestration/Bitcoin.cpp
        models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.cpp
        models/LocalProtocols/BitcoinMiner.cpp
        models/LocalProtocols/Protocol.cpp
        models/Networking/BitcoinRoutingTable.cpp
        models/Networking/FlexibleRoutingTable.cpp        
)

add_executable(test
        tests/main.cpp
        tests/TransportLayerTest.cpp
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
        core/Network/Messages/SubnetMessage.cpp
        core/Network/Node/Node.cpp   
        core/Networking/Bandwidth.cpp
        core/Networking/RoutingTable.cpp  
        core/Networking/Subnet.cpp   
        core/Networking/BandwidthModels/TransferProgress.cpp        
        core/Networking/BandwidthModels/gnp/AbstractGnpNetBandwidthManager.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthAllocation.cpp
        core/Networking/BandwidthModels/gnp/GnpNetBandwidthManager.cpp
        core/Networking/Isolation/IsolationManager.cpp
        core/Networking/Isolation/IsolationModel.cpp
        core/Networking/Isolation/Events/PartitionEvent.cpp
        core/Networking/LatencyModels/City.cpp
        core/Networking/LatencyModels/GnpLatencyModel.cpp
        core/Networking/LatencyModels/LatencyModel.cpp
        core/Networking/LatencyModels/LinkMetrics.cpp
        core/Networking/LatencyModels/PingER.cpp
        core/Networking/LatencyModels/RandomLatencyModel.cpp
        core/Networking/LatencyModels/StaticLatencyModel.cpp
        core/Networking/LatencyModels/WonderNetwork.cpp
        core/Networking/NetworkLayer/IPv4Address.cpp
        core/Networking/NetworkLayer/IPv4Message.cpp
        core/Networking/NetworkLayer/L3Address.cpp
        core/Networking/NetworkLayer/NetworkLayer.cpp
        core/Networking/NetworkLayer/NetworkMessage.cpp
        core/Networking/TransportLayer/L4Address.cpp
        core/Networking/TransportLayer/L4Message.cpp
        core/Networking/TransportLayer/L4Protocol.cpp
        core/Networking/TransportLayer/TCPMessage.cpp
        core/Networking/TransportLayer/TransportLayer.cpp
        core/Networking/TransportLayer/UDPMessage.cpp     
        helpers/Logger/easylogging.cpp   
        helpers/Random.cpp   
        lib/jsoncpp/jsoncpp.cpp
        models/BlockchainManagement/GlobalOrchestration/Bitcoin.cpp
        models/BlockchainManagement/GlobalOrchestration/GlobalOrchestration.cpp
        models/LocalProtocols/BitcoinMiner.cpp
        models/LocalProtocols/Protocol.cpp
        models/Networking/BitcoinRoutingTable.cpp
		models/Networking/FlexibleRoutingTable.cpp                      
)

add_definitions(-DELPP_DEFAULT_LOG_FILE="./logs/default.log")

set_property(TARGET simulation PROPERTY CXX_STANDARD 11)
set_property(TARGET test PROPERTY CXX_STANDARD 11)