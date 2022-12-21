#!/usr/bin/env bash

set -o pipefail

function print_header() {
    echo -e "\n***** ${1} *****"
}

function check_log() {
    LOG=$( { ${1}; } 2>&1 )
    STATUS=$?
    echo "$LOG"
    if echo "$LOG" | grep -q -E "${2}"
    then
        exit 1
    fi

    if [ $STATUS -ne 0 ]
    then
        exit $STATUS
    fi
}

SRC=$(find ../common ../server ../client -name "*\.cpp")

print_header "RUN cpplint"
check_log "cpplint --extensions=cpp ${SRC}" "Can't open for reading"

print_header "RUN cppcheck"
check_log "cppcheck --enable=all --inconclusive --error-exitcode=1 --inline-suppr --suppressions-list=../cppcheck.cfg ${SRC}" "\(information\)"

print_header "RUN clang-tidy"
check_log "clang-tidy -p . ${SRC} -warnings-as-errors=*" "Error (?:reading|while processing)"

print_header "SUCCESS"
