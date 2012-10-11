** WARNING **
These instructions are still being tested and may contain errors or other issues.

0) Assuming you have a text editor, cmake, make, g++, and git

1) Install Boost (sudo apt-get install libboost-all-dev)

2) Install GTest (sudo apt-get install liggtest-dev)

3) Install ruby and the appropriate gems

    # Method 1: Use apt-get
       sudo apt-get install ruby1.9

    # Method 2: Use rvm
       curl -L https://get.rvm.io | bash -s stable --ruby
       source ~/.bashrc
       rvm install 1.9.3

4) Get the gems for cucumber

       gem install gherkin cucumber
       gem install rspec

5) Download and compile Cucumber-CPP
    
    # Download from git
        git clone https://github.com/cucumber/cucumber-cpp.git

    # Change current directory
        cd cucumber-cpp.git

    # Enable examples in the cucumber build
        export CUKE_ENABLE_EXAMPLES=true

    # Build cucumber with the following commands
        cmake -E make_directory build
        cmake -E chdir build cmake ..
        cmake --build build
        cmake --build build --target test

    # Then test the cucumber build by attempting to run an example
        build/examples/Calc/CppSpecCalculatorSteps >/dev/null &
        cucumber examples/Calc/CalcFeatures

4) Create your project

    # create a project folder (MyProject)

        mkdir MyProject

    # create a CMakeList.txt file

        echo "cmake_minimum_required(VERSION 2.8)" >> MyProject/CMakeLists.txt

    # add enough code to the cmake file to build your test code

        project(StringReverser)

        #create a library from our code
        add_library(StringReverser src/StringReverser.cpp)

        #setup testing environment
        enable_testing()
        set(GTEST_ROOT ${CMAKE_SOURCE_DIR}/../gtest-1.6.0)
        link_directories(${GTEST_ROOT})
        find_package(GTest REQUIRED)

        #create a test executable linked to our code
        include_directories(${GTEST_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src)
        add_executable(TestStringReverser test/TestStringReverser.cpp)
        target_link_libraries(TestStringReverser StringReverser ${GTEST_MAIN_LIBRARY} ${GTEST_LIBRARIES} pthread)

    # Test Drive a StringReverser, put the source code in the src folder and the test code in the test folder

    # create a test code folder

        mkdir MyProject/test

    # create a the tests

        touch MyProject/test/TestStringReverser.cpp

        # Put the following code in the file

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
            
    # create a source code folder

        mkdir MyProject/src

    # create code to pass the tests

        touch MyProject/src/StringReverser.h

        # put the following code in the file

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

        touch MyProject/src/StringReverser.cpp

        # put the following code in the file

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

    # run cmake

        cd MyProject

        rm -Rf build

        cmake -E make_directory build

        cmake -E chdir build cmake ..

    # run make to compile and link your code

        cd build

        make

    # run the test suite

        ./TestStringReverser

        # Your output should look like this

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
            
    # Setting up Cucumber for Testing

    # create a feature sub-folder (features)

        mkdir MyProject/features

    # create a 'feature' file for the cucumer scenario(s)

        touch MyProject/features/reverser.feature

        # add the following gherkin to the feature file

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
            
    # create a 'wire' file for execution

        echo -e "host: localhost\nport: 55555" >> MyProject/features/myfeatures.wire

    # edit the CMakeLists.txt file and add the following

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

    # create a steps file for the cumber wire server

        touch MyProject/test/StringReverserSteps.cpp

        # put the following code in the file

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

    # run cmake

        cd MyProject

        rm -Rf build

        cmake -E make_directory build

        cmake -E chdir build cmake ..

    # run make to compile and link your code

        cd build

        make

    # run the cucumber wire server 

        ./MyProject/build/StringReverserSteps &

    # run the features file through cucumber

        cucumber -s features

        # You output should be 

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
