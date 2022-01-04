// Project UID af1f95f547e44c8ea88730dfb185559d
#include <iostream>
#include <fstream>
#include "processing.h"
#include "Image.h"
#include "Matrix.h"
#include <string>
#include <cassert>
#include <cstdlib>
#include <ostream>

using namespace std;

int main(int argc, char **argv)
{
    Image *img = new Image;
    if (argc == 4 || argc == 5)
    {
        string filename = argv[1];
        string outputFile = argv[2];
        int desiredWidth = atoi((argv[3]));
        ifstream fin;
        ofstream fout;
        fin.open(filename);
        fout.open(outputFile);
        if (!fin.is_open())
        {
            cout << "Error opening input file: " << filename << endl;
            return 1;
        }
        if (!fout.is_open())
        {
            cout << "Error opening output file: " << outputFile << endl;
            return 1;
        }
        Image_init(img, fin);
        if (!(desiredWidth > 0 && desiredWidth <= Image_width(img)))
        {
            cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                 << "WIDTH and HEIGHT must be less than or equal to original" << endl;
            return 1;
        }
        if (argc == 4)
        {
            seam_carve(img, desiredWidth,Image_height(img));
          
        }
        else if (argc == 5)
        {
            int desiredHeight = atoi((argv[4]));
            if (!(desiredHeight > 0 && desiredHeight <= Image_height(img)))
            {
                cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
                     << "WIDTH and HEIGHT must be less than or equal to original" << endl;
                return 1;
            }
            seam_carve(img, desiredWidth, desiredHeight);
        }
        Image_print(img, fout);
        fin.close();
        fout.close();
    }
    else
    {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }
    delete img;
    return 0;
}
