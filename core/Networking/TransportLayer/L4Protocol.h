#ifndef CORE_NETWORKING_TRANSPORTLAYER_L4PROTOCOL_H_
#define CORE_NETWORKING_TRANSPORTLAYER_L4PROTOCOL_H_

class L4Protocol {
private:
	bool isReliable;
	bool isConnectionOriented;

public:
	L4Protocol(bool _isReliable, bool _isConnectionOriented);
	bool isIsConnectionOriented() const;
	void setIsConnectionOriented(bool isConnectionOriented);
	bool isIsReliable() const;
	void setIsReliable(bool isReliable);
};

L4Protocol UDP(false, false);
L4Protocol TCP(true, true);

#endif /* CORE_NETWORKING_TRANSPORTLAYER_L4PROTOCOL_H_ */
