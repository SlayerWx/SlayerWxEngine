#include "baseGame/BaseGame.h"
class Game : BaseGame
{
private:
	void Update() override;
	void Draw() override;
public:
	void Play();
};

