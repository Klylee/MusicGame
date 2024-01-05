#pragma once

#include "Object2D.h"
#include "Note.h"
#include "TextLabel.h"
#include <queue>


class GameManager : public Object2D
{
public:
	std::queue<Note*> tracks[4];
	int score;


	void update() override
	{
		for (int i = 0; i < 4; i++) {
			if (tracks[i].empty()) {
				continue;
			}
			Note* n = tracks[i].front();
			if (n->transform.position().y <= -4.5f) {
				destroy(n, 0);
				tracks[i].pop();
			}
		}
	}
};

