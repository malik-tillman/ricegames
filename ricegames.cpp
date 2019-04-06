/* By: Malik Tillman | Date: April 5th, 2019
   Short <70 command line game for job interview at Rice Games.
   P.S. Sorry for the compression (Had to keep it under 70 lines somehow)*/
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <string>
using namespace std; using namespace std::this_thread; using namespace std::chrono;

string name = "Chosen One"; int regens = 5, turns = -1, saved; //Global Variables

void dialogue(string s, int t) { sleep_until(system_clock::now() + seconds(t)); cout << s << endl; } //Delays string s, some amount of seconds t

int getRandRoad() { return (rand() % 2) + 1; } //Returns some radom int n, where n = {1,2}

string getGrade() { //Returns grade g, where g = {S, A, B, C, D, F}. g is determined by turns t
	if (turns >= 20) return "S"; 
	else if (turns >= 15) return "A";
	else if (turns >= 12) return "B";
	else if (turns >= 10) return "C";
	else if (turns >= 6) return "D";
	else return "F";
}

void showStats() {//Simple output statatement that displays to console output the values of name, saved villages, turns played, turns left, and grade 
	cout << "\nStats\n----------------\nName: " + name + "\nVillages Saved: " + to_string(saved) + "\nTurns: "
		+ to_string(turns) + "\nRegen Orbs Left: " + to_string(regens) + "\nGrade: " + getGrade() + "\n----------------";
}

int main() {
	srand((unsigned)time(0)); 
	string skip_ans, road; bool skip, loop = false;
	
	do{ //Ask if user wants to skip intro dialogue. Loops as long as input is invalid
		loop = false; 
		cout << "Would you like to skip the intro?\n[N/Y] "; cin >> skip_ans; cout << endl; //Ask to skip intro and get response
		if (skip_ans.compare("Y") == 0 || skip_ans.compare("y") == 0) skip = true;
		else if (skip_ans.compare("N") == 0 || skip_ans.compare("n") == 0) skip = false;
		else { loop = true; cout << "Invalid entry\n" << endl; }
	} while (loop);
	
	if (!skip) {//Intro dialogue
		dialogue("Wise Man: What is your name chosen one?", 0); cout << "\nEnter name: "; cin >> name;
		dialogue("\nWise Man: I see...", 1); 
		dialogue("\nWise Man: Well, " + name + " the villages need you!", 2);
		dialogue("\nWise Man: The Yama-uba are mad! They want to eat all the villagers!!", 2);
		dialogue("\nWise Man: You need to save them!", 2);
		dialogue("\nWise Man: Here! Take these " + to_string(regens) + " regen orbs.", 2);
		dialogue("\nWise Man: They will help you stay alive if you fail to reach a village before the Yama-uba.", 2);
		dialogue("\nWise Man: Hurry " + name + " the villagers are counting on you!!\n", 3);
	}

	do {//Game loop
		loop = true; turns++;
		dialogue("\nChose a way to the next village. Road 1 or Road 2.\n", 1); cout << "Press 'H' to see your stats so far[1/2/H] ";  cin >> road; //Ask which road and get input
		if (road.compare("H") == 0 || road.compare("h") == 0) {showStats(); turns--;} //Show stats if input == 'H' or 'h'
		else if (road.compare("1") == 0 || road.compare("2") == 0) { //Correct entry
			if (road.compare(to_string(getRandRoad())) == 0) { //Right road case
				saved++; dialogue("\nVillagers: Thank you " + name + "! You have saved us from being eaten! The next village needs you! HURRY!!", 2); //Display right road dialogue
				dialogue("\nGood job! You saved them keep going", 1);
			} else { //Wrong road case
				dialogue("\nYama-uba: You are too late. HAHAHA!!", 2); dialogue("\nYama-uba: Now you are next!!", 1); dialogue("\nYou were killed by the Yama-uba", 1); //Display death dialogue
				if (regens > 0) { dialogue("\nYou used a regen orb", 1);regens--; } else { dialogue("\nYou are dead. Game Over", 1); showStats(); loop = false; } //Take regen if more than 0, else end game
			}
		} else { cout << "\nInvalid Entry!\n\nOnly Valid Entry is {1, 2, H, and h}\n\nRetry\n" << endl; turns--; } //Invalid entry case
	} while (loop);

	return 0;
}