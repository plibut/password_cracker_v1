extern std::string cracked_password;
extern std::atomic<bool> password_found; 
extern std::atomic<int> methode_used; // methode used to find the password


void password_liste(std::string password)
{
	std::ifstream password_liste("password_list.txt", std::ios::binary | std::ios::ate);
	if (password_liste.is_open())
	{
		std::streamsize file_size = password_liste.tellg();
		password_liste.seekg(0, std::ios::beg);

		std::vector<char> buffer(file_size);
		if (password_liste.read(buffer.data(), file_size))
		{
			std::string file_contents(buffer.begin(), buffer.end()); // this tells file_contents that it is everything between the start and end of the buffer content
			std::istringstream input_string_stream(file_contents); // std::istringstream is a type of input stream that reads data from a std::string
			std::string word_in_liste;
			while (input_string_stream >> word_in_liste)
			{
				// check word
				if (word_in_liste == password)
				{
					password_found = true;
					methode_used = 1;
					cracked_password = word_in_liste;
					break;
				}
				if (password_found == true)
				{
					break;
				}
			}
		}
	}
	else
	{
    // file could not be opend 
	}
}

