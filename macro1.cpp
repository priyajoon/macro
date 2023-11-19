#include<bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
int const N=100000;
vector<int> graph[N];
int ar[N];
int mod=1000000007;

signed main(){
    fstream inputMacro, mdtFile, mntFile, alaFile, icFile;
    inputMacro.open("input_macro.txt", ios::in);
    mdtFile.open("mdt.txt", ios::out);
    mntFile.open("mnt.txt", ios::out);
    alaFile.open("ala.txt", ios::out);
    icFile.open("ic.txt", ios::out);
    
    string line;
    int lineNumber = -1;
    int macroFlag = 0;
    int firstTimeFlag = 0;
    int currentLineNumber = -1;
    int numOfMacros = 0;
    
    map<string, int> macroNameMap;
    map<string, map<string, string>> macroDataMap;
    map<string, string> parameterMap;

    while(getline(inputMacro, line)){
        lineNumber++;
        if(line == "MACRO"){
            numOfMacros++;
            macroFlag = 1;
        }
        else if(line == "MEND"){
            mdtFile << line << endl;
            macroFlag = 0;
            firstTimeFlag = 0;
            parameterMap.clear();
        }
        else if(macroFlag == 1){
            if(firstTimeFlag == 0){
                mdtFile << line << endl;
                vector<string> tokens;
                firstTimeFlag = 1;
                string tempString = "";
                
                for(int i = 0; i < line.size(); i++){
                    if(line[i] == ' '){
                        tokens.push_back(tempString);
                        tempString = "";
                    }
                    else {
                        tempString += line[i];
                    }
                }
                tokens.push_back(tempString);
                macroNameMap[tokens[0]] = 1;
                mntFile << lineNumber - numOfMacros << " " << tokens[0] << endl;
                string parameterString = "";
                int index = 0;
                
                for(int i = 0; i < tokens[1].size(); i++){
                    if(tokens[1][i] == ','){
                        parameterMap[parameterString] = "#" + to_string(index);
                        parameterString = "";
                        index++;
                    }
                    else if(tokens[1][i] == '='){
                        parameterMap[parameterString] = "#" + to_string(index);
                        index++;
                        break;
                    }
                    else {
                        parameterString += tokens[1][i];
                    }
                }
                
                if(parameterMap.find(parameterString) == parameterMap.end()) {
                    parameterMap[parameterString] = "#" + to_string(index);
                }
                
                map<string, string> dummyMap;
                parameterString = "";
                index = 0;
                
                for(int i = 0; i < tokens[1].size(); i++){
                    if(tokens[1][i] == ','){
                        dummyMap["#" + to_string(index)] = parameterString;
                        parameterString = "";
                        index++;
                    }
                    else if(tokens[1][i] == '='){
                        parameterString = "";
                    }
                    else {
                        parameterString += tokens[1][i];
                    }
                }
                
                if(dummyMap.find(parameterString) == dummyMap.end()){
                    dummyMap["#" + to_string(index)] = parameterString;
                }
                
                macroDataMap[tokens[0]] = dummyMap;
            }
            else if(firstTimeFlag == 1){
                vector<string> tokens;
                string tempString = "";
                
                for(int i = 0; i < line.size(); i++){
                    if(line[i] == ' '){
                        tokens.push_back(tempString);
                        tempString = "";
                    }
                    else {
                        tempString += line[i];
                    }
                }
                tokens.push_back(tempString);
                mdtFile << tokens[0] << " ";
                string parameterString = "";
                
                for(int i = 0; i < tokens[1].size(); i++){
                    if(tokens[1][i] == ','){
                        if(parameterMap.find(parameterString) != parameterMap.end()) {
                            mdtFile << parameterMap[parameterString] << ",";
                            parameterString = "";
                        }
                        else {
                            mdtFile << parameterString << ",";
                            parameterString = "";
                        }
                    }
                    else {
                        parameterString += tokens[1][i];
                    }
                }
                
                mdtFile << parameterMap[parameterString] << endl;
            }
        }
        else{
            icFile << line << endl;
            string tempString = "";
            int index;
            
            for(int i = 0; i < line.size(); i++){
                if(line[i] == ' '){
                    index = i;
                    break;
                }
                tempString += line[i];
            }
            
            if(macroNameMap[tempString]){
                alaFile << line << endl;
                map<string, string> dummyMap = macroDataMap[tempString];
                string temp = tempString;
                tempString = "";
                int currentIndex = 0;
                
                for(int i = index + 1; i < line.size(); i++){
                    if(line[i] == ','){
                        string parameter = "#" + to_string(currentIndex);
                        dummyMap[parameter] = tempString;
                        tempString = "";
                        currentIndex++;
                    }
                    else if(line[i] == '='){
                        tempString = "";
                    }
                    else {
                        tempString += line[i];
                    }
                }
                
                dummyMap["#" + to_string(currentIndex)] = tempString;
                
                for(auto pair : dummyMap){
                    alaFile << pair.second << endl;
                }
                
                alaFile << endl;
                macroDataMap[temp] = dummyMap;
            }
        }
    }
    
    inputMacro.close();
    mdtFile.close();
    mntFile.close();
    alaFile.close();
    icFile.close();
    return 0;
}
