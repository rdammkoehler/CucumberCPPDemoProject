#include "gtest/gtest.h"
#include <string>

using namespace std;

// CODE UNDER TEST
const string SPACE = " ";
const string TAB = "\t";
const string NEWLINE = "\n";
const string CARRAIGE_RETURN = "\r";
const string VERTICAL_TAB = "\v";
const string BACKSPACE = "\b";
const string FORM_FEED = "\f";

const string WHITESPACE = SPACE + TAB + NEWLINE + CARRAIGE_RETURN + VERTICAL_TAB + BACKSPACE + FORM_FEED;

string reverseCharacters(string input)
{
  string rval = "";
  for(int i = 0; i < input.length(); ++i)
    {
      rval.insert(0, 1, input[i]);
    }
  return rval;
}

string reverseWords(string input)
{
  string accumulator("");
 
  int initialIdx = 0;
  int spaceIdx = input.find_first_of(WHITESPACE, initialIdx);
  string substr = input.substr(initialIdx, spaceIdx - initialIdx);
  accumulator.append(reverseCharacters(substr));
  
  if ( -1 != spaceIdx )
    {
      accumulator.append(input.substr(spaceIdx,1));
      accumulator.append(reverseWords(input.substr(spaceIdx - initialIdx + 1)));
    }
  
  return accumulator;
}

string reverse(string input)
{
  return reverseWords(reverseCharacters(input));
}


// TESTS
TEST(StringReverser, IsIdentityOperationOverEmptyString) 
{
  ASSERT_EQ("", reverse("")) << "Empty string is not empty";
}

TEST(StringReverser, IsIdentityOperationOverSingleCharacter)
{
  ASSERT_EQ("a", reverse("a")) << "Single Character string is not identity";
}

TEST(StringReverser, ReversesCharactersSeperatedByWhiteSpace)
{
  ASSERT_EQ("j i", reverse("i j")) << "Single Character Words not reversed";
}

TEST(StringReverser, ReversesCharacterPairsSeperatedByWhiteSpace)
{
  ASSERT_EQ("kl ij", reverse("ij kl")) << "Multicharacter Pairs Not Reversed";
}

TEST(TripleWordStringReverser, PutsLastWordFirstAndFirstWordLast)
{
  ASSERT_EQ("klmnop defghij abc", reverse("abc defghij klmnop")) << "First word is not last, or last word is not first. Or both.";
}

TEST(StringReverser, AdjacentSpacesPreservedInOutput) 
{
  ASSERT_EQ("xyzzy  lmnop", reverse("lmnop  xyzzy")) << "Adjacent Spaces should be preserved in output";
}

TEST(StringReverser, LeadingSpaceBecomesTrailingSpace)
{
  ASSERT_EQ("world hello ", reverse(" hello world")) << "Leading space should become trailing space";
}

TEST(StringReverser, TrailingSpaceBecomesLeadingSpace)
{
  ASSERT_EQ("  hello world", reverse("world hello  ")) << "Trailing space should become leading space";
}

TEST(StringReverser, IsIdentityOperationOverMulticharacterWord)
{
  ASSERT_EQ("xyzzy", reverse("xyzzy")) << "Multicharacter word is not identity";
}

TEST(StringReverser, TabIsWhitespaceToo)
{
  ASSERT_EQ("world\thello", reverse("hello\tworld")) << "Tabs should be treated like a whilspace";
}

TEST(StringReverser, NewlineIsWhitespaceToo)
{
  ASSERT_EQ("world\nhello", reverse("hello\nworld")) << "Newline should be treated like a whilspace";
}

TEST(StringReverser, CarriageReturnIsWhitespaceToo)
{
  ASSERT_EQ("world\rhello", reverse("hello\rworld")) << "Carriage Return should be treated like a whilspace";
}

TEST(StringReverser, VerticalTabIsWhitespaceToo)
{
  ASSERT_EQ("world\vhello", reverse("hello\vworld")) << "Vertical Tab should be treated like a whilspace";
}

TEST(StringReverser, BackspaceIsWhitespaceToo)
{
  ASSERT_EQ("world\bhello", reverse("hello\bworld")) << "Backspace should be treated like a whilspace";
}

TEST(StringReverser, FormFeedIsWhitespaceToo)
{
  ASSERT_EQ("world\fhello", reverse("hello\fworld")) << "Form Feed should be treated like a whilspace";
}

TEST(StringReverser, MultipleWhitespaceIsReversedWhitespace)
{
  ASSERT_EQ(" \b\v\r\b\n\f\t ", reverse(" \t\f\n\b\r\v\b ")) << "Whitespaces were not reveresed";
}



