#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <sstream>

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}

bool myfunction (int i, int j) { 
	return (i < j);
}

class KISS {
	std::ifstream fsm_in;
	std::ifstream fsm_in_transition;
	std::ofstream fsm_out;
	std::string number_of_state;
	std::string number_of_input;
	std::string number_of_output;
	std::string number_of_transition;
	std::string initial_state;
	int dig_number_of_state;
	int dig_number_of_input;
	int dig_number_of_output;
	int dig_number_of_transition;
	std::vector <int> hash_state;
	std::vector <int> use_state;
	int find_in_use_state(int dig);
public:
	KISS(const std::string &str_kiss, const std::string &str_fsm);
	void convert_transition();
	~KISS();
};

int KISS:: find_in_use_state(int dig) {
	for(int i = 0; i < use_state.size(); i++) {
		if(use_state[i] == dig) {
			return i;
		}
	}
	return -1;
}

KISS:: KISS(const std::string &str_kiss, const std::string &str_fsm) {
	try {
		fsm_in.open(str_kiss, std::ios::in);
	}
	catch(...) {
		std::cout<<"error_open_input_file"<<std::endl;
	}
	try {
		fsm_out.open(str_fsm, std::ios::out);
	}
	catch(...) {
		std::cout<<"error_open_output_file"<<std::endl;
	}
	try {
		fsm_in_transition.open(str_kiss, std::ios::in);
	}
	catch(...) {
		std::cout<<"error_open_input_file"<<std::endl;
	}
	std::string line;
	std::string line_2;
	// i
	if((std::getline(fsm_in, line)) && (std::getline(fsm_in_transition, line_2))) {
		dig_number_of_input = 0;
		for(int i = 3; i < line.size(); i++) {
			number_of_input.push_back(line[i]);
			if((line[i] >= '0') && (line[i] <= '9')) {
				dig_number_of_input = dig_number_of_input * 10 + (line[i] - '0');
			}
		}
		line.clear();
		line_2.clear();
	}
	else {
		std::cout<<"error_read_file_i"<<std::endl;
        exit(1);
	}
	// o
	if((std::getline(fsm_in, line)) && (std::getline(fsm_in_transition, line_2))) {
		dig_number_of_output = 0;
		for(int i = 3; i < line.size(); i++) {
			number_of_output.push_back(line[i]);
			if((line[i] >= '0') && (line[i] <= '9')) {
				dig_number_of_output = dig_number_of_output * 10 + (line[i] - '0');
			}
		}
		line.clear();
		line_2.clear();
	}
	else {
		std::cout<<"error_read_file_o"<<std::endl;
        exit(1);
	}
	// p
	if((std::getline(fsm_in, line)) && (std::getline(fsm_in_transition, line_2))) {
		dig_number_of_transition = 0;
		for(int i = 3; i < line.size(); i++) {
			number_of_transition.push_back(line[i]);
			if((line[i] >= '0') && (line[i] <= '9')) {
				dig_number_of_transition = dig_number_of_transition * 10 + (line[i] - '0');
			}
			//std::cout<<"dig_number_of_transition = "<<dig_number_of_transition<<' ';
		}
		//std::cout<<std::endl;
		//dig_number_of_transition = stoi(number_of_transition, nullptr, 10);
		//std::cout<<"dig_number_of_transition = "<<dig_number_of_transition<<std::endl;
		//exit(0);
		line.clear();
		line_2.clear();
	}
	else {
		std::cout<<"error_read_file_p"<<std::endl;
        exit(1);
	}
	// s
	if((std::getline(fsm_in, line)) && (std::getline(fsm_in_transition, line_2))) {
		dig_number_of_state = 0;
		for(int i = 3; i < line.size(); i++) {
			number_of_state.push_back(line[i]);
			if((line[i] >= '0') && (line[i] <= '9')) {
				dig_number_of_state = dig_number_of_state * 10 + (line[i] - '0');
			}
		}
		line.clear();
		line_2.clear();
	}
	else {
		std::cout<<"error_read_file"<<std::endl;
        exit(1);
	}
	fsm_out<<"F 1"<<std::endl;
	fsm_out<<"s "<<number_of_state<<std::endl;
	fsm_out<<"i "<<number_of_input<<std::endl;
	fsm_out<<"o "<<number_of_output<<std::endl;
	fsm_out<<"n0 0"<<std::endl;
	fsm_out<<"p "<<number_of_transition<<std::endl;
}

void KISS:: convert_transition() {
	std::string line;
	std::string line_input;
	std::string line_output;
	std::string line_transition;
	std::string line_state;
	int dig_input = 0, dig_output = 0, dig_next_state = 0, dig_state = 0;
	int max_state = 0;
	//std::cout<<"dig_number_of_transition = "<<dig_number_of_transition<<std::endl;
	for(int i = 0; i < dig_number_of_transition; i++) {
		if(std::getline(fsm_in, line)) {
			//std::cout<<"line = "<<line<<std::endl;
			// i
			int j = 0;
			dig_input = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_input = dig_input * 2 + (line[j] - '0');
				}
				j++;
			}
			//std::cout<<"dig_input = "<<dig_input<<std::endl;
			j++;
			// s
			dig_state = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_state = dig_state * 10 + (line[j] - '0');
				}
				j++;
			}
			if(dig_state > max_state) {
				max_state = dig_state;
			}
			if(find_in_use_state(dig_next_state) == -1) {
				use_state.push_back(dig_next_state);
				std::sort(use_state.begin(), use_state.end(), myfunction);
			}
			j++;
			// s'
			dig_next_state = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_next_state = dig_next_state * 10 + (line[j] - '0');
				}
				j++;
			}
			if(dig_next_state > max_state) {
				max_state = dig_next_state;
			}
			if(find_in_use_state(dig_next_state) == -1) {
				use_state.push_back(dig_next_state);
				std::sort(use_state.begin(), use_state.end(), myfunction);
			}
			j++;
			// o
			dig_output = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_output = dig_output * 2 + (line[j] - '0');
				}
				j++;
			}
			line.clear();
		}
		else {
			std::cout<<"error_read_fsm_in: transition_number = "<<i<<std::endl;
        	exit(1);
		}
	}
	for(int i = 0; i < dig_number_of_transition; i++) {
		if(std::getline(fsm_in_transition, line)) {
			int j = 0;
			//std::cout<<"line = "<<line<<std::endl;
			// i
			dig_input = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_input = dig_input * 2 + (line[j] - '0');
				}
				//std::cout<<"curr_dig_input = "<<dig_input<<std::endl;
				j++;
			}
			//std::cout<<"dig_input = "<<dig_input<<std::endl;
			j++;
			// s
			dig_state = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_state = dig_state * 10 + (line[j] - '0');
				}
				//std::cout<<"curr_dig_state = "<<dig_state<<std::endl;
				j++;
			}
			//std::cout<<"dig_state = "<<dig_state<<std::endl;
			if(dig_state > max_state) {
				max_state = dig_state;
			}
			j++;
			// s'
			dig_next_state = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_next_state = dig_next_state * 10 + (line[j] - '0');
				}
				//std::cout<<"curr_dig_next_state = "<<dig_next_state<<std::endl;
				j++;
			}
			//std::cout<<"dig_next_state = "<<dig_next_state<<std::endl;
			if(dig_next_state > max_state) {
				max_state = dig_next_state;
			}
			j++;
			// o
			dig_output = 0;
			while((j < line.size()) && (line[j] != ' ')) {
				if((line[j] >= '0') && (line[j] <= '9')) {
					dig_output = dig_output * 2 + (line[j] - '0');
				}
				//std::cout<<"curr_dig_output = "<<dig_output<<std::endl;
				j++;
			}
			//std::cout<<"dig_output = "<<dig_output<<std::endl;
			line.clear();
			fsm_out<<toString(find_in_use_state(dig_state))<<' '
				   <<toString(dig_input)<<' '
				   <<toString(find_in_use_state(dig_next_state))<<' '
				   <<toString(dig_output)
				   <<std::endl;
		}
		else {
			std::cout<<"error_read_fsm_in_transition: transition_number = "<<i<<std::endl;
        	exit(1);
		}
	}
	/*
	std::cout<<"use_state"<<std::endl;
	for(int i = 0; i < use_state.size(); i++) {
		std::cout<<use_state[i]<<' ';
	}
	std::cout<<std::endl;
	*/
}

KISS:: ~KISS() {
	fsm_in.close();
	fsm_in_transition.close();
	fsm_out.close();
}

int main(int argc, char **argv) {
	if(argc != 3) {
		std::cout<<"incorrect number of files. Please, enter *.kiss and *.fsm"<<std::endl;
	}
	KISS FSM(argv[1], argv[2]);
	FSM.convert_transition();
	return 0;
}
