/*
 * Author: coleman7245
 * Project: Lab 4 Exercise
 * Last Update: 2/26/19
 */

#include <iostream>
#include <cstdlib>

int main()
{
	const int RANDOM_NUM_MAX = 1000;
	const int RANDOM_NUM_MIN = 1;
	int guess = 0;
	int distance = 0;
	int previousDistance = 0;
	int randomNum = rand() % RANDOM_NUM_MAX + RANDOM_NUM_MIN;

	std::cout << "I'm thinking of a number between 1 and 1000..." << std::endl;
	std::cout << "Try to guess it!" << std::endl;

	while (true)
	{
		std::cout << "Enter an integer number." << std::endl;
		
		std::cin >> guess;

		if(guess == randomNum)
		{
			std::cout << "Ahh, shucks!" << std::endl;
			std::cout << "You win!" << std::endl;
			
			break;
		}
		
		distance = guess - randomNum;
		
		if (distance < 0)
		{
			distance *= -1;
		}
		
		if (distance == previousDistance)
		{
			std::cout << "You're getting nowhere in good time!" << std::endl;
		}
		else if (distance < previousDistance && previousDistance != 0)
		{
			std::cout << "Getting warmer..." << std::endl;
		}
		else
		{
			std::cout << "Getting colder..." << std::endl;
		}
		
		previousDistance = distance;
	}

	return 0;
}
