#include "./ED.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
//Constructor
ED::ED(string s1, string s2)
{
    //Assigning strings and length of strings to variables
    xString = s1;
    yString = s2;
    X = xString.size(); 
    Y = yString.size(); 
    
    counter = 0;
    //Initilizing holder variables
    yholder = 'n';
    xholder = 'n';
    minHolder= 0;
    answer = "";
    xc=yc=0;
    case1=case2=case3=0;
    //Creating [N][M] matrix like structure out of array pointers
    alMatx = new int*[X+1];
    for(int i = 0; i<X+1;i++){alMatx[i] = new int[Y+1];}
    //Internally stored editdistance value that is made by calling the OptDistance after 
    //the matrix has been made, this both populates that matrix with a constructor call 
    //and stores the value desired
    editDistance = OptDistance();
}
//Function that calculates mismatch penelty
int ED::penalty(char a, char b){
    if(a != b){return 1;}
    else{return 0;}
}
//Function that finds the minimum value of the three given
int ED::min(int a, int b, int c){
    if(a<=b&&a<=c){return a;}
    if(b<=a&&b<=c){return b;}
    if(c<=a&&c<=b){return c;}
    return 666;
}
//Main function that populates the matrix using the Needleman and wunsch method
int ED::OptDistance()
{
    /*
    These first two loops are for setting up the matrix so that 
    all [i][N] and [M][j] are filled with appropriate values
    */

    //First setting up all the cases for alMatx[j][Y] = 2(X-j)
    for(int j = 0; j<=X; j++)
    {
        alMatx[j][Y]= 2*(X-j);
    }
    //Then doing the same for alMatx[X][i] = 2(Y-j)
    for(int i = 0; i<=Y;i++){
        alMatx[X][i] = 2*(Y-i);
    }

    //This loop the goes through the matrix in reverse starting at alMatx[X-1][Y-1] and ending at [0][0]
    //It does this by finding the minimum of its current position between the three cases
    for(int x = X-1; x>=0;x--){        
        for(int y = Y-1; y>=0; y--){
            yholder =  yString[y];
            xholder = xString[x];
            case1 = alMatx[x+1][y+1] + penalty(xholder, yholder);   //If they are equal or mismatched
            case2 = alMatx[x+1][y] + 2;                             //If there is an x gap
            case3 = alMatx[x][y+1] + 2;                             //If there is a Y gap
            alMatx[x][y] = min(case1,case2,case3);                  //Sets the position equal to it
        }
    }
    /*
    //for loop that prints out the whole matrix from [0][0] to [n][m]
    //used for testing on small genes and commented out because it took to much space and wasnt nessesary for the assignment
    for(int x = 0; x<=X;x++)
    {
        for(int y = 0; y<=Y;y++)
        {
            cout<< "  |  " << to_string(alMatx[x][y])<< "  |  ";
        }
        cout<<endl;
    }*/
    return alMatx[0][0];
}
//This method creates a string that is the optimal allignment based off the matrix created
string ED::Alignment(){
    //Getting the edit distance first before adding the rest
    answer.append("Edit Distance = ");
    answer +=(to_string(alMatx[0][0]));
    answer.append("\n");
        //Main while loop that will loop as long as the x and y counters are less then the length of x or y
        while(xc < X && yc < Y){
            //assing char holders to current x y being used
            yholder =  yString[yc];
            xholder = xString[xc];
            //The three cases as shown in the pdf
            case1 = alMatx[xc+1][yc+1];
            case2 = alMatx[xc+1][yc];
            case3 = alMatx[xc][yc+1];
            //Using Min to find the smallest of the three
            minHolder=min(case1,case2,case3);
            //switch case using current matrix minus the smallest of the three 
            switch(alMatx[xc][yc] - minHolder)
            {
                //If the smallest minus the current is 0 then that means there was
                //no change between [xc][yc] and [xc+1][yc+1]
                //that means there is a match and it addes the two current letters to the answer string
                case 0: 
                    answer += xholder;
                    answer.append(" ");
                    answer += yholder;
                    answer.append(" 0 ");
                    answer.append(" ");
                    answer.append("\n");
                    xc++;
                    yc++;
                    break;

                //This 1 case is stange due to how I implemented the switch with
                //the min function. Because i use [xc][yc] - min there is a chance
                //[xc+1][yc] = [xc][yc] + 1 or [xc][yc+1] = [xc][yc] + 1 while 
                //[xc+1][yc+1] still equals [xc][yc], since we want to prioratize 
                //matches since they cost 0 I added a second switch statment that
                //subtracts the x and y char holders, and if they equal zero
                //we know that they still match so should add them to the string 
                //accordingly, however if they do not match then 
                //[xc+1][yc+1] = [xc][yc] + 1 meaning a missmatch so we apply the 
                //missmatch parameters
                case 1: 
                    switch(xholder-yholder)
                    {
                        //if they match but the [xc][yc]-min still = 1
                        case 0: 
                        answer += xholder;
                        answer.append(" ");
                        answer += yholder;
                        answer.append(" 0 ");
                        answer.append(" ");
                        answer.append("\n");
                        xc++;
                        yc++;
                        break;

                        //this means they dont match
                        default:
                        answer += xholder;
                        answer.append(" ");
                        answer += yholder;
                        answer.append(" ");
                        answer.append("1 ");
                        answer.append("\n");
                        xc++;
                        yc++;
                        break;
                    }
                    break;
                
                //Case 2 is also special due to using min, since there are
                //two possible ways you can get a gap, either 
                //[xc][yc] - [xc+1][yc](case2) = 2 or
                //[xc][yc] - [xc][yc+1](case3) = 2, since there are two
                //cases for case two I set up a switch statment inside to toggle
                //between the two cases
                case 2:
                    switch(case2-minHolder)
                    {
                        //If case2 is the cause move to the right and add
                        //corrispending characters to answer string
                        case 0:
                        answer += xholder;
                        answer.append(" - 2 \n");
                        xc++;
                        break;
                        //default checks if case 3
                        default: 
                        switch(case3 - minHolder)
                        {
                            //If case3 is the cause move down and add
                            //corrisponding characters to answer string
                            case 0:
                            answer.append("- ");
                            answer += yholder;
                            answer.append(" ");
                            answer.append("2 ");
                            answer.append("\n");
                            yc++;
                            break;
                            //Shouldnt every get to here
                            default:
                            break;
                        }
                        break;
                    }
                    break;
                //Also shouldnt ever get to here
                default:
                    break;
                }
            }
            //These two switch cases outside of the while loop are to double check
            //that all of string x and y have been used. The reason for adding this is due to an
            //issue in test case ./endgaps7.txt which due to the way the above while loop worked
            //It would boot itself after the last x string was accounted for without addressing the 
            //final Y, the while loop worked for every other test case except this one and I noticed
            //that is wasnt working because it was always just off by 1 meaning Xstring[N] = '\0' while
            //Ystring[M+1] = '\0' So my solution to this problem and any similar ones is by checking 
            //first if the Y string at the yc(counter for y) is '\0' which is the end of any string
            //If it is then we break out, if it isnt then it checks to see if the 
            //X string at xc is '\0' if it is then that means we missed the last Y so we just account 
            //for it by adding it to the string here. Similarly I added a switch for if this happened to 
            //the Xstring despite not encountering that problem.
            switch(yString[yc])
            {
                case '\0':
                break;
                default: 
                switch(xString[xc])
                {
                    case '\0':
                    answer.append("- ");
                    answer += yholder;
                    answer.append(" ");
                    answer.append("2 ");
                    answer.append("\n");
                    default: break;
                }
            }
            switch(xString[xc])
            {
                case '\0':
                break;
                default: 
                switch(yString[yc])
                {
                    case '\0':
                    answer += xholder;
                    answer.append(" - 2 \n");
                    default: break;
                }
            }
        return answer;
}
//simple function that prints the edit distance, used when I tested in order to see it easier as the big genes took a while to scroll 
void ED::coutEditDist(){
    cout << endl << endl <<"Edit Distance: " << to_string(alMatx[0][0])<<endl;}
ED::~ED()
{
    for(int i = 0; i<X+1;i++){delete [] alMatx[i];}
    delete [] alMatx;
}