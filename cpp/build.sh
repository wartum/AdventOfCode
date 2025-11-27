#!/bin/sh
parse_params() {
    [ "$#" -eq 0 ] && print_help && exit 0
    while (( "$#" )); do
        case "$1" in
            -h) HELP="true"; return ;;
            -p) shift; PRESET="$1"; shift ;;
            -c) shift; CLEAN="true" ;;
            -t) shift; TEST="true" ;;
        esac
    done
}

print_help() {
    echo "USAGE: ./build.sh [options]"
    echo ""
    echo "OPTIONS:"
    echo ""
    echo -e "-h\t\tPrints this message"
    echo -e "-p <value>\tChooses CMake preset: possible values: <Debug|Release>"
    echo -e "-c \t\tPerform clean build, aka remove existing build tree"
    echo -e "-t \t\tRun unit tests after compilation"
}

parse_params $@
[ "$HELP" == "true" ] && print_help && exit 0

PRESET="${PRESET:-Debug}"
BUILD_TREE=build

[ "$CLEAN" == "true" ] && rm -rf "$BUILD_TREE"
cmake --preset "$PRESET" || exit 1
cmake --build "$BUILD_TREE" || exit 1
[ "$TEST" == "true" ] && ctest --test-dir "$BUILD_TREE" --output-on-failure
