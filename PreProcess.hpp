
#ifndef PREPROCESS_HPP_INCLUDED
#define PREPROCESS_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <typeinfo>
using namespace std;
struct Newone
{
float x;
float y;
float z;
};
Newone check;
int value=0;
vector<string> className;
vector<Newone> newone;
string attributes="";
class PreProcess
{
    public: PreProcess(std::string inputFile){
         // Turn the string into a stream.
        check.x=0.0;
        check.y=0.0;
        check.z=0.0;
        newone.push_back(check);
        ifstream myfile (inputFile);
        string line;
        if (myfile.is_open()){
        while (!myfile.eof()){
        getline (myfile,line);
        if(strstr(line.c_str(),"@data")){
            attributes += line+"\n"+"\n";
                break;
          }
          attributes += line+"\n";
        }
        }
        myfile.close();
         std::ifstream ifs;
        ifs.open(inputFile);
        string content;
        int note=0,j;
        float xl,yl,zl;
        while(ifs >> content) {

                if(note == 1){
                    split(content, ',');
                }
                if(content.compare("@data") == 0){
                    note = 1;
                }
        }
        ifs.close();
}

  void split(string str, char delimiter){
  //vector<string> internal;
  value=0;
  stringstream ss(str);
  string tok;
        int i =1;

  while(getline(ss, tok, delimiter)) {
    if(!strstr(tok.c_str(),"T")){
        value++;
        switch(i){
            case 1 :    
                        check.x = stof(tok);
                        i++;
                        break;
            case 2 :    check.y = stof(tok);
                        i++;
                        break;
            case 3 :    check.z = stof(tok);
                        newone.push_back(check);
                        i=1;
                        break;
        }
      }else{
        className.push_back(tok);
      }
    }
  }
     void Translate(std::string translateType){
         float r1=0,r2=0,r3=0;
         float addx=0.0,addy=0.0,addz=0.0,avgx=0.0,avgy=0.0,avgz=0.0;
         if(translateType =="origin"){
          for(int i=1;i<newone.size();i++){
                addx += (newone[i].x);
                addy += (newone[i].y);
                addz += (newone[i].z); 
            if(i%((value/3)) == 0 && i!=0){      
              avgx=addx/(value/3); 
              avgy=addy/(value/3); 
              avgz=addz/(value/3);
              addx=addy=addz=0.0;
              for(int k=i;k>i-(value/3);k--){
                newone[k].x=newone[k].x-avgx;
                newone[k].y=newone[k].y-avgy;
                newone[k].z=newone[k].z-avgz;
              }
            }
          }
         }else{
          r1= rand() % 100+1;
          r2= rand() % 100+1;
          r3= rand() % 100+1;
          for(int k=1;k<newone.size();k++){
                newone[k].x=newone[k].x+r1;
                newone[k].y=newone[k].y+r2;
                newone[k].z=newone[k].z+r3;
            if(k%((value/3)) == 0 && k!=0){       
                r1= rand() % 100+1;
                r2= rand() % 100+1;
                r3= rand() % 100+1;
            }
          }
         }
       }
         

     void WriteOutput(std::string outputFile){

        string temp="";
        std::ofstream ofs;
        ofs.open (outputFile, std::ofstream::app);
        ofs << attributes;
        ofs.close();

        attributes="";
        for(int j=0;j<className.size();j++){
        for(int i=1;i<=value/3;i++){
          temp += to_string(newone[i].x)+","+to_string(newone[i].y)+","+to_string(newone[i].z)+",";
        }
        ofs.open (outputFile, std::ofstream::app);
        ofs << temp<<className[j]<<endl;
        ofs.close();
        temp="";
        newone.erase(newone.begin()+1, newone.begin()+(value/3)+1); 
      }
   }
};








#endif // PREPROCESS_HPP_INCLUDED
