/* 
Name: Brandon Fenske
Date: 04/05/22
Description: Multidimensional Arrays
Usage: Functions- int **makeParticleMap, bool moveExists, int findMax, void NormalizeMap,
 run as g++ Assignment4.cpp -o assn4
        ./assn4
*/  
#include <iostream>
#include <time.h> //includes random function
#include <math.h> //implements mathematics for sqrt
#include <fstream> //implements file i/o
using namespace std;

int **makeParticleMap(int width, int height, int windowX, int windowY, int radius, int numParticles, int maxLife){ //generates map data
int ** grid; //initialize our map with double pointer
     
double theta; //set variables to describe dropzone as doubles
double r;
double rando = (double) rand() / (RAND_MAX); //generate a random number
grid = new int *[height];                    //initialize map array

for(int i =0;i<height;i++){ 
        grid[i] = new int[width]; //now we set initialize width in grid array
        }
for(int i =0;i<height;i++){
        for(int j=0;j<width;j++){
                grid[i][j]=0;    // fill the map with 0's
        }}
for (int drop=0;drop<numParticles;drop++) {          //generation of dropzone
        r = radius * sqrt(rando); 
        theta = rando * 2 * (atan(1)*4);
        int xdrop = (int)(windowX + r * cos(theta)); 
        int ydrop = (int)(windowY + r * sin(theta)); //function for the dropzone

bool moveExists(int** map, int width, int height, int x, int y);   //call move exists function
for (int particle = 0; particle < maxLife; particle++) {
        if (moveExists(grid, width, height, xdrop, ydrop)==true) { //if moveexists function returns true
                int moves[8][2]= {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //directions for any 8 direction
                bool mymove =true;
        while (mymove == true){         //aslong as mymove is true we keep moving
                int movewhere = rand() % 8; 
                int ymove = ydrop + moves[movewhere][1];
                int xmove = xdrop + moves[movewhere][0];  
        if (xmove >= 0 && ymove >= 0) { //if our move is greater than 0 and
                if(xmove<width && ymove <height){ //again,if its less than the map dimensions 
                        if (grid[ymove][xmove] <= grid[ydrop][xdrop]) { //if moves if less than blocks explored
                        xdrop = xmove; 
                        ydrop = ymove;  //set them equal
                        grid[ydrop][xdrop] = grid[ydrop][xdrop] + 1;  //and add 1 to the drop particle
                        mymove = false; //reset while loop
        }}}}}
}
}
return grid;
}    
int findMax(int** map, int width, int height) { //max function called for to set parameters for map size 
int maxmap = 0; 
for (int y=0;y<height;y++) { 
        for (int x=0;x<width;x++) {
                if (map[y][x] > maxmap) {
                maxmap = map[y][x]; //this just finds the max value of the map
                        }}}
        return maxmap; //return maxmap for normalizing 
}

bool moveExists(int** map, int width, int height, int x, int y) { //move exists function
int moves[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; //moves available
for (int i=0;i<8;i++) { //iterate
        int xmove = x + moves[i][0]; //x and y are xdrop and ydrop
        int ymove = y + moves[i][1]; //iterate through moves 
                if (xmove >= 0 && ymove >= 0 && xmove < width && ymove < height) { //if our move is in bounds
                        if (map[ymove][xmove] <= map[y][x]) { //if we have a move available return true
                        return true;
                        }}}
        return false;
}

void normalizeMap(int** map, int width, int height, int maxVal) {//create function for normalizing map
for(int y=0;y<height;y++) { 
        for(int x=0;x<width;x++) {  //iterate through map 
                map[y][x] = (map[y][x] / ((double) maxVal) * 255); //and divide by every value mult to get every value between 0 and 1
}}}
////////////////////////////////////////////main/////////////////////////////////////////////
int main(){


int width,height,windowX,windowY,radius,numParticles,maxLife,water; //set variables as ints
srand(time(NULL));           //for random number generation, once in main
ofstream myoutput; //tell program we want an output file

myoutput.open("island.txt"); //open island.txt

cout << "Welcome to Brandon's CSE240 Island Generator! \n"; //user input starts
cout << "Enter Grid Width:";
cin >> width;
cout << "Enter Grid Height:";
cin >> height;

cout << "Enter drop-zone x-coordinate (0 - <width>):";
while(true){                 //create while loops to ask again if the answer is not in parameters
        cin >> windowX; 
        if(windowX>width){
                cout << "Dropzone cannot be outside the map,reenter:\n";
        }else break;}

cout << "Enter drop-zone y-coordinate (0 - <height>):";
while(true){                //if the coordinates for x or y are outside the map, reenter
        cin >> windowY;
        if(windowY>height){
            cout << "Dropzone cannot be outside the map,reenter:\n";
        }else break;}
    
cout << "Enter drop-zone radius (minimum 2):";
while(true){                //minimum raiduius of 2, max cannot be larger than map
        cin >> radius;
        if(radius<2 || radius>width || radius>height){
           cout << "Radius cannot be larger than the map or is too small,reenter:\n"; 
        }else break;}
    
cout << "Enter number of particles to drop:";
cin >> numParticles;
cout << "Enter max life of particles: ";
cin >> maxLife;

cout << "Enter value for waterline (40-200): ";
while(true){                //parameters given for the waterline
        cin >> water;
        if(water<40 || water >200){
            cout << "Invalid water level,reenter:\n";  
        }else break;}

int ** myisland = makeParticleMap(width,height,windowX,windowY,radius,numParticles,maxLife); //call map generating function
int maxVal = findMax(myisland, width, height); // didnt need this function really except for normalizing, we send maxVal
normalizeMap(myisland, width, height, maxVal); // normalize the map to be userfriendly


char** polish; //polish the map in main
polish = new char*[height];
for(int m=0;m<height;m++) { //set array to iterate through
        polish[m] = new char[width];
} 
int landzone = 255-water; //set our parameters to only land
for(int m=0;m<height;m++) {
        for(int n=0;n<width;n++) {
                if (myisland[m][n] < (.5 * water)) {  //less then 50% we get deep water
                polish[m][n] = '#';
                }
                else if (myisland[m][n] > (water*.5) && myisland[m][n] <= water) { //50-100% we get shallow water
                polish[m][n] = '~'; 
                }
                else if (myisland[m][n] < (water + (0.15 * landzone))) {          //1-1.15 we have sand
                polish[m][n] = '.';
                }
                else if (myisland[m][n] < (water + (0.40 * landzone)) && myisland[m][n] >= (water + (0.15 * landzone))) {
                polish[m][n] = '-';                                               //1.15-1.4 we have grass or plains
                }
                else if ( myisland[m][n] < (water + (0.80 * landzone))&& myisland[m][n] >= (water + (0.40 * landzone))) {
                polish[m][n] = '*';                                               //1.4-1.8 is forests
                }
                else{
                polish[m][n] = '^';                                               //1.8<is mountains
                }}}
       
for(int y=(height-1);y>=0;y--) {
        for(int x=0;x<width;x++) {
        cout << polish[y][x];     //print the completed map to display
        myoutput << polish[y][x]; //print the completed map to file
}
cout << "\n";      //correct display
myoutput <<"\n";
}
myoutput.close(); //close output file
free (myisland);
free (polish);    //free memory 
return 0;
}
