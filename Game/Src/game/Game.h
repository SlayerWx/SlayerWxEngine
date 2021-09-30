#include "baseGame/BaseGame.h"
class Game : public BaseGame
{
private:
	Shape shape;
	void Update();
	void Start();
public:
	Game();
	void Play();
};
