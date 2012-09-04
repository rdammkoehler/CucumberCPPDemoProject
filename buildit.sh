rm -f *.o TestStringReverser
g++ $(gtest-config --cppflags --cxxflags) -o TestStringReverser.o -c TestStringReverser.cpp \
&& g++ $(gtest-config --ldflags --libs) -o TestStringReverser TestStringReverser.o /usr/lib/libgtest_main.a \
&& ./TestStringReverser