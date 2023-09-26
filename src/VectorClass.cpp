#include "VectorClass.h"
#include "DiscreteFourierTransform.h"
#include "ofMain.h"

using namespace std;


VectorStructure::VectorStructure()    //no-arg constructor, initialize to 0
{
	x = 0.0;
	y = 0.0;
	magnitude = sqrt(pow(x, 2) + pow(y, 2));
	theta = atan2(y, x);
}
VectorStructure::VectorStructure(float x_in, float y_in)
{
	x = x_in;
	y = y_in;
	magnitude = sqrt(pow(x, 2) + pow(y, 2));
	theta = atan2(y, x);
}

VectorStructure& VectorStructure::operator=(VectorStructure& other)
{
	if (this != &other) 
	{
		x = other.x;
		y = other.y;
	}
	return *this;
}

VectorStructure& VectorStructure::operator+(VectorStructure& other)
{
	VectorStructure sum(x + other.x, y + other.y);
	return(sum);
}

VectorStructure& VectorStructure::operator-(VectorStructure& other)
{
	VectorStructure sub(x - other.x, y - other.y);
	return(sub);
}

VectorStructure& VectorStructure::operator*(VectorStructure& other)
{
	VectorStructure product(x * other.x, y * other.y);
	return(product);
}

VectorStructure& VectorStructure::operator/(VectorStructure& other)
{
	VectorStructure quotient(x / other.x, y / other.y);
	return(quotient);
}

float VectorStructure::vectorStructlLength()
{
	float length = sqrt(x * x + y * y);

	return(length);
}

void VectorStructure::vectorStructNormalize()
{
	float length = vectorStructlLength();
	if (length != 0.0f) 
	{
		float inverseLength = 1.0f / length;
		x *= inverseLength;
		y *= inverseLength;
	}
}

float VectorStructure::vectorStructDot(VectorStructure &other)
{
	float dotProduct = x * other.x + y * other.y;
	return(dotProduct);
}

float VectorStructure::vectorStructDistance(VectorStructure &other)
{
	float distance =  (*this - other).vectorStructlLength();

	return(distance);
}





VectorClass::VectorClass()
{
	arr = new VectorStructure[1];    //data initially null

	//size and capacity of array both initially 0
	size = 0;
	capacity = 1;
}


VectorClass::~VectorClass()
{
	delete[] arr;
}


void VectorClass::pushBack(VectorStructure data)
{
	if (size == capacity) //if the current size of the array is equal to the max size of the array, then increase the capacity
	{

		capacity = capacity * 2;
		
		VectorStructure* tempArr = new VectorStructure[capacity];   //allocate new memory for the increased size of array

		for (int i = 0; i < size; i++)
		{

			tempArr[i] = arr[i]; //copy old array elements to new resized array 
		}
		//delete the old array and reassign it's values to resized array
		delete[] arr;
		arr = tempArr;
	}
	arr[size] = data;
	size = size + 1;
}

void VectorClass::copyVector(VectorClass data)
{
	delete[] arr;
	arr = new VectorStructure[1];
	size = 0;
	capacity = 1;
	for (int i = 0; i < data.getSize(); i++)
	{
		pushBack(data.arr[i]);
	}
}

void VectorClass::popBack()
{
	if (size > 0)
	{
		size = size - 1;
	}
}

void VectorClass::pushAtIndex(VectorStructure data, int index)
{
	// if index is equal to capacity then this
	// function is same as push defined above
	if (index >= 0 && index <= size)
	{
		if (index == size)
		{
			pushBack(data);
		}
		else
		{
			//push each element down 1 index starting from the max element and going down to the index. i.e., all indexes 
			for (int i = size - 1; i >= index; i--) {
				//arr[i + 1] = arr[i];
				arr[i] = arr[i+1];
			}
			arr[index] = data;
		}

		size = size + 1;
	}
	else
	{
		cout << "\nIndex out of range, pushAtIndex";
	}
}

VectorStructure VectorClass::getElement(int index)
{
	// if index is size of array
	if (index >= 0 && index < size)
	{
		return(arr[index]);
	}
	else
	{
		//cout << "\nIndex out of range, getElement";
	}
}

void VectorClass::replaceElement(VectorStructure data, int index)
{
	if (index >= 0 && index < size)
	{
		arr[index] = data;
	}
	else
	{
		//cout << "\nIndex out of range, replaceElement";
	}
}

int VectorClass::getSize()
{
	return(size);
}

VectorStructure VectorClass::frontEnd()
{
	if (size > 0)
	{
		return(arr[0]);
	}
	else
	{
		//cout << "\nVector is Empty, frontEnd";
	}
}

VectorStructure VectorClass::backEnd()
{
	if (size > 0)
	{
		return(arr[size-1]);
	}
	else
	{
		//cout << "\nVector is Empty, backEnd";
	}
}

VectorStructure VectorClass::subtractVectors(VectorStructure p1, VectorStructure p2)
{
	VectorStructure difference;
	difference.x = p1.x - p2.x;
	difference.y = p1.y - p2.y;	
	return(difference);
}

VectorStructure VectorClass::addtVectors(VectorStructure p1, VectorStructure p2)
{
	VectorStructure sum;
	sum.x = p1.x + p2.x;
	sum.y = p1.y + p2.y;
	return(sum);
}

float VectorClass::getMagnitude(VectorStructure p1, VectorStructure p2)
{
	float magnitude = sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y), 2));

	return(magnitude);
}

void VectorClass::printVector()
{
	for (int i = 0; i < size; i++) {
		cout << "\n\narr[i].x:  " << arr[i].x;
		cout << "     arr[i].y: " << arr[i].y;
	}
	cout << endl;
}


void VectorClass::vectorClear()
{
	size = 0;
}


























vectorComponentClass::vectorComponentClass()
{
	arrComponent = new float[1];    //data initially null

	//size and capacity of array both initially 0
	sizeComponent = 0;
	capacityComponent = 1;
}

vectorComponentClass::~vectorComponentClass()
{
	delete[] arrComponent;
}

void vectorComponentClass::pushBackComponent(float data)
{
	if (sizeComponent == capacityComponent) //if the current size of the array is equal to the max size of the array, then increase the capacity
	{
		capacityComponent = capacityComponent * 2;
		
		float* tempArr = new float[capacityComponent];   //allocate new memory for the increased size of array

		for (int i = 0; i < sizeComponent; i++)
		{
			tempArr[i] = arrComponent[i]; //copy old array elements to new resized array 
		}
		//delete the old array and reassign it's values to resized array
		delete[] arrComponent;
		arrComponent = tempArr;
	}

	arrComponent[sizeComponent] = data;
	sizeComponent = sizeComponent + 1;

}

void vectorComponentClass::copyComponent(vectorComponentClass data)
{
	delete[] arrComponent;
	arrComponent = new float[1];
	sizeComponent = 0;
	capacityComponent = 1;
	for (int i = 0; i < data.getSizeComponent(); i++)
	{
		pushBackComponent(data.arrComponent[i]);
	}
}

void vectorComponentClass::popBackComponent()
{
	if (sizeComponent > 0)
	{
		sizeComponent = sizeComponent - 1;
	}

}

void vectorComponentClass::pushAtIndexComponent(float data, int index)
{

	// if index is equal to capacity then this
	// function is same as push defined above
	if (index == capacityComponent)
	{
		pushBackComponent(data);
	}
	else
	{
		arrComponent[index] = data;
	}
}

float vectorComponentClass::getElementComponent(int index)
{
	// if index is size of array
	if (index >= 0 && index < sizeComponent)
	{
		return(arrComponent[index]);
	}
	else
	{
		cout << "\nIndex out of range, getElementComponent";
	}
}

int vectorComponentClass::getSizeComponent()
{
	return(sizeComponent);
}

float vectorComponentClass::frontEndComponent()
{
	if (sizeComponent > 0)
	{
		return(arrComponent[0]);
	}
	else
	{
		cout << "\nVector is Empty, frontEndComponent";
	}
}

float vectorComponentClass::backEndComponent()
{
	if (sizeComponent > 0)
	{
		return(arrComponent[sizeComponent - 1]);
	}
	else
	{
		cout << "\nVector is Empty, backEndComponent";
	}
}

void vectorComponentClass::printVectorComponent()
{

	for (int i = 0; i < sizeComponent; i++) {
		cout << "\n\narr[i]:  " << arrComponent[i];

	}
	cout << endl;
}

void vectorComponentClass::vectorClearComponent()
{
	sizeComponent = 0;
}




























ComplexPlane::ComplexPlane()
{
}


ComplexPlane::ComplexPlane(float real_in, float imaginary_in)
{
	
	real = real_in;
	imaginary = imaginary_in;
}




vectorClassComplex::vectorClassComplex()
{
	arrComplex = new ComplexPlane[1];    //data initially null

	//size and capacity of array both initially 0
	sizeComplex = 0;
	capacityComplex = 1;
}

vectorClassComplex::~vectorClassComplex()
{
	delete[] arrComplex;
}

void vectorClassComplex::pushBackComplex(ComplexPlane data)
{
	if (sizeComplex == capacityComplex) //if the current size of the array is equal to the max size of the array, then increase the capacity
	{
	
		capacityComplex = capacityComplex * 2;
		
		ComplexPlane* tempArr = new ComplexPlane[capacityComplex];   //allocate new memory for the increased size of array

		for (int i = 0; i < sizeComplex; i++)
		{
			tempArr[i] = arrComplex[i]; //copy old array elements to new resized array 
		}
		//delete the old array and reassign it's values to resized array
		delete[] arrComplex;
		arrComplex = tempArr;
	}
	arrComplex[sizeComplex] = data;
	sizeComplex = sizeComplex + 1;
}

void vectorClassComplex::popBackComplex()
{
	if (sizeComplex > 0)
	{
		sizeComplex = sizeComplex - 1;
	}
}

void vectorClassComplex::pushAtIndexComplex(ComplexPlane data, int index)
{
	// if index is equal to capacity then this
	// function is same as push defined above
	if (index == capacityComplex)
	{
		pushBackComplex(data);
	}
	else
	{
		arrComplex[index] = data;
	}
}

ComplexPlane vectorClassComplex::getElementComplex(int index)
{
	// if index is size of array
	if (index >= 0 && index < sizeComplex)
	{
		return(arrComplex[index]);

	}
	else
	{
		//cout << "\nIndex out of range, getElementComplex";
	}
}

void vectorClassComplex::replaceElementComplex(ComplexPlane data, int index)
{
	if (index >= 0 && index < sizeComplex)
	{
		arrComplex[index] = data;
	}
	else
	{
		//cout << "\nIndex out of range, replaceElementComplex";
	}
}


int vectorClassComplex::getSizeComplex()
{
	return(sizeComplex);
}

ComplexPlane vectorClassComplex::frontEndComplex()
{
	if (sizeComplex > 0)
	{
		return(arrComplex[0]);
	}
	else
	{
		//cout << "\nVector is Empty, frontEndComplex";
	}
}

ComplexPlane vectorClassComplex::backEndComplex()
{
	if (sizeComplex > 0)
	{
		return(arrComplex[sizeComplex - 1]);
	}
	else
	{
		//cout << "\nVector is Empty, backEndComplex";
	}
}

void vectorClassComplex::vectorClearComplex()
{
	sizeComplex = 0;

}








