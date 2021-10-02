#include "baseGame/BaseGame.h"
class Game : public BaseGame
{
private:
	Shape triangleAuto;
	Shape squareAuto;
	Shape shape;
	void Start();
	void Update();
	bool Input(int keycode, float &variable, float modif);
public:
	Game();
	void Play();
};
