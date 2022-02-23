#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "Node.h"
#include <algorithm>


class HuffmanAlgorithm
{
private:
	std::string huffman_code;

	std::unordered_map<char, int> node_frequency_map;
	std::vector<Node*> node_vector;
	std::unordered_map<char, std::string> encode_map;


	void encode(Node* root, std::string encoding_string, std::unordered_map<char, std::string>& encode_map);
	
	void serialize(Node* root, FILE* file_pointer);
	void deserialize(Node*& root, FILE* fp);
	
	void create_char_freq_file(Node* root, std::ofstream& chars_file);
	void deserialize_chars(Node*, std::ifstream &);

	void init_freq_map(std::string);
	void create_char_freq_file_interface();

	void init_nodes();
	void print_freq_map();

	void create_tree();
	void print_tree(const std::string&, const Node*, bool);



	void encode_interface();
	void print_encode_char_keys_all();

	std::string encode_string(std::string encoded_text);

	void serialize_interface();


	void decode(Node* node, std::string str);
	void decode_string(std::string);

public:
	~HuffmanAlgorithm();

	void deserialize_interface();
	
	void encode_run(std::string);
	void decode_run(std::string);
	void print_char_code(std::string, char);
	void print_tree_interface();
};



