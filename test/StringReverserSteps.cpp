#include <gtest/gtest.h>
#include <cucumber-cpp/defs.hpp>
#include <string>
#include "StringReverser.h"

using namespace std;

struct Context
{
  StringReverser stringReverser;
  string output;
};

GIVEN("^a String Reverser$")
{
  USING_CONTEXT(Context, context);
  context->stringReverser = StringReverser();
}

WHEN("^I reverse the string \"(.*)\"$")
{
  REGEX_PARAM(string, input);
  USING_CONTEXT(Context, context);
  context->output = context->stringReverser.reverse(input);
}

THEN("^the result is \"(.*)\"$")
{
  REGEX_PARAM(string, expected);
  USING_CONTEXT(Context, context);
  EXPECT_EQ(expected, context->output);
}
