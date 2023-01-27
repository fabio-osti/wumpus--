enum class sensors : char 
{ 
	none = 0, 
	breeze = 1, 
	stench = 2, 
	glitter = 4, 
	scream = 8, 
	bump = 16, 
};

inline sensors operator+(const sensors &lhs, const sensors &rhs) { return (sensors)((int)lhs | (int)rhs); }
inline sensors operator-(const sensors &lhs, const sensors &rhs) { return (sensors)((int)lhs & ~(int)rhs); }
inline bool operator==(const sensors &lhs, const sensors &rhs) { return ((int)lhs & (int)rhs) == (int)rhs; }