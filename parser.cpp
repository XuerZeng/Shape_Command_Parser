//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>
#include <valarray>


using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes=-1;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {

    string line;
    string command;
    bool error = false;
    cout << "> ";         // Prompt for input
    getline(cin, line);
        // Get a line from standard input
    bool full = false;
    //no need to worry about eof.
    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        //--------check if the command is stored correctly-------------
        
        if(lineStream.fail()){
            lineStream.clear();
            cout<<"Error: invalid command\n";
            cout << "> ";          // Prompt for input
            getline(cin, line);
            continue;
        }
        //--------check if the input is valid for the key words-------
        bool validCommand =false;
        for(int i=0;i<7;i++){
            if(command == keyWordsList[i]){
                validCommand = true;
            }
        }
        if(!validCommand){
          cout<<"Error: invalid command"<<endl;
          cout << "> ";         
          getline(cin, line);
          continue;
        }
        Shape* newShape;
        string name,type_s;
        int x_loc,y_loc,x_sz,y_sz;
        int rotate;
        
        
        //---------create the dynamic array for it-------
        if(command == "maxShapes"){
            lineStream>>max_shapes;
            if(lineStream.fail()){
                if(lineStream.eof()){
                    cout<<"Error: too few arguments\n";
                    error = true;
                }else{
                    cout<<"Error: invalid arguments\n";
                    error = true;
                }
            }
            string many;
            bool toomany = false;
            lineStream>>many;
            //cout<<many<<endl;
            if (!lineStream.fail()){
                toomany = true;
            }
            
            if((!lineStream.eof()&&!error)||(toomany&&!error)){
                cout<<"Error: too many arguments\n";
                error = true;
            }
            
            if(max_shapes<0){
            
                cout<<"Error: invalid value\n";
                error = true;
            }
          
            if(error){
                lineStream.clear();
                error=false;
                cout << "> ";         
                getline(cin, line);
                //lineStream.clear();
                
                continue;
            }
            
            if(shapeCount!=0){
                for(int i =0;i<shapeCount;i++){
                    if(shapesArray[i]==NULL){
                        continue;
                    }
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                    
                }
                delete [] shapesArray;
            }
            shapesArray = new Shape*[max_shapes];
            
            for(int i =0;i<max_shapes;i++){
                shapesArray[i]=NULL;
            }
            
            shapeCount=0;
            full=false;
            cout<<"New database: max shapes is "<<max_shapes<<endl;
        }
        //---------create the new project--------
        if(command == "create"){
            bool match = false;
            bool done = false;
            bool validShape = false;
            for(int i=0;i<6&&!error;i++){
                if(i==0){
                    lineStream>>name;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid input";
                        error=true;
                    }
                    
                    for(int i=0;i<7&&!error;i++){
                        if(name==shapeTypesList[i]&&i<4&&!error){
                            match = true;
                            error=true;
                            cout<<"Error: invalid shape name"<<endl;
                        }else if(name==keyWordsList[i]&&!error){
                            match=true;
                            error=true;
                            cout<<"Error: invalid shape name"<<endl;
                        }
                    }
                    
                    for(int i=0;i<shapeCount&&!done;i++){
                        if(shapesArray[i]==NULL){
                            continue;
                        }
                        if(name==shapesArray[i]->getName()&&!error){
                            //cout<<"Error: shape "<<name<<" exists"<<endl;
                            done = true;
                            error=true;
                            cout<<"Error: shape "<<name<<" exists"<<endl;
                            //error = true;
                        }
                    }
                    
                    
                           
                }if(i==1){
                    lineStream>>type_s;
                    
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid input";
                        error=true;
                    }
                    for(int i=0;i<4;i++){
                        if(type_s==shapeTypesList[i]&&!error){
                            validShape = true;
                            
                            
                        }
                    }
                    if(!validShape&&!error){
                        error=true;
                        cout<<"Error: invalid shape type"<<endl;
                    }
                }if(i==2){
                    lineStream>>x_loc;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }else if(lineStream.peek()=='.'&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }
                    if(x_loc<0&&!error){
                        cout<<"Error: invalid value"<<endl;
                        error=true;
                    }
                }else if(i==3){
                    lineStream>>y_loc;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }else if(lineStream.peek()=='.'&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }
                    if(y_loc<0&&!error){
                        cout<<"Error: invalid value"<<endl;
                        error=true;
                    }
                }else if(i==4){
                    lineStream>>x_sz;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }else if(lineStream.peek()=='.'&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }
                    if(x_sz<0&&!error){
                        cout<<"Error: invalid value"<<endl;
                        error=true;
                    }
                }else if(i==5){
                    lineStream>>y_sz;
                    //cout<<"checkpoint 5"<<endl;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }else if(lineStream.peek()=='.'&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }
                    //cout<<"Checkpoint 6"<<endl;
                    if(y_sz<0&&!error){
                        cout<<"Error: invalid value"<<endl;
                        error=true;
                    }
                }
                //cout<<"Checkpoint 7"<<endl;
            }
            
            //lineStream>>name>>type_s>>x_loc>>y_loc>>x_sz>>y_sz;
            
            //cout<<name<<type_s<<x_loc<<y_loc<<x_sz<<y_sz;
            string many;
            bool toomany = false;
            lineStream>>many;
            //cout<<many<<endl;
            if (!lineStream.fail()){
                toomany = true;
            }
            
            if((!lineStream.eof()&&!error)||(toomany&&!error)){
                cout<<"Error: too many arguments\n";
                error = true;
            }
            if(type_s=="circle"&&x_sz!=y_sz){
                cout<<"Error: invalid value"<<endl;
                error = true;
            }
            
            
            
            
            if(error){
                lineStream.clear();
                error=false;
                cout << "> ";         
                getline(cin, line);
                //lineStream.clear();
                
                continue;
            }
            if(shapeCount==max_shapes&&!error&&!full){
                error=true;
                full = true;
                cout<<"Error: shape array is full"<<endl;

            }
            if(error){
                lineStream.clear();
                error=false;
                cout << "> ";         
                getline(cin, line);
                //lineStream.clear();
                //cout<<"ddd";
                continue;
            }
            if(!full){
                newShape = new Shape(name, type_s, x_loc, x_sz, y_loc, y_sz);
                shapesArray[shapeCount]=newShape;
                cout<<"Created "<<name<<": "<<type_s<<" "<<x_loc<<" "<<y_loc<<" "<<x_sz<<" "<<y_sz<<endl;
                shapeCount++;
            }else{
                cout<<"Error: shape array is full"<<endl;
            }            
                    
            //int i=0;
            //while(shapesArray[i]!=NULL){
            //    if(i<shapeCount){
            //        shapesArray[i]->draw();
            //    }
            //    i++;
            //}
        }
        //-----------move the shape to the new place-----
        if (command == "move"){
            //cout<<name;
            bool here=false;
            for(int i =0;i<3&&!error;i++){
                if(i==0){
                    lineStream>>name; 
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true;                  
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument\n"<<endl;
                        error=true;
                    }
                    
                    
                    for(int i =0;i<shapeCount&&!error;i++){
                        if(shapesArray[i]==NULL){
                            continue;
                        }
                        if(shapesArray[i]->getName()==name&&!error){
                            here=true;
                        }                        
                    }
                    if(!here&&!error){
                        cout<<"Error: shape "<<name<<" not found"<<endl;
                        error=true;
                    }
                

                }else if(i==1){

                    lineStream>>x_loc;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true; 
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }
                    if(x_loc<0&&!error){
                        cout<<"Error: invalid value"<<endl;
                        error=true;
                    }
                }else if(i==2){
                    lineStream>>y_loc;
                    if(lineStream.fail()&&lineStream.eof()&&!error){
                        cout<<"Error: too few arguments"<<endl;
                        error=true; 
                    }
                    if(lineStream.fail()&&!lineStream.eof()&&!error){
                        cout<<"Error: invalid argument"<<endl;
                        error=true;
                    }
                    if(y_loc<0&&!error){
                        cout<<"Error: invalid value"<<endl;
                        error=true;
                    }
                }
            }
            
            string many;
            bool toomany = false;
            lineStream>>many;
            //cout<<many<<endl;
            if (!lineStream.fail()){
                toomany = true;
            }
            
            if((!lineStream.eof()&&!error)||(toomany&&!error)){
                cout<<"Error: too many arguments\n";
                error = true;
            }
            
            
            if(error){
                lineStream.clear();
                error=false;
                cout << "> ";         
                getline(cin, line);
                //lineStream.clear();
                
                continue;
            }
            
            bool end = false;
            bool inList = false;
            for(int i=0;i<max_shapes&&!end;i++){
                if(shapesArray[i]==NULL){
                    end = true;
                    continue;
                }
                if(shapesArray[i]->getName()==name){
                    shapesArray[i]->setXlocation(x_loc);
                    shapesArray[i]->setYlocation(y_loc);
                    end=true;
                    
                    cout<<"Moved "<<name<<" to "<<x_loc<<" "<<y_loc<<endl;
                }
            }
            
        }
        
        //------------rotate----
        if(command=="rotate"){
            lineStream>>name;
            bool inList = false;
            for(int i = 0;i<max_shapes&&!error;i++){
                if(shapesArray[i]==NULL){
                    continue;
                }
                if(shapesArray[i]->getName() ==name){
                    inList = true;
                }
            }
            if(lineStream.fail()&&!lineStream.eof()&&!error){
                
                cout<<"Error: invalid argument\n";
                
                error = true;
           
            }
            if(lineStream.fail()&&lineStream.eof()&&!error){ 
                cout<<"Error: too few arguments\n";
                error=true;
            }
            if(!inList&&!error){
                cout<<"Error: shape "<<name<<" not found"<<endl;
                error=true;
            }
            
            lineStream>>rotate;
            if(lineStream.fail()&&!lineStream.eof()&&!error){
                
                cout<<"Error: invalid argument\n";
                error = true;
           
            }
            if((rotate<0||rotate>360)&&!error){
                cout<<"Error: invalid value"<<endl;
                error=true;
            }
            string many;
            bool toomany = false;
            lineStream>>many;
            //cout<<many<<endl;
            if (!lineStream.fail()){
                toomany = true;
            }
            
            if((!lineStream.eof()&&!error)||(toomany&&!error)){
                cout<<"Error: too many arguments\n";
                error = true;
            }
            if(error){
                lineStream.clear();
                error=false;
                cout << "> ";         
                getline(cin, line);
                //lineStream.clear();
                
                continue;
            }
            int location;
            for(int i=0;i<max_shapes&&shapesArray[i]!=NULL;i++){
                if(shapesArray[i]->getName()==name){
                    location = i;
                }
            }
            shapesArray[location]->setRotate(rotate);
            cout<<"Rotated "<<name<<" by "<<rotate<<" degrees"<<endl;
        }
        //----------draw-------
        if(command == "draw"){
            int count = 0;
            int location;
            
            if(lineStream.eof()){
                cout<<"Error: too few arguments\n";
                error=true;
            }
            lineStream>>name;
            //cout<<name<<endl;
            if(lineStream.fail()&&!error){

                cout<<"Error: invalid argument\n";
                
                error=true;
            }

            bool inList = false;
            
            for(int i=0;i<max_shapes;i++){
                if(shapesArray[i] == NULL){
                    continue;
                }
                if(shapesArray[i]->getName()==name){
                    location = i;
                    inList = true;
                    
                }
                
            }
            
            if(!inList&&!error&&(name!="all")){
                cout<<"Error: shape "<<name<<" not found"<<endl;
                error =true;
            }
            string many;
            bool toomany = false;
            lineStream>>many;
            //cout<<many<<endl;
            if (!lineStream.fail()){
                toomany = true;
            }
            
            if((!lineStream.eof()&&!error)||(toomany&&!error)){
                cout<<"Error: too many arguments\n";
                error = true;
            }
            if(error){
                lineStream.clear();
                error=false;
                cout << "> ";         
                getline(cin, line);
                //lineStream.clear();
                
                continue;
            }
            
                       
            if(name!="all"){
                cout<<"Drew ";
                shapesArray[location]->draw();
            }
            if(name =="all"){
                cout<<"Drew all shapes\n";
                for(int i = 0;i<shapeCount;i++){
                    if(shapesArray[i]==NULL){
                        continue;
                    }else{
                        shapesArray[i]->draw();
                    }
              
                }
                
            }
            
 
        }
        
        if(command == "delete"){
            
            if(lineStream.eof()){
                cout<<"Error: too few arguments\n";
                error=true;
            }
            lineStream>>name;
            if(lineStream.fail()&&!error){
                
                cout<<"Error: invalid argument\n";
                error=true;
                
            }
            
                
            
            
            bool inList = false;
            int location;
            for(int i = 0;i<max_shapes&&!error;i++){
                if(shapesArray[i]==NULL){
                    continue;
                }
                if(shapesArray[i]->getName() ==name){
                    inList = true;
                    location=i;
                }
            }
            if(!inList&&!error&&name!="all"){
                cout<<"Error: shape "<<name<<" not found"<<endl;
                error=true;
            }
            
            string many;
            bool toomany = false;
            lineStream>>many;
            //cout<<many<<endl;
            if (!lineStream.fail()){
                toomany = true;
            }
            
            if((!lineStream.eof()&&!error)||(toomany&&!error)){
                cout<<"Error: too many arguments\n";
                error = true;
            }
            if(error){
                
                lineStream.clear();
                error=false;
                
                cout << "> ";         
                getline(cin, line);
                
                
                
                continue;
            }
            
            if(name!="all"){
                delete shapesArray[location];
                shapesArray[location]=NULL;
                cout<<"Deleted shape "<<name<<endl;
            }
            if(name=="all"){
                for(int i =0;i<max_shapes;i++){
                    if(shapesArray[i]==NULL){
                        continue;
                    }
                    delete shapesArray[i];
                    shapesArray[i] = NULL;
                }
                cout<<"Deleted: "<<name<<" shapes"<<endl;
                
            }
        }
        
        
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

