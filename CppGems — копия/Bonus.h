#pragma once
#include "Board.h"

#define BONUS_CHANCE 20
#define BOMB_TARGETS 5
#define PAINT_TARGETS 3
#define COMBO_SIZE_FOR_BONUS 3
#define PAINT_RADIUS 3




class Bonus: public sf::Sprite {
protected:
	int _num_affected_gems;
public:


	int GetNumTargets() const { return _num_affected_gems; };
	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
		const sf::Vector2i& coord) = 0;
	virtual ~Bonus() {};
};


class Bomb : public Bonus {
	
public:

	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
										const sf::Vector2i& coord);
	~Bomb() {};
	
};


class Paint : public Bonus {
	
public:

	virtual std::vector<sf::Vector2i> Activate(const sf::Vector2i& board_size,
											const sf::Vector2i& coord);
	
	~Paint() {};
};
