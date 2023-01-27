#include "includes.hpp"

class cell
{
	int x_, y_;

public:
	const int x() const { return x_; }
	const int y() const { return y_; }

	cell() : x_(0), y_(0) {}
	cell(int _x, int _y) : x_(_x), y_(_y) {}
	cell(cell origin, direction dest) : cell(origin.x_, origin.y_)
	{
		switch (dest) {
		case direction::east:
			y_ += 1;
			break;
		case direction::west:
			y_ -= 1;
			break;
		case direction::north:
			x_ += 1;
			break;
		case direction::south:
			x_ -= 1;
			break;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const cell& cell)
	{
		return os << "[" << cell.x_ << ", " << cell.y_ << "]";
	}

	friend cell operator+(const cell &lhs, const direction rhs)
	{
		return cell(lhs, rhs);
	}
	friend bool operator==(const cell &lhs, const cell &rhs) { return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_; }

	struct pairhash {
	public:
		std::size_t operator()(const cell &c) const { return std::hash<int>()(c.x_) ^ std::hash<int>()(c.y_); }
	};
};

