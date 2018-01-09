#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Transform.h"
#include "Camera.h"
#include "Texture2D.h"
#include <IL/il.h>
#include "DepthBuffer.h"

//Mesh que dibuja la palma de la mano
Mesh _mesh;
//Mesh que dibuja cada una de las falanges
Mesh _mesh1;
//Shader program que dibuja las geometrías de la escena
ShaderProgram _shaderProgram;
//Shader que hace el render de profundidad
ShaderProgram _shaderProgramDepth;
//Geometría de la palma de la mano
Transform _transform;
//Geometría del suelo
Transform _transform1;
//Geometría de cada una de las falanges de la mano
//Falanges inferiores
Transform _falangetransform;
Transform _falangetransform1;
Transform _falangetransform2;
Transform _falangetransform3;
//Falanges superiores
Transform _falangetransform4;
Transform _falangetransform5;
Transform _falangetransform6;
Transform _falangetransform7;
//Cámara para la escena
Camera _camera;
//Camara que proyecta la luz, se usa para el render de profundidad
Camera _cameraLuz;
//Textura de caja de madera
Texture2D _texture;
//Textura de red para el suelo
Texture2D _texture1;
//Buffer de profundidad
DepthBuffer _depthBuffer;
//Parámetros para medir el movimiento de la mano
float limit = 0.0f;
float openClose = 0.3f;

void Initialize() {
	//Vector de posiciones para la palma de la mano
	std::vector<glm::vec3> positions;
	//Vector de posiciones para las falanges
	std::vector<glm::vec3> positions1;
	//Normales de las geometrías
	std::vector<glm::vec3> normals;
	//índices para dibujar con el mesh
	std::vector<unsigned int> indices;
	//Vector de texturas
	std::vector<glm::vec2> texturas;
	//Texturas
	_texture.loadTexture("caja.jpg");
	_texture1.loadTexture("red.jpg");

	//Posiciones para la palma
	positions.push_back(glm::vec3(-2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(-2.0f, 4.0f, 0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, 4.0f, 0.50f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, 0.250f));
	positions.push_back(glm::vec3(-2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, -0.250f));
	positions.push_back(glm::vec3(2.0f, -4.0f, 0.250f));

	//Posiciones para las falanges
	positions1.push_back(glm::vec3(-0.50f, -1, 0.250f));
	positions1.push_back(glm::vec3(0.50f, 1, 0.250f));
	positions1.push_back(glm::vec3(-0.50f, 1, 0.250f));
	positions1.push_back(glm::vec3(0.50f, -1, 0.250f));
	positions1.push_back(glm::vec3(-0.50f, 1, 0.250f));
	positions1.push_back(glm::vec3(-0.50f, -1, -0.250f));
	positions1.push_back(glm::vec3(-0.50f, -1, 0.250f));
	positions1.push_back(glm::vec3(-0.50f, 1, -0.250f));
	positions1.push_back(glm::vec3(-0.5f, 1.0f, -0.250f));
	positions1.push_back(glm::vec3(0.50f, 1, -0.250f));
	positions1.push_back(glm::vec3(-0.5f, -1, -0.250f));
	positions1.push_back(glm::vec3(0.50f, -1, -0.250f));
	positions1.push_back(glm::vec3(0.50f, -1, -0.250f));
	positions1.push_back(glm::vec3(0.50f, 1, 0.250f));
	positions1.push_back(glm::vec3(0.50f, -1, 0.250f));
	positions1.push_back(glm::vec3(0.5f, 1, -0.250f));
	positions1.push_back(glm::vec3(-0.50f, 1, -0.250f));
	positions1.push_back(glm::vec3(-0.50f, 1, 0.250f));
	positions1.push_back(glm::vec3(0.50f, 1, -0.250f));
	positions1.push_back(glm::vec3(0.50f, 1, 0.250f));
	positions1.push_back(glm::vec3(-0.50f, -1, 0.250f));
	positions1.push_back(glm::vec3(-0.50f, -1, -0.250f));
	positions1.push_back(glm::vec3(0.50f, -1, -0.250f));
	positions1.push_back(glm::vec3(0.50f, -1, 0.250f));
	
	//Normales
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));

	//Vector para dibujar texturas en los vértices adecuados
	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(0.0f, 0.0f));
	texturas.push_back(glm::vec2(0.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 1.0f));
	texturas.push_back(glm::vec2(1.0f, 0.0f));

	//Los índices son ingresados en el orden en el que se dibujarán
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(1);
	indices.push_back(0);
	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);
	indices.push_back(7);
	indices.push_back(5);
	indices.push_back(4);
	indices.push_back(8);
	indices.push_back(9);
	indices.push_back(10);
	indices.push_back(10);
	indices.push_back(9);
	indices.push_back(11);
	indices.push_back(12);
	indices.push_back(13);
	indices.push_back(14);
	indices.push_back(15);
	indices.push_back(13);
	indices.push_back(12);
	indices.push_back(16);
	indices.push_back(17);
	indices.push_back(18);
	indices.push_back(18);
	indices.push_back(17);
	indices.push_back(19);
	indices.push_back(20);
	indices.push_back(21);
	indices.push_back(22);
	indices.push_back(22);
	indices.push_back(23);
	indices.push_back(20);

	//Vector de colores (que se sigue necesitando aunque esté vacío)
	std::vector<glm::vec3> colors;

	//Creamos el buffer de profundidad con la resolución adecuada
	_depthBuffer.Create(2048);

	//Inicializamos el mesh que dibujará el suelo y la palma de la mano
	_mesh.setIndices(indices, GL_STATIC_DRAW);
	_mesh.createMesh(24);
	_mesh.setPositionAttribute(positions, GL_STATIC_DRAW, 0);
	_mesh.setColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh.setIndices(indices, GL_STATIC_DRAW);
	_mesh.setNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_mesh.setTexCoordAttribute(texturas, GL_STATIC_DRAW, 3);

	//Inicializamos el mesh que dibujará las falanges
	_mesh1.setIndices(indices, GL_STATIC_DRAW);
	_mesh1.createMesh(24);
	_mesh1.setPositionAttribute(positions1, GL_STATIC_DRAW, 0);
	_mesh1.setColorAttribute(colors, GL_STATIC_DRAW, 1);
	_mesh1.setIndices(indices, GL_STATIC_DRAW);
	_mesh1.setNormalAttribute(normals, GL_STATIC_DRAW, 2);
	_mesh1.setTexCoordAttribute(texturas, GL_STATIC_DRAW, 3);

	//Creamos el programa que manejará el shader para las geometrías de la escena
	_shaderProgram.createProgram();
	_shaderProgram.attachShader("Shadow.vert", GL_VERTEX_SHADER);
	_shaderProgram.attachShader("Shadow.frag", GL_FRAGMENT_SHADER);
	_shaderProgram.setAttribute(0, "VertexPosition");
	_shaderProgram.setAttribute(1, "VertexColor");
	_shaderProgram.setAttribute(2, "VertexNormal");
	_shaderProgram.setAttribute(3, "VertexTexCoord");

	//Creamos el programa que manejará los shaders de profundidad
	_shaderProgramDepth.createProgram();
	_shaderProgramDepth.attachShader("Depth.frag", GL_FRAGMENT_SHADER);
	_shaderProgramDepth.attachShader("Depth.vert", GL_VERTEX_SHADER);
	_shaderProgramDepth.setAttribute(0, "VertexPosition");

	//Atamos los programas de shader
	_shaderProgram.linkProgram();
	_shaderProgramDepth.linkProgram();

	//Posicionamos las cámaras
	_camera.moveForward(25.0f);
	_cameraLuz.setOrthigraphic(45.0f, 1);
	_cameraLuz.setPosition(10, 37, 0);
	_cameraLuz.pitch(-90);

	//Manejamos las transformacíones
	_transform.moveUp(-5, true);
	_transform1.setScale(150, 0.5, 150);
	_transform1.moveUp(-10, true);
	_falangetransform.moveUp(5.6f, true);
	_falangetransform.moveRight(-1.7, true);
	_falangetransform1.moveUp(5.6f, true);
	_falangetransform2.moveUp(5.6f, true);
	_falangetransform2.moveRight(1.9, true);
	_falangetransform3.moveUp(-2.8f, true);
	_falangetransform3.moveRight(-3.1f, true);
	_falangetransform3.rotate(0, 0, 80, true);
	_falangetransform4.moveUp(2.8f, true);
	_falangetransform5.moveUp(2.8f, true);
	_falangetransform6.moveUp(2.8f, true);
	_falangetransform7.moveUp(2.8f, true);
	_transform.rotate(-73.0f, 0.00f, 0.0f, true);
	
}

void GameLoop() {
	//Atamos el buffer de profundidad
	_depthBuffer.bind();

	//Limpiamos la pantalla
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//La mano rota
	_transform.rotate(0.0f, 0.3f, 0.0f, true);
	
	//Establecemos los límites del movimiento de la mano
	if (limit >= 128.0f || limit < 0.0f) {
		openClose *= -1;
	}

	limit += openClose;

	//Establecemos las posiciones por cuadro de las falanges inferiores
	_falangetransform.moveForward(openClose / 50, false);
	_falangetransform.rotate(openClose, 0, 0.0f, false);
	_falangetransform1.moveForward(openClose*0.76 / 50, false);
	_falangetransform1.rotate(openClose*0.76, 0, 0.0f, false);
	_falangetransform2.moveForward(openClose*0.66 / 50, false);
	_falangetransform2.rotate(openClose*0.66, 0, 0.0f, false);
	_falangetransform3.moveForward(openClose*0.82 / 50, false);
	_falangetransform3.rotate(openClose*0.82, 0, 0.0f, false);
	//Establecemos las posiciones por cuadro de las falanges superiores
	_falangetransform4.moveForward(openClose / 50, false);
	_falangetransform4.rotate(openClose, 0, 0.0f, false);
	_falangetransform5.moveForward(openClose*0.76 / 50, false);
	_falangetransform5.rotate(openClose*0.76, 0, 0.0f, false);
	_falangetransform6.moveForward(openClose*0.66 / 50, false);
	_falangetransform6.rotate(openClose*0.66, 0, 0.0f, false);
	_falangetransform7.moveForward(openClose*0.82 / 50, false);
	_falangetransform7.rotate(openClose*0.82, 0, 0.0f, false);
		
	//Hacemos el render de profundidad para...
	_shaderProgramDepth.activate();	
	//...la palma de la mano,...
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix());
	_mesh.draw(GL_TRIANGLES);
	//...el suelo,...
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()* _transform1.getModelMatrix());
	_mesh.draw(GL_TRIANGLES);
	//...las falanges inferiores y...
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform1.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform2.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform3.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	//...las falanges superiores...
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform.getModelMatrix()*_falangetransform4.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform1.getModelMatrix()*_falangetransform5.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform2.getModelMatrix()*_falangetransform6.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	_shaderProgramDepth.setUniformMatrix("mvpMatrix", _cameraLuz.getViewProjection()*_transform.getModelMatrix()*_falangetransform3.getModelMatrix()*_falangetransform7.getModelMatrix());
	_mesh1.draw(GL_TRIANGLES); 
	
	//Quitamos el buffer de profundidad al terminar
	_depthBuffer.unbind();
	_shaderProgramDepth.deactivate();

	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	//Limpiamos la pantalla para el siguiente render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Activamos el shader para las geometrías
	_shaderProgram.activate();

	//Pasamos las uniformes de la luz y la cámara al shader
	_shaderProgram.setUniformf("luzX", 0);
	_shaderProgram.setUniformf("luzY", 5);
	_shaderProgram.setUniformf("luzZ", 0);
	_shaderProgram.setUniformf("camaraX", _camera.getPosition()[0]);
	_shaderProgram.setUniformf("camaraY", _camera.getPosition()[1]);
	_shaderProgram.setUniformf("camaraZ", _camera.getPosition()[2]);
	_shaderProgram.setUniformi("Diffusetexture", 0);
	_shaderProgram.setUniformi("ShadowMap", 1);

	//Dibujamos la palma de la mano
	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	//Dibujamos las falanges inferiores
	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform1.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform1.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform2.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform2.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform3.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform3.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	//Dibujamos las falanges superiores
	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform.getModelMatrix()*_falangetransform4.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform.getModelMatrix()*_falangetransform4.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform1.getModelMatrix()*_falangetransform5.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform1.getModelMatrix()*_falangetransform5.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform2.getModelMatrix()*_falangetransform6.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform2.getModelMatrix()*_falangetransform6.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();
	
	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform.getModelMatrix()*_falangetransform3.getModelMatrix()*_falangetransform7.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform.getModelMatrix()*_falangetransform3.getModelMatrix()*_falangetransform7.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh1.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	//Dibujamos el suelo
	_shaderProgram.setUniformMatrix("mvpMatrix", _camera.getViewProjection() * _transform1.getModelMatrix());
	_shaderProgram.setUniformMatrix("ModelMatrix", _transform1.getModelMatrix());
	_shaderProgram.setUniformMatrix("LightVPMatrix", _cameraLuz.getViewProjection());
	glActiveTexture(GL_TEXTURE0);
	_texture1.bind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.bindDepthMap();
	_mesh.draw(GL_TRIANGLES);
	glActiveTexture(GL_TEXTURE0);
	_texture1.unbind();
	glActiveTexture(GL_TEXTURE1);
	_depthBuffer.unbindDepthMap();

	//Desactivamos el shader
	_shaderProgram.deactivate();

	glutSwapBuffers();
}

void Idle() {
	glutPostRedisplay();
}

void ReshapeWindow(int width, int height) {
	glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Hello World GL");
	glutDisplayFunc(GameLoop);
	glutReshapeFunc(ReshapeWindow);
	glutIdleFunc(Idle);

	glewInit();
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	glClearColor(1.0f, 1.0f, 0.5f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	std::cout << glGetString(GL_VERSION) << std::endl;

	Initialize();

	glutMainLoop();

	return 0;
}