#include "includes.hpp"
#define INIT_H cell(0, 0)
class dungeon
{
	const cell initial_hero_cell = INIT_H;
	int x_size_, y_size_;
	std::vector<cell> wells_;
	cell wumpus_;
	bool wumpus_dead_ = false;
	cell treasure_;

	cell inline get_unused_cell()
	{
		unique_seed();
		while (true) {
			auto _cell = cell(rand() % x_size_, rand() % y_size_);
			if (
				std::find(wells_.begin(), wells_.end(), _cell) == wells_.end() 
				&& _cell != initial_hero_cell 
				&& _cell != treasure_ 
				&& _cell != wumpus_) {
				return _cell;
			}
		}
	}

public:
	// friend class world;
	
	dungeon(int x_size, int y_size, int n_holes)
		: x_size_(x_size), y_size_(y_size), wumpus_(get_unused_cell()), treasure_(get_unused_cell())
	{
		wells_.reserve(n_holes);
		while (wells_.size() < n_holes)
			wells_.push_back(get_unused_cell());
	}

	int x_size() const { return x_size_; }
	int y_size() const { return y_size_; }
	cell wumpus() const { return wumpus_; }
	bool wumpus_dead() const { return wumpus_dead_; }
	void kill_wumpus() { wumpus_dead_ = true; }

	bool well_at(const cell &cell) const { return std::find(wells_.begin(), wells_.end(), cell) != wells_.end(); }

	bool wumpus_at(const cell &cell) const { return cell == wumpus_ && !wumpus_dead_; }
	
	bool treasure_at(const cell &cell) const { return cell == treasure_; }

	bool stench_at(const cell &cell) const
	{
		return (
			wumpus_ == cell + direction::north || wumpus_ == cell + direction::south ||
			wumpus_ == cell + direction::west || wumpus_ == cell + direction::east);
	}

	bool breeze_at(const cell &cell) const
	{
		return std::find(wells_.begin(), wells_.end(), cell + direction::north) != wells_.end() ||
			std::find(wells_.begin(), wells_.end(), cell + direction::south) != wells_.end() ||
			std::find(wells_.begin(), wells_.end(), cell + direction::west) != wells_.end() ||
			std::find(wells_.begin(), wells_.end(), cell + direction::east) != wells_.end();
	}

	bool out_of_bounds(const cell &cell) const
	{
		return cell.x() > x_size_ || cell.x() < 0 || cell.y() > y_size_ || cell.y() < 0;
	}

	void print_layout() const
	{
		std::cout << initial_hero_cell << ": HERO" << std::endl;
		std::cout << wumpus_ << ": WUMPUS" << std::endl;
		std::cout << treasure_ << ": TREASURE" << std::endl;
		for (auto cell : wells_)
			std::cout << cell << ": WELL" << std::endl;
	}
};
