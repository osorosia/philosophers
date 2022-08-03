#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function CHECK_DIED() {
  testcase="${1}_${2}_${3}_${4}_${5}"
  ../philo $1 $2 $3 $4 $5 > "log/${testcase}.txt"

  python3 test.py "log/${testcase}.txt" "$1" "$2" "$3" "$4" "$5"
  result=$?

  cat "log/${testcase}.txt" | grep died > /dev/null
  result=$?

  if [ "$result" = "0" ]; then
    echo -e "${GREEN}DIED:${NC} $1 $2 $3 $4 $5"
  else
    echo -e "${RED}DIED:${NC} $1 $2 $3 $4 $5"
  fi

}

function CHECK_LIVE() {
  testcase="${1}_${2}_${3}_${4}_${5}"
  ../philo $1 $2 $3 $4 $5 > "log/${testcase}.txt"
  
  python3 test.py "log/${testcase}.txt" "$1" "$2" "$3" "$4" "$5"
  result=$?

  cat "log/${testcase}.txt" | grep died > /dev/null
  result1=$?
  if [ "$result" = "0" ] && [ "$result1" = "0" ]; then
    result=1
  fi

  if [ "$result" = "0" ]; then
    echo -e "${GREEN}LIVE:${NC} $1 $2 $3 $4 $5"
  else
    echo -e "${RED}LIVE:${NC} $1 $2 $3 $4 $5"
  fi
}

rm -rf log
mkdir log

CHECK_LIVE 5 800 200 200 7
CHECK_LIVE 4 410 200 200 10

CHECK_DIED 1 800 200 200 1000
CHECK_DIED 4 310 200 100 1000
