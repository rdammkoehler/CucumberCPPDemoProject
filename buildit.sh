rm -Rf build && cmake -E make_directory build && cmake -E chdir build cmake .. && cd build && make && ./TestStringReverser && cd -
