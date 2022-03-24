#include "branch.h"

namespace toe
{
	branch::branch(std::size_t branchNumber, std::size_t branchBegin, std::size_t branchEnd, double resistorValue,
	               double voltageValue, double amperageValue)
		: _branchNumber(branchNumber), _branchBegin(branchBegin), _branchEnd(branchEnd)
		  , _resistorValue(resistorValue), _voltageValue(voltageValue), _amperageValue(amperageValue) { }
}
