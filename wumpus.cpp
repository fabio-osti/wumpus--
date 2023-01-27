#include "includes.hpp"

main()
{
	auto c = world(10, 10, 6);
	c.print_layout();
	int i;
	while (true) {
		c.print_state();
		std::cout << "Choose an action (keypad arrows or 5 to shoot)\n> " << std::flush;
		std::cin >> i;
		switch (i) {
		case 8:
			c.move_hero_forward();
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

		default:
			break;
		}
	}
}
