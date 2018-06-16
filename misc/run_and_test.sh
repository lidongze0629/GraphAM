#!/bin/bash -e

# example ${0} -a libapp_sssp.so -v ./graph_test/twitter.v -e ./graph_test/twitter.e -o ./sssp_ -q '(4 63)'
# example ${0} -a libapp_pagerank.so -v ./graph_test/twitter.v -e ./graph_test/twitter.e -o ./pagerank_ -q '(0.85 0.01 100 100000)'
# example ${0} -a libapp_bfs.so -v ./graph_test/twitter.v -e ./graph_test/twitter.e -o ./bfs_ -q '(1 4)'
# example ${0} for mst

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
    exit
}

get-graph-data(){
  if [[ -z "$GRAPH_DATA" ]]
  then
    GRAPH_DATA=./graph-data
  fi

  # download the correct results
  if [[ -d ${GRAPH_DATA} ]]
  then
    cd ${GRAPH_DATA}
    #git pull
    cd -
  else
    git clone --depth=1 https://github.com/lidongze0629/graph-data.git ${GRAPH_DATA}
  fi

  export LC_ALL=C
  export GRAPH_DATA
  export GRAPH_LIB=.
}


run-test(){

    # sssp
    cmd="./graph-engine --vfile ${GRAPH_DATA}/twitter.v --efile ${GRAPH_DATA}/twitter.e --query '(4)' --output ${GRAPH_LIB}/sssp_ --algo_dynamic_lib libapp_sssp.so"
    echo $cmd
    eval $cmd

    # wcc
    cmd="./graph-engine --vfile ${GRAPH_DATA}/p2p-31.v --efile ${GRAPH_DATA}/p2p-31.e --query '()' --output ${GRAPH_LIB}/wcc_ --algo_dynamic_lib libapp_wcc.so"
    echo $cmd
    eval $cmd

    # bfs
    cmd="./graph-engine --vfile ${GRAPH_DATA}/twitter.v --efile ${GRAPH_DATA}/twitter.e --query '(1 4)' --output ${GRAPH_LIB}/bfs_ --algo_dynamic_lib libapp_bfs.so"
    echo $cmd
    eval $cmd

    # prim's mst
    cmd="./graph-engine --vfile ${GRAPH_DATA}/test.v --efile ${GRAPH_DATA}/test.e --query '()' --output ${GRAPH_LIB}/mst_ --algo_dynamic_lib libapp_mst_prim.so"
    echo $cmd
    eval $cmd

    # pagerank
    cmd="./graph-engine --vfile ${GRAPH_DATA}/twitter.v --efile ${GRAPH_DATA}/twitter.e --query '(0.85 0.01 100 100000)' --output ${GRAPH_LIB}/pagerank_ --algo_dynamic_lib libapp_pagerank.so"
    echo $cmd
    eval $cmd
}

Verify(){
  cat ./${1}* | sort -k1n > tmp.res
  if ! cmp tmp.res ${2} >/dev/null 2>&1
  then
    echo "[GRAPH_TEST] failed to pass ${3} check."
    rm tmp.res
    exit 1
  else
    echo "passed ${3} test."
    rm ./${1}*
    rm tmp.res
  fi
}


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

get-graph-data

run-test

Verify sssp $GRAPH_DATA/twitter-sssp-4.dat sssp
Verify bfs $GRAPH_DATA/twitter-bfs.dat bfs
Verify pagerank $GRAPH_DATA/twitter-pagrank.dat pagerank
Verify mst $GRAPH_DATA/test-mst.dat prim_mst
Verify wcc $GRAPH_DATA/p2p-31-wcc.dat wcc

