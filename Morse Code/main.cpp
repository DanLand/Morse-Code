//
//  main.cpp
//  Morse Code
//
//  Special characters are not handled.
//  Only letters and numbers are handled.
//
//  Created by Dan Landrum on 5/23/16.
//

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>  //for setw

//function prototypes
void displaymorse(struct language key[], int SIZE);
void englishtomorse(struct language key[], int SIZE);
void morsetoenglish(struct language key[], int SIZE);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

struct language
{
    std::string english;
    std::string morse;
};

int main()
{
    const int SIZE = 37;
    int choice=1;

    language key[SIZE];
    key[0] = {"a", ".-"};
    key[1] = {"b", "-..."};
    key[2] = {"c", "-.-."};
    key[3] = {"d", "-.."};
    key[4] = {"e", "."};
    key[5] = {"f", "..-."};
    key[6] = {"g", "--."};
    key[7] = {"h", "...."};
    key[8] = {"i", ".."};
    key[9] = {"j", ".---"};
    key[10] = {"k", "-.-"};
    key[11] = {"l", ".-.."};
    key[12] = {"m", "--"};
    key[13] = {"n", "-."};
    key[14] = {"o", "---"};
    key[15] = {"p", ".--."};
    key[16] = {"q", "--.-"};
    key[17] = {"r", ".-."};
    key[18] = {"s", "..."};
    key[19] = {"t", "-"};
    key[20] = {"u", "..-"};
    key[21] = {"v", "...-"};
    key[22] = {"w", ".--"};
    key[23] = {"x", "-..-"};
    key[24] = {"y", "-.--"};
    key[25] = {"z", "--.."};
    key[26] = {"0", "-----"};
    key[27] = {"1", ".----"};
    key[28] = {"2", "..---"};
    key[29] = {"3", "...--"};
    key[30] = {"4", "....-"};
    key[31] = {"5", "....."};
    key[32] = {"6", "-...."};
    key[33] = {"7", "--..."};
    key[34] = {"8", "---.."};
    key[35] = {"9", "----."};
    key[36] = {" ", " "};
    
    std::cout << "This programm will convert a letter, number, word or phrase\n";
    std::cout << "from english to morse code, or from morse code to english.\n";
    std::cout << "Only letters and numbers are converted, others are ignored,\n";
    std::cout << "all letters are converted to lowercase automatically.\n";
    std::cout << "\n";
    
    while (choice != 0)
    {
        std::cout << "What would you like to do?\n";
        std::cout << "Enter 0 to exit...\n";
        std::cout << "Enter 1 to display the morse code table...\n";
        std::cout << "Enter 2 for english to morse code...\n";
        std::cout << "Enter 3 for morse code to english...\n";
        std::cout << "Enter your choice: ";

        std::cin >> choice;

        //if user entered something besides a number we handle it here
        //after clearing the error we set choice to 4 to inform the user
        //of an invalid entry and ask them to try again
        if(!std::cin)
        {
            std::cin.clear();
            std::cin.ignore(999,'\n');
            choice = 4;
        }
            
        std::cout << "\n";

        switch (choice)
        {
            case 0:
                std::cout << "\nGood bye\n\n\n";
                exit(0);
                break;
            case 1:
                displaymorse(key, SIZE);
                break;
            case 2:
                englishtomorse(key, SIZE);
                break;
            case 3:
                displaymorse(key, SIZE);
                morsetoenglish(key, SIZE);
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n\n\n";
                break;
        }
    }
    return 0;
}

void displaymorse(struct language key[], int SIZE)
{
    const int width = 6;
    //display the table in 3 columns so we divide the size by 3
    for (int i=0; i<(SIZE-1)/3; i++)//minus 1 so we dont include the space
    {
        std::cout << key[i].english << " = " << std::left << std::setw(width) << (key[i].morse) << "\t"; //left justify
        std::cout << key[i+SIZE/3].english << " = " << std::setw(width) << (key[i+SIZE/3].morse) << "\t";
        std::cout << key[i+SIZE/3+SIZE/3].english << " = " << std::setw(width) << (key[i+SIZE/3+SIZE/3].morse) << "\n";

    }
    std::cout << std::right << "\n";    //return back to default right justify
}

void englishtomorse(struct language key[], int SIZE)
{
    std::string character = "";
    std::string input = "";
    std::string word = "";
    std::vector<std::string> words;
    std::vector<std::string> ingnoreditem;
    bool found=false;

    std::cout << "Enter a letter, number, word, or phrase to convert to morse code: ";
    std::cin.ignore();//clear any newlines cin may have left behind
    getline(std::cin, input, '\n');

    std::cout << "Desired input for translation: \"" << input << "\"\n";
    std::cout << "Morse code output: ";

    std::istringstream iss(input);
    while (iss)
    {
        iss >> word;
        for(unsigned int j = 0; j<word.size(); j++)
        {
            character = word[j];// so we are comparing a string to a string
            for(int i=0; i<SIZE; i++)
            {
                if(key[i].english == character)
                {
                    std::cout << key[i].morse << " ";
                    found = true;
                }
            }
            if (found == false)
            {
                ingnoreditem.push_back(character);
            }
            found = false;//set it back to false
        }
        std::cout << " ";//add another space so between words is double spaced
        word="";//clear word
    }
    if(ingnoreditem.size() != 0)
    {
        std::cout << "\nThe following items were ignored: ";
        for(unsigned int i = 0; i<ingnoreditem.size(); i++)
        {
            std::cout << "\"" << ingnoreditem[i] << "\" ";
        }
    }

    std::cout << "\n\n\n";
}

void morsetoenglish(struct language key[], int SIZE)
{
    std::string input = "";
    std::string morsechrs = "";
    std::vector<std::string> morse;
    std::vector<std::string> ingnoreditem;
    bool found=false;
    
    std::cout << "Enter morse code, seperate letters with a single space\n";
    std::cout << "seperate words with a double space: ";
    std::cin.ignore();//clear any newlines cin may have left behind
    getline(std::cin, input);

    std::cout << "Morse code entered: \"" << input << "\"\n";
    std::cout << "Translates to: ";
    
    morse = split(input, ' ');
    for(unsigned int i = 0; i<morse.size(); i++)
    {
        if(morse[i] == "")
        {
            std::cout << " ";
        }
        for(int j=0; j<SIZE; j++)
        {
            if(key[j].morse == morse[i])
            {
                std::cout << key[j].english;
                found = true;
            }
        }
        if (found == false)
        {
            if(morse[i] != "")
            {
                ingnoreditem.push_back(morse[i]);
            }
        }
        found = false;//set it back to false
    }
    if(ingnoreditem.size() != 0)
    {
        std::cout << "\nThe following items were ignored: ";
        for(unsigned int i = 0; i<ingnoreditem.size(); i++)
        {
            std::cout << "\"" << ingnoreditem[i] << "\" ";
        }
    }
    std::cout << "\n\n\n";
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
