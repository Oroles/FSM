#!/bin/bash

# create libs for components
cd ../components
make libs

cp *.a ../tests
cp *.h ../tests/components

make clean
cd ../tests

# create libs for pugixml
cd ../pugixml
make libs

cp *.a ../tests
cp *.h ../tests/pugixml
cp *.hpp ../tests/pugixml

make clean
cd ../tests

# create libs for utils

cd ../utils
make libs

cp *.a ../tests
cp *.h ../tests/utils

make clean
cd ../tests