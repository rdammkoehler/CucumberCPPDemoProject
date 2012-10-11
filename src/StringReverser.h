#ifndef STRING_REVERSER_H						
#define STRING_REVERSER_H						
#include <string>							

using namespace std;

class StringReverser							
{									
 public:								
  StringReverser() {}
  ~StringReverser() {}
  string reverseCharacters(string, int, int);
  string reverseWords(string);
  string reverse(string);
};									

#endif
