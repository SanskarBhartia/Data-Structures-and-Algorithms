#include <cstdio>
#include <iostream>
#include <random>
#include <set>
#include <string>

#include "json.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		printf("Usage: %s numPlayers\n", argv[0]);
		return EXIT_FAILURE;
	}
	unsigned int numPlayers = 0;
	if (sscanf(argv[1], "%u", &numPlayers) != 1) {
		printf("numPlayers must be a positive integer\n");
		return EXIT_FAILURE;
	}

	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<int> winDist(0, 100000);

	nlohmann::json players;
	players["metadata"]["numPlayers"] = numPlayers;
	std::set<double> seenWinPercentages;
	for (unsigned int player = 0; player < numPlayers; player++) {
		for (unsigned int partner = player + 1; partner < numPlayers; partner++) {
			nlohmann::json playerObj;
			double winPercentage = (double) winDist(rng) / 1000;
			while (seenWinPercentages.count(fabs(winPercentage - 50)) > 0) {
				winPercentage = (double) winDist(rng) / 10;
			}
			seenWinPercentages.insert(fabs(winPercentage - 50));
			playerObj["winPercentage"] = winPercentage;
			playerObj["playerOne"] = player;
			playerObj["playerTwo"] = partner;
			players["teamStats"].push_back(playerObj);
		}
	}
	std::cout << players.dump(2);
}