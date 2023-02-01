#include "includes.hpp"

main()
{
	auto c = world(4, 4, 2);
	c.print_dungeon_layout();
	int i;
	bool game_over = false;
	while (!game_over) {
		c.print_state();
		std::cout << "Choose an action (keypad arrows, 5 to shoot or 0 to pick treasure)\n> " << std::flush;
		std::cin >> i;
		switch (i) {
		case 8:
			game_over = !c.move_hero_forward();
			break;
		case 4:
			c.turn_hero_left();
			break;
		case 6:
			c.turn_hero_right();
			break;
		case 2:
			c.turn_hero_back();
			break;
		case 5:
			c.shoot();
			break;
		case 0:
			game_over = c.pick_treasure();
			break;
		default:
			break;
		}
	}
	std::cout << "\n>>> You made " << c.get_score() << " points!!! <<<\n" << std::endl;
}
