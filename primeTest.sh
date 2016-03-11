#!/bin/bash
#
#   Barbara Hazlett
#	hazlettb@onid.oregonstate.edu
#	CS311-400
#	Homework #6
#
rm primeTime.txt
(time ./primeMProc -c 1 -q -m 1000000) 2>> primeTime.txt
(time ./primeMProc -c 1 -q -m 2000000) 2>> primeTime.txt
(time ./primeMProc -c 1 -q -m 4000000) 2>> primeTime.txt
(time ./primeMProc -c 1 -q -m 8000000) 2>> primeTime.txt
(time ./primeMProc -c 1 -q -m 16000000) 2>> primeTime.txt
(time ./primeMProc -c 5 -q -m 1000000) 2>> primeTime.txt
(time ./primeMProc -c 5 -q -m 2000000) 2>> primeTime.txt
(time ./primeMProc -c 5 -q -m 4000000) 2>> primeTime.txt
(time ./primeMProc -c 5 -q -m 8000000) 2>> primeTime.txt
(time ./primeMProc -c 5 -q -m 16000000) 2>> primeTime.txt