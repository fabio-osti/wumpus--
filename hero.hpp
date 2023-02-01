#include "main.hpp"
#define SCORE_ACTION -1
#define SCORE_SHOOT -10
#define SCORE_WIN 1000
#define SCORE_DEATH -1000
class hero
{
	cell current_cell_ = INIT_H;
	int score_ = 0;
	direction facing_direction_ = direction::east;
	bool arrow_used_ = false;

public:
	// friend class game;

	int score() const { return score_; }
	cell current_cell() const { return current_cell_; }
	direction facing_direction() const { return facing_direction_; }

	void move_forward(auto& out_of_bounds)
	{
		score_ += SCORE_ACTION;
		// moves forward if not out of bounds
		cell new_cell = current_cell_ + facing_direction_;
		if (out_of_bounds(new_cell))
			return;

		current_cell_ = new_cell;
	}

	bool move_forward(int x_size, int y_size)
	{
		score_ += SCORE_ACTION;
		// moves forward if not out of bounds
		cell new_cell = current_cell_ + facing_direction_;
		if (new_cell.x() > x_size || new_cell.x() < 0 || new_cell.y() > y_size || new_cell.y() < 0)
			return false;

		current_cell_ = new_cell;
		return true;
	}

	bool shoot()
	{
		if (arrow_used_)
			return false;
		arrow_used_ = true;
		score_ += SCORE_SHOOT + SCORE_ACTION;
		return true;
	}

	void turn_left()
	{
		facing_direction_ = facing_direction_ - 1;
		score_ += SCORE_ACTION;
	}

	void turn_right()
	{
		facing_direction_ = facing_direction_ + 1;
		score_ += SCORE_ACTION;
	}

	void turn_back()
	{
		facing_direction_ = facing_direction_ + 2;
		score_ += (SCORE_ACTION * 2);
	}

	void die() { score_ += SCORE_DEATH; }
	void win() { score_ += SCORE_WIN; }
	void grab() { score_ += SCORE_ACTION; }
};