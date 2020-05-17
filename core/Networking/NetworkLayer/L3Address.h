#ifndef CORE_NETWORKING_NETWORKLAYER_L3ADDRESS_H_
#define CORE_NETWORKING_NETWORKLAYER_L3ADDRESS_H_

class L3Address {
public:
	L3Address();
	bool operator==(const L3Address &other) const;
	int getSize();
};

//namespace std
//{
    template<> struct std::hash<L3Address>
    {
    	std::size_t operator()(L3Address const& l) const noexcept
        {
            return 0; // TODO
        }
    };
//}

#endif /* CORE_NETWORKING_NETWORKLAYER_L3ADDRESS_H_ */
