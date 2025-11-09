#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <iostream>
#include <glad/gl.h>

class Program { 
    public:
        Program(const char* vertex_path, const char* fragment_path);
        ~Program();
        void use();
        void suspend();
        unsigned int getID() const { return m_id; }

    private:
        unsigned int m_id;

        void compile_program(const char* vertex_code, const char* fragment_code);
};

#endif // PROGRAM_HPP