#!/bin/bash
mkdir build
rm build/cli.zip
zip build/cli.zip src/* examples/*/* extras/*/*/*
