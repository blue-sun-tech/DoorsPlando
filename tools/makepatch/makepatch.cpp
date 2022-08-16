#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std; 

int main(int argc, char **argv) {
    if (argc < 3) {
        cout << "Usage: makepatch.exe [transform-file] [output-file] ([log-file])" << endl;
        return 0;
    } 

    bool proceed = true;

    string s_tfile(argv[1]);
    string s_outfile(argv[2]);
 
    vector<string> filenames;
    vector<vector<vector<string>>> files;
    filenames.push_back(s_tfile);
    files.push_back(vector<vector<string>>());

    for (int i_file = 0; i_file < filenames.size(); i_file++) {
        if (i_file >= 1000)
        {
            cout << "Error: attempting to open more than 1000 files. " << endl <<
                "Something went horribly wrong. " << endl;
            proceed = false;
            break;
        }

        fstream fs(filenames[i_file], ios_base::in);
        if (!fs.is_open()) {
            //if can't read, move on
            cout << "Could not open transform file " << filenames[i_file] << endl;
            continue;
        }
        //read all lines in 
        string s_line;
        while (getline(fs, s_line)) {
            //read each word as a seperate argument
            istringstream iss(s_line);
            vector<string> s_args;
            string s_temp;
            while (iss >> s_temp) {
                s_args.push_back(s_temp);
            }
            //only read in non-blank lines that don't start with #
            //i don't think s_args[0].size() can be 0 but not 100% on this
            if (s_args.size() > 0 && (s_args[0].size() == 0 || s_args[0][0] != '#')) {
                //if line is an include, add the filename to filenames, if it isn't already
                if (s_args[0] == "inc" && s_args.size() > 1 &&
                    !any_of(filenames.cbegin(),filenames.cend(),[s_args](string s){return s==s_args[1];})) 
                {
                    filenames.push_back(s_args[1]);
                    files.push_back(vector<vector<string>>());
                }
                files[i_file].push_back(s_args);
            } 
        }        
    }

    //pre-process files



    if (proceed) {
               

    }

}