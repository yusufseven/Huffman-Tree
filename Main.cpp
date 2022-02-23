#include "HuffmanAlgorithm.h"

int main(int argc, char* argv[])
{
	HuffmanAlgorithm huff;

	if (argc == 4) // -i input.txt/decode.txt -encode/-decode
	{
		std::string input_string;
		std::string temp_string;

		if (std::string(argv[3]) == "-encode") // -encode
		{
			std::ifstream input_file(argv[2]); // input.txt filename
			while (std::getline(input_file, temp_string))
			{
				input_string += temp_string;
			}
			huff.encode_run(input_string); // encoding operation
		}
		else
		{
			std::ifstream input_file(argv[2]); // input.txt filename
			while (std::getline(input_file, temp_string))
			{
				input_string += temp_string;
			}
			huff.decode_run(input_string); // encoding operation
		}
	}

	else if (argc == 6) // -i input_file.txt -encode -s character
	{
		std::string input_char_str = std::string(argv[5]);
		char input_char = input_char_str[0];

		std::string input_string;
		std::string temp_string;

		std::ifstream input_file(argv[2]); // input.txt filename
		while (std::getline(input_file, temp_string))
		{
			input_string += temp_string;
		}
		huff.print_char_code(input_string, input_char); // printing char		
	}
	
	else if (argc == 2) // -l
	{
		huff.print_tree_interface();
	}
	
	return 0;
}
