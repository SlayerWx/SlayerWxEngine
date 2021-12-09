#include "baseGame/BaseGame.h"
#include "AnimatorController/Animation/Animation.h"
class Game : public BaseGame
{
private:
	Shape triangleAuto;
	Shape squareAuto;
	Shape shape;
	Sprite itsfineSprite;
	Sprite dog;
	Sprite ncat;
	Sprite link;
	void Start();
	void Update();
	bool Input(int keycode, float &variable, float modif);
	Animation* leftAnim;
	Animation* rightAnim;
	Animation* upAnim;
	Animation* downAnim;
	Animation* idleRightAnim;
	Animation* idleUpAnim;
	Animation* idleLeftAnim;
	Animation* idleDownAnim;
public:
	Game();
	void Play();
};
