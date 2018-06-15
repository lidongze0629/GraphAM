#!/bin/bash -e

help(){
    echo "# ----------------------------------------"
    echo "#          run graph algo                 "
    echo "#     -v: the path for vertex file        "
    echo "#     -e: the path for edge file          "
    echo "#     -q: algorithm query                 "
    echo "#     -a: the path for algo dynamic lib   "
    echo "#     -o: the prefix of result            "
    echo "#     -h: help                            "
    echo "# ----------------------------------------"
}

SHELL_FOLDER=$(dirname $(readlink -f "$0"))

BASE_DIR=${SHELL_FOLDER%/*}

echo $BASE_DIR

VFILE=""
EFILE=""
QUERY=""
ALGO=""
OUTPUT=""

while getopts "v:e:q:a:o:h" opt; do
  case $opt in
    v)
      VFILE=$OPTARG
      echo "get vfile: $VFILE"
      ;;
    e)
      EFILE=$OPTARG
      echo "get efile: $EFILE"
      ;;
    q)
      QUERY=$OPTARG
      echo "get query: $QUERY"
      ;;
    a)
      ALGO=$OPTARG
      echo "get algorithm: $ALGO"
      ;;
    o)
      OUTPUT=$OPTARG
      echo "get output: $OUTPUT"
      ;;
    h)
      help
      ;;
    \?)
      echo "Invalid option: -$OPTARG"
      ;;
  esac
done