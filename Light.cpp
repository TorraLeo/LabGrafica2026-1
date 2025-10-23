#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
}

void Light::SetColor(GLfloat red, GLfloat green, GLfloat blue)
{
	// Esta función actualiza la variable 'color' de la clase
	color = glm::vec3(red, green, blue);
}

void Light::SetIntensity(GLfloat aIntensity, GLfloat dIntensity)
{
	// Esta función actualiza las variables de intensidad
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
}

Light::~Light()
{
}
