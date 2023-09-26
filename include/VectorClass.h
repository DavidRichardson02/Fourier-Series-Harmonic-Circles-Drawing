#pragma once

#include "ofMain.h"


struct VectorStructure
{
	float x;
	float y;
	float magnitude;
	float theta;

	VectorStructure();  //no-arg
	VectorStructure(float x_in, float y_in);  //two-arg constructor, pass in values for x and y components


	/*-----   operators   -----*/
	VectorStructure &operator=(VectorStructure &other);
	VectorStructure &operator+(VectorStructure& other);
	VectorStructure &operator-(VectorStructure& other);
	VectorStructure &operator*(VectorStructure& other);
	VectorStructure &operator/(VectorStructure& other);

	float vectorStructlLength(); //Length of the vector
	void vectorStructNormalize();  // Normalize the vector
	float vectorStructDot(VectorStructure &other);  //Dot product with another vector
	float vectorStructDistance(VectorStructure &other); // Distance to another vector



};



class VectorClass
{
public:
	/*-----------   No-arg constructor   ------------*/
	VectorClass();

	/*-----------    Destructor   ------------*/
	~VectorClass();


	/*-----------   Add element to end of vector, increase size by 1   ------------*/
	void pushBack(VectorStructure data);  //read only, the passed in value cannot be modified after initialization within this function, just added 

	void copyVector(VectorClass data);

	/*-----------   Remove last element from vector, decrease size by 1   ------------*/
	void popBack();

	/*-----------   Add element to any index of vector, increase size by 1 at the specified index   ------------*/
	void pushAtIndex(VectorStructure data, int index);

	/*-----------   Access an element at a specific index of vector   ------------*/
	VectorStructure getElement(int index);

	/*-----------   Replace an element at a specific index with a passed in value   ------------*/
	void replaceElement(VectorStructure data, int index);

	/*-----------   Get current size of vector   ------------*/
	int getSize();

	/*-----------   Return a reference to the last element of the vector   ------------*/
	VectorStructure frontEnd();

	/*-----------   Return a reference to the first element of the vector   ------------*/
	VectorStructure backEnd();

	/*-----------   Vector operations   ------------*/
	VectorStructure subtractVectors(VectorStructure p1, VectorStructure p2);

	VectorStructure addtVectors(VectorStructure p1, VectorStructure p2);

	float getMagnitude(VectorStructure p1, VectorStructure p2);

	/*-----------   Print vector   ------------*/
	void printVector();

	/*-----------   Clear vector   ------------*/
	void vectorClear();

private:
	VectorStructure* arr;  // Pointer to the dynamically allocated array
	int size;   //total current size of array/vector, i.e., number of elements
	int capacity;  // Total capacity of the allocated array, i.e., max size 
};








class vectorComponentClass
{
public:
	/*-----------   No-arg constructor   ------------*/
	vectorComponentClass();

	/*-----------    Destructor   ------------*/
	~vectorComponentClass();


	/*-----------   Add element to end of vector, increase size by 1   ------------*/
	void pushBackComponent(float data);  //read only, the passed in value cannot be modified after initialization within this function, just added 

	void copyComponent(vectorComponentClass data);

	/*-----------   Remove last element from vector, decrease size by 1   ------------*/
	void popBackComponent();

	/*-----------   Add element to any index of vector, increase size by 1 at the specified index   ------------*/
	void pushAtIndexComponent(float data, int index);

	/*-----------   Access an element at a specific index of vector   ------------*/
	float getElementComponent(int index);

	/*-----------   Get current size of vector   ------------*/
	int getSizeComponent();

	/*-----------   Return a reference to the last element of the vector   ------------*/
	float frontEndComponent();

	/*-----------   Return a reference to the first element of the vector   ------------*/
	float backEndComponent();

	/*-----------   Print vector   ------------*/
	void printVectorComponent();

	/*-----------   Clear vector   ------------*/
	void vectorClearComponent();

private:
	float *arrComponent;  // Pointer to the dynamically allocated array
	int sizeComponent;   //total current size of array/vector, i.e., number of elements
	int capacityComponent;  // Total capacity of the allocated array, i.e., max size 
};













struct ComplexPlane
{
	float real;  // real
	float imaginary;  // imaginary
	int frequency;    // frequency
	float amplitude; // amplitude
	float phaseRadians;   // phase(radian)
	ComplexPlane();  //no-arg
	ComplexPlane(float real_in, float imaginary_in);  //two-arg constructor, pass in values for x and y components
};

ComplexPlane addComplexNumbers();
ComplexPlane multiplyComplexNumbers();

class vectorClassComplex
{
public:
	/*-----------   No-arg constructor   ------------*/
	vectorClassComplex();

	/*-----------    Destructor   ------------*/
	~vectorClassComplex();


	/*-----------   Add element to end of vector, increase size by 1   ------------*/
	void pushBackComplex(ComplexPlane data);  //read only, the passed in value cannot be modified after initialization within this function, just added 

	/*-----------   Remove last element from vector, decrease size by 1   ------------*/
	void popBackComplex();

	/*-----------   Add element to any index of vector, increase size by 1 at the specified index   ------------*/
	void pushAtIndexComplex(ComplexPlane data, int index);

	/*-----------   Access an element at a specific index of vector   ------------*/
	ComplexPlane getElementComplex(int index);

	void replaceElementComplex(ComplexPlane data, int index);

	/*-----------   Get current size of vector   ------------*/
	int getSizeComplex();

	/*-----------   Return a reference to the last element of the vector   ------------*/
	ComplexPlane frontEndComplex();

	/*-----------   Return a reference to the first element of the vector   ------------*/
	ComplexPlane backEndComplex();

	/*-----------   Clear vector   ------------*/
	void vectorClearComplex();

private:
	ComplexPlane *arrComplex;  // Pointer to the dynamically allocated array
	int sizeComplex;   //total current size of array/vector, i.e., number of elements
	int capacityComplex;  // Total capacity of the allocated array, i.e., max size 
};









