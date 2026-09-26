#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::string code_input;

  // read file name from user
  std::string file_name;
  std::cin >> file_name;
  std::ifstream in(file_name);

  if (!in) {
    std::cout << "Error opening file!" << std::endl;
    return 1;
  }

  // read entire file into code_input
  std::string line;
  while (getline(in, line)) {
    code_input += line; // append each line
  }
  in.close();

  // Brainfuck setup
  std::stack<size_t> loop;
  int ptr = 0;
  std::vector<unsigned char> tape(30000, 0);
  std::unordered_map<int, int> loop_bracket_matching;
  bool error = false;

  // bracket matching
  int open_brackets = 0;
  for (int i = 0; i < code_input.size(); i++) {
    if (code_input[i] == '[') {
      loop.push(i);
      open_brackets++;
    } else if (code_input[i] == ']') {
      if (loop.empty()) {
        std::cout << "Unmatched closing bracket at " << i << std::endl;
        error = true;
        break;
      }
      int start = loop.top();
      loop.pop();
      loop_bracket_matching[start] = i;
      loop_bracket_matching[i] = start;
      open_brackets--;
    }
  }

  if (open_brackets != 0) {
    std::cout << "Unmatched opening bracket(s)" << std::endl;
    error = true;
  }

  // run program if no bracket errors
  if (!error) {
    for (int i = 0; i < code_input.length(); i++) {
      switch (code_input[i]) {
      case '+':
        tape[ptr]++;
        break;
      case '-':
        tape[ptr]--;
        break;
      case '>':
        ptr = (ptr + 1) % tape.size();
        break;
      case '<':
        ptr = (ptr - 1 + tape.size()) % tape.size();
        break;
      case '.':
        std::cout << static_cast<char>(tape[ptr]);
        break;
      case ',': {
        char input_char;
        std::cin >> input_char;
        tape[ptr] = static_cast<unsigned char>(input_char);
        break;
      }
      case '[':
        if (tape[ptr] == 0)
          i = loop_bracket_matching[i];
        break;
      case ']':
        if (tape[ptr] != 0)
          i = loop_bracket_matching[i];
        break;
      }
    }
  }
  std::string ok;
  return 0;
}
