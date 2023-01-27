#include "includes.hpp"
class hero
{
	cell current_cell_ = INIT_H;
	int score_ = 0;
	direction facing_direction_ = direction::east;
	bool arrow_used = false;

public:
	friend class world;
};