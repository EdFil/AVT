#include "Vertex.h"

Vertex::Vertex(){
	_position = new float[4];
	_color = new float[4];
	_normal = new float[4];
	_txCoord = new float[2];
}

const float *Vertex::getPosition() const{
	return _position;
}

const float Vertex::getPositionSize() const{
	return sizeof(float)*4;
}

void Vertex::setPosition(const float &x, const float &y, const float &z, const float &w){
	_position[0] = float(x);
	_position[1] = float(y);
	_position[2] = float(z);
	_position[3] = float(w);
}

void Vertex::setPosition(const glm::vec4 &position){
	setPosition(position.x, position.y, position.z, position.w);
}

const float *Vertex::getColor() const{
	return _color;
}

const float Vertex::getColorSize() const{
	return sizeof(float)*4;
}

void Vertex::setColor(const float &r, const float &g, const float &b, const float &a){
	_color[0] = float(r);
	_color[1] = float(g);
	_color[2] = float(b);
	_color[3] = float(a);
}

void Vertex::setPosition(const glm::vec4 &color){
	setColor(color.r, color.g, color.b, color.a);
}

const float *Vertex::getNormal() const{
	return _normal;
}

const float Vertex::getNormalSize() const{
	return sizeof(float)*4;
}

void Vertex::setNormal(const float &x, const float &y, const float &z, const float &w){
	_normal[0] = float(x);
	_normal[1] = float(y);
	_normal[2] = float(z);
	_normal[3] = float(w);
}

void Vertex::setNormal(const glm::vec4 &normal){
	setNormal(normal.x, normal.y, normal.z, normal.w);
}

const float *Vertex::getTxCoord() const{
	return _txCoord;
}

const float Vertex::getTxCoordSize() const{
	return sizeof(float)*2;
}

void Vertex::setTxCoord(const float &x, const float &y){
	_txCoord[0] = float(x);
	_txCoord[1] = float(y);
}

void Vertex::setTxCoord(const glm::vec2 &txCoord){
	setTxCoord(txCoord.x, txCoord.y);
}