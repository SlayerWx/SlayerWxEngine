#include "baseGame/BaseGame.h"
class Game : public BaseGame
{
private:
	Shape shape;
	Shape shape2;
	void Start();
	void Update();
	bool Input(int keycode, float &variable, float modif);
public:
	Game();
	void Play();
};
