#include "baseGame/BaseGame.h"
class Game : public BaseGame
{
private:
	Shape shape;
	void Start(); 
	void Update();

public:
	void Play();
};

