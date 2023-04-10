#include <fstream> // used to read files 
#include <thread> // adds thread usage
#include <iostream>
#include <string>

std::string password_cracked_done;
std::atomic<bool> password_found = false;
std::atomic<int> methode;
// std::atomic creates a global variable that can be comunicated between threads


void password_liste(std::string password, std::ifstream& file)
{

	std::string rockyou_passwords;
	int password_checked = 0;

	while (file >> rockyou_passwords) // takes the passwords from thefile puts them into "words"
	{
		if (rockyou_passwords == password)
		{
			password_cracked_done = rockyou_passwords;
			password_found = true;
			methode = 1;
			break;
		}
		password_checked = password_checked + 1;
		std::cout << "Im counting... " << rockyou_passwords << "\n";
	}
}

void brute_force(std::string password)
{

	while (password_found == false)
	{
		if (password_found == true)
		{
			// i will be here in the near future :)
			break;
		}
	}


}


int main()
{
	std::ifstream file("example.txt"); //std::ifstream file opens a file
	std::string password = "moomoo";


	if (file.is_open())
	{
		std::thread thread1(password_liste, password, std::ref(file));
		std::thread thread2(brute_force, password);

		thread1.join();
		thread2.join();
		// thread fater to be done after the declaration of the thread to start them simultaneously
	}
	else
	{
		std::cout << "Failed to open file";
	}



	if (password_found = true)
	{
		std::cout << "Your password was found: " << password_cracked_done;
	}



	return 0;
}