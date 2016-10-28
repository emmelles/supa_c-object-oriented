#!/bin/bash

read filename

progname="${filename%.*}"

g++ -o $progname $filename

echo "Created executable C++ file ${progname}"
