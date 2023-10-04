#include "baseGame/BaseGame.h"
#include "AnimatorController/Animation/Animation.h"
class Game : public BaseGame
{
private:
	DirectionalLight myDirLight;
	PointLight* point1;
	PointLight* point2;
	SpotLight* pot1;
	SpotLight* pot2;
	Shape triangleAuto;
	Shape squareAuto;
	Shape shape;
	Sprite itsfineSprite;
	Sprite dog;
	Sprite ncat;
	Sprite link;
	Cube mat1;
	Cube lightCUbe;
	Cube spotlightCUbe;
	Cube spotlightCUbe2;
	BSPPlane bspPlaneFront;
	BSPPlane bspPlaneRight;
	BSPPlane bspPlaneLeft;
	Model* model1;
	void Start();
	void Update();
	bool Input(int keycode, float &variable, float modif);
	void Delete();
	Animation* leftAnim;
	Animation* rightAnim;
	Animation* upAnim;
	Animation* downAnim;
	Animation* idleRightAnim;
	Animation* idleUpAnim;
	Animation* idleLeftAnim;
	Animation* idleDownAnim;
	void SpriteStart();
	void MaterialStart();
	void ShapeStart();
	void SpriteUpdate();
	void MaterialUpdate();
	void ShapeUpdate();
	void SpriteDraw();
	void ShapeDraw();
	void MaterialDraw();
public:
	Game();
	void Play();
};
