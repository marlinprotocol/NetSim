#include "TransportLayerTest.h"
#include "../core/EventManagement/Event/EventTypes/MessageToNodeEvent.h"
#include "../core/Network/Messages/MessageType.h"
#include "../core/Network/Messages/SubnetMessage.h"
#include "../core/Networking/NetworkLayer/L3Protocol.h"
#include "../core/Networking/NetworkLayer/NetworkLayer.h"
#include "../core/Networking/NetworkLayer/IPv4Message.h"
#include "../core/Networking/NetworkLayer/NetworkProtocol.h"
#include "../core/Networking/Subnet.h"
#include "../core/Networking/TransportLayer/UDPMessage.h"
#include "../core/Networking/TransportLayer/TCPMessage.h"
#include "../core/Networking/TransportLayer/TransportLayer.h"

TransportLayerTest::TransportLayerTest() : network(simulator.getNetwork()) {
	std::shared_ptr<TestLatencyModel> pingER = populatePingER();
	subnet = std::make_shared<Subnet>(network, pingER);
	simulator.resetSubnet(subnet);
}

std::shared_ptr<TestLatencyModel> TransportLayerTest::populatePingER() {
	std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>> linkMetrics;

	std::shared_ptr<TestLatencyModel> gnpLatencyModel(new TestLatencyModel(network));
	gnpLatencyModel->getPingER().setLinkMetrics(linkMetrics);

	return gnpLatencyModel;
}

void TransportLayerTest::test1Sender1Receiver1Stream() {
	std::cout<<"TransportLayerTest::test1Sender1Receiver1Stream()"<<std::endl;
	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->getTransportLayer()->send(100, L4Address(L3Address(1), 100), l4TCP, -1,
																	 message, false, currentTick, newEvents);

	std::cout<<"newEvents size: "<<newEvents.size()<<std::endl;

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	simulator.start();
}

int TransportLayerTest::test() {
	std::shared_ptr<Node> node0(new Node(0, 1000, 100, subnet, "US", "BitcoinRoutingTable"));
	std::shared_ptr<Node> node1(new Node(1, 1000, 100, subnet, "CA", "BitcoinRoutingTable"));
	std::shared_ptr<Node> node2(new Node(2, 1000, 100, subnet, "JP", "BitcoinRoutingTable"));

	network.addNode(node0);
	network.addNode(node1);
	network.addNode(node2);

	test1Sender1Receiver1Stream();

	return 0;
}
