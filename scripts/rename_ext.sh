#!/bin/bash

find ./src/ -type f -name "*.cpp" -exec bash -c 'mv "$0" "${0%.cpp}.cc"' {} \;
