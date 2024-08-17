#include <iostream>
#include <sstream>
#include <vector>
#include <bitset>

using namespace std;

string binary(int num) {
    bitset<12> binaryRepresentation(num);
    string binaryString = binaryRepresentation.to_string();
    size_t binaryLength = binaryString.length();
    return (binaryLength >= 12 ? binaryString.substr(binaryString.length() - 12) : binaryString);
}

string Assembler(string inputString) {
    // Using std::istringstream and std::getline to split the string
    istringstream iss(inputString);
    vector<string> tokens;
    string token;

    while (getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    string binaryOpcode = "";

    int a = 0;
    if (tokens[a] == "LOAD") {
        a++;
        if (tokens[a] == "M(X)") {
            binaryOpcode += "00000001";
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        } else if (tokens[a] == "MQ") {
            a++;
            if (tokens[a] == "M(X)") {
                binaryOpcode += "00000001";
                a++;
                int p = stoi(tokens[a]);
                string h = binary(p);
                binaryOpcode += h;
            } else {
                binaryOpcode = "00001010000000000000";
            }
        }
    } else if (tokens[a] == "SUB") {
        binaryOpcode = "00000110";
        a++;
        if (tokens[a] == "M(X)") {
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        }
    } else if (tokens[a] == "MUL") {
        binaryOpcode += "00001011";
        a++;
        if (tokens[a] == "M(X)") {
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        }
    } else if (tokens[a] == "STOR") {
        binaryOpcode = "00100001";
        a++;
        if (tokens[a] == "M(X)") {
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        }
    } else if (tokens[a] == "JUMP") {
        a++;
        if (tokens[a] == "LHS") {
            binaryOpcode = "00001101";
            a++;
            if (tokens[a] == "M(X)") {
                a++;
                int p = stoi(tokens[a]);
                string h = binary(p);
                binaryOpcode += h;
            }
        } else if (tokens[a] == "RHS") {
            binaryOpcode += "00001110";
            a++;
            if (tokens[a] == "M(X)") {
                a++;
                int p = stoi(tokens[a]);
                string h = binary(p);
                binaryOpcode += h;
            }
        }
    }
    else if(tokens[a] == "FACT"){
        binaryOpcode += "10111011";
        a++;
        if(tokens[a] == "M(X)"){
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        }
    }
    else if(tokens[a] == "DIV"){
        binaryOpcode += "00001100";
        a++;
        if(tokens[a] == "M(X)"){
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        }
    }
    else if(tokens[a] == "NULL"){
        binaryOpcode += "00000000000000000000";
        a++;
        
    }
    else if(tokens[a] == "CMP"){
        binaryOpcode += "11111111";
        a++;
        if(tokens[a] == "M(X)"){
            a++;
            int p = stoi(tokens[a]);
            string h = binary(p);
            binaryOpcode += h;
        }
    }
        

    return binaryOpcode;
}

int main() {
    vector<string> text = {"LOAD M(X) 100","CMP M(X) 101" ,"SUB M(X) 101", "STOR M(X) 101", "FACT M(X) 101", "STOR M(X) 101", "FACT M(X) 100", "DIV M(X) 101"};
    vector<string> ans(text.size());
    vector<string> MainMemory(text.size()/2);

    for (int i = 0; i < text.size(); i++) {
        ans[i] = Assembler(text[i]);
    }

    for (int j = 0; j < text.size() - 1; j += 2) {
        ans[j - j / 2] = ans[j] + ans[j + 1];
    }
    if((text.size())%2==0){
        for(int k=0;k<(text.size())/2;k++){
            MainMemory[k]=ans[k];
        }
    }
    else{
        for(int k=0;k<((text.size())/2)+1;k++){
            MainMemory[k]=ans[k];
        }
        
    }

    for(int h=0;h<MainMemory.size();h++){
        cout<<"MainMemory"<<"["<<h<<"]"<<": "<<MainMemory[h]<<endl;
    }

    return 0;
}