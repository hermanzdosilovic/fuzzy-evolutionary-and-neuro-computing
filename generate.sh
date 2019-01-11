#!/bin/bash
./build/Release/hw05gradient_descent 1 | tail -n 81 > gd1.txt
./build/Release/hw05gradient_descent 2 | tail -n 81 > gd2.txt
./build/Release/hw05gradient_descent 4 | tail -n 81 > gd4.txt
./build/Release/hw05online_gradient_descent 1 | tail -n 81 > ogd1.txt
./build/Release/hw05online_gradient_descent 2 | tail -n 81 > ogd2.txt
./build/Release/hw05online_gradient_descent 4 | tail -n 81 > ogd4.txt
gnuplot -p plot.sh
