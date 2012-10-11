#include "StringReverser.h"

using namespace std;							

const string SPACE = " ";						
const string TAB = "\t";						
const string NEWLINE = "\n";						
const string CARRAIGE_RETURN = "\r";					
const string VERTICAL_TAB = "\v";					
const string BACKSPACE = "\b";						
const string FORM_FEED = "\f";						
const string WHITESPACE = SPACE + TAB + NEWLINE + CARRAIGE_RETURN + VERTICAL_TAB + BACKSPACE + FORM_FEED; 

string StringReverser::reverseCharacters(string input, int stIdx, int edIdx)		
  {									
    int len = edIdx - stIdx + 1;						
    if ( 1 >= len )							
      {									
	return input.substr(stIdx, len);					
      }									
    return input.substr(edIdx, 1) + reverseCharacters( input, stIdx, edIdx - 1); 
  }									
  
string StringReverser::reverseWords(string input)					
  {									
    string accumulator("");						
    
    int spaceIdx = input.find_first_of(WHITESPACE, 0);			
    accumulator.append(reverseCharacters(input, 0, (-1 == spaceIdx) ? input.length() - 1: spaceIdx - 1));	
    
    if ( -1 != spaceIdx )							
      {									
	accumulator.append(input.substr(spaceIdx,1));			
	accumulator.append(reverseWords(input.substr(spaceIdx + 1)));	
      }									
    
    return accumulator;							
  }									
  
string StringReverser::reverse(string input)						
  {									
    return reverseWords(reverseCharacters(input, 0, input.length() -1 ));	
  }									
