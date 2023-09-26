#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() 
{

	ofSetCircleResolution(100);
	ofSetFrameRate(120);
	ofBackground(0);
	ofSetBackgroundAuto(true);


	traceStart = false;
}

//--------------------------------------------------------------
void ofApp::update() 
{
	if (traceStart == true)
	{
		dft->update();
	
		if(dft->isLoop() == true)
		{
			outputTraces.vectorClear();
		}
		else if (dft->isLoop() == false)
		{
			outputTraces.pushBack(VectorStructure(dft->outputPosition.getElement(dft->numPoints).x, dft->outputPosition.getElement(dft->numPoints).y));
		}
		//cout << "\n\n\n\n\n\n\n\n\n ----------------------------------------- OFAPP.CPP, update ---------------------------------";
		//cout << "\noutputTraces ";
		//outputTraces.printVector();
	}
}

//--------------------------------------------------------------
void ofApp::draw() 
{
	if (traceStart == true)
	{
		dft->draw();

		ofPushMatrix();
		ofNoFill();
		ofSetLineWidth(5);
		ofSetColor(255);
		ofBeginShape();
		for (int i = 0; i < outputTraces.getSize(); i++)
		{
			ofVertex(outputTraces.getElement(i).x, outputTraces.getElement(i).y);
			outputLines.pushBack(outputTraces.getElement(i));
		}
		ofEndShape();
		ofPopMatrix();


		//draw line from the last circle's center position to the last element of the ftX x output and the ftY y output. Effectively drawing a line from the last circle to the last ftX and ftY
		ofNoFill();
		ofSetLineWidth(1);
		ofSetColor(255);
		ofDrawLine(dft->outputPosition.getElement(dft->numPoints).x, dft->outputPosition.getElement(dft->numPoints).y, outputLines.getElement(((outputLines.getSize()) - 1)).x, outputLines.getElement(((outputLines.getSize()) - 1)).y);
	}
	else if (traceStart == false)
	{
		ofPushMatrix();
		ofNoFill();
		ofSetLineWidth(5);
		ofSetColor(255);
		ofBeginShape();

		for (int i = 0; i < mousePositions.getSize(); i++)
		{
			ofVertex(mousePositions.getElement(i).x, mousePositions.getElement(i).y);
		}
		ofEndShape();
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) 
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	traceStart = false;
	mouseInput.pushBack(VectorStructure(x - ofGetWidth() / 2, y - ofGetHeight() / 2));
	mousePositions.pushBack(VectorStructure(x, y));
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	mousePositions.vectorClear();
	outputTraces.vectorClear();
	mouseInput.vectorClear();
	traceStart = false;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	dft = new DiscreteFourierTransform[mouseInput.getSize()];
	for (int i = 0; i < mouseInput.getSize(); i++)
	{

		if (mouseInput.getElement(i).x != 0 && mouseInput.getElement(i).y != 0)  //if the inputted position is zero, the radius will be infinite
		{
			dft->inputPoints.pushBack(mouseInput.getElement(i));
		}


	}
	dft->numPoints = dft->inputPoints.getSize();
	dft->complexPlaneSettings = new ComplexPlane[dft->numPoints];
	dft->setup();
	dft->setEpicyclePosition(VectorStructure(ofGetWidth() / 2, ofGetHeight() / 2));

	traceStart = true;

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}



