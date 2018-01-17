# NDFSM
non_deterministic_fsm

Please find attached tool for conversion between two various formats for FSM descriptions.

They both were developed at UC Berkeley. ABC tools for digital circuits the input files should be delivered in .fsm formats. But tools for converting a digital circuits to Finite State Machines return FSM in .kiss formats.

Therefore, I think this tool would be useful for convenient work for using FSM-based test models for creating a test suite for digital circuits.

for compiling please use command:

g++ -std=c++11 convert_kiss_to_fsm.cpp -o convert_kiss_to_fsm

for run please use following command:

./convert_kiss_to_fsm *.kiss *.fsm
