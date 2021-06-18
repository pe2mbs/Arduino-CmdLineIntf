#!/bin/bash
mkdir build
rm build/cli.zip
zip build/cli.zip cli.hpp cli.cpp examples/*/* 
