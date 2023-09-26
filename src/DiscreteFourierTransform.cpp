#include "DiscreteFourierTransform.h"



DiscreteFourierTransform::DiscreteFourierTransform()
{
	epicyclePosition.x = 0;
	epicyclePosition.y = 0;
	time = 0;
	loop = false;
}

DiscreteFourierTransform::~DiscreteFourierTransform()
{


}

void DiscreteFourierTransform::setEpicyclePosition(VectorStructure p)
{
    epicyclePosition = p;

}


void DiscreteFourierTransform::sortComplexSinusoids(ComplexPlane* complex_plane, int n)
{
    n = numPoints;

    //assume no swaps need to be made
    //bool swaps = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (complex_plane[j + 1].amplitude > complex_plane[j].amplitude)
            {
                ComplexPlane tempComplexPlane = complex_plane[j];
                complex_plane[j] = complex_plane[j + 1];
                complex_plane[j + 1] = tempComplexPlane;
            }
        }
    }

}



void DiscreteFourierTransform::implementDiscreteFourierTransform()
{


    for (int n = 0; n < numPoints; n++)
    {
        //reset each real and imaginary component after they are stored
        ComplexPlane complexSum(0, 0); //complexPlane represents a complex number 
        float real = 0, imaginary = 0;
        complexSum.real = 0, complexSum.imaginary = 0;;


        for (int k = 0; k < numPoints; k++)
        {
            //each complex vector will have it's own real, imaginary, and theta components
            float theta = float(2 * PI * k * n) / (float)numPoints;
            ComplexPlane complexPlane;
            real = cos(theta);
            imaginary = sin(theta);
            complexPlane.real = inputPoints.getElement(k).x * real + inputPoints.getElement(k).y * imaginary;
            complexPlane.imaginary = inputPoints.getElement(k).y * real - inputPoints.getElement(k).x * imaginary;

            //the fourier coefficients, complex products
            complexSum.real += complexPlane.real;
            complexSum.imaginary += complexPlane.imaginary;
        }
        complexSum.real = complexSum.real / numPoints;
        complexSum.imaginary = complexSum.imaginary / numPoints;

        complexPlaneSettings[n].real = complexSum.real;
        complexPlaneSettings[n].imaginary = complexSum.imaginary;
        complexPlaneSettings[n].frequency = n;
        complexPlaneSettings[n].amplitude = sqrt(complexSum.real * complexSum.real + complexSum.imaginary * complexSum.imaginary);
        complexPlaneSettings[n].phaseRadians = atan2(complexSum.imaginary, complexSum.real);
    }
    sortComplexSinusoids(complexPlaneSettings, numPoints);  
   // cout << "\n\n\n\n\n\n\n\n\n ----------------------------------------- implementDiscreteFourierTransform ---------------------------------";
   // for (int i = 0; i < numPoints; i++)
   // {
   //     cout << "\n\n ---  complexPlaneSettings[i].amplitude: " << complexPlaneSettings[i].amplitude;
   // }
}


void DiscreteFourierTransform::epiCycles()
{
    VectorStructure pos(ofGetWidth() / 2, ofGetHeight() / 2);

    outputPosition.vectorClear();
    outputPosition.pushBack(pos);
    
    for(int i = 0; i < numPoints; i++)
    {
        int freq = complexPlaneSettings[i].frequency;
        float radius = complexPlaneSettings[i].amplitude;
        float phase = complexPlaneSettings[i].phaseRadians;

        pos.x += radius * cos(freq * time + phase);
        pos.y += radius * sin(freq * time + phase);

        outputPosition.pushBack(pos);
    }
    //cout << "\n\n\n\n\n\n\n\n\n ----------------------------------------- epiCycles output, AFTER ---------------------------------";
    //outputPosition.printVector();

    float dt = TWO_PI / numPoints;
    time += dt;
    if (time > (float)TWO_PI)
    {
        time = 0;
        loop = true;
    }
    else if (time <= (float)TWO_PI)
    {
        loop = false;
    }
}

VectorStructure DiscreteFourierTransform::getOutputPosition()
{
    return(outputPosition.getElement(outputPosition.getSize()));
}

bool DiscreteFourierTransform::isLoop()
{
	return(loop);
}

void DiscreteFourierTransform::setup()
{
    implementDiscreteFourierTransform();
}
void DiscreteFourierTransform::update()
{
    epiCycles();
}
void DiscreteFourierTransform::draw()
{
    ofPushMatrix();
    ofFill();
    ofSetLineWidth(1);
    ofSetColor(255);

    ofDrawCircle(outputPosition.getElement(0).x, outputPosition.getElement(0).y, 2);
    for (int i = 0; i < numPoints - 1; i++)
    {
        ofSetColor(ofColor(255), 100);
        ofNoFill();
        ofSetLineWidth(1);
        ofDrawLine(outputPosition.getElement(i).x, outputPosition.getElement(i).y, outputPosition.getElement(i+1).x, outputPosition.getElement(i+1).y);
        ofDrawCircle(outputPosition.getElement(i).x, outputPosition.getElement(i).y, 2);

        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(ofColor(255), 100); 
        ofDrawCircle(outputPosition.getElement(i).x, outputPosition.getElement(i).y, outputPosition.getMagnitude(outputPosition.getElement(i + 1), outputPosition.getElement(i)));
    }
    ofPopMatrix();
}
