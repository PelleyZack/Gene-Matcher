#include "./ED.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <SFML/System.hpp>
using namespace std;
int main(int argc, char* argv[])
{
    //setting up clock timer
    sf::Clock clock;
    sf::Time t;
    //setting up strings and assigning them to the input files values
    string s1;
    string s2;
    cin >>s1>>s2;
    //Creating an object of the ED class to test the two inputed strings
    ED test(s1,s2);
    cout << endl << test.Alignment() << endl;
    t=clock.getElapsedTime();
    cout<< endl<< "Execution time is " << t.asSeconds() << " seconds \n";
    //Optional code that wasnt in design documents but it prints out the edit distance again so you dont have to scroll up on the large genes
    //test.coutEditDist();
}