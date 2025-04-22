#include "mypipe.h"

#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <stdexcept>



mypipe::mypipe() {
    if(pipe(fd.data()) < 0) {
        std::cerr << "pipe failed" << "\n";
        exit(1); 
    }
}

mypipe::~mypipe() {
    close(fd[0]);
    close(fd[1]); 
}

void mypipe::redirect() {
    if(dup2(fd[1], STDOUT_FILENO) < 0) {
        std::cerr << "redirect failed" << "\n"; 
        exit(1); 
    }

    close(fd[1]); 
}

std::string mypipe::read() {
    std::array<char, 256> buf; 
    std::string output; 
    size_t bytes; 

    while((bytes = ::read(fd[0], buf.data(), buf.size())) > 0) {
        output.append(buf.data(), bytes); 
    }

    if(bytes < 0) {
        std::cerr << "read failed" << "\n"; 
        exit(1); 
    }

    return output; 
}