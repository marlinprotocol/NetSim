#include <functional>

#include "L3Address.h"

namespace std
{
    template<> struct hash<L3Address>
    {
    	std::size_t operator()(L3Address const& l) const noexcept
        {
            return 0; // TODO
        }
    };
}
