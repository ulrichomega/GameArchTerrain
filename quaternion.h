#pragma once
#include "matrix.h"

class quaternion
{
public:
	quaternion(void);
	quaternion(matrix& m);
	~quaternion(void);
	
	void slerp(quaternion& other, float b);
	float dotProduct(quaternion& other);
	void scalarMultiplication(float scalar);
	void addQuaternion(quaternion& other);

	//Currently implements both pointer and non-pointer versions
	//Both do the same thing, except that the pointer versions 
	//A) don't require the object to be copied after the function returns (this is potentially a performance concern)
	//B) Create on the heap instead of the stack, and so possible other issues
	//C) returned values must be "delete()"-ed at some point
	// The pointer versions are currently not in use

	//Pointer versions
	matrix* createMatrixP();

	static quaternion* quaternionFromMatrixP(matrix& m);
	static matrix* matrixFromQuaternionP(quaternion& q);
	static quaternion* slerpQuaternionP(quaternion& q, quaternion& p, float b);
	static quaternion* slerpQuaternionP(matrix& q, matrix& p, float b);
	static matrix* slerpMatrixP(quaternion& q, quaternion& p, float b);
	static matrix* slerpMatrixP(matrix& q, matrix& p, float b);

	//Non-pointer versions
	matrix createMatrix();

	static quaternion quaternionFromMatrix(matrix& m);
	static matrix matrixFromQuaternion(quaternion& q);
	static quaternion slerpQuaternion(quaternion& q, quaternion& p, float b);
	static quaternion slerpQuaternion(matrix& q, matrix& p, float b);
	static matrix slerpMatrix(quaternion& q, quaternion& p, float b);
	static matrix slerpMatrix(matrix& q, matrix& p, float b);

private:
	float i;
	float j;
	float k;
	float w;
};

