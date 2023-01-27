#include "includes.hpp"
class world
{
	hero hero;
	dungeon dungeon;

public:
	world(int x_size, int y_size, int n_holes) : hero(), dungeon(x_size, y_size, n_holes) {}

	void move_hero_forward()
	{
		hero.score_ -= 1;
		// moves forward if not out of bounds
		cell moved = hero.current_cell_ + hero.facing_direction_;
		if (dungeon.out_of_bounds(moved))
			return;

		hero.current_cell_ = moved;
		if (dungeon.well_at(moved) || dungeon.wumpus_at(moved)) {
			hero.score_ -= 1000;
		}
	}

	sensors get_sensor()
	{
		sensors sensor = sensors::none;
		if (dungeon.stench_at(hero.current_cell_))
			sensor = sensor + sensors::stench;
		if (dungeon.breeze_at(hero.current_cell_))
			sensor = sensor + sensors::breeze;
		if (dungeon.treasure_at(hero.current_cell_))
			sensor = sensor + sensors::glitter;
		if (dungeon.wumpus_dead)
			sensor = sensor + sensors::scream;
		if ((hero.current_cell_.x() == 0 && hero.facing_direction_ == direction::south) ||
			(hero.current_cell_.x() == dungeon.x_size() && hero.facing_direction_ == direction::north) ||
			(hero.current_cell_.y() == 0 && hero.facing_direction_ == direction::west) ||
			(hero.current_cell_.y() == dungeon.y_size() && hero.facing_direction_ == direction::east))
			sensor = sensor + sensors::bump;
		return sensor;
	}

	void turn_hero_left()
	{
		hero.score_ -= 1;
		hero.facing_direction_ = hero.facing_direction_ - 1;
	}
	void turn_hero_right()
	{
		hero.score_ -= 1;
		hero.facing_direction_ = hero.facing_direction_ + 1;
	}
	void turn_hero_back()
	{
		hero.score_ -= 2;
		hero.facing_direction_ = hero.facing_direction_ - 2;
	}

	void shoot()
	{
		hero.score_ -= 11;
		hero.arrow_used = true;
		switch (hero.facing_direction_) {
		case direction::north:
			if (dungeon.wumpus_.x() == hero.current_cell_.x() && dungeon.wumpus_.y() > hero.current_cell_.y()) {
				hero.score_ += 100;
				dungeon.wumpus_dead = true;
			}
			return;
		case direction::south:
			if (dungeon.wumpus_.x() == hero.current_cell_.x() && dungeon.wumpus_.y() < hero.current_cell_.y()) {
				hero.score_ += 100;
				dungeon.wumpus_dead = true;
			}

			return;
		case direction::east:
			if (dungeon.wumpus_.y() == hero.current_cell_.y() && dungeon.wumpus_.x() > hero.current_cell_.x()) {
				hero.score_ += 100;
				dungeon.wumpus_dead = true;
			}

			return;
		case direction::west:
			if (dungeon.wumpus_.y() == hero.current_cell_.y() && dungeon.wumpus_.y() < hero.current_cell_.y()) {
				hero.score_ += 100;
				dungeon.wumpus_dead = true;
			}

			return;
		}
	}

	bool pick_treasure()
	{
		hero.score_--;
		if (dungeon.treasure_at(hero.current_cell_)) {
			hero.score_ += 1000;
			return true;
		} else {
			return false;
		}
	}

	int get_score() { return hero.score_; }

	void print_state()
	{
		std::cout << "\n+Score:\t\t" << hero.score_ << "\n+Position:\t" << hero.current_cell_ << "\n+Direction:\t"
				  << hero.facing_direction_ << "\n+Sensors:\t" << std::bitset<5>((int)get_sensor()).to_string()
				  << std::endl;
	}

	void print_layout()
	{
		std::cout << dungeon.initial_hero_cell << ": HERO" << std::endl;
		std::cout << dungeon.wumpus_ << ": WUMPUS" << std::endl;
		std::cout << dungeon.treasure_ << ": TREASURE" << std::endl;
		for (auto cell : dungeon.wells_)
			std::cout << cell << ": WELL" << std::endl;
	}
};