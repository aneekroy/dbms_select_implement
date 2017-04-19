#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
using namespace std;

bool checkDataDict(string table_name){
    string buffer;

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp=fopen("Dictionary.txt", "r");

    while((read=getline(&line, &len, fp))!=-1){
        stringstream str(line);
        str >> buffer;
        if(buffer==table_name) return 1;
    }

    return 0;
}

vector<vector<string> > getData(string file_name){
    string buffer;
    vector<string> row;
    vector<vector<string> > data;

    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp=fopen((file_name+".txt").c_str(), "r");

    while((read=getline(&line, &len, fp))!=-1){
        stringstream str(line);
        row.clear();
        while (str >> buffer)
       	    row.push_back(buffer);
        data.push_back(row);
    }
    
    return data;
}

void selectData(string table_name, vector<int> attr_no){
    //vector<int> attr_no;
    vector<vector<string> > data;

    if(!checkDataDict(table_name)){
        cout<<"Table not found!\n";
        return;
    }

    data=getData(table_name);


    for(int i=1;i<data.size();i++){
        for(int j=0;j<attr_no.size();j++){
            cout<<data[i][attr_no[j]]<<"\t";
        }
        cout<<endl;
    }

    return;
}
vector<string> returnColumns(string cols){
	vector<string> colm ;
	string temp ="";
	int i = 0;
	while(cols[i]!='\0'||i<cols.size()){
		if((cols[i]>=65&&cols[i]<=90)||(cols[i]>=97&&cols[i]<=122)||cols[i]>='0'&&cols[i]<='9'){
			temp = temp + cols[i++];
		}
		else if((i==0)&&cols[i++]=='*'){
			colm.push_back("*");
			return colm;
		}
		else if(cols[i]==','){
			colm.push_back(temp);
			temp = "";
			i++;
		}
		else{
			printf("\nERROR!!\n");
			exit(0);
		}
	}
	colm.push_back(temp);
	return colm;
}
vector <int> checkColumnsandReturnIndexes(vector <string> cols,vector <string> attr){
	vector <int> corr;
	int i = 0,j=0,match=0;
	string temp = "";
	if(cols.size()==1 && cols[0] == "*"){
		for (int i = 0; i < attr.size(); i++)
		{
			corr.push_back(i);
		}
	}
	else{
		i=0,match=0;
		while(i<cols.size()){
			j=0,match=0;
			while(j<attr.size()){
				if(cols[i]==attr[j]||boost::iequals(cols[i],attr[j]))
				{
					match=1;
					corr.push_back(j);
				}
				j++;
			}
			if(match==0){
				cout<<"No Column Found Named : "<<cols[i]<<" ! ERROR!! \n";
				exit(0);
			}
			i++;
		}
	}
	return corr;
}
void printattributes(std::vector<int> v,std::vector<string> att){
	for (int i = 0; i < v.size(); ++i)
	{
		cout<<att[v[i]]<<"\t";
	}
	cout<<"\n";
}
int main(){
    string table_name="STUDENT";
    vector <string> attr;
    vector <string> stmts;
    attr.push_back("ROLL");
    attr.push_back("NAME");
    attr.push_back("DIST");
    attr.push_back("CLASS");
    attr.push_back("DEPT");
    attr.push_back("GPA");
    string *line = NULL;
    size_t s = 0;
    string buffer;
    char lin[150];

    cout<<"\nEnter Select statement :\n";
    scanf("%[^\n]s",lin);
    
    stringstream str(lin);
        while (str >> buffer)
       	    stmts.push_back(buffer);
    int i = 0;
    if(stmts.size()<4){
    	cout<<"ERROR in query !! Query Incomplete !!!\n";
    	exit(0);
    }
   	if(!boost::iequals(stmts[0],"SELECT"))//case insensitive checking for string
   	{ 
   		cout<<"ERROR in query !! No SELECT Query Found !!\n";
   		exit(0);
   	}
   	if(!boost::iequals(stmts[2],"FROM"))//case insensitive checking for string
   	{ 
   		cout<<"ERROR in query !! FROM misspelled!!\n";
   		exit(0);
   	}
    vector <string> columns = returnColumns(stmts[1]);
    // while(i<stmts.size())
    // cout<<stmts[i++]<<"\n";
    if(!boost::iequals(stmts[3],table_name+";"))//case insensitive checking for string
   	{ 
   		cout<<"ERROR in tablename !!\n";
   		exit(0);
   	}

	vector <int> indices = checkColumnsandReturnIndexes(columns,attr);
	printattributes(indices,attr);
	selectData(table_name,indices);
    return 0;
}
