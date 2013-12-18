#ifndef VERTEX_H
#define VERTEX_H

#include <glm\glm.hpp>

class Vertex {

private:
	float *_position;
	float *_color;
	float *_normal;
	float *_txCoord;

public:
	Vertex();

	const float* getPosition() const;
	const float getPositionSize() const;
	void setPosition(const float &x, const float &y, const float &z, const float &w);
	void setPosition(const glm::vec4 &position);

	const float* getColor() const;
	const float getColorSize() const;
	void setColor(const float &r, const float &g, const float &b, const float &a);
	void setColor(const glm::vec4 &color);

	const float* getNormal() const;
	const float getNormalSize() const;
	void setNormal(const float &x, const float &y, const float &z, const float &w);
	void setNormal(const glm::vec4 &normal);

	const float* getTxCoord() const;
	const float getTxCoordSize() const;
	void setTxCoord(const float &x, const float &y);
	void setTxCoord(const glm::vec2 &txCoord);
};

#endif
