#include "gtest/gtest.h"
#include <string>

using namespace std;

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
  
  if ( spaceIdx != -1 )
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

TEST(StringReverser, IsIdentityOperationOverEmptyString) 
{
  string actual = reverse("");

  ASSERT_EQ("", actual) << "Empty string is not empty";
}

TEST(StringReverser, IsIdentityOperationOverSingleCharacter)
{
  string actual = reverse("a");

  ASSERT_EQ("a", actual) << "Single Character string is not identity";
}

TEST(StringReverser, ReversesCharactersSeperatedByWhiteSpace)
{
  string actual = reverse("i j");

  ASSERT_EQ("j i", actual) << "Single Character Words not reversed";
}

TEST(StringReverser, ReversesCharacterPairsSeperatedByWhiteSpace)
{
  string actual = reverse("ij kl");

  ASSERT_EQ("kl ij", actual) << "Multicharacter Pairs Not Reversed";
}

TEST(TripleWordStringReverser, PutsLastWordFirstAndFirstWordLast)
{
  string actual = reverse("abc defghij klmnop");

  ASSERT_EQ("klmnop defghij abc", actual) << "First word is not last, or last word is not first. Or both.";
}

TEST(StringReverser, AdjacentSpacesPreservedInOutput) 
{
  string actual = reverse("lmnop  xyzzy");

  ASSERT_EQ("xyzzy  lmnop", actual) << "Adjacent Spaces should be preserved in output";
}

TEST(StringReverser, LeadingSpaceBecomesTrailingSpace)
{
  string actual = reverse(" hello world");

  ASSERT_EQ("world hello ", actual) << "Leading space should become trailing space";
}

TEST(StringReverser, TrailingSpaceBecomesLeadingSpace)
{
  string actual = reverse("world hello  ");

  ASSERT_EQ("  hello world", actual) << "Trailing space should become leading space";
}

TEST(StringReverser, IsIdentityOperationOverMulticharacterWord)
{
  string actual = reverse("xyzzy");

  ASSERT_EQ("xyzzy", actual) << "Multicharacter word is not identity";
}

TEST(StringReverser, TabIsWhitespaceToo)
{
  string actual = reverse("hello\tworld");

  ASSERT_EQ("world\thello", actual) << "Tabs should be treated like a whilspace";
}

TEST(StringReverser, NewlineIsWhitespaceToo)
{
  string actual = reverse("hello\nworld");

  ASSERT_EQ("world\nhello", actual) << "Newline should be treated like a whilspace";
}

TEST(StringReverser, CarriageReturnIsWhitespaceToo)
{
  string actual = reverse("hello\rworld");

  ASSERT_EQ("world\rhello", actual) << "Carriage Return should be treated like a whilspace";
}

TEST(StringReverser, VerticalTabIsWhitespaceToo)
{
  string actual = reverse("hello\vworld");

  ASSERT_EQ("world\vhello", actual) << "Vertical Tab should be treated like a whilspace";
}

TEST(StringReverser, BackspaceIsWhitespaceToo)
{
  string actual = reverse("hello\bworld");

  ASSERT_EQ("world\bhello", actual) << "Backspace should be treated like a whilspace";
}

TEST(StringReverser, FormFeedIsWhitespaceToo)
{
  string actual = reverse("hello\fworld");

  ASSERT_EQ("world\fhello", actual) << "Form Feed should be treated like a whilspace";
}

TEST(StringReverser, MultipleWhitespaceIsReversedWhitespace)
{
  string actual = reverse(" \t\f\n\b\r\v\b ");

  ASSERT_EQ(" \b\v\r\b\n\f\t ", actual) << "Whitespaces were not reveresed";
}



