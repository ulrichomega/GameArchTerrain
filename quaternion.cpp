#include "quaternion.h"
#include <math.h>

quaternion::quaternion(void)
{
	i=0;
	j=0;
	k=0;
	w=1;
}

quaternion::~quaternion(void)
{
}

quaternion::quaternion(matrix& m) {
	//MATH
	//MATH
	i=0;
	j=0;
	k=0;
	w=0;

	float q[4] = {0,0,0,0};
	int nxt[3] = {1,2,0};
	float trace = m[0][0] + m[1][1] + m[2][2];

	if (trace > 0) {
		float s = sqrt(trace+1.0);
		w = s/2;
		s = 0.5/s;

		i=(m[2][1] - m[1][2])*s;
		j=(m[0][2] - m[2][0])*s;
		k=(m[1][0] - m[0][1])*s;
	}
	else {
		int x = 0;
		if (m[1][1] > m[0][0]) {
			x=1;
		}
		if (m[2][2] > m[x][x]) {
			x=2;
		}
		int y = nxt[x];
		int z = nxt[y];
		float s = sqrt((m[x][x] - (m[y][y] + m[z][z])) + 1.0);
		q[x] = s*0.5;
		//if (s > 0.000001 && s < -0.000001) {
		if (s != 0.0) {
			s = 0.5/s;
		}
		w = (m[y][z] - m[z][y])*s;
		q[y] = (m[x][y] + m[y][x])*s;
		q[z] = (m[x][z] + m[z][x])*s;
		i=q[0];
		j=q[1];
		k=q[2];
	}

}

void quaternion::slerp(quaternion& other, float b){
	float theta = acos(dotProduct(other));

	float wThis = sin((1-b)*theta)/sin(theta);
	float wOther = sin(theta*b)/sin(theta);

	//This is essentially what is going on below, but requires too many 
	//instances of temporary quaternions, so we're going to hardcode it out
	/*quaternion tempCopyThis = quaternion(this);
	quaternion tempCopyOther = quaternion(other);

	tempCopyThis.scalarMultiplication(wThis);
	tempCopyOther.scalarMultiplication(wOther);

	tempCopyThis.addQuaternion(tempCopyOther);*/

	//Same as above, simpler to look at, less function call overhead
	i = wThis*i + wOther*other.i;
	j = wThis*j + wOther*other.j;
	k = wThis*k + wOther*other.k;
	w = wThis*w + wOther*other.w;
}
float quaternion::dotProduct(quaternion& other) {
	return i*other.i + j*other.j + k*other.k + w*other.w;
}
void quaternion::scalarMultiplication(float scalar) {
	i*=scalar;
	j*=scalar;
	k*=scalar;
	w*=scalar;
}
void quaternion::addQuaternion(quaternion& other) {
	i+=other.i;
	j+=other.j;
	k+=other.k;
	w+=other.w;
}

//Pointer Variations of functions
matrix* quaternion::createMatrixP(){
	//Note: Translation component is currently not included, due to it being initialized to 0
	//Note 2: The above might be based on false assumptions
	matrix* m = new matrix();

	*m[0][0] = 1 - 2*j*j - 2*k*k;
	*m[0][1] = 2*i*j - 2*w*k;
	*m[0][2] = 2*i*k + 2*w*j;
	//*m[0][3] = 0;
	
	*m[1][0] = 2*i*j + 2*w*k;
	*m[1][1] = 1 - 2*i*i - 2*k*k;
	*m[1][2] = 2*j*k - 2*w*i;
	//*m[1][3] = 0;
	
	*m[2][0] = 2*i*k - 2*w*j;
	*m[2][1] = 2*j*k + 2*w*i;
	*m[2][2] = 1 - 2*i*i - 2*j*j;
	//*m[2][3] = 0;

	return m;
}

//Static functions
quaternion* quaternion::quaternionFromMatrixP(matrix& m){
	quaternion* q = new quaternion(m);
	return q;
}
matrix* quaternion::matrixFromQuaternionP(quaternion& q) {
	matrix* m = q.createMatrixP();
	return m;
}
quaternion* quaternion::slerpQuaternionP(quaternion& q, quaternion& p, float b) {
	quaternion* qTemp = new quaternion(q);
	qTemp->slerp(p,b);
	return qTemp;
}
quaternion* quaternion::slerpQuaternionP(matrix& q, matrix& p, float b) {
	quaternion* qTemp = new quaternion(q);
	quaternion pTemp = quaternion(p);
	
	qTemp->slerp(pTemp, b);
	return qTemp;
}
matrix* quaternion::slerpMatrixP(quaternion& q, quaternion& p, float b) {
	quaternion qTemp = quaternion(q);

	qTemp.slerp(p,b);
	return qTemp.createMatrixP();
}
matrix* quaternion::slerpMatrixP(matrix& q, matrix& p, float b) {
	quaternion qTemp = quaternion(q);
	quaternion pTemp = quaternion(p);
	
	qTemp.slerp(pTemp, b);
	return qTemp.createMatrixP();
}

//Non-Pointer Variations of functions
matrix quaternion::createMatrix(){
	//Note: Translation component is currently not included, due to it being initialized to 0
	//Note 2: The above might be based on false assumptions
	matrix m = matrix();

	m[0][0] = 1 - 2*j*j - 2*k*k;
	m[0][1] = 2*i*j - 2*w*k;
	m[0][2] = 2*i*k + 2*w*j;
	//m[0][3] = 0;
	
	m[1][0] = 2*i*j + 2*w*k;
	m[1][1] = 1 - 2*i*i - 2*k*k;
	m[1][2] = 2*j*k - 2*w*i;
	//m[1][3] = 0;
	
	m[2][0] = 2*i*k - 2*w*j;
	m[2][1] = 2*j*k + 2*w*i;
	m[2][2] = 1 - 2*i*i - 2*j*j;
	//m[2][3] = 0;

	return m;
}

//Static functions
quaternion quaternion::quaternionFromMatrix(matrix& m){
	quaternion q = quaternion(m);
	return q;
}
matrix quaternion::matrixFromQuaternion(quaternion& q) {
	matrix m = q.createMatrix();
	return m;
}
quaternion quaternion::slerpQuaternion(quaternion& q, quaternion& p, float b) {
	quaternion qTemp = quaternion(q);
	qTemp.slerp(p,b);
	return qTemp;
}
quaternion quaternion::slerpQuaternion(matrix& q, matrix& p, float b) {
	quaternion qTemp = quaternion(q);
	quaternion pTemp = quaternion(p);
	
	qTemp.slerp(pTemp, b);
	return qTemp;
}
matrix quaternion::slerpMatrix(quaternion& q, quaternion& p, float b) {
	quaternion qTemp = quaternion(q);

	qTemp.slerp(p,b);
	return qTemp.createMatrix();
}
matrix quaternion::slerpMatrix(matrix& q, matrix& p, float b) {
	quaternion qTemp = quaternion(q);
	quaternion pTemp = quaternion(p);
	
	qTemp.slerp(pTemp, b);
	return qTemp.createMatrix();
}