#include "testApp.h"
#include "ofxCsv.h"
#include "math.h"

using namespace wng;

ofMesh mesh;
ofVbo vbo;
ofEasyCam cam;
ofxCsv parser;
ofTrueTypeFont font;

vector <float> longitude;
vector <float> latitude;
vector <string> countries;
vector <float> price;
vector <int> rating;

int radius = 6371;
int circumference = 40075;
int myPrice = 500;
int myRating = 3;

bool drawDistance = false;
bool drawDeal = false;
bool drawRate = true;

float myLatitude = 40.4417;
float myLongitude = -80.0000;
int myDist = 500;

//------------------------My Functions--------------------------
float radians (float deg){
    float a = (deg*3.14159)/180.0;
    return a;
}
//
vector<float> coords (float lat, float lon, int radius){
  float x = radius * cos(radians(lat)) * cos(radians(lon));
  float y = radius * cos(radians(lat)) * sin(radians(lon));
  float z = radius *sin(radians(lat));
//
  vector<float> myVec;
  myVec.push_back(x);
  myVec.push_back(y);
  myVec.push_back(z);
  return myVec;
}
void getInfo(){
    float d;
    int r;
    float p;
    cout<<"Enter distance in miles:";
    cin>>d;
    cout<<"Enter rating from 1 to 5:";
    cin>>r;
    cout<<"Enter maximum price:";
    cin>>p;
    myDist = int(d/11.3);
    myRating = r;
    myPrice = p;
}

void parseEverything(){
    for (int i = 1; i<499000; i++){
        latitude.push_back(parser.getFloat(i,12));
        longitude.push_back(parser.getFloat(i,13));
        countries.push_back(parser.getString(i,7));
        price.push_back(parser.getFloat(i,12));
        rating.push_back(parser.getInt(i, 2));
    }
}

float distance( float a1, float b1, float c1, float a2, float b2, float c2){
    float d = sqrt(pow((a2-a1),2) + pow((b2-b1),2) + pow((c2-c1),2));
    return d;
}

void generatePoints (){
    mesh.clear();
    for (int i = 1; i<499000; i++){
        vector<float> a;
        vector<float> b;
        a = coords(latitude[i], longitude[i], 350);
        b = coords(myLatitude, myLongitude, 350);
        mesh.addVertex(ofVec3f(a[0], a[1], a[2]));
        float d = distance(b[0],b[1],b[2],a[0],a[1],a[2]);
        int r = rating[i];
        int p = price[i];
        if ((d<=myDist) & (r == myRating) & (p <= myPrice)){
            mesh.addColor(ofFloatColor(255,0,0));
        } else {
            mesh.addColor(ofFloatColor(255,255,255));
        }
    }
}

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);

    parser.loadFile(ofToDataPath("hotel.txt"),"~");
    parseEverything();
    getInfo();
    generatePoints();

    font.loadFont("232MKL.TTF", 16, false);
}
//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    //ofDrawBitmapString("hello", 100,100);
    cam.begin();
    //ofScale(.001,.001,.001);
    mesh.drawVertices();

//    font.drawString("Maximum Price: $" + ofToString(myPrice), -100,0);
//    font.drawString("Minimum Rating: " + ofToString(myRating),-90,40);

    cam.end();


}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == 'g'){
        getInfo();
        generatePoints();
    }

    if (key == 'l'){
        cout<<"Enter latitude";
        cin>>myLatitude;
        cout<<"Enter longitude";
        cin>>myLongitude;
        generatePoints();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

//--------------------------------------------------------------

// Function Graveyard

//void generatePoints (){
//    mesh.clear();
//    for (int i = 1; i<499000; i++){
//        vector<float> a;
//        a = coords(latitude[i], longitude[i], 350);
//        mesh.addVertex(ofVec3f(a[0], a[1], a[2]));
//        if ((rating[i] <= myRating) & (price[i] <= myPrice)){
//            mesh.addColor(ofFloatColor(255,0,0));
//        } else {
//            mesh.addColor(ofFloatColor(255,255,255));
//        }
//    }
//}


//float getDistance (float lat2, float lon2){
//    float lat_1= radians(myLatitude);
//    float lon_1 = radians(myLongitude);
//    float lat_2= radians(lat2);
//    float lon_2 = radians(lon2);
//    float theta = 3.14159*(lon_2-lon_1)/180;
//
//    float a = sin(lat_1)*sin(lat_2) + cos(lat_1)*cos(lat_2)*cos(theta);
//    float b = acos(a);
//    float c = b*180/3.14159;
//    float d = c*60*1.1515;
//
//    return d*1.609344;
//}


//void generatePoints (){
//    mesh.clear();
//    for (int i = 1; i<499000; i++){
//        vector<float> a;
//        vector<float> b;
//        a = coords(latitude[i], longitude[i], 350);
//        b = coords(myLatitude, myLongitude, 350);
//        mesh.addVertex(ofVec3f(a[0], a[1], a[2]));
//        float d = distance(b[0],b[1],b[2],a[0],a[1],a[2]);
//        int r = rating[i];
//        int p = price[i];
//        if (drawDistance == true){
//            if (d<=140){
//                mesh.addColor(ofFloatColor(255,0,0));
//            } else if ((d>140) & (d<=280)){
//                mesh.addColor(ofFloatColor(255,255,0));
//            } else if ((d>280) & (d<=420)){
//                mesh.addColor(ofFloatColor(0,255,0));
//            } else if ((d>420) & (d<=560)){
//                mesh.addColor(ofFloatColor(0,255,255));
//            } else {
//                mesh.addColor(ofFloatColor(0,0,255));
//            }
//        }
//        if (drawRate == true){
//            if (r == myRating){
//                mesh.addColor(ofFloatColor(255,0,0));
//            } else {mesh.addColor(ofFloatColor(255,255,255));}
//        }
//        if (drawDeal == true){
//            if (p <= myPrice){
//                mesh.addColor(ofFloatColor(255,0,0));
//            } else {mesh.addColor(ofFloatColor(255,255,255));}
//        }
//    }
//}
