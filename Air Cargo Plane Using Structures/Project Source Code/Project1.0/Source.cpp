//Air Cargo Plane Using Structures

//This program simulates the loading of a cargo plane.
#include<iostream> //Files/Headers that must be included
#include <string>  //Files/Headers that must be included
#include <fstream> //Files/Headers that must be included
#include <iomanip> //Files/Headers that must be included
using namespace std;
//Cargo Structure.
struct Cargo{
	string label; //Stores the name of the cargo
	int height;   //Stores the height of the cargo, integer value only
	int width;    //Stores the width of the cargo, integer value only
	int length;   //Stores the length of the cargo, integer value only
	double weight;  //Stores the weight of the cargo, double value only.
	// Initialize member values, upon creation of the object to prevent errors.
	Cargo() :label(""), height(0), width(0), length(0), weight(0){}
	//Funtion initCargo. This funtion will set the values of the cargo object that is passed in.
	//Must pass the address of a cargo object,height,width,length,weight and label to be set
	void initCargo(Cargo* cargo,int height, int width, int length, double weight, string label){
		cargo->label = label;
		cargo->height = height;
		cargo->width = width;
		cargo->length = length;
		cargo->weight = weight;
	}
	//Funtion cargoWeight. Returns the weight of the cargo object that is passed in.
	double cargoWeight(Cargo cargo){
		return cargo.weight;
	}
	//Funtion cargoVolume. Returns the volume(height*width*length) of the cargo object that is passed in.
	int cargoVolume(Cargo cargo){
		return cargo.height*cargo.width*cargo.length;
	}
	//Funtion printCargo. Will print out the values of the cargo object that is passed in.
	//The output format is: Label   Weight   Volume   Dimensions(L*W*H)
	void printCargo(Cargo cargo){
		cout << fixed; //Change from exponention format to standard format
		cout << setw(15) << cargo.label 
			<< setw(15) << setprecision(2) << cargo.weight  //Setting the output of weight to 2 decimal places
			<< setw(12) << cargo.cargoVolume(cargo) 
			<< setw(3) << cargo.length << setw(4) << " X " << setw(2) << cargo.width << setw(4) << " X "  << cargo.height << endl;
	
	}
};
//Funtion loadFile. This funtion will load the "allCargo.txt" external file and input the data within that file into a Cargo object array.
//loadFile funtion returns the number of cargos that was successfully loaded into the cargo array.
//loadFile funtion will throw an const char* exception if there was an error in the file or loading process.
//loadFile funtion will return the usedWeight and usedVolume by use of pointers
//The file must be in precise format:
//label= Name
//weight= 999
//height= 999
//width= 999
//length= 999
int loadFile(Cargo* allCargo, int size, double maxWeight, double*  usedWeight, int maxVolume, int* usedVolume){
	string holder1;  //A holder for the value that was inputed from the file
	string holder2;  //Second holder for the value that was inputed from the file
	//heightCheck,lengthCheck and widthCheck is used for checking when all three of the values have been inputed.
	//The volume of the cargo can only be calculated after all three has been inputed. The used of these booleans are used for checking that.
	//volume is calculated after all three booleans are true. After calculation the bools will be reset to false.
	bool heightCheck = false;
	bool lengthCheck = false;
	bool widthCheck = false;
	//Integer cargoCount must be set to negative one due to current limitations of the file data input algorithm.
	//cargoCount stores the number of cargos that was successfully loaded into the cargo object array.
	int cargoCount = (-1); 
	fstream file; //Creates a file stream named file.
	file.open("allCargo.txt"); //attempts to open the allCargo.txt file
	try{ //Error handling. Trys to pull the data from the file and input the data into the Cargo object array.
		if (file.is_open()){ //Checks if the file has successfully open. Will throw a const char* with value of "File could not be open" if the file is not open.
			while (file >> holder1 >> holder2){ //Beginning of the loop that will grab the data form the file. The loop will continue to grab data untill it reach a error or the end of file.
				
				if (holder1 == "label="){ //Trys to find a label= setting in file 
					if (cargoCount < size){
						cargoCount++;//increments the cargoCount after loop finds a label= setting. 
						allCargo[cargoCount].label = holder2; //If a label= is found then the next value should be the name of the label. The name will be placed into the label of the cargo.
					}
					else{
						//Will throw a const char* exception if the file contains more labels then the cargo object array can hold. And then breaks out of the loop
						throw "Max Cargo Limit Reached";
						break;
					}
				}
				else if (holder1 == "weight="){//Trys to find a weight= setting after a label= is found.
					//After finding a weight= setting, the next value should be the value of the weight to be inputed.
					//converts the string to a double then sets the weight of the cargo. Using strings instead of a double for holder2 helps prevents some file errors.
					allCargo[cargoCount].weight = stod(holder2);
					*usedWeight = *usedWeight + allCargo[cargoCount].weight; //updates the usedWeight
					if (*usedWeight > maxWeight){ 
						//Will throw a const char* exception if the file contains more weight then the cargo object array can hold. And then breaks out of the loop
						throw "Max Weight Limit Reached";
						break;
					}

				}
				else if (holder1 == "height="){
					//converts the string to a double then sets the height of the cargo. Using strings instead of a double for holder2 helps prevents some file errors.
					allCargo[cargoCount].height = stoi(holder2);
					heightCheck = true; //Sets the heightCheck bool to true after a height have been found.
				}
				else if (holder1 == "width="){
					//converts the string to a double then sets the width of the cargo. Using strings instead of a double for holder2 helps prevents some file errors.
					allCargo[cargoCount].width = stoi(holder2);
					widthCheck = true;//Sets the widthCheck bool to true after a height have been found.
				}
				else if (holder1 == "length="){
					//converts the string to a double then sets the length of the cargo. Using strings instead of a double for holder2 helps prevents some file errors.
					allCargo[cargoCount].length = stoi(holder2);
					lengthCheck = true;//Sets the lengthCheck bool to true after a height have been found.
				}
				else{
					//If the file contains a setting other then "label=" "weight=" "height=" "width=" "length="
					//A const char* exception will be thrown
					throw "Error in file";
				}
				
				if (heightCheck && lengthCheck && widthCheck){
					//Checks height,length and width have been set
					//If true the algorithm will check and upate the volume.
					*usedVolume = *usedVolume + allCargo[cargoCount].cargoVolume(allCargo[cargoCount]);//Updates the usedVolume value
					//resets all the check booleans back to false after volume have been updated
					heightCheck = false;
					lengthCheck = false;
					widthCheck = false;
					if (*usedVolume > maxVolume){
					    //Checks if the usedVolume does not reach the max volume.
						//If usedVolume reach the max volume. A const char* exception will be thrown then breaks out of the loop.
						throw "Max Volume Limit Reached";
						break;
					}
				}

			}
		}
		else{
			//A const char* exception will be thrown if the file could not be open
			throw "File could not be open";
		}
	}
	catch (const char* exHandler){
		//exception handler. Resets all the values of the cargo object array back to its defaults if there was any errors found in trying to input data from the file.
		for (int i = 0; i <= cargoCount;i++){
			allCargo[i].label = "";
			allCargo[i].weight = 0;
			allCargo[i].length = 0;
			allCargo[i].height = 0;
			allCargo[i].width = 0;
		}
		*usedWeight = 0; //resets usedWeight and usedVolume after reseting the cargo object array.
		*usedVolume = 0;
		cargoCount = 0;
		throw exHandler;//Rethrows the exception to the funtion caller, after resetting the array.
	}
	file.close(); //Close the file
	return cargoCount; //returns the number of cargos that was loaded
}
//Funtion addCargo. Will attempt to add a cargo to the cargo object array that is passed in.
//The funtion will throw a const char* exception if it was unable to add the cargo due to exceeding the maxWeight,maxVolume or max number of cargos that the cargo array can fit.
//Values to pass in:
//A cargo object array, The current number of cargos loaded in the array, the size of the array, maxWeight, address of usedWeight,maxVolume,Address of usedVolume,
//label,height,width,length and weight to be added.
void addCargo(Cargo* allCargo, int* cargoCount, int size, double maxWeight, double* usedWeight, int maxVolume, int* usedVolume, string label, int height, int width, int length, double weight){

	*cargoCount = *cargoCount+ 1; //increase the cargoCount, cargoCount is used to point to the next available cargo space.

	if (*cargoCount >= size){
		//checks if the cargoCount is not greater then the size of the cargo array
		//if it is greater, then cargoCount will point back to the last cargo in the array, and then throw a exception to the caller.
		*cargoCount--;
		throw "Cargo Limit Reached";
	}
	else if (*usedWeight >= maxWeight || (*usedWeight + weight) > maxWeight){
		//Checks if the current usedWeight is not greater then the maxWeight,then checks if the usedWeight plus the weight of the cargo to be added is not greater then the maxweight.
		//if it is greater, then cargoCount will point back to the last cargo in the array, and then throw a exception to the caller.
		*cargoCount--;
		throw "Weight Limit Reached";
	}
	else if (*usedVolume >= maxVolume || (*usedVolume + (height*width*length)) > maxVolume){
		//Checks if the current usedVolume  is not greater then the maxVolume ,then checks if the usedVolume  plus the weight of the cargo to be added is not greater then the maxVolume.
		//if it is greater, then cargoCount will point back to the last cargo in the array, and then throw a exception to the caller.
		*cargoCount--;
		throw "Volume Limit Reached";
	}
	else{
		//If no error was found then the cargo will be added to the cargo object array.
		*usedWeight = *usedWeight + weight; //updates the used weight
		*usedVolume = *usedVolume + (height * width * length); //updates the used volume
		allCargo[*cargoCount].initCargo(&allCargo[*cargoCount],height,width,length,weight,label); //sets the values of the unused cargo object in that array that was passed in.
	}
}
//Funtion loadPlane. Inputs,verifies and loads all user data.
//Must pass a cargo object array, size of the array,maxWeight,address of usedWeight,maxVolume,address of usedVolume
void loadPlane(Cargo* allCargo,int size,double maxWeight, double* usedWeight, int maxVolume, int* usedVolume){
	//temporary variable that holds the values before actually loading the data into the cargo
	string label;
	int height = 0;
	int width = 0;
	int length = 0;
	double weight = 0;
	bool run = true; //bool run controls when  the funtion stops asking the user for cargo data
	int cargoCount = 0; //cargoCount holds the current number of cargos loaded

	try{
		//trys to load the file
		//returns the number of cargos loaded to the cargoCount variable
		//loadfile  will throw a exception of there was any kind of error in the file loading process
		cargoCount = loadFile(allCargo, size, maxWeight, usedWeight, maxVolume, usedVolume);
	}
	catch (const char* exhandler){
		//handler that will handle the exceptions rethrown by loadfile.
		if (exhandler == "Max Cargo Limit Reached"){
			cout << "Max Cargo Limit Exceed, File could not be loaded!!!\n\n";
			//Tells the user that the cargo limit was exceed and that the file could not be loaded.
			//cargo limit is the number of cargos the array can hold.
		}
		else if (exhandler == "Max Weight Limit Reached"){
			cout << "Max Weight Limit Exceed, File could not be loaded!!!\n\n";
			//Tells the user that the weight limit was exceedand that the file could not be loaded.
		}
		else if (exhandler == "Max Volume Limit Reached"){
			cout << "Max Volume Limit Exceed, File could not be loaded!!!\n\n";
			//Tells the user that the volume limit was exceed and that the file could not be loaded.
		}
		else if (exhandler == "Error in file"){
			//Tells the user that there was a error in the file.
			//Then it will give the user an example of how the file should look like
			cout << "Error in file, Please make sure file is in correct format!!!\n\n";
			cout << "Example:\n\n"
				<< "label= Name\n"
				<< "weight= 999\n"
				<< "height= 999\n"
				<< "width= 999\n"
				<< "length= 999\n";
		}
		else if (exhandler == "File could not be open"){
			//Tells the user that the file could not be open.
			cout << "File could not be open!!!\n\n";
		}
		else{
			//Tells the user that a unknown error was found.
			cout << "Unknown Error Found!!!\n\n";
		}
		run = false; //Stops/skips the whole loading process if the allCargo file was not loaded.
	}
	if (run){
		//If no erros was found in loading the file, will tell the user that the file was sucessfully loaded
		cout << "File Successfully Loaded.\n";
		//Tells the user what to do next
		cout << "Enter cargos to be loaded. Enter quit for the label to quit loading.\n\n";
	}
	while (run){
		//This loop will continue to prompt the user for cargo data untill the user enters "quit" as the label.
		//This loop will only run if there was no error in the file loading process.
		cout << "\nInput Label:  "; //Ask for label
		cin >> label;
		if (label == "quit" || label == "Quit"){ //Checks if the label inputed was quit
			//If the label inputed was quit, the loop will end.
			run = false;//ends loop
			continue;//skips the rest of the loop because the user quited.
		}
		else{//If quit was not entered, will ask for weight next.
			while (true){//This loop will continue to ask the user for the weight untill a correct value is entered
				try{
					//trys to get a value from the user
					cout << "Input Weight: ";
					cin >> weight;
					if (cin.fail() || weight < 0){
						//If the user enters a weight less then zero or enters a letter,
						//a exception will be thrown.
						throw "ERROR";
					}
					else
					{
						//if there was no error in the weight input, will break out of the input error checking loop.
						break;
					}
				}
				catch (const char* exHandler){
					//catch the exception thrown.
					//Resets and clears the cin stream/buffer
				    cin.clear();
					cin.ignore(255, '\n');
					cout << "Error in weight input, please try again.\n"; //Ask the user to try again.
					//Loops back up to the beginning of the weight input loop.
				}
			}
			while (true){//This loop will continue to ask the user for the height untill a correct value is entered
				try{
					//trys to get a value from the user
					cout << "Input height: ";
					cin >> height;
					if (cin.fail() || height < 0){
						//If the user enters a height less then zero or enters a letter,
						//a exception will be thrown.
						throw "ERROR";
					}
					else
					{
						//if there was no error in the height input, will break out of the input error checking loop.
						break;
					}
				}
				catch (const char* exHandler){
					//catch the exception thrown.
					//Resets and clears the cin stream/buffer
					cin.clear();
					cin.ignore(255, '\n');
					cout << "Error in height input, please try again.\n";//Ask the user to try again.
					//Loops back up to the beginning of the height input loop.
				}
			}
			while (true){//This loop will continue to ask the user for the width untill a correct value is entered
				try{
					//trys to get a value from the user
					cout << "Input width:  ";
					cin >> width;
					if (cin.fail() || width < 0){
						//If the user enters a width less then zero or enters a letter,
						//a exception will be thrown.
						throw "ERROR";
					}
					else
					{
						//if there was no error in the width input, will break out of the input error checking loop.
						break;
					}
				}
				catch (const char* exHandler){
					//catch the exception thrown.
					//Resets and clears the cin stream/buffer
					cin.clear();
					cin.ignore(255, '\n');
					cout << "Error in width input, please try again.\n";//Ask the user to try again.
					//Loops back up to the beginning of the width input loop.
				}
			}

			while (true){//This loop will continue to ask the user for the length untill a correct value is entered
				try{
					//trys to get a value from the user
					cout << "Input length: ";
					cin >> length;
					if (cin.fail() || length < 0){
						//If the user enters a length less then zero or enters a letter,
						//a exception will be thrown.
						throw "ERROR";
					}
					else
					{
						//if there was no error in the length input, will break out of the input error checking loop.
						break;
					}
				}
				catch (const char* exHandler){
					//catch the exception thrown.
					//Resets and clears the cin stream/buffer
					cin.clear();
					cin.ignore(255, '\n');
					cout << "Error in length input, please try again.\n";//Ask the user to try again.
					//Loops back up to the beginning of the length input loop.
				}
			}
		}
		try{
			//Trys to load/add the data that the user inputed into the cargo object array.
			//Must pass in the cargo object array, address of cargoCount, size of array, maxWeight, usedWeight, maxVolume, usedVolume, label, height, width, length and weight.
			//addcargo will throw  a exception if the cargo can not be loaded, due to exceeding a value.
			addCargo(allCargo,&cargoCount,size,maxWeight,usedWeight,maxVolume,usedVolume,label, height, width, length, weight);
		}
		catch (const char* exHandler){
			//handler that handlers the exception thrown by addCargo funtion
			if (exHandler == "Cargo Limit Reached"){
				//Tells the user the reason the cargo could not be loaded.
				cout << "Cargo Limit Reached, Cargo could not be loaded.\n";
			}
			else if (exHandler == "Weight Limit Reached"){
				//Tells the user the reason the cargo could not be loaded.
				cout << "Weight Limit Reached, Cargo could not be loaded.\n";
			}
			else if (exHandler == "Volume Limit Reached"){
				//Tells the user the reason the cargo could not be loaded.
				cout << "Volume Limit Reached, Cargo Could not be loaded.\n";
			}
			else{
				//Tells the user the reason the cargo could not be loaded.
				cout << "A Limit Was Reached, Cargo could not be loaded.\n";
			}
		}
	}

}
//Funtion printWeight prints out the maxWeight, usedWeight, and unusedWeight
void printWeight(double maxWeight, double usedWeight){
	cout << fixed;//Change from exponention format to standard format
	//couts all weight values in 2 decimal places.
	cout << "Maximum Cargo Weight: " << setprecision(2) << maxWeight << endl;
	cout << "Used Cargo Weight   : " << setprecision(2) << usedWeight << endl;
	cout << "Unused Cargo Weight : " << setprecision(2) << maxWeight - usedWeight << "\n\n";
}
//Funtion printVolume prints out the maxVolume, usedVolume and unusedVolume
void printVolume(int maxVolume, int usedVolume){
	cout << "Maximum Cargo Volume: " << maxVolume << endl;
	cout << "Used Cargo Volume   : " << usedVolume << endl;
	cout << "Unused Cargo Volume : " << maxVolume - usedVolume << "\n\n";
}
//Funtion printHeaviest will print out the heaviest cargo.
//Must pass in the cargo object array, and the size of it.
void printHeaviest(Cargo* allCargo, int size){
	double heaviest = 0; //holds the weight of the heaviest cargo
	int location = 0; //holds the location in the array of the heaviest cargo

	for (int i = 0; i < size; i++){//loops through the cargo array to find the heaviest cargo.
		if (allCargo[i].cargoWeight(allCargo[i]) > heaviest){
			heaviest = allCargo[i].cargoWeight(allCargo[i]); //updates the heaviest variable and its location.
			location = i;
		}
	}
	cout << fixed;//Change from exponention format to standard format
	//couts all weight values in 2 decimal places.
	cout << "Heaviest container weighed     : " << setprecision(2) <<heaviest << " Pounds\n";
	cout << "Located at location number     : " << location << "\n\n"; //outputs the location of the heaviest cargo

}
//Funtion printLargest will print out the largest cargo.
//Must pass in the cargo object array, and the size of it.
void printLargest(Cargo* allCargo, int size){
	int largest = 0;//holds the volume of the largest cargo
	int location = 0;//holds the location in the array of the largest cargo

	for (int i = 0; i < size; i++){//loops through the cargo array to find the largest cargo.
		if (allCargo[i].cargoWeight(allCargo[i]) > largest){
			largest = allCargo[i].cargoVolume(allCargo[i]);//updates the largest variable and itslocation.
			location = i;
		}
	}
	cout << "Largest container had volume of: " << largest << " Cubic Inches\n";
	cout << "Located at location number     : " << location << "\n\n";//outputs the location of the largest cargo
}
//Funtion printCargo will print out all the cargos in the cargo object array. In table format/layout
//Must pass in a cargo object array and its size
void printCargo(Cargo* allCargo, int size){
	//Intro message to tell the user that the values are a table of cargo containers that is loaded.
	cout << "\n-------------------------Table of Cargo Containers-------------------------\n";
	cout << left << setw(12) << "Location #" << setw(15) << "Label" << setw(15) << "Weight" << setw(12) << "Volume" << "Dimensions\n\n";
	//Loop that will output the values.
	for (int i = 0; i <= size-1; i++){
		//Checks if the cargo is empty or not.
		//Will not print out empty cargo labels.
		if (!allCargo[i].label.empty()){
			cout << setw(12) << i;
			allCargo[i].printCargo(allCargo[i]); //Calls the cargo funtion that prints out the cargo values.
		}
	}
}
void main(){
	double maxWeight = 50000; //Set the maxWeight of the plane
	double usedWeight = 0;    //Set the usedWeight of the plane, should start at zero
	int maxVolume = 70000;    //Set the maxVolume of the plane
	int usedVolume = 0;       //Set the usedVolume of the plane, should start at zero
	const int sizeof_cargoArray = 200;//Sets the size of the cargo object array. The size should be atleast greater or equals to the number of cargos in the allCargo.txt file.
	Cargo allCargo[sizeof_cargoArray]; //Creates the cargo object array.

	loadPlane(allCargo, sizeof_cargoArray, maxWeight, &usedWeight, maxVolume, &usedVolume); //Call the loadPlane funtion
	cout << "---------------------------- Cargo Statistics ----------------------------\n\n"; //Intro message for cargo statistics before print out the statistics
	printWeight(maxWeight,usedWeight); //prints out the  max weight, used weight and unused weight(free space left)
	printVolume(maxVolume,usedVolume); //prints out the  max volume, used volume and unused volume(free space left)
	printHeaviest(allCargo, sizeof_cargoArray); //print out the heaviest cargo
	printLargest(allCargo, sizeof_cargoArray); //print out the largest cargo
	printCargo(allCargo, sizeof_cargoArray); //prints out all the cargos in the cargo object array.
	system("pause"); //stops the program from closing to fast.
}



//<SampleOutput>
/*
File Successfully Loaded.
Enter cargos to be loaded. Enter quit for the label to quit loading.

Input Label:  CocaCola
Input Weight: 5444
Input height: 22
Input width:  12
Input length: 6

Input Label:  Watermelon
Input Weight: 2252
Input height: 17
Input width:  12
Input length: 9

Input Label:  quit
---------------------------- Cargo Statistics ----------------------------

Maximum Cargo Weight: 50000.00
Used Cargo Weight   : 26941.32
Unused Cargo Weight : 23058.68

Maximum Cargo Volume: 70000
Used Cargo Volume   : 12852
Unused Cargo Volume : 57148

Heaviest container weighed     : 8231.66 Pounds
Located at location number     : 6

Largest container had volume of: 1836 Cubic Inches
Located at location number     : 22


-------------------------Table of Cargo Containers-------------------------
Location #  Label          Weight         Volume      Dimensions

0           Cake           1000.51        210         7   X  6  X  5
1           candy          2000.62        720         10  X  9  X  8
2           paper          3000.77        66          3   X  22 X  1
3           soda           234.23         222         37  X  2  X  3
4           beds           24.62          27          3   X  3  X  3
5           cars           1242.14        512         32  X  4  X  4
6           trucks         8231.66        924         77  X  2  X  6
7           flashlights    4.21           48          6   X  2  X  4
8           playstation    7.52           27          3   X  3  X  3
9           books          8.33           36          3   X  2  X  6
10          iphones        455.63         336         8   X  6  X  7
11          batterys       254.33         35          7   X  1  X  5
12          tv             431.12         120         4   X  5  X  6
13          computers      522.52         5236        14  X  22 X  17
14          movies         25.65          280         8   X  7  X  5
15          mail           188.33         80          5   X  4  X  4
16          food           466.63         28          4   X  1  X  7
17          cloth          416.26         175         7   X  5  X  5
18          amazon         726.76         343         7   X  7  X  7
19          potato         1.11           1           1   X  1  X  1
20          herbs          2.37           6           2   X  1  X  3
21          CocaCola       5444.00        1584        6   X  12 X  22
22          Watermelon     2252.00        1836        9   X  12 X  17
Press any key to continue . . .
*/

//<CONTENTS OF "allCargo.txt" FILE>
/*
label= Cake
height= 5
width=  6
length= 7
weight= 1000.51
label= candy
height= 8
width=  9
length= 10
weight= 2000.62
label= paper
height= 1
width=  22
length= 3
weight= 3000.77
label= soda
height= 3
width=  2
length= 37
weight= 234.23
label= beds
height= 3
width=  3
length= 3
weight= 24.62
label= cars
height= 4
width=  4
length= 32
weight= 1242.14
label= trucks
height= 6
width=  2
length= 77
weight= 8231.66
label= flashlights
height= 4
width=  2
length= 6
weight= 4.21
label= playstation
height= 3
width=  3
length= 3
weight= 7.52
label= books
height= 6
width=  2
length= 3
weight= 8.33
label= iphones
height= 7
width=  6
length= 8
weight= 455.63
label= batterys
height= 5
width=  1
length= 7
weight= 254.33
label= tv
height= 6
width=  5
length= 4
weight= 431.12
label= computers
height= 17
width=  22
length= 14
weight= 522.52
label= movies
height= 5
width=  7
length= 8
weight= 25.65
label= mail
height= 4
width=  4
length= 5
weight= 188.33
label= food
height= 7
width=  1
length= 4
weight= 466.63
label= cloth
height= 5
width=  5
length= 7
weight= 416.26
label= amazon
height= 7
width=  7
length= 7
weight= 726.76
label= potato
height= 1
width=  1
length= 1
weight= 1.11
label= herbs
height= 3
width=  1
length= 2
weight= 2.37
*/