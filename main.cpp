#include<iostream>
#include<vector>
#include<fstream>
#include<iterator>
#include<string>
#include<stack>
#include<set>

int main() {
    //Start of code
    //Assume this is the code
    std::string code_input = ">+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.[<+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.>,++.[]]";
    //the base
    std::stack<size_t> loop;
    int ptr = 0;
    std::set<int> history_ptr;
    std::vector<unsigned char> tape(30, 0);
    
    for(int i = 0; i < code_input.length(); i++) {
        switch (code_input[i]) {
            case '+': 
                tape[ptr]++; // Unsigned char auto-wraps from 255 to 0
                std::cout << "tape id: " << ptr << " ; data: " << (int)tape[ptr] << std::endl;
                break;
            case '-': 
                tape[ptr]--; // Unsigned char auto-wraps from 0 to 255
                break;
            case '>': 
                ptr += 1;
                if (ptr >= tape.size()) ptr = 0; // Wrap around if exceeds tape size
                history_ptr.insert(ptr);
                std::cout << "ptr: " << ptr << std::endl;
                break;
            case '<': 
                ptr -= 1;
                if (ptr < 0) ptr = tape.size() - 1; // Wrap around if goes negative
                history_ptr.insert(ptr);
                std::cout << "ptr: " << ptr << std::endl;
                break;
            case '.': 
                // Output current cell as ASCII character
                std::cout << static_cast<char>(tape[ptr]) << std::endl;
                break;
            case ',': 
                // Read a single character from input
                char input_char;
                std::cin >> input_char;
                tape[ptr] = static_cast<unsigned char>(input_char);
                break;
            case '[': 
                loop.push(i);
                std::cout << "Opening bracket at position: " << i << std::endl;
                
                break;
            case ']':
                if (!loop.empty()) {
                    int matching = loop.top();
                    loop.pop();
                    std::cout << "Closing bracket at position: " << i << " matches with position: " << matching << std::endl;
                }
                break;
        }
    }
    return 0;
}
