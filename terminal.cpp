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
        perror("fork failed"); 
        return -1; 
    } 

    // child
    else if(id == 0) {
        mp.redirect(); 
        std::cout << "\n[child] PID = " << getpid();
        std::cout << " - execvp\n" << std::flush; 
        execvp(argv[0], argv.data()); 
        perror("exec failed");
        exit(127); 
    }

    // parent
    if(id != 0) {
        int status; 
        wait(&status); 
        std::string output = mp.read(); 
        std::cout << output; 
        return status;  
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