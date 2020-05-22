#include "NetworkLayerTest.h"
#include "../core/Network/Messages/MessageType.h"
#include "../core/Networking/NetworkLayer/L3Protocol.h"
#include "../core/Networking/NetworkLayer/NetworkLayer.h"
#include "../core/Networking/Subnet.h"
#include "../core/Networking/TransportLayer/TCPMessage.h"

class TestEvent : public Event {
private:
	std::shared_ptr<TCPMessage> tcpMessage;

public:
	TestEvent(std::shared_ptr<TCPMessage> _tcpMessage) : Event(0, EventType::TEST) {
		tcpMessage = _tcpMessage;
	};

	bool execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
				 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick, std::shared_ptr<Subnet> _subnet) {
		LOG(DEBUG) << "[" << std::setw(35) << std::left << "TestEvent::execute]";

		std::vector<std::shared_ptr<Event>> newEvents;
		_network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, _currentTick, _newEvents);

		return true;
	};

	bool execute(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick, std::shared_ptr<Subnet> _subnet) {
		LOG(FATAL) << "[" << std::setw(35) << std::left << "TestEvent::execute][call without block cache not allowed]";
		return true;
	}
};

class TestEvent2 : public Event {
private:
	std::shared_ptr<TCPMessage> tcpMessage;

public:
	TestEvent2(std::shared_ptr<TCPMessage> _tcpMessage) : Event(0, EventType::TEST) {
		tcpMessage = _tcpMessage;
	};

	bool execute(Network& _network, std::shared_ptr<BlockCache> _blockCache,
				 std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick, std::shared_ptr<Subnet> _subnet) {
		LOG(DEBUG) << "[" << std::setw(35) << std::left << "TestEvent::execute]";

		std::vector<std::shared_ptr<Event>> newEvents;
		_network.getNode(1)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, _currentTick, _newEvents);

		return true;
	};

	bool execute(Network& _network, std::vector<std::shared_ptr<Event>>& _newEvents, uint64_t _currentTick, std::shared_ptr<Subnet> _subnet) {
		LOG(FATAL) << "[" << std::setw(35) << std::left << "TestEvent::execute][call without block cache not allowed]";
		return true;
	}
};

NetworkLayerTest::NetworkLayerTest() : network(simulator.getNetwork()) {
	std::shared_ptr<TestLatencyModel> pingER = populatePingER();
	subnet = std::make_shared<Subnet>(network, pingER);
	simulator.resetSubnet(subnet);
}

std::shared_ptr<TestLatencyModel> NetworkLayerTest::populatePingER() {
	std::unordered_map<std::string, std::unordered_map<std::string, LinkMetrics>> linkMetrics;
//	linkMetrics["DE"]["DE"] = LinkMetrics(10, 12.5, 1);
//	linkMetrics["US"]["DE"] = LinkMetrics(200, 250, 2);
//	linkMetrics["JP"]["JP"] = LinkMetrics(20, 25, 3);
//	linkMetrics["EU"]["JP"] = LinkMetrics(300, 375, 4);
//	linkMetrics["US"]["CA"] = LinkMetrics(30, 30, 5);
//	linkMetrics["JP"]["CA"] = LinkMetrics(250, 275, 6);
//	linkMetrics["BR"]["BR"] = LinkMetrics(40, 45, 7);
//	linkMetrics["CA"]["BR"] = LinkMetrics(100, 120, 8);

	std::shared_ptr<TestLatencyModel> gnpLatencyModel(new TestLatencyModel(network));
	gnpLatencyModel->getPingER().setLinkMetrics(linkMetrics);

	return gnpLatencyModel;
}

void NetworkLayerTest::test1Sender1Receiver1Stream() {
	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	simulator.start();
}

void NetworkLayerTest::test1Sender1Receiver2Streams() {
	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TestMessage> message2(std::make_shared<TestMessage>());
	message2->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	std::shared_ptr<TCPMessage> tcpMessage2(std::make_shared<TCPMessage>(
			message2, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	std::shared_ptr<TestEvent> event(std::make_shared<TestEvent>(tcpMessage2));
	simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + 300));

	simulator.start();
}

void NetworkLayerTest::test1Sender2Receivers2Streams() {
	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TestMessage> message2(std::make_shared<TestMessage>());
	message2->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	std::shared_ptr<TCPMessage> tcpMessage2(std::make_shared<TCPMessage>(
			message2, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(3), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	std::shared_ptr<TestEvent> event(std::make_shared<TestEvent>(tcpMessage2));
	simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + 300));

	simulator.start();
}

void NetworkLayerTest::test2Senders1Receiver2Streams() {
	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TestMessage> message2(std::make_shared<TestMessage>());
	message2->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	std::shared_ptr<TCPMessage> tcpMessage2(std::make_shared<TCPMessage>(
			message2, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	std::shared_ptr<TestEvent2> event(std::make_shared<TestEvent2>(tcpMessage2));
	simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + 300));

	simulator.start();
}

void NetworkLayerTest::test1Sender1Receiver1StreamLtdTCPThroughput() {
	std::static_pointer_cast<TestLatencyModel>(subnet->getLatencyModel())->setTcpThroughput(10);

	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	simulator.start();
}

void NetworkLayerTest::test1Sender1Receiver2StreamsLtdTCPThroughput() {
	std::static_pointer_cast<TestLatencyModel>(subnet->getLatencyModel())->setTcpThroughput(10);

	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TestMessage> message2(std::make_shared<TestMessage>());
	message2->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	std::shared_ptr<TCPMessage> tcpMessage2(std::make_shared<TCPMessage>(
			message2, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	std::shared_ptr<TestEvent> event(std::make_shared<TestEvent>(tcpMessage2));
	simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + 300));

	simulator.start();
}

void NetworkLayerTest::test1Sender2Receivers2StreamsLtdTCPThroughput() {
	std::static_pointer_cast<TestLatencyModel>(subnet->getLatencyModel())->setTcpThroughput(10);

	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TestMessage> message2(std::make_shared<TestMessage>());
	message2->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	std::shared_ptr<TCPMessage> tcpMessage2(std::make_shared<TCPMessage>(
			message2, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(3), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	std::shared_ptr<TestEvent> event(std::make_shared<TestEvent>(tcpMessage2));
	simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + 300));

	simulator.start();
}

void NetworkLayerTest::test2Senders1Receiver2StreamsLtdTCPThroughput() {
	std::static_pointer_cast<TestLatencyModel>(subnet->getLatencyModel())->setTcpThroughput(10);

	std::shared_ptr<TestMessage> message(std::make_shared<TestMessage>());
	message->setSize(58400);

	std::shared_ptr<TestMessage> message2(std::make_shared<TestMessage>());
	message2->setSize(58400);

	std::shared_ptr<TCPMessage> tcpMessage(std::make_shared<TCPMessage>(
			message, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	std::shared_ptr<TCPMessage> tcpMessage2(std::make_shared<TCPMessage>(
			message2, false, L4Address(L3Address(0), 0), L4Address(L3Address(2), 0), 0
	));

	uint64_t currentTick = 0;
	std::vector<std::shared_ptr<Event>> newEvents;

	network.getNode(0)->getNetworkLayer()->send(L3Address(2), L3Protocol::IPv4, tcpMessage, currentTick, newEvents);

	for(auto event: newEvents) {
		simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + event->getTicksBeforeExecution()));
	}

	std::shared_ptr<TestEvent2> event(std::make_shared<TestEvent2>(tcpMessage2));
	simulator.getEventManager().getEventQueue().addEvent(AsyncEvent(event, currentTick + 300));

	simulator.start();
}

int NetworkLayerTest::test() {
	std::shared_ptr<Node> sender1(new Node(0, 1000, 100, subnet, "US"));
	std::shared_ptr<Node> sender2(new Node(1, 1000, 100, subnet, "CA"));
	std::shared_ptr<Node> receiver1(new Node(2, 1000, 100, subnet, "JP"));
	std::shared_ptr<Node> receiver2(new Node(3, 1000, 100, subnet, "CN"));

	network.addNode(sender1);
	network.addNode(sender2);
	network.addNode(receiver1);
	network.addNode(receiver2);

//	test1Sender1Receiver1Stream(); // works - no automated testing - view logs to verify
//	test1Sender1Receiver2Streams();  // works - no automated testing - view logs to verify
//	test1Sender2Receivers2Streams(); // works - no automated testing - view logs to verify
//	test2Senders1Receiver2Streams();  // works - no automated testing - view logs to verify
//	test1Sender1Receiver1StreamLtdTCPThroughput(); // works - no automated testing - view logs to verify
//	test1Sender1Receiver2StreamsLtdTCPThroughput(); // works - no automated testing - view logs to verify
//	test1Sender2Receivers2StreamsLtdTCPThroughput(); // works - no automated testing - view logs to verify
	test2Senders1Receiver2StreamsLtdTCPThroughput();

	return 0;
}
