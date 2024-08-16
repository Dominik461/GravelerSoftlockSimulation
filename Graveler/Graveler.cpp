// Graveler.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <iomanip> // for std::setfill and std::setw

//This function is slower as it prints out the current number of simulations
void SimulateBattlesSlow(int numberOfSimulations)
{
	//setting the the start time of the function
	auto start = std::chrono::high_resolution_clock::now();

	//Check if the number entered is valid
    if (numberOfSimulations <= 0) return;
	
	//Setting up the random generator
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4);

	int maxOnes = 0, rolls;
	//to break out if 177 one rolls happend (I think this could be more optimised without the need of a variable)
	bool foundEscape = false;

	std::cout << "Current Simulation: ";

	//Simulations 
	for (rolls = 0; rolls < numberOfSimulations; rolls++)	
	{
		//printing out the current simulation number
		std::cout << rolls << std::endl;
		//this sets the cursor of the console to overwrite the simulation number with the next
		//this just helps with not spamming the console
		std::cout << "\033[" << 2 << ";" << 21 << "H";
		
		//stop simulations if 177 ones were rolled
		if (foundEscape) break;

		int currentOnes = 0;

		//the 231 turns in the battle
		for (size_t i = 0; i < 231; i++)
		{
			if (dist4(rng) == 1)
			{
				currentOnes++;
				if (currentOnes == 177)
					foundEscape = true;
			}
				
		}

		if (currentOnes > maxOnes)
			maxOnes = currentOnes;
	}

	//get the time when all simulations finished
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// Convert milliseconds to hours, minutes, seconds, milliseconds
	long long total_milliseconds = duration.count();
	int hours = static_cast<int>(total_milliseconds / (1000 * 60 * 60));
	total_milliseconds %= (1000 * 60 * 60);

	int minutes = static_cast<int>(total_milliseconds / (1000 * 60));
	total_milliseconds %= (1000 * 60);

	int seconds = static_cast<int>(total_milliseconds / 1000);
	total_milliseconds %= 1000;

	int milliseconds = static_cast<int>(total_milliseconds);

	std::cout << "Slow Simulation" << std::endl;
	std::cout << "Highest Ones Roll: " << maxOnes << std::endl;
	std::cout << "Number of Simulations: " << rolls << std::endl;
	std::cout << "Time for simulation = " << std::setfill('0') << std::setw(2) << hours << ":"
		<< std::setfill('0') << std::setw(2) << minutes << ":"
		<< std::setfill('0') << std::setw(2) << seconds << ":"
		<< std::setfill('0') << std::setw(3) << milliseconds << std::endl;;
}

//This function is faster as it does not print out the current number of simulations
void SimulateBattlesFast(int numberOfSimulations)
{
	//setting the the start time of the function
	auto start = std::chrono::high_resolution_clock::now();

	//Check if the number entered is valid
	if (numberOfSimulations <= 0) return;

	//Setting up the random generator
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist4(1, 4);


	int maxOnes = 0, rolls;
	//to break out if 177 one rolls happend (I think this could be more optimised without the need of a variable)
	bool foundEscape = false;
	
	//Simulations 
	for (rolls = 0; rolls < numberOfSimulations; rolls++)
	{
		//stop simulations if 177 ones were rolled
		if (foundEscape) break;

		int currentOnes = 0;

		//the 231 turns in the battle
		for (size_t i = 0; i < 231; i++)
		{
			if (dist4(rng) == 1)
			{
				currentOnes++;
				if (currentOnes == 177)
					foundEscape = true;
			}

		}

		if (currentOnes > maxOnes)
			maxOnes = currentOnes;
	}

	//get the time when all simulations finished
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	// Convert milliseconds to hours, minutes, seconds, milliseconds
	long long total_milliseconds = duration.count();
	int hours = static_cast<int>(total_milliseconds / (1000 * 60 * 60));
	total_milliseconds %= (1000 * 60 * 60);

	int minutes = static_cast<int>(total_milliseconds / (1000 * 60));
	total_milliseconds %= (1000 * 60);

	int seconds = static_cast<int>(total_milliseconds / 1000);
	total_milliseconds %= 1000;

	int milliseconds = static_cast<int>(total_milliseconds);

	std::cout << "Fast simulation" << std::endl;
	std::cout << "Highest Ones roll: " << maxOnes << std::endl;
	std::cout << "Number of simulations: " << rolls << std::endl;
	std::cout << "Time for simulations = " << std::setfill('0') << std::setw(2) << hours << ":"
		<< std::setfill('0') << std::setw(2) << minutes << ":"
		<< std::setfill('0') << std::setw(2) << seconds << ":"
		<< std::setfill('0') << std::setw(3) << milliseconds << std::endl;;
}

int main()
{
    std::cout << "Graveler Softlock Simulator" << std::endl;
	//SimulateBattlesSlow(1000000000);
	SimulateBattlesFast(1000000000);
	std::cin;
}
