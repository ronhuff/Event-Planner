/*****
* Object: CLI Input
* Description: Validates input received from the CLI
* Author: William Graham
* Modified: February 18, 2017
*****/

#include "CLIInput.h"

CLIInput::CLIInput(){
  stringIn = "";
  characterIn = '\0';
  integerIn = 0;
  doubleIn = 0.0;
}

string CLIInput::getLine(string message){
  cout << message;
  getline(cin, stringIn, '\n');

  while(cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "The previous input is invalid.";
    cout << message;
    getline(cin, stringIn, '\n');
  }

  return stringIn;
}

string CLIInput::getString(string message){
  cout << message;
  cin >> stringIn;

  while(cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << message;
    cin >> stringIn;
  }

  return stringIn;
}

char CLIInput::getCharacter(string message){
  cout << message;
  cin >> characterIn;

  while(cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << message;
    cin >> characterIn;
  }

  return characterIn;
}

double CLIInput::getDouble(string message){
  cout << message;
  cin >> doubleIn;

  while(cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << message;
    cin >> doubleIn;
  }

  return doubleIn;
}

int CLIInput::getInteger(string message){
  cout << message;
  cin >> integerIn;

  while(cin.fail()){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "The integer you entered is not valid.\n";
    cout << message;
    cin >> integerIn;
  }

  return integerIn;
}

int CLIInput::getInteger(string message, int max, int min){
  cout << message;
  cin >> integerIn;

  while(cin.fail() && (integerIn < min || integerIn > max)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "The integer you entered is not valid. It should be between " << min << " and " << max << std::endl;
    cout << message;
    cin >> integerIn;
  }

  return integerIn;
}
