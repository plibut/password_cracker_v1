#include <fstream> // used to read files 
#include <thread> // adds thread usage
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "password_liste.h"


std::string cracked_password;
std::atomic<bool> password_found = false;
std::atomic<int> methode_used;
std::atomic<int> time_used;
// std::atomic creates a global variable that can be comunicated between threads



// das hast du in seperaten project gemacht!!!
void brute_force_helper(std::string characters, std::string attempt, std::string password, int max_length, bool& found)
{
	if (found || attempt.length() > max_length)
		return;

	// std::cout << attempt << "\n"; 
	// just here for debug 

	if (attempt == password)
	{
		std::cout << "Password found: " << attempt << std::endl;
		found = true;
		return;
	}

	for (int i = 0; i < characters.length(); ++i)
		brute_force_helper(characters, attempt + characters[i], password, max_length, found);
}

void brute_force(std::string password)
{
	std::string characters = "abcdefghijklmnopqrstuvwxyz";
	int max_length = 8;
	bool found = false;

	brute_force_helper(characters, "", password, max_length, found);

	if (found == false)
		std::cout << "Password not found" << std::endl;
}


void timer()
{
	int timer = 0;
	while (password_found == false)
	{
		timer = timer + 1;
		std::this_thread::sleep_for(std::chrono::seconds(1));

		if (password_found == true)
		{
			time_used = timer;
		}
	}
}


int main()
{
	std::string password = "helloworld";



	{
		// timer
		std::thread thread1(timer);

		// password liste
		std::thread thread2(password_liste, password);
		std::thread thread3(brute_force, password);

		thread1.join();
		thread2.join();
		thread3.join();

		// thread have to be done after the declaration of the thread to start them simultaneously
	}

	std::string methode_used_string = std::to_string(methode_used); // converts into to string
	std::string password_liste_was_used = "Password liste";
	if (password_found == true)
	{
		if (methode_used == 1)
		{
			methode_used_string = "Password liste";
		}
		if (methode_used == 2)
		{
			methode_used_string = "Brute force";
		}
		if (methode_used == 3)
		{
			methode_used_string = "Word liste";
		}
	}

	if (password_found == true)
	{
		std::cout << "\nYour password was found! \n"
			<< "Password: " << cracked_password << "\n"
			<< "Methode used: " << methode_used_string << "\n"
			<< "Time needed: " << time_used << " ~seconds";
	}

	return 0;
}