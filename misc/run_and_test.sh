#!/bin/bash -e

# example ${0} -a libapp_sssp.so -v ./graph_test/twitter.v -e ./graph_test/twitter.e -o ./sssp_ -q '(4 63)'
# example ${0} -a libapp_pagerank.so -v ./graph_test/twitter.v -e ./graph_test/twitter.e -o ./pagerank_ -q '(0.85 0.01 100 100000)'
# example ${0} -a libapp_bfs.so -v ./graph_test/twitter.v -e ./graph_test/twitter.e -o ./bfs_ -q '(1 4)'
# example ${0} for mst

SHELL_FOLDER=$(dirname $(readlink -f "$0"))

BASE_DIR=${SHELL_FOLDER%/*}

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

run-test(){
    export LC_ALL=C

    cmd="./graph-engine --vfile ${VFILE} --efile ${EFILE} --query ${QUERY} --output ${OUTPUT} --algo_dynamic_lib ${ALGO}"
    echo $cmd
    eval $cmd
}

VFILE="../misc/test-data/test.v"
EFILE="../misc/test-data/test.e"
QUERY="'()'"
ALGO="libapp_mst_prim.so"
OUTPUT="$BASE_DIR/build/default_output"

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
      QUERY="'${OPTARG}'"
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

run-test
