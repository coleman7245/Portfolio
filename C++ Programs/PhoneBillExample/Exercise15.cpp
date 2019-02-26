/*
 * Author: coleman7245
 * Project: Exercise 15
 * Last Update: 2/26/19
 */

#include <iostream> //Header needed for input and output streams.
#include <iomanip> //Header needed for the manipulation of input and output.
#include <string> //Header needed for creating strings of characters.

double const INITIAL_REGULAR_CHARGE = 10.0; //Constant initial charge for regular customers.
double const REGULAR_CHARGE_RATE = .2; //Constant charge rate for regular customers. 
double const INITIAL_PREMIUM_CHARGE = 25.0; //Constant initial charge for premium customers. 
double const PREMIUM_DAYTIME_CHARGE_RATE = .1; //Consant charge rate for premium customers in the daytime. 
double const PREMIUM_NIGHTTIME_CHARGE_RATE = .05; //Constant charge rate for premium customers in the nighttime. 

int main()
{
	std::string accountNumber; //Stores the account number for the user. 
	char serviceCode, quit; //Stores service type (regular or premium), and the character to quit the program. 
	int regMinutes, preDayMinutes, preNightMinutes; //Stores the minutes of a regular customer and the daytime/nighttime minutes of a premium customer. 
	double charges = 0.0; //Stores the charges after every parameter has been calculated.

	std::cout << std::setprecision(2) << std::fixed << std::endl; //Sets the amount of displayed decimal places to two. 

	std::cout << "If you use our regular service, enter 'R'." << "\n" << "If you use our premium service, enter 'P'." << std::endl; //Tells the user to input his or her service type using a single character. 

	std::cin >> serviceCode; //Accepts the account number and service type of the user.

	std::cout << " " << std::endl; //Blank space for better formating.

	if(serviceCode == 'R' || serviceCode == 'r') //If the user has picked the regular service, diverge.
	{
		std::cout << "For a bill of your account, please enter your account number." << std::endl; //Asks the regular user for his or her account number.

		std::cin >> accountNumber; //Accepts the regular user's account number.

		std::cout << " " << std::endl; //Blank space for better formating.
		
		std::cout << "Now enter the amount of minutes used while using our service." << std::endl; //Asks the regular user for the minutes they used while on the phone. 

		std::cin >> regMinutes; //Accepts the account number and the amount of minutes used from the user. 

		if(regMinutes > 50) //If the regular mintues used by the user exceed 50, diverge.
		{
			charges = INITIAL_REGULAR_CHARGE + REGULAR_CHARGE_RATE * (regMinutes - 50); //Stores the sum of the initial regular customer charge to the product of the regular customer charge rate and the difference of the minutes used and 50.
		}
		else //Otherwise...
		{
			charges = INITIAL_REGULAR_CHARGE; //Stores the intial regular customer charge rate. 
		}

		std::cout << "Account #: " << accountNumber << "\n" << "Service Type: " << serviceCode << "\n" << "Minutes Used: " << regMinutes << "\n" << "Total Charges: $" << charges << std::endl; //Outputs the bill for the regular user. 
	}
	else if(serviceCode == 'P' || serviceCode == 'p') //If the user picked the premium service, diverge. 
	{
		std::cout << "For a bill of your account, please enter your account number." << std::endl; //Asks the premium user for his or her account number.

		std::cin >> accountNumber; //Accepts the premium user's account number.

		std::cout << " " << std::endl; //Blank space for better formating.

		std::cout << "Please enter the amount of daytime minutes used while using our service." << std::endl; //Asks the user to enter the amount of daytime minutes used.

		std::cin >> preDayMinutes; //Accepts the amount of daytime minutes.

		std::cout << " " << std::endl; //Blank space for better formating.

		std::cout << "Please enter the amount of nighttime minutes used while using our service." << std::endl;

		std::cin >> preNightMinutes; //Accepts the amount of nighttime minutes.

		std::cout << " " << std::endl; //Blank space for better formating.
			
		if(preDayMinutes > 75) //If the premium daytime minutes exceed 75, diverge.
		{
			charges = PREMIUM_DAYTIME_CHARGE_RATE * (preDayMinutes - 75); //Stores the product of the premium daytime charge rate and the difference of premium daytime minutes and 75.
		}

		if(preNightMinutes > 100) //If the premium nighttime minutes exceeds 100, diverge. 
		{
			charges += PREMIUM_NIGHTTIME_CHARGE_RATE * (preNightMinutes - 100); //Stores the sum of the previous charges and the product of the premium nighttime charge rate and the difference of the premium nighttime minutes and 100.
		}
		
		charges = charges + INITIAL_PREMIUM_CHARGE; //Stores the sum of the previous charges and the initial premium charge.
		
		std::cout << "Account #: " << accountNumber << "\n" << "Service Type: " << serviceCode << "\n" << "Daytime Minutes Used: " << preDayMinutes << "\n" << "Nighttime Minutes Used: " << preNightMinutes << "\n" << "Total Charges: $" << charges << std::endl; //Outputs the account number, the service type, the daytime minutes, the nighttime minutes, and finally, the total charges.
	}
	else //Otherwise(from service code check)...
	{
		std::cout << "Invalid data." << "\n" << "Please exit the program and try again." << "\n" << std::endl; //Outputs an invalid data message.
	}

	return 0;
}
