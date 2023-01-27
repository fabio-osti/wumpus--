enum class direction : char {
	north = 0,
	east = 1,
	south = 2,
	west = 3,
};

inline std::ostream& operator<<(std::ostream& os, const direction& dir)
{
    switch (dir) 
	{
		case direction::east:
			os << "East";
			break;
		case direction::west:
			os << "West";
			break;
		case direction::north:
			os << "North";
			break;
		case direction::south:
			os << "South";
			break;
		}
    return os;
}


inline direction operator+(const direction &lhs, const int &rhs)
{
	return (direction)(((int)lhs + rhs) % 4);
}

inline direction operator-(const direction &lhs, const int &rhs)
{
	return (direction)(((unsigned)lhs - rhs) % 4);
}