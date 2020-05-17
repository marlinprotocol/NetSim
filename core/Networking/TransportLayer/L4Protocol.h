#ifndef CORE_NETWORKING_TRANSPORTLAYER_L4PROTOCOL_H_
#define CORE_NETWORKING_TRANSPORTLAYER_L4PROTOCOL_H_

enum L4ProtocolType {UDP, TCP};

class L4Protocol {
private:
	bool isReliable;
	bool isConnectionOriented;
	L4ProtocolType l4ProtocolType;

public:
	L4Protocol(L4ProtocolType _l4ProtocolType, bool _isReliable, bool _isConnectionOriented);
	L4ProtocolType getL4ProtocolType();
	bool isIsConnectionOriented() const;
	void setIsConnectionOriented(bool isConnectionOriented);
	bool isIsReliable() const;
	void setIsReliable(bool isReliable);
};

#endif /* CORE_NETWORKING_TRANSPORTLAYER_L4PROTOCOL_H_ */
