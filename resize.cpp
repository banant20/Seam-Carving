// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include "Matrix.h"
#include "Image.h"
#include "processing.h"

using namespace std;

int main(int argc, char ** argv) {

    ifstream file;
    ofstream stream;

    string filename;
    string outputFile;
    
    Image* img = new Image;


    if (argc == 4 || argc == 5) {
        filename = argv[1];
        outputFile = argv[2];
        int width;
        int height;
        
        file.open(filename);
        stream.open(outputFile);
        
        if (!(file.is_open())) {
            cout << "Error opening file: " << filename << endl;
            delete img;
            return 1;
        }

        if (argc == 5) {
            width = atoi(argv[3]);
            height = atoi(argv[4]);
            Image_init(img, file);
            
            if (width > 0 && width <= Image_width(img) && height > 0 && height <=
                Image_height(img)) {
                
                seam_carve(img, width, height);
                Image_print(img, stream);
            }
            else {
                cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                    << "WIDTH and HEIGHT must be less than or equal to original" << endl;
                delete img;
                return 1;
            }
            
        }
        if (argc == 4) {
            width = atoi(argv[3]);
            Image_init(img, file);
            
            if (width > 0 && width <= Image_width(img)) {
                seam_carve(img, width, Image_height(img));
                Image_print(img, stream);
            }
            else {
                cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                    << "WIDTH and HEIGHT must be less than or equal to original" << endl;
                delete img;
                return 1;
            }
        }
    }
    delete img;
    return 0;
}
