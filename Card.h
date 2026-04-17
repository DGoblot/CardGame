#pragma once

#include <vector>

struct Card
{
	int cost;
	int atk;
	int def;
	std::vector<bool> capa;
	int max_def;
	bool awake = false;
	
	bool operator==(const Card& other) const
	{
		return cost == other.cost &&
			atk == other.atk &&
			def == other.def &&
			capa == other.capa &&
			awake == other.awake;
	}

	bool operator!=(const Card& other) const
	{
		return !(*this == other);
	}
};