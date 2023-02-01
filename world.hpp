#include "includes.hpp"
class world
{
	hero hero;
	dungeon dungeon;

public:
	world(int x_size, int y_size, int n_holes) : hero(), dungeon(x_size, y_size, n_holes) {}

	bool move_hero_forward()
	{
		hero.move_forward(dungeon.x_size(), dungeon.y_size());
		if (dungeon.well_at(hero.current_cell()) || dungeon.wumpus_at(hero.current_cell())) {
			hero.die();
			return false;
		}
		return true;
	}

	sensors get_sensor()
	{
		sensors sensor = sensors::none;
		if (dungeon.stench_at(hero.current_cell()))
			sensor = sensor + sensors::stench;
		if (dungeon.breeze_at(hero.current_cell()))
			sensor = sensor + sensors::breeze;
		if (dungeon.treasure_at(hero.current_cell()))
			sensor = sensor + sensors::glitter;
		if (dungeon.wumpus_dead())
			sensor = sensor + sensors::scream;
		if ((hero.current_cell().x() == 0 && hero.facing_direction() == direction::south) ||
			(hero.current_cell().x() == dungeon.x_size() && hero.facing_direction() == direction::north) ||
			(hero.current_cell().y() == 0 && hero.facing_direction() == direction::west) ||
			(hero.current_cell().y() == dungeon.y_size() && hero.facing_direction() == direction::east))
			sensor = sensor + sensors::bump;
		return sensor;
	}

	void turn_hero_left() { hero.turn_left(); }
	void turn_hero_right() { hero.turn_right(); }
	void turn_hero_back() { hero.turn_back(); }

	void shoot()
	{
		if (!hero.shoot())
			return;
		auto wumpus = dungeon.wumpus();
		switch (hero.facing_direction()) {
		case direction::north:
			if (wumpus.x() == hero.current_cell().x() && wumpus.y() > hero.current_cell().y())
				dungeon.kill_wumpus();

			return;
		case direction::south:
			if (wumpus.x() == hero.current_cell().x() && wumpus.y() < hero.current_cell().y())
				dungeon.kill_wumpus();

			return;
		case direction::east:
			if (wumpus.y() == hero.current_cell().y() && wumpus.x() > hero.current_cell().x())
				dungeon.kill_wumpus();

			return;
		case direction::west:
			if (wumpus.y() == hero.current_cell().y() && wumpus.y() < hero.current_cell().y())
				dungeon.kill_wumpus();

			return;
		}
	}

	bool pick_treasure()
	{
		hero.grab();
		if (dungeon.treasure_at(hero.current_cell())) {
			hero.win();
			return true;
		} else {
			return false;
		}
	}

	int get_score() { return hero.score(); }

	void print_state()
	{
		std::cout << "\n+Score:\t\t" << hero.score() << "\n+Position:\t" << hero.current_cell() << "\n+Direction:\t"
				  << hero.facing_direction() << "\n+Sensors:\t" << std::bitset<5>((int)get_sensor()).to_string()
				  << std::endl;
	}

	void print_dungeon_layout() { dungeon.print_layout(); }
};