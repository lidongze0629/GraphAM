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
    exit
}

SYSTEM=`uname -o`

get-graph-data(){
  if [[ -z "$GRAPH_DATA" ]]
  then
    GRAPH_DATA=./graph-data
  fi

  # download the correct results
  if [[ -d ${GRAPH_DATA} ]]
  then
    cd ${GRAPH_DATA}
    git pull
    cd -
  else
    git clone --depth=1 https://github.com/lidongze0629/graph-data.git ${GRAPH_DATA}
  fi

  export LC_ALL=C
  export GRAPH_DATA
  export GRAPH_LIB=.
}

run-test(){
    cmd=""
    if [ "$SYSTEM" = "Darwin" ]; then
        cmd="./graph-engine --command_file ../misc/batch_file.mac --serialize=false --deserialize=false"
    else
        cmd="./graph-engine --command_file ../misc/batch_file --serialize=false --deserialize=false"
    fi
    echo $cmd
    eval $cmd
}

Verify(){
  cat ./${1}* | sort -k1n > tmp.res
  if ! cmp tmp.res ${2} >/dev/null 2>&1
  then
    echo "[GRAPH_TEST] failed to pass ${3} check."
    # rm tmp.res
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
Verify mst $GRAPH_DATA/test-mst.dat prim_mst
Verify wcc $GRAPH_DATA/p2p-31-wcc.dat wcc
Verify pagerank $GRAPH_DATA/twitter-pagerank.dat pagerank

