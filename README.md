** WARNING **
These instructions are still being tested and may contain errors or other issues.

0) Assuming you have cmake, make, g++, and git

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

    1) create a project folder (MyProject)

    2) create a feature sub-folder (features)