#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    fstream inp, mdt, ic, expand;
    inp.open("input_macro.txt", ios::in);
    ic.open("ic.txt", ios::in);
    expand.open("expand.txt", ios::out);

    string line;
    int flag = 0, f = 0;
    map<string, map<string, string>> mp;
    map<string, int> names;
    while (getline(inp, line))
    {
        if (line == "MACRO"){
            flag = 1;
        }
        else if (line == "MEND"){
            flag = 0;
            f = 0;
        }
        else if (flag == 1)
        {
            if (f == 0)
            {
                f = 1;
                int in = 0;
                map<string, string> damy;
                int check = 0;
                string dm = "";
                string macname;
                for (int i = 0; i < line.size(); i++)
                {
                    if (check == 0)
                    {
                        if (line[i] == ' ')
                        {
                            check = 1;
                        }
                        else
                            macname += line[i];
                    }
                    else
                    {
                        if (line[i] == ',')
                        {
                            damy["#" + to_string(in)] = dm;
                            dm = "";
                            in++;
                        }
                        else if (line[i] == '=')
                            dm = "";
                        else
                            dm += line[i];
                    }
                }
                damy["#" + to_string(in)] = dm;
                mp[macname] = damy;
                names[macname] = 1;
            }
        }
    }
    while(getline(ic,line)){
        vector<string>vs;
        string ds="";
        for(auto c : line){
            if(c==' '){
                vs.push_back(ds);
                ds="";
            }
            else{
                ds+=c;
            }
        }
        vs.push_back(ds);
        if(names[vs[0]]){
            string l;
            int g=0;
            map<string,string>mpx=mp[vs[0]];
            vector<string>sx;
            string x="";
            for(auto c : vs[1]){
                if(c==','){
                    sx.push_back(x);x="";
                }
                else if(c=='=') x="";
                else x+=c;
            }
            sx.push_back(x);
            for(int i=0;i<sx.size();i++){
                mpx["#"+to_string(i)]=sx[i];
            }

            // cout<<vs[0]<<endl;
            // for(auto p : mpx){
            //     cout<<p.first<<" "<<p.second<<endl;
            // }
            mdt.open("mdt.txt", ios::in);
            while(getline(mdt,l)){
                vector<string>s4;
                x="";
                for(int i=0;i<l.size();i++){
                    if(l[i]==' '){
                        s4.push_back(x);x="";
                    }
                    else x+=l[i];
                }
                s4.push_back(x);
                // for(auto c : s4) cout<<c<<" ";
                //         cout<<endl;
                if(s4[0]==vs[0]){
                    g=1;
                }
                else if(g==1){
                    if(s4[0]=="MEND"){
                        g=0;break;
                    }
                    else{
                        x="";
                        vector<string>s5;
                        for(auto c: s4[1]){
                            if(c==','){
                                s5.push_back(x);x="";
                            }
                            else x+=c;
                        }
                        s5.push_back(x);
                        // for(auto c : s5) cout<<c;
                        // cout<<endl;
                        expand<<s4[0]<<" ";
                        for(int i=0;i<s5.size();i++){
                            if(mpx.find(s5[i])==mpx.end()){
                                if(i!=s5.size()-1) expand<<s5[i]<<",";
                                else expand<<s5[i]<<endl;
                            }
                            else{
                                if(i!=s5.size()-1) expand<<mpx[s5[i]]<<",";
                                else expand<<mpx[s5[i]]<<endl;
                            }
                        }
                    }
                }
            }
            mdt.close();
        }
        else{
            expand<<line<<endl;
        }
    }
    inp.close();
    
    ic.close();
    expand.close();
    return 0;
}