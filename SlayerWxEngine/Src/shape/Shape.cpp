#include "Shape.h"

Shape::Shape() : Entity2D()
{
}
void Shape::SetColor(float R,float G, float B)
{
	VertexTriangle[3] = R;
	VertexTriangle[4] = G;
	VertexTriangle[5] = B;

	VertexTriangle[9] = R;
	VertexTriangle[10] = G;
	VertexTriangle[11] = B;

	VertexTriangle[15] = R;
	VertexTriangle[16] = G;
	VertexTriangle[17] = B;
}
void Shape::Draw()
{
	renderer->Draw(VertexTriangle, IndexTriangle, model);
}
