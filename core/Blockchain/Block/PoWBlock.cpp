#include "./PoWBlock.h"

PoWBlock::PoWBlock(int _parentBlockId, int _blockProducerId, int _blockHeight) 
		 : Block(_parentBlockId, _blockProducerId, _blockHeight) {
	difficulty = 0;
}

PoWBlock::PoWBlock(int _parentBlockId, int _blockProducerId, int _blockHeight, long long _tickStamp)
		 : Block(_parentBlockId, _blockProducerId, _blockHeight, _tickStamp) {
	difficulty = 0;
}

PoWBlock::PoWBlock(int _parentBlockId, int _blockProducerId, int _blockHeight, long long _tickStamp, double _difficulty)
		 : Block(_parentBlockId, _blockProducerId, _blockHeight, _tickStamp), difficulty(_difficulty) {
}
