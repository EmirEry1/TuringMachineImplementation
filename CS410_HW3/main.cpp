#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "map"
#include "stack"

enum InputStates{
    NUMBER_OF_VARIABLES_IN_INPUT_ALPHABET,
    NUMBER_OF_VARIABLES_IN_TAPE_ALPHABET,
    NUMBER_OF_STATES,
    STATES,
    START_STATE,
    ACCEPT_STATE,
    REJECT_STATE,
    BLANK_SYMBOL,
    VARIABLES_IN_TAPE_ALPHABET,
    VARIABLES_IN_INPUT_ALPHABET,
    TRANSITIONS,
    STRINGS
};
struct TuringMachineOutput{
    bool accepted;
    std::vector<std::string> path;
};
struct TuringMachineEvaluater{
    int number_of_states = 0;
    int number_of_variables_in_input_alphabet = 0;
    int number_of_variables_in_tape_alphabet = 0;
    int state_start = 0;
    int state_length = 0;
    std::vector<std::string> states;
    std::string start_state;
    std::string accept_state;
    std::string reject_state;
    char blank_symbol;
    std::vector<char> variables_in_input_alphabet;
    std::vector<char> variables_in_tape_alphabet;
    std::map<std::pair<std::string, char>, std::pair<std::pair<char, char>, std::string>> transitions ;
    std::vector<std::string> strings;

    TuringMachineEvaluater(int number_of_states_parameter, int number_of_variables_in_input_alphabet_parameter, int number_of_variables_in_tape_alphabet_parameter, auto& states_parameter, std::string start_state_parameter, std::string accept_state_parameter, std::string reject_state_parameter, char blank_symbol_parameter, auto& variables_in_input_alphabet_parameter, auto& variables_in_tape_alphabet_parameter, auto& transitions_parameter, auto& strings_parameter){
        this->number_of_states = number_of_states_parameter;
        this->number_of_variables_in_input_alphabet = number_of_variables_in_input_alphabet_parameter;
        this->number_of_variables_in_tape_alphabet = number_of_variables_in_tape_alphabet_parameter;
        this->states = states_parameter;
        this->states = states_parameter;
        this->start_state = start_state_parameter;
        this->accept_state = accept_state_parameter;
        this->reject_state = reject_state_parameter;
        this->blank_symbol = blank_symbol_parameter;
        this->variables_in_input_alphabet = variables_in_input_alphabet_parameter;
        this->variables_in_tape_alphabet = variables_in_tape_alphabet_parameter;
        this->transitions = transitions_parameter;
        this->strings = strings_parameter;

    }

    bool checkTuringMachine(){
        if (number_of_states != states.size()){
            std::cout << "The provided number of states is inconsistent with the given states." << std::endl;
            exit(EXIT_FAILURE);
        }

        //Input Variable Number Check

        if (number_of_variables_in_input_alphabet != variables_in_input_alphabet.size()){
            std::cout << "The provided number of input variables is inconsistent with the given input variables." << std::endl;
            exit(EXIT_FAILURE);
        }

        //Stack Variable Number Check

        if (number_of_variables_in_tape_alphabet != variables_in_tape_alphabet.size()-1){
            std::cout << "The provided number of tape variables is inconsistent with the given tape variables." << std::endl;
            exit(EXIT_FAILURE);
        }

        bool start_state_found = false;
        for (const auto& state: states) {
            if (start_state == state) {
                start_state_found = true;
                break;
            }
        }
        if(!start_state_found){
            std::cout << "Start state is not among the states of the Turing Machine" << std::endl;
            exit(EXIT_FAILURE);
        }

        bool accept_state_found = false;
        for (const auto& state: states) {
            if (accept_state == state) {
                accept_state_found = true;
                break;
            }
        }
        if(!accept_state_found){
            std::cout << "Accept state is not among the states of the Turing Machine" << std::endl;
            exit(EXIT_FAILURE);
        }

        bool reject_state_found = false;
        for (const auto& state: states) {
            if (reject_state == state) {
                reject_state_found = true;
                break;
            }
        }
        if(!reject_state_found){
            std::cout << "Reject state is not among the states of the Turing Machine" << std::endl;
            exit(EXIT_FAILURE);
        }

        bool blank_symbol_found = false;
        for (const auto& var: variables_in_tape_alphabet) {
            if (blank_symbol == var) {
                blank_symbol_found = true;
                break;
            }
        }
        if(!blank_symbol_found){
            std::cout << "Blank symbol is not among the tape variables" << std::endl;
            exit(EXIT_FAILURE);
        }

        bool character_found;
        for (auto& string: strings) {
            for (auto &character: string) {
                character_found = false;
                for (const auto &variable: variables_in_input_alphabet) {
                    if (character == variable) {
                        character_found = true;
                        break;
                    }
                }
                if (!character_found) {
                    std::cout << "Invalid character in one of the strings." << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

        for(char var_in: variables_in_input_alphabet){
            bool var_in_found = false;
            for(char var_tape: variables_in_tape_alphabet){
                if(var_in == var_tape){
                    var_in_found = true;
                }
            }
            if(!var_in_found){
                std::cout << "At least one of the input variables is not a part of the tape variables." << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        for (const auto& transition: transitions){
            bool from_state_found = false;
            bool read_character_found = false;
            bool write_character_found = false;
            bool dest_state_found = false;

            auto from_state = transition.first.first;
            auto read_character = transition.first.second;
            auto write_character = transition.second.first.first;
            auto direction = transition.second.first.second;
            auto dest_state = transition.second.second;

            for(const auto& state: states){
                if (from_state == state){
                    from_state_found = true;
                    break;
                }
            }
            if (!from_state_found) {
                std::cout << "From State is not among the states of the Turing Machine in at least one transition" << std::endl;
                exit(EXIT_FAILURE);
            }

            for(const auto& var: variables_in_tape_alphabet){
                if (read_character == var){
                    read_character_found = true;
                    break;
                }
            }
            if (!read_character_found) {
                std::cout << "Read character is not among the tape variables in at least one transition" << std::endl;
                exit(EXIT_FAILURE);
            }

            for(const auto& var: variables_in_tape_alphabet){
                if (write_character == var){
                    write_character_found = true;
                    break;
                }
            }
            if (!write_character_found) {
                std::cout << "Write character is not among the tape variables in at least one transition" << std::endl;
                exit(EXIT_FAILURE);
            }

            if(direction != 'L' && direction != 'R'){
                std::cout << "Transition direction has a value other than L or R in at least one of the transitions." << std::endl;
                exit(EXIT_FAILURE);
            }

            for(const auto& state: states){
                if (dest_state == state){
                    dest_state_found = true;
                    break;
                }
            }
            if (!dest_state_found) {
                std::cout << "Destination State is not among the states of the Turing Machine in at least one transition" << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        return true;
    }

    TuringMachineOutput evaluateString(std::string& current_string){
        std::string current_state = this->start_state;
        auto path = std::vector<std::string>();
        auto tape = std::vector<char>();
        path.push_back(current_state);
        for(char current_character: current_string){
            tape.push_back(current_character);
        }
        tape.push_back(blank_symbol);
        int tape_index = 0;
        while((current_state != accept_state) && (current_state != reject_state)){
            auto transitionResult = transitions[std::pair(current_state, tape[tape_index])];
            char write_character = transitionResult.first.first;
            char direction = transitionResult.first.second;
            std::string transition_to = transitionResult.second;
            tape[tape_index] = write_character;
            if(tape_index == tape.size()-1 && direction == 'R'){
                tape.push_back(blank_symbol);
                tape_index++;
            }
            else if(tape_index == 0 && direction == 'L'){}
            else{
                if(direction == 'L'){
                    tape_index--;
                } else{
                    tape_index++;
                }
            }
            current_state = transition_to;
            path.push_back(current_state);
        }
        if(current_state == accept_state){
            return TuringMachineOutput(true, path);
        }
        else if(current_state == reject_state){
            return TuringMachineOutput(false, path);
        }
        return TuringMachineOutput(false, path);
    }
    void evaluateTuringMachine(){
        checkTuringMachine();
        std::ofstream outputFile;
        outputFile.open("output.txt");
        for(std::string current_string: strings){
            auto result = evaluateString(current_string);


            for(const auto& state: result.path){
                outputFile << state << " ";
            }

            outputFile << "(route taken)";
            outputFile << std::endl;
            if(result.accepted){
                outputFile << "Accepted" << std::endl;
            }
            else{
                outputFile << "Rejected" << std::endl;
            }
            outputFile << std::endl;
        }
        outputFile.close();

        std::cout << "Successfully written the results on the file: output.txt" << std::endl;
    }
};

struct InputParse{
    int number_of_states = 0;
    int number_of_variables_in_input_alphabet = 0;
    int number_of_variables_in_tape_alphabet = 0;
    int state_start = 0;
    int state_length = 0;
    InputStates inputState = InputStates();
    std::vector<std::string> states;
    std::string start_state;
    std::string accept_state;
    std::string reject_state;
    char blank_symbol;
    std::vector<char> variables_in_input_alphabet;
    std::vector<char> variables_in_tape_alphabet;
    std::map<std::pair<std::string, char>, std::pair<std::pair<char, char>, std::string>> transitions ;
    std::vector<std::string> strings;
    std::ifstream inputFile;
    std::string transition_state_from;
    char read_character;
    char write_character;
    char direction;
    std::string transition_state_to;

    InputParse(auto &inputFile_parameter){
        inputState = InputStates();
        states = std::vector<std::string>();
        variables_in_input_alphabet = std::vector<char>();
        variables_in_tape_alphabet = std::vector<char>();
        transitions = std::map<std::pair<std::string, char>, std::pair<std::pair<char, char>, std::string>>();
        strings = std::vector<std::string>();
        inputFile = std::move(inputFile_parameter);
    }
    int parseInput(int &number_of_states_parameter, int &number_of_variables_in_input_alphabet_parameter, int &number_of_variables_in_tape_alphabet_parameter, auto& states_parameter, std::string& start_state_parameter, std::string& accept_state_parameter, std::string& reject_state_parameter, char& blank_symbol_parameter, auto& variables_in_input_alphabet_parameter, auto& variables_in_tape_alphabet_parameter, auto& transitions_parameter, auto& strings_parameter ) {
        std::string line;
        int num_spaces = 0;
        inputState = NUMBER_OF_VARIABLES_IN_INPUT_ALPHABET;
        while (std::getline(inputFile, line)) {
            switch (inputState) {
                case NUMBER_OF_STATES:
                    number_of_states = std::stoi(line);
                    inputState = STATES;
                    break;
                case NUMBER_OF_VARIABLES_IN_INPUT_ALPHABET:
                    number_of_variables_in_input_alphabet = std::stoi(line);
                    inputState = NUMBER_OF_VARIABLES_IN_TAPE_ALPHABET;
                    break;
                case NUMBER_OF_VARIABLES_IN_TAPE_ALPHABET:
                    number_of_variables_in_tape_alphabet = std::stoi(line);
                    inputState = NUMBER_OF_STATES;
                    break;
                case STATES:
                    state_start = 0;
                    state_length = 0;
                    for (auto i = 0; i <= line.length(); i++) {
                        if (i == line.length() || line[i] == ' ') {
                            states.push_back(line.substr(state_start, state_length));
                            state_start = i + 1;
                            state_length = 0;
                        } else {
                            state_length++;
                        }
                    }
                    inputState = START_STATE;
                    break;
                case START_STATE:
                    start_state = line;
                    inputState = ACCEPT_STATE;
                    break;
                case ACCEPT_STATE:
                    accept_state = line;
                    inputState = REJECT_STATE;
                    break;
                case REJECT_STATE:
                    reject_state = line;
                    inputState = BLANK_SYMBOL;
                    break;
                case BLANK_SYMBOL:
                    blank_symbol = line[0];
                    inputState = VARIABLES_IN_TAPE_ALPHABET;
                    break;
                case VARIABLES_IN_INPUT_ALPHABET:
                    for(auto i = 0; i < line.length(); i++) {
                        if (line[i] != ' ') {
                            variables_in_input_alphabet.push_back(line[i]);
                        }
                    }
                    inputState = TRANSITIONS;
                    break;
                case VARIABLES_IN_TAPE_ALPHABET:
                    for(auto i = 0; i < line.length(); i++) {
                        if (line[i] != ' ') {
                            variables_in_tape_alphabet.push_back(line[i]);
                        }
                    }
                    inputState = VARIABLES_IN_INPUT_ALPHABET;
                    break;
                case TRANSITIONS:
                    state_start = 0;
                    state_length = 0;
                    num_spaces = 0;
                    if (line == "END_OF_TRANSITIONS") {
                        inputState = STRINGS;
                        break;
                    }
                    for (auto i = 0; i <= line.length(); i++) {
                        if (i == line.length()) {
                            transition_state_to = line.substr(state_start, state_length);
                            state_start = i + 1;
                            state_length = 0;
                            auto transition_tuple = std::pair(transition_state_from, read_character);
                            if(transitions[transition_tuple] != std::pair<std::pair<char, char>, std::string>()){
                                std::cout << "There is at least two transitions that use the same source state, read character pair." << std::endl;
                                exit(EXIT_FAILURE);
                            }
                            transitions[transition_tuple] = std::pair(std::pair(write_character, direction), transition_state_to);
                        } else if (line[i] == ' ' && num_spaces == 0) {
                            transition_state_from = line.substr(state_start, state_length);
                            state_length = 0;
                            num_spaces++;
                        } else if (line[i] == ' ' && num_spaces == 1) {
                            read_character = line[i - 1];
                            state_start = i + 1;
                            state_length = 0;
                            num_spaces++;
                        } else if (line[i] == ' ' && num_spaces == 2) {
                            write_character = line[i - 1];
                            state_start = i + 1;
                            state_length = 0;
                            num_spaces++;
                        }  else if (line[i] == ' ' && num_spaces == 3) {
                            direction = line[i - 1];
                            state_start = i + 1;
                            state_length = 0;
                        } else {
                            state_length++;
                        }
                    }
                    break;
                case STRINGS:
                    std::string current_string = "";
                    for (auto i = 0; i < line.length(); i++) {
                        current_string+=line[i];
                        state_start = i + 1;
                        state_length = 0;
                    }

                    strings.push_back(current_string);
                    break;
            }
        }
        number_of_states_parameter = number_of_states;
        number_of_variables_in_input_alphabet_parameter = number_of_variables_in_input_alphabet;
        number_of_variables_in_tape_alphabet_parameter = number_of_variables_in_tape_alphabet;
        states_parameter = std::move(states);
        start_state_parameter = start_state;
        accept_state_parameter = accept_state;
        reject_state_parameter = reject_state;
        strings_parameter = std::move(strings);
        blank_symbol_parameter = blank_symbol;
        transitions_parameter = std::move(transitions);
        variables_in_input_alphabet_parameter = std::move(variables_in_input_alphabet);
        variables_in_tape_alphabet_parameter = std::move(variables_in_tape_alphabet);
        return 0;
    }
};

int main()
{
    int number_of_states = 0;
    int number_of_variables_in_input_alphabet = 0;
    int number_of_variables_in_tape_alphabet = 0;
    std::vector<std::string> states;
    std::string start_state;
    std::string accept_state;
    std::string reject_state;
    char blank_symbol;
    std::vector<char> variables_in_input_alphabet;
    std::vector<char> variables_in_tape_alphabet;
    std::map<std::pair<std::string, char>, std::pair<std::pair<char, char>, std::string>> transitions ;
    std::vector<std::string> strings;
    std::string file_loc;
    std::cout << "Please enter the loaction of the input file:";
    std::cin >> file_loc;
    std::ifstream inputFile(file_loc);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }
    auto inputParser = InputParse{inputFile};
    inputParser.parseInput(number_of_states, number_of_variables_in_input_alphabet, number_of_variables_in_tape_alphabet, states, start_state, accept_state, reject_state, blank_symbol, variables_in_input_alphabet, variables_in_tape_alphabet, transitions, strings );
    auto turingMachine = TuringMachineEvaluater(number_of_states, number_of_variables_in_input_alphabet, number_of_variables_in_tape_alphabet, states, start_state, accept_state, reject_state, blank_symbol, variables_in_input_alphabet, variables_in_tape_alphabet, transitions, strings);
    turingMachine.evaluateTuringMachine();
    /*std::cout << "Num States: "  << number_of_states << std::endl;
    std::cout << "Num Variables in Input Alphabet: " << number_of_variables_in_input_alphabet << std::endl;
    std::cout << "Num Variables in Tape Alphabet: " << number_of_variables_in_tape_alphabet << std::endl;

    std::cout << "States: " << std::endl;
    for (auto state: states) {
        std::cout << state << std::endl;
    }
    std::cout << "Start State: " << start_state << std::endl;
    std::cout << "Accept State: " << accept_state << std::endl;
    std::cout << "Reject State: " << reject_state << std::endl;

    std::cout << "Blank Symbol: " << blank_symbol << std::endl;

    std::cout << "Variables in Input Alphabet" << std::endl;
    for (auto variable: variables_in_input_alphabet) {
        std::cout << variable << std::endl;
    }
    std::cout << "Variables in Tape Alphabet" << std::endl;
    for (auto variable: variables_in_tape_alphabet) {
        std::cout << variable << std::endl;
    }
    std::cout << "Transitions: " << std::endl;

    for(auto element: transitions){
        std::cout << "From State: " << element.first.first << std::endl;
        std::cout << "With Read Character: " << element.first.second << std::endl;
        std::cout << "Write Character: " << element.second.first.first << std::endl;
        std::cout << "Direction: " << element.second.first.second << std::endl;
        std::cout << "To State: " << element.second.second << std::endl;
        std::cout << "************" << std::endl;
    }

    std::cout << "Strings: " << std::endl;

    for (auto string: strings) {
        std::cout << string << std::endl;
    }
    */
    return 0;
}
