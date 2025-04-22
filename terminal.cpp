#include "terminal.h"
#include "mypipe.h"
#include "utility.h"

#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string>



int run_cmd(std::vector<char *> argv) {
    mypipe mp; 
    auto id{fork()};

    if(id < 0) {
        std::cerr << "Fork failed" << "\n"; 
        return 1; 
    } 

    // parent
    if(id != 0) {
        int status; 
        wait(&status); 
        std::string output = mp.read(); 
        std::cout << output; 
        std::cout << "child terminated: ";
        std::cout << WEXITSTATUS(status) << "\n";
        return status;  
    }

    // child
    else if(id == 0) {
        mp.redirect(); 
        execvp(argv[0], const_cast<char* const*>(argv.data())); 
        
        std::cerr << "execution failed" << "\n"; 
        exit(1); 
    }

    return 1; 
}

void terminal_app() {
    std::string line; 

    while(true) {
        std::cout << ": "; 
        std::getline(std::cin, line); 

        if(line == "exit") {
            break; 
        }

        std::vector<std::string> tokens = cmd2vec(line); 
        
        if(tokens.empty()) {
            continue;
        }

        std::vector<char*> argv = castArgs(tokens);
        run_cmd(argv); 
    }

    std::cout << "Exit terminal." << "\n"; 
    
}