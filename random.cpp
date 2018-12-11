#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include "random.h"
#include <cerrno>

////////////////////////////////////////////////////////////////////////////////////////////////
//Print Error And Exit//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void Random::PrintErrorAndExit(std::string error_message)
{
	//std::cout << error_message;
	exit(-1);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Print Vector//////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void Random::PrintVector (std::vector<int> input_vector)
{
	for (std::vector<int>::iterator it = input_vector.begin(); it != input_vector.end(); ++it)
	{
		std::cout << ' ' << *it;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Print Vector Ascii////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void Random::PrintVectorAscii (std::vector<int> input_vector)
{
	for (std::vector<int>::iterator it = input_vector.begin(); it != input_vector.end(); ++it)
	{
		char character = static_cast<char>(*it);
		std::cout << character;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//Get Random Number List////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<int> Random::GetRandomNumberList(int key_length)
{

	unsigned char random_buffer[key_length];


	int file_handler = open("/dev/urandom", O_RDWR);

	if(file_handler < 0)
	{
		std::string error_message =  "ERROR: Failed to open file handler errorCode="+ std::string(strerror(errno));
		Random::PrintErrorAndExit(error_message);
	}


	int read_handler = read(file_handler, random_buffer, key_length);

	if(read_handler < 0)
	{
		close(file_handler);
		std::string error_message =  "ERROR: Failed to read file handler errorCode="+ std::string(strerror(errno));
		Random::PrintErrorAndExit(error_message);
	}


	int close_handler = close(file_handler);

	if(close_handler < 0)
	{
		std::string error_message =  "WARNING: Failed to close file handler errorCode="+ std::string(strerror(errno));
		Random::PrintErrorAndExit(error_message);
	}


	std::vector<int> output_vector;

	for (int i=0; i < key_length; i++)
	{
		int number = random_buffer[i];
		output_vector.push_back(number);
	}

	//possible mods free up random_buffer
	//return output_vector as pointer

	return output_vector;

}

////////////////////////////////////////////////////////////////////////////////////////////////
//Convert Random Number/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
int Random::ConvertRandomNumber(int min, int max, int random_number)
{
	//First Algorithm
	int calc = min + random_number % ((max + 1) - min);

	//Second Algorithm
	//return min + int( ((max+1-min) * random_number) / (sizeof(random_number)<<8) );

	return calc;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//Convert Random Number/////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<int> Random::ConvertRandomNumberList(std::vector<int> input_list)
{

	std::vector <int> character_list;
	character_list.push_back('A');
	character_list.push_back('B');
	character_list.push_back('C');
	character_list.push_back('D');
	character_list.push_back('E');
	character_list.push_back('F');
	character_list.push_back('G');
	character_list.push_back('H');
	character_list.push_back('J');
	character_list.push_back('K');
	character_list.push_back('L');
	character_list.push_back('M');
	character_list.push_back('N');
	character_list.push_back('P');
	character_list.push_back('Q');
	character_list.push_back('R');
	character_list.push_back('S');
	character_list.push_back('T');
	character_list.push_back('U');
	character_list.push_back('V');
	character_list.push_back('W');
	character_list.push_back('X');
	character_list.push_back('Y');
	character_list.push_back('Z');
	character_list.push_back('2');
	character_list.push_back('3');
	character_list.push_back('4');
	character_list.push_back('5');
	character_list.push_back('6');
	character_list.push_back('7');
	character_list.push_back('8');
	character_list.push_back('9');
	character_list.push_back('@');
	character_list.push_back('#');
	character_list.push_back('$');
	character_list.push_back('%');
	character_list.push_back('&');
	character_list.push_back('*');
	character_list.push_back('!');
	character_list.push_back('+');
	character_list.push_back('=');
	//character_list.push_back('>'); --removed
	//character_list.push_back('<'); --removed



	int character_list_size  = character_list.size();
	int character_list_size_minus = character_list_size -1;

	std::vector<int> output_list;
	int input_list_size = input_list.size();


	for (int i = 0; i < input_list_size; ++i)
	{
		int random_number = Random::ConvertRandomNumber(0, character_list_size_minus, input_list[i]);
		int character_number = character_list[random_number];
		output_list.push_back(character_number);

	}

	return output_list;

}

////////////////////////////////////////////////////////////////////////////////////////////////
//Replace First Character///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<int> Random::ReplaceFirstCharacter(std::vector<int> number_list)
{

	std::vector <int> character_list;
	character_list.push_back('A');
	character_list.push_back('B');
	character_list.push_back('C');
	character_list.push_back('D');
	character_list.push_back('E');
	character_list.push_back('F');
	character_list.push_back('G');
	character_list.push_back('H');
	character_list.push_back('J');
	character_list.push_back('K');
	character_list.push_back('L');
	character_list.push_back('M');
	character_list.push_back('N');
	character_list.push_back('P');
	character_list.push_back('Q');
	character_list.push_back('R');
	character_list.push_back('S');
	character_list.push_back('T');
	character_list.push_back('U');
	character_list.push_back('V');
	character_list.push_back('W');
	character_list.push_back('X');
	character_list.push_back('Y');
	character_list.push_back('Z');

	int list_size  = character_list.size();
	int list_size_minus  = list_size -1;
	int random_number = Random::ConvertRandomNumber(0, list_size_minus, number_list[0]);
	int character_number = character_list[random_number];

	number_list[0] = character_number;

	return number_list;

}



void Random::GetRandomKey(int key_lenght)
{

	//Get Random Number List
	std::vector<int> number_list_random= Random::GetRandomNumberList(key_lenght);
	//Random::PrintVector(number_list_random);
	//std::cout << std::endl;

	//Convert Random Number List
	std::vector<int> number_list_convert= Random::ConvertRandomNumberList(number_list_random);
	//Random::PrintVector(number_list_convert);
	//std::cout << std::endl;

	//Replace First Character
	std::vector<int> number_list_replace = Random::ReplaceFirstCharacter(number_list_convert);
	//Random::PrintVector(number_list_replace);
	//std::cout << std::endl;

	//Print Vector as Ascii
	Random::PrintVectorAscii(number_list_replace);


}
