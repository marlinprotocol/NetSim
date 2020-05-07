/*
 * Copyright (c) 2012-2013 Open Source Community - <http://www.peerfact.org>
 * Copyright (c) 2011-2012 University of Paderborn - UPB
 * Copyright (c) 2005-2011 KOM - Multimedia Communications Lab
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

// ported to C++ for Marlin Protocol

#include <cmath>
#include <iostream>

#include "SubnetTest.h"
#include "../core/Network/Node/Node.h"
#include "../core/Network/Network.h"
#include "../core/Networking/BandwidthModels/gnp/AbstractGnpNetBandwidthManager.h"
#include "../core/Networking/BandwidthModels/gnp/GnpNetBandwidthAllocation.h"
#include "../core/Networking/Subnet.h"
#include "../core/Networking/Bandwidth.h"

SubnetTest::SubnetTest() {
	network = std::make_shared<Network>();
	subnet = std::make_shared<Subnet>(*network);
}

void SubnetTest::AllAtOnce_FullAllocation_OneStream() {
	auto sender0 = network->getNode(0);
	auto sender1 = network->getNode(1);
	auto sender2 = network->getNode(2);
	auto receiver0 = network->getNode(3);
	auto receiver1 = network->getNode(4);
	auto receiver2 = network->getNode(5);
	auto receiver3 = network->getNode(6);
	auto receiver4 = network->getNode(7);
	auto receiver5 = network->getNode(8);

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);

	assert(subnet->getBandwidthManager()->getChangedAllocations().size() == 0);

	subnet->getBandwidthManager()->addConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getChangedAllocations().size() == 0);

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) != nullptr);

	subnet->getBandwidthManager()->allocateBandwidth();

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 36.6666) <= 0.0001);

	subnet->getBandwidthManager()->removeConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);
}

void SubnetTest::AllAtOnce_FullAllocation_MultiStream() {
	auto sender0 = network->getNode(0);
	auto sender1 = network->getNode(1);
	auto sender2 = network->getNode(2);
	auto receiver0 = network->getNode(3);
	auto receiver1 = network->getNode(4);
	auto receiver2 = network->getNode(5);
	auto receiver3 = network->getNode(6);
	auto receiver4 = network->getNode(7);
	auto receiver5 = network->getNode(8);

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);

	// Add First Stream
	subnet->getBandwidthManager()->addConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	// Add Second Stream
	subnet->getBandwidthManager()->addConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) != nullptr);

	subnet->getBandwidthManager()->allocateBandwidth();

//	std::cout<<"getBandwidthAllocation(0, 3)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth()<<std::endl;
//	std::cout<<"getBandwidthAllocation(0, 4)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth()<<std::endl;

	subnet->getBandwidthManager()->allocateBandwidth();

//	std::cout<<"getBandwidthAllocation(0, 3)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth()<<std::endl;
//	std::cout<<"getBandwidthAllocation(0, 4)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth()<<std::endl;

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 36.6666) <= 0.0001);

	subnet->getBandwidthManager()->removeConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) != nullptr);

	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 36.6666) <= 0.0001);

	subnet->getBandwidthManager()->removeConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);
}

void SubnetTest::StepByStep_FullAllocation_OneStream() {
	auto sender0 = network->getNode(0);
	auto sender1 = network->getNode(1);
	auto sender2 = network->getNode(2);
	auto receiver0 = network->getNode(3);
	auto receiver1 = network->getNode(4);
	auto receiver2 = network->getNode(5);
	auto receiver3 = network->getNode(6);
	auto receiver4 = network->getNode(7);
	auto receiver5 = network->getNode(8);

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);

	subnet->getBandwidthManager()->addConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->addConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->allocateBandwidth();

//	std::cout<<"getBandwidthAllocation(0, 3)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth()<<std::endl;
//	std::cout<<"getBandwidthAllocation(0, 4)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth()<<std::endl;
//	std::cout<<"getBandwidthAllocation(1, 5)->getAllocatedBandwidth(): "<<subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth()<<std::endl;

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 36.6666) <= 0.0001);

	subnet->getBandwidthManager()->removeConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);
}

void SubnetTest::allAtOnce_RestrictedAllocation_MultiStream() {
	auto sender0 = network->getNode(0);
	auto sender1 = network->getNode(1);
	auto sender2 = network->getNode(2);
	auto receiver0 = network->getNode(3);
	auto receiver1 = network->getNode(4);
	auto receiver2 = network->getNode(5);
	auto receiver3 = network->getNode(6);
	auto receiver4 = network->getNode(7);
	auto receiver5 = network->getNode(8);

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);

	subnet->getBandwidthManager()->addConnection(0, 3, 2);
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 3, 2);
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 8, 11);

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) != nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) != nullptr);

	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 2) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 4) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 4) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 2.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 8) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 11) <= 0.0001);

	subnet->getBandwidthManager()->addConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 36.6666) <= 0.0001);

	subnet->getBandwidthManager()->removeConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 2) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 4) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 4) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 2.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 8) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 11) <= 0.0001);

	subnet->getBandwidthManager()->addConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->addConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	subnet->getBandwidthManager()->removeConnection(0, 3, 2);
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, 2);
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, 11);

	subnet->getBandwidthManager()->allocateBandwidth();
	subnet->getBandwidthManager()->allocateBandwidth();

	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6)->getAllocatedBandwidth() - 3.3333) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5)->getAllocatedBandwidth() - 5.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4)->getAllocatedBandwidth() - 26.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6)->getAllocatedBandwidth() - 6.6666) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7)->getAllocatedBandwidth() - 10.0) <= 0.0001);
	assert(fabs(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8)->getAllocatedBandwidth() - 36.6666) <= 0.0001);

	subnet->getBandwidthManager()->removeConnection(0, 3, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 4, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(0, 6, sender0->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 3, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(1, 5, sender1->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 4, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 6, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 7, sender2->getMaxBandwidth()->getUpBW());
	subnet->getBandwidthManager()->removeConnection(2, 8, sender2->getMaxBandwidth()->getUpBW());

	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(0, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 3) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(1, 5) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 4) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 6) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 7) == nullptr);
	assert(subnet->getBandwidthManager()->getBandwidthAllocation(2, 8) == nullptr);
}

int SubnetTest::test() {
	std::shared_ptr<Node> sender0(new Node(0, 0, 10));
	std::shared_ptr<Node> sender1(new Node(1, 0, 10));
	std::shared_ptr<Node> sender2(new Node(2, 0, 80));

	std::shared_ptr<Node> receiver0(new Node(3, 40, 0));
	std::shared_ptr<Node> receiver1(new Node(4, 30, 0));
	std::shared_ptr<Node> receiver2(new Node(5, 10, 0));
	std::shared_ptr<Node> receiver3(new Node(6, 10, 0));
	std::shared_ptr<Node> receiver4(new Node(7, 10, 0));
	std::shared_ptr<Node> receiver5(new Node(8, 40, 0));

	network->addNode(sender0);
	network->addNode(sender1);
	network->addNode(sender2);
	network->addNode(receiver0);
	network->addNode(receiver1);
	network->addNode(receiver2);
	network->addNode(receiver3);
	network->addNode(receiver4);
	network->addNode(receiver5);

	AllAtOnce_FullAllocation_OneStream();
	AllAtOnce_FullAllocation_MultiStream();
	StepByStep_FullAllocation_OneStream();
	allAtOnce_RestrictedAllocation_MultiStream();

	return 0;
}
