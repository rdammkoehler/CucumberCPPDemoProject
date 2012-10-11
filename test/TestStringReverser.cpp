#include "gtest/gtest.h"
#include <string>
#include "StringReverser.h"

TEST(CharacterReverser, ReversesGivenStringWithIndexes)
{
  ASSERT_EQ("cba", StringReverser().reverseCharacters("abc", 0, 2));
}

TEST(CharacterReverser, FourCharReversesGivenStringWithIndexes)
{
  ASSERT_EQ("dcba", StringReverser().reverseCharacters("abcd", 0, 3));
}

TEST(CharacterReverser, TwoCharWithSpaceReversesGivenStringWithIndexes)
{
  ASSERT_EQ("d a", StringReverser().reverseCharacters("a d", 0, 2));
}

TEST(CharacterReverser, FourCharWithSpacesReversesGivenStringWithIndexes)
{
  ASSERT_EQ("d c b a", StringReverser().reverseCharacters("a b c d", 0, 6));
}

TEST(CharacterReverser, WorksOnAPartial) 
{
  ASSERT_EQ("defg", StringReverser().reverseCharacters("abcgfed",3, 6));
}

TEST(CharacterReverser, SingleCharReversesGivenStringWithIndexes)
{
  ASSERT_EQ("a", StringReverser().reverseCharacters("a", 0, 1));
}

TEST(StringReverser, IsIdentityOperationOverEmptyString) 
{
  ASSERT_EQ("", StringReverser().reverse("")) << "Empty string is not empty";
}

TEST(StringReverser, IsIdentityOperationOverSingleCharacter)
{
  ASSERT_EQ("a", StringReverser().reverse("a")) << "Single Character string is not identity";
}

TEST(StringReverser, ReversesCharactersSeperatedByWhiteSpace)
{
  ASSERT_EQ("j i", StringReverser().reverse("i j")) << "Single Character Words not reversed";
}

TEST(StringReverser, ReversesCharacterPairsSeperatedByWhiteSpace)
{
  ASSERT_EQ("kl ij", StringReverser().reverse("ij kl")) << "Multicharacter Pairs Not Reversed";
}

TEST(TripleWordStringReverser, PutsLastWordFirstAndFirstWordLast)
{
  ASSERT_EQ("klmnop defghij abc", StringReverser().reverse("abc defghij klmnop")) << "First word is not last, or last word is not first. Or both.";
}

TEST(StringReverser, AdjacentSpacesPreservedInOutput) 
{
  ASSERT_EQ("xyzzy  lmnop", StringReverser().reverse("lmnop  xyzzy")) << "Adjacent Spaces should be preserved in output";
}

TEST(StringReverser, LeadingSpaceBecomesTrailingSpace)
{
  ASSERT_EQ("world hello ", StringReverser().reverse(" hello world")) << "Leading space should become trailing space";
}

TEST(StringReverser, TrailingSpaceBecomesLeadingSpace)
{
  ASSERT_EQ("  hello world", StringReverser().reverse("world hello  ")) << "Trailing space should become leading space";
}

TEST(StringReverser, IsIdentityOperationOverMulticharacterWord)
{
  ASSERT_EQ("xyzzy", StringReverser().reverse("xyzzy")) << "Multicharacter word is not identity";
}

TEST(StringReverser, TabIsWhitespaceToo)
{
  ASSERT_EQ("world\thello", StringReverser().reverse("hello\tworld")) << "Tabs should be treated like a whilspace";
}

TEST(StringReverser, NewlineIsWhitespaceToo)
{
  ASSERT_EQ("world\nhello", StringReverser().reverse("hello\nworld")) << "Newline should be treated like a whilspace";
}

TEST(StringReverser, CarriageReturnIsWhitespaceToo)
{
  ASSERT_EQ("world\rhello", StringReverser().reverse("hello\rworld")) << "Carriage Return should be treated like a whilspace";
}

TEST(StringReverser, VerticalTabIsWhitespaceToo)
{
  ASSERT_EQ("world\vhello", StringReverser().reverse("hello\vworld")) << "Vertical Tab should be treated like a whilspace";
}

TEST(StringReverser, BackspaceIsWhitespaceToo)
{
  ASSERT_EQ("world\bhello", StringReverser().reverse("hello\bworld")) << "Backspace should be treated like a whilspace";
}

TEST(StringReverser, FormFeedIsWhitespaceToo)
{
  ASSERT_EQ("world\fhello", StringReverser().reverse("hello\fworld")) << "Form Feed should be treated like a whilspace";
}

TEST(StringReverser, MultipleWhitespaceIsReversedWhitespace)
{
  ASSERT_EQ(" \b\v\r\b\n\f\t ", StringReverser().reverse(" \t\f\n\b\r\v\b ")) << "Whitespaces were not reveresed";
}

