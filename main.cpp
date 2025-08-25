#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<stack>
#include<set>
#include<unordered_map>

int main() {
    //Start of code
    //Assume this is the code
    std::string code_input;
    //the base
    std::stack<size_t> loop;
    int ptr = 0;
    std::vector<unsigned char> tape(30000, 0);
    std::unordered_map<int,int> loop_bracket_matching;
    int bracket_matching_error = 0;
    bool error = false;
    std::string file_name;
    std::cin>>file_name;
    std::cout<<std::endl;
    std::ifstream in(file_name);
    if (!in) {
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }
    std::string line;
    code_input += line;
    while (getline(in, line)) {  // read line by line
        
    }
    in.close();
    
    
    for(int i =0;i<code_input.size();i++){
        if(code_input[i] == '['||code_input[i] == ']'){
            bracket_matching_error += 1;
        }
    }

    for(int i =0;i<code_input.size();i++){
        if(bracket_matching_error%2 == 0){
            if(code_input[i] ==  '['){
                loop.push(i);
            }
            else if (code_input[i] == ']'){
                int start = loop.top();
                loop.pop();
                loop_bracket_matching[start] = i;
                loop_bracket_matching[i] = start;
            }
        }
        else{
            std::cout<<"error";
            error = true;
            break;
        }
    }
    if(error == false){
        for(int i = 0; i < code_input.length(); i++) {
            switch (code_input[i]) {
                case '+': 
                    tape[ptr]++; // Unsigned char auto-wraps from 255 to 0
                    break;
                case '-': 
                    tape[ptr]--; // Unsigned char auto-wraps from 0 to 255
                    break;
                case '>': 
                    ptr += 1;
                    if (ptr >= tape.size()) ptr = 0; // Wrap around if exceeds tape size
                    
                    break;
                case '<': 
                    ptr -= 1;
                    if (ptr < 0) ptr = tape.size() - 1; // Wrap around if goes negative
                    break;
                case '.': 
                    // Output current cell as ASCII character
                    std::cout << static_cast<char>(tape[ptr]);
                    break;
                case ',': 
                    // Read a single character from input
                    char input_char;
                    std::cin >> input_char;
                    tape[ptr] = static_cast<unsigned char>(input_char);
                    break;
                case '[':
                    if(tape[ptr] == 0){
                        i = loop_bracket_matching[i];
                    }
                    break;
                case ']':
                    if(tape[ptr] != 0){
                        i = loop_bracket_matching[i];
                    }
            }
        }
    }
    int ok;
    std::cin>>ok;
    return 0;
}
