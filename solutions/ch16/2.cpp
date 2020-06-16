// EXERCISES
// 16-2. Write a program that takes output from stdin, capitalizes it, and writes the
//       result to stdout.
#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>

int main(){
    std::string str;

    while(true) {
        std::cout << "Give me some input: ";
        std::getline(std::cin, str);
        boost::algorithm::to_upper(str);
        std::cout << str << std::endl;        
    };
}