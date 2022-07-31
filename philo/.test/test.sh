#!/bin/bash

RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function CHECK() {
  testcase="$1"
  ../philo $2 $3 $4 $5 $6 > "log/${testcase}.txt"
  python3 test.py "log/${testcase}.txt" "$2" "$3" "$4" "$5" "$6"

  result=$?
  if [ "$result" = "0" ]; then
    echo -e "${GREEN}OK:${NC} ${testcase}"
  else
    echo -e "${RED}KO:${NC} ${testcase}"
  fi

}

rm -rf log
mkdir log

CHECK normal 2 510 200 200 10
