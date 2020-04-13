rm -rf logs
mkdir -p build
cd build
cmake ..
make -j8
chmod 777 simulation
cd ..

chmod 777 ./build/simulation
./build/simulation
# g++ -std=c++11 $(find . -name '*.cpp') -DELPP_DEFAULT_LOG_FILE='"./logs/default.log"'
