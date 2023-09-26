#pragma once

#include "VectorClass.h"
#include "ofMain.h"



class DiscreteFourierTransform
{
public:

	int numPoints;  //number of vertices in the drawing/trace
	float time;  //differentiation
	bool loop;

	VectorClass inputPoints;
	VectorClass outputPosition;
	VectorStructure epicyclePosition;  //the position of the epicycle. Each fourier transform gets a single epicycle position, no need for array/pointer. Use the magnitude when possible
	ComplexPlane * complexPlaneSettings; //the complexPlaneSettings variable will have numPoints elements, and each element will be a complePlane having it's own real, imaginary, frequency, amplitude, and phaseRadians



	DiscreteFourierTransform();
	~DiscreteFourierTransform();


	void setEpicyclePosition(VectorStructure p);  //set the epicycle's origin
	void sortComplexSinusoids(ComplexPlane *complex_plane, int n);
	void implementDiscreteFourierTransform();
	void epiCycles();
	VectorStructure getOutputPosition();
	bool isLoop();  //whether or not the fourier trace is looping, will loop unless the user creates a new drawing


	void setup();
	void update();
	void draw();
};









/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
INPUTTED 2D WAVE
		- draw with mouse
		- get line coordinates
		- draw the line

DISCRETE FOURIER TRANSFORM
		- perform the Fourier transform on line coordiates, treat the drawing as a 2D wave made up of a series of points

		- the sine waves created from these input points are created in the complex plane, meaning they are complex sinusoids and are 3D, howeveer from the side they look like regular 2D sine waves

		- to get the complex sine waves, we have to use the Fourier transform, (compute the complex sum for each inputted point),  which when done will return a circle in the complex plane centered around the origin with a radius equal
		  to the amplitude of it's respective sine wave as well as the magnitude of it's complex number.
		  The complex number will be at some point on the circle with a starting position of theta(on circle) == phase(of complex sinusoid wave), and the
		  complex number will move around the path of the circle with a speed equal to the gain in frequency by the wave during each time spike. The complex sum can be interperated as a vector revolving about the circle's origin with
		  a magnitude equal to the radius of the circle (complex number magnitude) and moving with a rotation speed equal to the frequency of the complex sinusoid
					- the amplitude of the complex sinusoid == radius of the circle in complex plane == magnitude of the complex number moving around the path of it's respective circle
					- the phase of the complex sinusoid == theta of the circle in complex plane, i.e., the starting position of the complex number on it's respective circle
					- the frequency of the complex sinusoid ==  the rotation speed of the revolving vector , i.e., how fast moving around the circle
		All that is to say, the fourier transform expresses a given function as a sum of complex sinusoids which have outputs that are entirely described by circles in the complex plane, meaning, each complex sinusoid
		can be represented by a circle and a revolving vector. HENCE, we can represent a function as a sum of revolving circles and vectors concatenated tip to toe (summed together) to produce the final drawing

COMPUTE EPICYCLES
		- After we've computed all of the complex sum in terms of the phases, frequencies, and amplitudes of the complex sinusoids, the next step is to express the phases and amplitudes of the complex sinusoid wave into the
		  circle's theta, rotation speed, and radius.

		- Then from here to compute the x and y components of the complex numbers magnitude, i.e., the circle's radius, which will also be the length of the line used to link each circle to the next one

		- The traced path will be visualized using the concatenated circles in the complex plane, connected by a vector line extending from the center of one circle to the next that
		  has a magnitude and direction equal to that of the complex sum == circle's radius == sinusoid amplitude, i.e., each circle will have a line connecting it's center to the next circle's center

		- we will visualize them using a set of concatenated circles in the complex plane, connected by a vector line extending from the center of one circle to the next that
		  has a magnitude and direction equal to that of the complex sum, i.e., each circle will have a line connecting it's center to the next circle's center
					- Draw connecting lines between circles
						- draw line from current position, i, to next position, i+1

DRAW THE CONCATENATED CIRCLES LINKED BY CONCATENATED LINES
		- we will visualize them using a set of concatenated circles in the complex plane, connected by a vector line extending from the center of one circle to the next that
		  has a magnitude and direction equal to that of the complex sum, i.e., each circle will have a line connecting it's center to the next circle's center

		- Draw connecting lines between circles
						- draw line from current position, i, to next position, i+1
						- draw little circle at the end of current line, i.e., at the beginning of next circle

		- Draw circles
						- draw circle at current position with a radius equal to the distance between the current circle and the next circle
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/







/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
BASIC STEPS
		- receive inputted line coordinates and treat them as  2D waves made up of a series of points, the user drawing

		- draw the inputted line

		- Use discrete fourier transform to convert the inputted data into complex sinusoids and compute each one's amplitude, phase, and frequency

		- Compute the epicycles as a function of time, i.e., the position of each concatenated circle and it's rotating vector from the complex sinusoid's amplitude, phase, and frequency

		- Clear the inputted line and draw the epicycles as a trace of the inputted line
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/









/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
IMPLEMENTING THE FOURIER TRANSFORM

compute the properties of each sinusoid in the complex plane from the inputted points
			- frequency of complex sinusoid (each concatenated circle will have a revolving speed linearly proportional to the product of it's index and time)
			- real part  (cosine portion of euler identity)
			- imaginary part  (sine portion of euler identity)
			- phase of complex sinusoid, the arctangent of the imaginary and real parts
			- amplitude, the magnitude of the real and imaginary parts


	because we cannot use complex numbers in our program, compute the discrete fourier transform as a sum of real cosine waves and imaginary sine waves
	then from here compute the amplitude (magnitude of the complex number) to eliminate the imaginary number

	because we cannot use complex numbers in our program,use euler's formula to express the discrete fourier transform formula(a complex exponential)
	in terms of real cosine and imaginary sines:

			e^( (-j*2*PI*k*n)/N) = cos(2*PI*k*n / N) - sin(2*PI*k*n / N)


	to compute the x traces (the amplitudes outputted by each complex sinusoid) , need to use a nested for loop to first compute each complex sinusoid within the nest, and then
			X_k = sum from 0 to N-1{x_n * [ cos(2*PI*k*n / N) - i*sin(2*PI*k*n / N) ]

			WHERE:
				-   X_k == amplitude of complex sinusoid == radius of each concatenated circle == magnitude of the vectors linking the cirles

				-   The range [0,N-1] == [0,nMax] == number of inputted points

				-   x_n == inputPoints[k]

 Each complex sinusoid will have it's own properties, which are then to be added to the global array of complex sinusoids, the amplitudes of which will later be summed as the outputted positions to compute points of the path
 and then summed as concenated circles to visualize the geometric representation of the fourier transforms being done within the complex plane


 Each complex sinusoid will correspond to a concatenated circle, so add each complex sinusoid property to a global pointer variable before computing the next one


 When the concatenated circles are drawn, they need to be in order of their radius's from greatest to least, so sort the complex sinudoids by amplitude
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/





/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 TREAT THE TWO INCOMING SIGNALS AS A PAIR OF SIGNALS, RATHER THAN COMPUTING THE DISCRETE FOURIER TRANSFORM FOR EACH ONE INDIVIDUALLY
	- Formerly treated the inputted signals as an array of signals then computed the transform of each signal individually
	- NOW, treat the inputted signals as an array of pairs of signals and compute a signal transform for the position


COMPLEX NUMBER MULTIPLICATION, TREAT DISCRETE FOURIER TRANSFORM SAMPLE POINTS AS PAIRS OF POINTS T



----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/