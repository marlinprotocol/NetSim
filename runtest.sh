rm -rf logs
mkdir -p build
cd build
cmake ..
make -j8
chmod 777 test
cd ..

chmod 777 ./build/test
./build/test
# g++ -std=c++11 $(find . -name '*.cpp') -DELPP_DEFAULT_LOG_FILE='"./logs/default.log"'
