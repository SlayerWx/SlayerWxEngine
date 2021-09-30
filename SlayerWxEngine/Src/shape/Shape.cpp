#include "Shape.h"

Shape::Shape()
{
}

Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
}

void Shape::Draw()
{
	renderer->Draw(VertexTriangle, IndexTriangle,model);
}
