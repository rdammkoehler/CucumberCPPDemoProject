#What is this?
This is a setup and build exercise for Cucumber-CPP on Ubuntu 10.04. It does not (yet) attempt to explain how to use Cucumber to do ATDD. You should be able to setup Cucumber-CPP and a simple test project using this information with little or no difficulty. 

Soon, more stuff about what is ATDD, What is Cucumber, How does it all work? When should I do this? etc. will be added to this project.

If you have any suggestions or comments, please let me know.

#Assuming you are starting from Ubuntu 10.04 i386 iso

```
http://mirror.anl.gov/pub/ubuntu-iso/DVDs/ubuntu/10.04/release/
http://mirror.anl.gov/pub/ubuntu-iso/DVDs/ubuntu/10.04/release/ubuntu-10.04.4-dvd-i386.iso
```

#Assuming you have a curl, text editor, cmake, make, g++, and git

```bash
sudo apt-get install curl cmake make g++ git-core emacs
```

# Install Boost 

```bash
sudo apt-get install libboost-all-dev
```

# Install GTest 

```bash
sudo apt-get install libgtest-dev
```

# Install ruby and the appropriate gems

```bash
sudo apt-get install zlib1g zlib1g-dev libyaml-0-2 libyaml-dev
curl -L https://get.rvm.io | bash -s stable --ruby
source ~/.bashrc
rvm install 1.9.3
```

# Get the gems for cucumber

```bash
gem install gherkin cucumber
source ~/.rvm/scripts/rvm
```

# Download Cucumber-CPP

Create a projects folder from your home directory

```bash
mkdir projects
```

Change the current directory to your new projects directory

```bash
cd projects
```

Use git to copy the cucumber project

```bash
git clone https://github.com/cucumber/cucumber-cpp.git
```

# Compile Cucumber-CPP

Change current directory

```bash
cd cucumber-cpp
```

Build cucumber with the following commands
  
```bash      
cmake -E make_directory build
cmake -E chdir build cmake -DCUKE_ENABLE_EXAMPLES=on ..
cmake --build build
cmake --build build --target test
```

Then test the cucumber build by attempting to run an example

```bash
build/examples/Calc/GTestCalculatorSteps >/dev/null &
cucumber -s examples/Calc/CalcFeatures
```

Your output should look like this;

```cucumber         
# language: en
 Feature: Addition
     In order to avoid silly mistakes
     As a math idiot 
     I want to be told the sum of two numbers
        
     Scenario Outline: Add two numbers                    
       Given I have entered <input_1> into the calculator 
       And I have entered <input_2> into the calculator   
       When I press <button>                              
       Then the result should be <output> on the screen   
        
       Examples: 
         | input_1 | input_2 | button | output |
         | 20      | 30      | add    | 50     |
         | 2       | 5       | add    | 7      |
         | 0       | 40      | add    | 40     |
        
# language: en
 Feature: Division
     In order to avoid silly mistakes
     Cashiers must be able to calculate a fraction
        
     Scenario: Regular numbers                     
       Given I have entered 3 into the calculator  
       And I have entered 2 into the calculator    
       When I press divide                         
       Then the result should be 1.5 on the screen 
        
 4 scenarios (4 passed)
16 steps (16 passed)
0m3.454s
```
        
# Create your project

Create a project folder (MyProject)

```bash
mkdir MyProject
```

Create a test code folder

```bash
mkdir MyProject/test
```

Create a source code folder

```bash
mkdir MyProject/src
```

Create a *CMakeLists.txt* file in your MyProject folder using a text editor. The file should contain the following code;

```cmake
cmake_minimum_required(VERSION 2.8)

project(StringReverser)

#create a library from our code
add_library(StringReverser src/StringReverser.cpp)

#setup testing environment
enable_testing()
set(GTEST_ROOT /usr/lib)
link_directories(${GTEST_ROOT})
find_package(GTest REQUIRED)

#create a test executable linked to our code
include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
add_executable(TestStringReverser test/TestStringReverser.cpp)
target_link_libraries(TestStringReverser StringReverser ${GTEST_MAIN_LIBRARY} ${GTEST_LIBRARIES} pthread)
```

Test Drive a StringReverser, put the source code in the src folder and the test code in the test folder. Optionally you can download the source code from the github project folder.

Create the tests
      
Copy the test code from github using curl

    curl https://raw.github.com/rdammkoehler/StringReverser/master/test/TestStringReverser.cpp > MyProject/test/TestStringReverser.cpp

Create code to pass the tests

Copy the source code form github using curl

    curl https://raw.github.com/rdammkoehler/StringReverser/master/src/StringReverser.h > MyProject/src/StringReverser.h
    curl https://raw.github.com/rdammkoehler/StringReverser/master/src/StringReverser.cpp > MyProject/src/StringReverser.cpp

Run cmake

```bash
cd MyProject
rm -Rf build
cmake -E make_directory build
cmake -E chdir build cmake ..
```

Run make to compile and link your code

```bash
cd build
make
```

Run the test suite

```bash
./TestStringReverser
```

Your output should look like this

```bash
Running main() from gtest_main.cc
[==========] Running 22 tests from 3 test cases.
[----------] Global test environment set-up.
[----------] 6 tests from CharacterReverser
[ RUN      ] CharacterReverser.ReversesGivenStringWithIndexes
[       OK ] CharacterReverser.ReversesGivenStringWithIndexes (0 ms)
[ RUN      ] CharacterReverser.FourCharReversesGivenStringWithIndexes
[       OK ] CharacterReverser.FourCharReversesGivenStringWithIndexes (0 ms)
[ RUN      ] CharacterReverser.TwoCharWithSpaceReversesGivenStringWithIndexes
[       OK ] CharacterReverser.TwoCharWithSpaceReversesGivenStringWithIndexes (0 ms)
[ RUN      ] CharacterReverser.FourCharWithSpacesReversesGivenStringWithIndexes
[       OK ] CharacterReverser.FourCharWithSpacesReversesGivenStringWithIndexes (0 ms)
[ RUN      ] CharacterReverser.WorksOnAPartial
[       OK ] CharacterReverser.WorksOnAPartial (0 ms)
[ RUN      ] CharacterReverser.SingleCharReversesGivenStringWithIndexes
[       OK ] CharacterReverser.SingleCharReversesGivenStringWithIndexes (0 ms)
[----------] 6 tests from CharacterReverser (0 ms total)

[----------] 15 tests from StringReverser
[ RUN      ] StringReverser.IsIdentityOperationOverEmptyString
[       OK ] StringReverser.IsIdentityOperationOverEmptyString (0 ms)
[ RUN      ] StringReverser.IsIdentityOperationOverSingleCharacter
[       OK ] StringReverser.IsIdentityOperationOverSingleCharacter (0 ms)
[ RUN      ] StringReverser.ReversesCharactersSeperatedByWhiteSpace
[       OK ] StringReverser.ReversesCharactersSeperatedByWhiteSpace (0 ms)
[ RUN      ] StringReverser.ReversesCharacterPairsSeperatedByWhiteSpace
[       OK ] StringReverser.ReversesCharacterPairsSeperatedByWhiteSpace (0 ms)
[ RUN      ] StringReverser.AdjacentSpacesPreservedInOutput
[       OK ] StringReverser.AdjacentSpacesPreservedInOutput (0 ms)
[ RUN      ] StringReverser.LeadingSpaceBecomesTrailingSpace
[       OK ] StringReverser.LeadingSpaceBecomesTrailingSpace (0 ms)
[ RUN      ] StringReverser.TrailingSpaceBecomesLeadingSpace
[       OK ] StringReverser.TrailingSpaceBecomesLeadingSpace (0 ms)
[ RUN      ] StringReverser.IsIdentityOperationOverMulticharacterWord
[       OK ] StringReverser.IsIdentityOperationOverMulticharacterWord (0 ms)
[ RUN      ] StringReverser.TabIsWhitespaceToo
[       OK ] StringReverser.TabIsWhitespaceToo (0 ms)
[ RUN      ] StringReverser.NewlineIsWhitespaceToo
[       OK ] StringReverser.NewlineIsWhitespaceToo (0 ms)
[ RUN      ] StringReverser.CarriageReturnIsWhitespaceToo
[       OK ] StringReverser.CarriageReturnIsWhitespaceToo (0 ms)
[ RUN      ] StringReverser.VerticalTabIsWhitespaceToo
[       OK ] StringReverser.VerticalTabIsWhitespaceToo (0 ms)
[ RUN      ] StringReverser.BackspaceIsWhitespaceToo
[       OK ] StringReverser.BackspaceIsWhitespaceToo (0 ms)
[ RUN      ] StringReverser.FormFeedIsWhitespaceToo
[       OK ] StringReverser.FormFeedIsWhitespaceToo (0 ms)
[ RUN      ] StringReverser.MultipleWhitespaceIsReversedWhitespace
[       OK ] StringReverser.MultipleWhitespaceIsReversedWhitespace (0 ms)
[----------] 15 tests from StringReverser (0 ms total)

[----------] 1 test from TripleWordStringReverser
[ RUN      ] TripleWordStringReverser.PutsLastWordFirstAndFirstWordLast
[       OK ] TripleWordStringReverser.PutsLastWordFirstAndFirstWordLast (0 ms)
[----------] 1 test from TripleWordStringReverser (0 ms total)

[----------] Global test environment tear-down
[==========] 22 tests from 3 test cases ran. (0 ms total)
[  PASSED  ] 22 tests.
```

#Setting up Cucumber for Testing

Create a feature sub-folder (features)

```bash
mkdir MyProject/features
```

Create a 'feature' file for the cucumer scenario(s) called *reverser.feature* in the newly created features subdirectory. Then add the following gherkin to the feature file

```gherkin
Feature: Reverse Words in a String
  In order to read backwards
  readers must have the words in their text reveresed

  Scenario: Empty String Reversal
    Given a String Reverser
    When I reverse the string ""
    Then the result is ""

  Scenario: Single Character Reversal
    Given a String Reverser
    When I reverse the string "A"
    Then the result is "A"

  Scenario: Multicharacter Word Reversal
    Given a String Reverser
    When I reverse the string "Bacon"
    Then the result is "Bacon"

  Scenario: Multiword String Reversal
    Given a String Reverser
    When I reverse the string "Bacon is the life blood of Agile Software Development"
    Then the result is "Development Software Agile of blood life the is Bacon"

  Scenario: Palindrome String Reversal
    Given a String Reverser
    When I reverse the string "Rats Live on no Evil Star"
    Then the result is "Star Evil no on Live Rats"
```

Create a 'wire' file for execution

```bash
echo -e "host: localhost\nport: 3902" >> MyProject/features/myfeatures.wire
```

Edit the *CMakeLists.txt* file and add the following

```cmake
#get boost
set(CUKE_CORE_BOOST_LIBS thread system regex date_time)
set(CUKE_DYNAMIC_BOOST_LIBS ${CUKE_CORE_BOOST_LIBS} ${CUKE_TEST_BOOST_LIBS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_ALL_DYN_LINK")
set(Boost_USE_STATIC_LIBS OFF)
find_package(Boost COMPONENTS ${CUKE_DYNAMIC_BOOST_LIBS})
include_directories(${Boost_INCLUDE_DIRS})
set(CUKE_EXTRA_LIBRARIES ${CUKE_EXTRA_LIBRARIES} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_DATE_TIME_LIBRARY})

#create the Cucumber wire-server to provied steps
set(CUKE_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/../cucumber-cpp/include)
set(CUKE_LIBRARIES libcucumber-cpp.a)
link_directories(${CMAKE_SOURCE_DIR}/../cucumber-cpp/build/src)
include_directories(${CUKE_INCLUDE_DIRS})
add_executable(StringReverserSteps test/StringReverserSteps)
target_link_libraries(StringReverserSteps StringReverser ${GTEST_LIBRARIES} pthread ${CUKE_LIBRARIES} ${CUKE_EXTRA_LIBRARIES})
```

Create a steps file for the cumber wire server, put the following code in the file *StringReverserSteps.cpp* in the test folder

```cpp
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
```

Run cmake

```bash
cd MyProject
rm -Rf build
cmake -E make_directory build
cmake -E chdir build cmake ..
cmake --build build
```
# Running your tests

Run the cucumber wire server 

```bash
./build/StringReverserSteps &
cucumber -s features
```

You output should look like this 
```bash
Feature: Reverse Words in a String
  In order to read backwards
  readers must have the words in their text reveresed

  Scenario: Empty String Reversal
    Given a String Reverser
    When I reverse the string ""
    Then the result is ""

  Scenario: Single Character Reversal
    Given a String Reverser
    When I reverse the string "A"
    Then the result is "A"

  Scenario: Multicharacter Word Reversal
    Given a String Reverser
    When I reverse the string "Bacon"
    Then the result is "Bacon"

  Scenario: Multiword String Reversal
    Given a String Reverser
    When I reverse the string "Bacon is the life blood of Agile Software Development"
    Then the result is "Development Software Agile of blood life the is Bacon"

  Scenario: Palindrome String Reversal
    Given a String Reverser
    When I reverse the string "Rats Live on no Evil Star"
    Then the result is "Star Evil no on Live Rats"

5 scenarios (5 passed)
15 steps (15 passed)
0m3.128s
```
