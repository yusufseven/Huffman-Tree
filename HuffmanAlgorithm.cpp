#include "HuffmanAlgorithm.h"

void HuffmanAlgorithm::init_freq_map(std::string input_string)
{
	for (char& i : input_string)
	{
		node_frequency_map[i]++;
	}
}

void HuffmanAlgorithm::create_char_freq_file_interface() // runs the function which stores chars which are in leaf nodes into a text file 
{
	std::ofstream chars_file("chars.txt");
	create_char_freq_file(node_vector[0], chars_file); 
}

void HuffmanAlgorithm::create_char_freq_file(Node* root, std::ofstream& chars_file) // the function which stores chars which are in leaf nodes into a text file
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left_child && !root->right_child) 
	{
		chars_file << root->character;
	}

	create_char_freq_file(root->left_child, chars_file);
	create_char_freq_file(root->right_child, chars_file);
}

void HuffmanAlgorithm::deserialize_chars(Node* root, std::ifstream& chars_file)
{
	if (root == nullptr)
		return;
	if (!root->left_child && !root->right_child) 
	{
		chars_file.get(root->character);
	}
	deserialize_chars(root->left_child, chars_file);
	deserialize_chars(root->right_child, chars_file);
}

HuffmanAlgorithm::~HuffmanAlgorithm()
{
	node_vector.clear();
}

void HuffmanAlgorithm::init_nodes()
{
	auto map_iterator = node_frequency_map.begin();		     // creates new nodes and setting their characters and frequency values
	while (node_frequency_map.end() != map_iterator)		 // and stores them in a vector
	{
		Node* node = new Node();
		node->character = map_iterator->first;
		node->character_frequency = map_iterator->second;

		node_vector.push_back(node);
		++map_iterator;
	}
}

void HuffmanAlgorithm::print_freq_map()
{
	for (int i = 0; i < node_vector.size(); i++)	// printing frequency map
	{
		std::cout << node_vector[i]->character << " : " << node_vector[i]->character_frequency << std::endl;
	}
	std::cout << '\n';
}

void HuffmanAlgorithm::create_tree()
{
	while (node_vector.size() != 1)	
	{
		std::sort(node_vector.begin(), node_vector.end(), [](Node* node_1, Node* node_2)-> bool
			{
				return node_2->character_frequency > node_1->character_frequency;
			});  // sorting by frequency
		Node* node = new Node();	

		node->character_frequency = node_vector[0]->character_frequency + node_vector[1]->character_frequency;	
		node->character = '\0';	
		node->left_child = node_vector[0];	
		node->right_child = node_vector[1];	

		node_vector.erase(node_vector.begin(), node_vector.begin() + 2);	
		node_vector.emplace_back(node);	
	}
}

void HuffmanAlgorithm::print_tree_interface()
{
	deserialize_interface();
	print_tree("", node_vector[0], false);
}

void HuffmanAlgorithm::encode_interface()
{
	encode(node_vector[0], "", encode_map);
}


void HuffmanAlgorithm::print_tree(const std::string& tree_branches, const Node* node, bool is_left_node)
{
	// printing character frequency and the character itself
	if (node != nullptr)
	{
		std::cout << tree_branches;
		std::cout << "+==";

		if (node->character == '\0')
		{
			std::cout << "(" << node->character_frequency << ")" << std::endl;
		}
		else if (node->character == ' ')
		{
			std::cout << "' '" << "(" << node->character_frequency << ")" << std::endl;  //for whitespace, printing ' '
		}
		else
		{

			std::cout << node->character << "(" << node->character_frequency << ")" << std::endl;
		}

		print_tree(tree_branches + (is_left_node ? "|    " : "     "), node->left_child, true);	  // printing left side
		print_tree(tree_branches + (is_left_node ? "|    " : "     "), node->right_child, false);	  // and right side recursively
	}
}

void HuffmanAlgorithm::encode(Node* root, std::string encoding_string, std::unordered_map<char, std::string>& encode_map)
{
	if (root == nullptr)							// null node
		return;
	if (!root->left_child && !root->right_child)	// leaf node
	{
		encode_map[root->character] = encoding_string;
	}
	encode(root->left_child, encoding_string + "0", encode_map);
	encode(root->right_child, encoding_string + "1", encode_map);
}

void HuffmanAlgorithm::print_encode_char_keys_all()
{
	std::cout << "\nencoded char keys: \n";
	for (auto& pair : encode_map)
	{
		std::cout << pair.first << " : " << pair.second << std::endl;
	}
	std::cout << '\n';
}

void HuffmanAlgorithm::print_char_code(std::string input_string,char ch)
{
	init_freq_map(input_string);
	init_nodes();

	create_tree();
	encode_interface();     // encode characters

	serialize_interface();
	create_char_freq_file_interface();
	
	std::cout << encode_map[ch];
}

std::string HuffmanAlgorithm::encode_string(std::string encoded_text)	// creates encoded text
{
	std::string encoded_string;
	for (int i = 0; i < encoded_text.size(); i++)
	{
		encoded_string += encode_map[encoded_text[i]];
	}
	return encoded_string;
}

void HuffmanAlgorithm::serialize_interface()
{
	FILE* file_pointer;
	file_pointer = fopen("tree.txt", "w");
	serialize(node_vector[0], file_pointer);
	fclose(file_pointer);
}

void HuffmanAlgorithm::deserialize_interface()
{
	std::ifstream chars_file("chars.txt");
	FILE* file_pointer;
	file_pointer = fopen("tree.txt", "r");
	node_vector.push_back(new Node());
	deserialize(node_vector[0], file_pointer);
	deserialize_chars(node_vector[0], chars_file);
	fclose(file_pointer);
}

void HuffmanAlgorithm::serialize(Node* root, FILE* file_pointer)
{
	if (root == nullptr) // If the node is null, puts a mark in the file.
	{
		fprintf(file_pointer, "%d ", -1);
		return;
	}
	fprintf(file_pointer, "%d ", root->character_frequency); // If the node is not empty, it stores 
	serialize(root->left_child, file_pointer);					   // the current node frequency and it's left and right child
	serialize(root->right_child, file_pointer);
}

void HuffmanAlgorithm::deserialize(Node*& root, FILE* fp)
{
	int current_value;
	if (!fscanf(fp, "%d ", &current_value) || current_value == -1) // Reads from the file, If the next value is marker, it returns.
		return;
	root = new Node();						     // If the next value is not marker, creates a new node and sets it's left and right child.
	root->character_frequency = current_value;
	deserialize(root->left_child, fp);
	deserialize(root->right_child, fp);
}

void HuffmanAlgorithm::decode(Node* node, std::string str)
{
	if (node == nullptr) //empty node
	{		
		return;
	}
	
	if (!node->left_child && !node->right_child)  //leaf node
	{
		std::cout << node->character;
		node = node_vector[0];
	}
	
	if (str.empty())
	{
		return;
	}
	
	if (str[0] == '0') //left side
	{
		str.erase(str.begin());
		decode(node->left_child, str);
	}
	else               //right side
	{
		str.erase(str.begin());
		decode(node->right_child, str);
	}
}

void HuffmanAlgorithm::decode_string(std::string encoded_string)
{
	decode(node_vector[0], encoded_string);
}

void HuffmanAlgorithm::encode_run(std::string input_string)
{
	init_freq_map(input_string);
	init_nodes();

	create_tree();
	encode_interface();     // encode characters
	
	serialize_interface();
	create_char_freq_file_interface();

	std::cout << encode_string(input_string) << '\n';
}

void HuffmanAlgorithm::decode_run(std::string decode_input)
{
	deserialize_interface();
	encode_interface();
	decode_string(decode_input);

}

