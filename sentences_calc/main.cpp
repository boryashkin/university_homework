#include <string>
#include <fstream>
#include <iostream>

int main()
{
    int i = 0;
    int cnt = 0;
    std::string line;
    int state = 1;
    char letter;

    std::ifstream reader("example.txt");

    if(!reader) {
        std::cout << "Error opening input file" << std::endl ;
        return -1 ;
    }

    while (!reader.eof()) {
        std::getline(reader, line);

        if (state == 0) {
            break;
        }
        while (state != 0) {
            if (i >= line.size()) {
                letter = ' ';
            } else {
                letter = line[i];
            }
            switch (state) {
                case 1:
                    if (letter == '.') {
                        i++;
                        state = 2;
                    } else if (letter == ' ') {
                        i++;
                        state = 8;
                    } else {
                        i++;
                    }
                    break;
                case 2:
                    if (letter == '.') {
                        i++;
                    } else if (letter == ' ') {
                        i--;
                        state = 6;
                    } else {
                        i++;
                        state = 1;
                    }
                    break;
                case 6:
                    if (letter == '.') {
                        cnt++;
                        i++;
                        state = 1;
                    } else {
                        state = 0;
                    }
                    break;
                case 8:
                    if (letter == ' ') {
                        state = 0;
                    } else {
                        state = 1;
                        i++;
                    }
                default:
                    //stop
                    break;
            }
        }
    }
    std::cout << "cnt: " << cnt << std::endl;
    reader.close() ;

    return 0 ;
}