#include <bits/stdc++.h>
using namespace std;

int main(){
	fstream in_mac,ala_f,mnt_f,mdt_f,ic_f;
	in_mac.open("input_macro.txt",ios::in);
	ala_f.open("ala.txt",ios::out);
	mdt_f.open("mdt.txt",ios::out);
	mnt_f.open("mnt.txt",ios::out);
	ic_f.open("ic.txt",ios::out);

	string line;
	int line_num=-1;
	int num_macro=0;
	int m_flag=0;
	int f_flag=0;

	map<string,int> macro_name;
	map<string,map<string,string>> macro_data;
	map<string,string> parameter;

	while(getline(in_mac,line)){
		line_num++;
		if(line=="MACRO"){
			m_flag=1;
			num_macro++;
		}
		else if(line=="MEND"){
			mdt_f<<line<<endl;
			m_flag=0;
			f_flag=0;
			parameter.clear();
		}
		else if(m_flag==1){
			if(f_flag==0){
				mdt_f<<line<<endl;
				f_flag=1;
				vector<string> token;
				string temp="";

				for(int i=0;i<line.size();i++){
					if(line[i]==' '){
						token.push_back(temp);
						temp="";
					}
					else{
						temp+=line[i];
					}
				}
				token.push_back(temp);
				macro_name[token[0]]=1;
				mnt_f<<line_num-num_macro<<" "<<token[0]<<endl;
				string para_string="";
				int index=0;

				for(int i=0;i<token[1].size();i++){
					if(token[1][i]==','){
						parameter[para_string]="#"+to_string(index);
						para_string="";
						index++;
					}
					else if(token[1][i]=='='){
						parameter[para_string]="#"+to_string(index);
						index++;
						break;
					}
					else{
						para_string+=token[1][i];
					}
				}

				if(parameter.find(para_string)==parameter.end()){
					parameter[para_string]="#"+to_string(index);
				}



			}
			else if(f_flag==1){
				vector<string> token;
				string temp="";
				for(int i=0;i<line.size();i++){
					if(line[i]==' '){
						token.push_back(temp);
						temp="";
					}
					else{
						temp+=line[i];
					}
				}
				token.push_back(temp);
				mdt_f<<token[0]<<" ";
				string para_string="";

				for(int i=0;i<token[1].size();i++){
					if(token[1][i]==','){
						if(parameter.find(para_string)!=parameter.end()){
							mdt_f<<parameter[para_string]<<",";
							para_string="";
						}
						else{
							mdt_f<<para_string<<",";
							para_string="";
						}
					}
					else{
						para_string+=token[1][i];
					}
				}

				mdt_f<<parameter[para_string]<<endl;

			}
		}
		else{
			ic_f<<line<<endl;

			string temp="";
			int index;

			for(int i=0;i<line.size();i++){
				if(line[i]==' '){
					index=i;
					break;
				}
				temp+=line[i];
			}

			if(macro_name[temp]){
				ala_f<<line<<endl;
				string temp2="";
				vector<string> token;
				for(int i=0;i<line.size();i++){
					if(line[i]==' '){
						token.push_back(temp2);
						temp2="";
					}
					else{
						temp2+=line[i];
					}
				}
				token.push_back(temp2);

				string pr="";
				for(int i=0;i<token[1].size();i++){
					if(token[1][i]==','){
						ala_f<<pr<<endl;
						pr="";
					}
					else{
						pr+=token[1][i];
					}
				}
				ala_f<<pr<<endl;
				ala_f<<endl;
			}


		}
	}

    in_mac.close();
	ala_f.close();
	mdt_f.close();
	mnt_f.close();
	ic_f.close();


}