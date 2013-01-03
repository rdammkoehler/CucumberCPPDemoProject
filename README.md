#What is this?
This is a setup and build exercise for Cucumber-CPP on Ubuntu 10.04. It does not (yet) attempt to explain how to use Cucumber to do ATDD. You should be able to setup Cucumber-CPP and a simple test project using this information with little or no difficulty. 

>
> This example is _not_ intended to convey best practices for writing Gherkin
>

Soon, more stuff about what is ATDD, What is Cucumber, How does it all work? When should I do this? etc. will be added to this project.

If you have any suggestions or comments, please let me know.

#Notice: Ubuntu 12.04
I've just received comments that this is *not* working on Ubuntu 12.04. I'll work out the why and update soon on that topic.

#Assuming you are starting from Ubuntu 10.04 i386 iso

```
http://mirror.anl.gov/pub/ubuntu-iso/DVDs/ubuntu/10.04/release/
http://mirror.anl.gov/pub/ubuntu-iso/DVDs/ubuntu/10.04/release/ubuntu-10.04.4-dvd-i386.iso
```

#Setup the development environment

##Install curl, a text editor, cmake, make, g++, and git

>
> I've left the editor install out. I prefer emacs, you may choose some other tool.
>
> For example you could use;
> 
> sudo apt-get install emacs
>
> *OR*
>
> sudo apt-get install vim
>
> *OR*
>
> use gedit which should already be available in your applications menu
>

```bash
sudo apt-get install curl cmake make g++ git-core
```

## Install Boost 

```bash
sudo apt-get install libboost-all-dev
```
>
> The boost libraries are necessary for the cucmber-cpp implementation. 
> While a more concise subset of the boost libraries is required, it is easiest to just
> install them all
>

## Install GTest 

```bash
sudo apt-get install libgtest-dev
```

>
> There are alaternatives here, however GTest provides a simple set of assertion macros that can
> be used in the step files. Boost also provides a set of assertion classes, as does CPPSPEC. We
> don't use CPPSPEC because no documentation is available (due to link rot). 
>

## Install ruby and the appropriate gems

```bash
sudo apt-get install zlib1g zlib1g-dev libyaml-0-2 libyaml-dev
curl -L https://get.rvm.io | bash -s stable --ruby
source ~/.bashrc
rvm install 1.9.3
```

>
> Cucumber comes to us from the Ruby world. Cucmber-CPP works with Cucumber via the *wire protocol*. 
> So in order to make this all work we need the Ruby part of Cucumber to execute our feature files. 
> Here is a short description of the way the wire protocol works; https://github.com/cucumber/cucumber/wiki/Wire-Protocol
>

## Get the gems for cucumber

```bash
gem install gherkin cucumber
source ~/.rvm/scripts/rvm
```

>
> Gems are a Ruby technology that allow you to pull in modules of code from other sources. In this case
> we are pulling in gherkin and cucumber. Here ***the orderder is important*** so be sure to pull gherkin
> first. Gherkin is the interpreter for your feature files. Cucumber uses this to read and execute the steps
> you have defined in a scenario. Cucumber is the test execution engine. It also creates the output.
>

## Download Cucumber-CPP

###Create a projects folder from your home directory

```bash
mkdir projects
```

###Change the current directory to your new projects directory

```bash
cd projects
```

###Use git to copy the cucumber project

```bash
git clone https://github.com/cucumber/cucumber-cpp.git
```

### Compile Cucumber-CPP

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

>
> ***Note*** You should see some warnings, but no errors at this point. If you see a warning that Google Test (GTEST) was *not* found, the following step(s) will fail. Go back and check to see that Google Test was installed correctly. You can do this by looking for the following information;
>
> 1. You have the binary librarires for Google Test in */usr/lib*
>    1.1. 
>    1.1. /usr/lib/libgtest.a
>    1.1. /usr/lib/libgtest.la
>    1.1. /usr/lib/libgtest_main.a
>    1.1. /usr/lib/libgtest_main.la
>    1.1. /usr/lib/libgtest_main.so
>    1.1. /usr/lib/libgtest_main.so.0
>    1.1. /usr/lib/libgtest_main.so.0.0.0
>    1.1. /usr/lib/libgtest.so
>    1.1. /usr/lib/libgtest.so.0
>    1.1. /usr/lib/libgtest.so.0.0.0 
> 1. You have the include headers for Google Test in */usr/include/gtest*
>
> If these conditions are not true, go back and check what happened when you ran *sudo apt-get install libgtest-dev*
>
> ***Note:*** we know this isn't working correctly on Ubuntu 12.04 at this time.

##Test cucumber 

###Run an example

```bash
build/examples/Calc/GTestCalculatorSteps >/dev/null &
cucumber -s examples/Calc/CalcFeatures
```

>
> **Note:** The -s flag disables source line reporting in the output. You can try this command without the -s and see that each line of the feature file is reported next to its output. I find that annoying, so I surpress that part of the output.
>

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

Here we are creating a new project that uses Cucumber-CPP. The point is not about learning C++, but rather how to setup your project to use Cucumber. You won't need to write any actual C++ code, you can just copy it from various locations on the web (this repo) and copy-paste it from this README.md file. In real life I don't recommend copy-paste approach. But for expedience I'm using that approach here. 

##Create a project folder (MyProject)

```bash
cd ~/projects
mkdir MyProject
```

###Create a test code folder

```bash
mkdir MyProject/test
```

###Create a source code folder

```bash
mkdir MyProject/src
```

##Create a *CMakeLists.txt* file

In your MyProject folder using a text editor. The file should contain the following code;

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

> #What does that CMakeLists.txt file do?
>
> The important (irregular) part is setting up your testing environment.
>
> For our purposes we use GoogleTest 
> http://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&ved=0CCAQFjAA&url=http%3A%2F%2Fcode.google.com%2Fp%2Fgoogletest%2F&ei=Wg1_UIFUyJvIAYiAgZAJ&usg=AFQjCNFzFRdftgqf2liiAPhuxnsOJqxnLA
>
> We installed Google test using apt-get and it placed our library in /usr/lib
>
> First off, add GTest to our link directories (link_directories...) [not strictly necessary unless the location is not */usr/lib*]
>
> Using find_package(GTest REQUIRED) we've told CMake to go look for Google
>
> Test and if it isn't found, stop.
>
> Then add the include directories for Google Test along with our own source code
>
> Finally create an executable called TestStringReverser using our TestStringReverser.cpp file and then
>
> Add link librarires for the executable including Google Test's main library
>

#Test Drive a StringReverser

Put the source code in the src folder and the test code in the test folder. Optionally you can download the source code from the github project folder.

##Create the tests
      
###Copy the test code from github using curl

    curl https://raw.github.com/rdammkoehler/StringReverser/master/test/TestStringReverser.cpp > MyProject/test/TestStringReverser.cpp

##Create code to pass the tests

###Copy the source code form github using curl

    curl https://raw.github.com/rdammkoehler/StringReverser/master/src/StringReverser.h > MyProject/src/StringReverser.h
    curl https://raw.github.com/rdammkoehler/StringReverser/master/src/StringReverser.cpp > MyProject/src/StringReverser.cpp

##Run cmake

```bash
cd MyProject
rm -Rf build
cmake -E make_directory build
cmake -E chdir build cmake ..
cmake --build build
```

##Run the test suite

Before we proceed we should make sure the code we just compiled actually works. So lets run the tests to make sure.

```bash
./build/TestStringReverser
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

##Create a feature sub-folder (features)

```bash
cd ..
mkdir MyProject/features
```

##Create a 'feature' 

Create a file for the cucumer scenario(s) called *reverser.feature* in the newly created features subdirectory. Then add the following gherkin to the feature file

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

##Create a 'wire' file 

```bash
echo -e "host: localhost\nport: 55555" >> MyProject/features/myfeatures.wire
```

>
> Cucumber uses this file to determine where to connect for test execution. The file can be *anywhere* inside the directory structure that contains your
> feature. There should be only one of these files. The host is the machine that is running your cucumber-cpp application (we'll build that in a minute) 
> and the port is the TCP port that the cucumber-cpp application is listening on. This number *must*match* the argument passed into the cucumber-cpp 
> application. Otherwise cucumber won't be able to find the steps and execution will fail.  
>

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

> #What does that CMake stuff do?
>
> Configure the location ofthe Boost libriaries, both static and dynamic
>
> Set some linker flags for using Boost
>
> Turn Static Boost libraries off
>
> Add the Boost include libraries to the include path for the compiler
>
> Add the Boost libriaries into the extra libs path for compilation
>
> Identify the location of the Cucumber-CPP include files
>
> Identify the location of the Cucumber-CPP libriaries
>
> Add the cucumber libriaries into the linker path
>
> Create an executable called StirngReverserSteps from our Steps code
>
> Link the StringReverserSteps executable with Google Test, Cucumber, and implicitly Boost via the CUKE_EXTRA_LIBRARIES variable
>

##Create a steps file 

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

>
> # What does this do?
> The macros GIVEN, WHEN, and THEN will match the regular expression argument against the feature file we created. 
> When cucumber reads the feature file it will send each line from a scenario to your cucumber-cpp application and 
> the cucumber-cpp application will execute it. The code above **is** that cucumber-cpp application. Therefore, any
> line in your scenario must have a matching regular expression in this application. 
> 
> Also note that by including cucumber-cpp (and later linking this code into cucumber-cpp's libriaries) it will create 
> a 'wire server' that runs on a computer using TCP to talk to a cucumber client (the Ruby cucumber application). 
> All this *magic* is done for us by the cucumber-cpp libriaries.
>

###Run cmake

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
./build/StringReverserSteps 55555 &
cucumber -s features
```

>
> The 55555 argument passed into StringReverserSteps application tells your 'wire server' to listen for network traffic
> on port 55555. This port number must match the number given in the *myfeatures.wire* file we created earlier. Note that
> you can use any valid TCP port 1..65535, however ports below 1024 are generally reserved for the operating system, and 
> there are several ports above 1024 that are commonly used. Cucumber defaults to 3902, so you can just specifiy the default
> if you like. 
>
> For more information on TCP ports, you can start here; http://en.wikipedia.org/wiki/Port_(computer_networking)
>

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

# Hooks and Tags

Another feature available to you when using Cucumber CPP is hooks and tags. There is a resonable example of this feature in the Cucumber CPP repository that can be found here https://github.com/cucumber/cucumber-cpp/tree/master/examples/FeatureShowcase/tag
The short form of how this works is that there are a few macros provided for creating hooks into the step file execution. They include

* BEFORE
* AFTER
* BEFORE("@tag")
* AFTER("@tag")
* AROUND_STEP("@tag")
* AFTER_STEP("@tag")

>
> Where I have used the @tag is a place holder for any annotation that you would add to the feature (Gherkin) file to mark a scenario with a tag. For example
>
>   @live_db
>   Scenario: Duplicate Record Failure
>      Given the database contains a record for "Joe"
>      When I create a new record for "Joe"
>      Then it fails to save because of a duplicate record error 
>

Each of these macros can be used in your step definitions to add hooks to your current definitions.

# More Information

Cucumber: http://cukes.info/

Cucumber CPP: https://github.com/cucumber/cucumber-cpp

Cucumber Book: http://pragprog.com/book/hwcuc/the-cucumber-book

Gherkin: http://docs.behat.org/guides/1.gherkin.html

RVM: https://rvm.io/

Ruby: http://www.ruby-lang.org/en/

Google Test: http://code.google.com/p/googletest/

Boost: http://www.boost.org/

CMake: http://www.cmake.org/

github: https://github.com/

git: http://git-scm.com/

Ubuntu: http://www.ubuntu.com/

Apt-Get How To: https://help.ubuntu.com/8.04/serverguide/apt-get.html

Emacs: http://www.gnu.org/software/emacs/

VIM: http://www.vim.org/