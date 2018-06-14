# GraphAM
GraphAM, a graph platform to provide c++ API to run graph algorithm.It incorporates various high level graph algorithms such as Single Source Shortest Path(SSSP) to deliver high performance experience.

# Prerequisite
These codes are implemented and tested with cmake>=2.8, boost, glog and gflags <br>
with ubuntu16.04, install glog and gflags is rather simple, just use `apt-get`
```
sudo apt-get update
sudo apt-get install -y libgoogle-glog-dev libgflags-dev libboost-all-dev
```

# compile and Install
```
git clone <this-repository>
cd GraphAM
mkdir build && cd build
cmake .. && make
```

# How to run
## Prepare DataSet
### vertex file format
```
# each vertex in one line
# with format: v_id, followd its value
0   10
1   73
2   23
3   8
4   98
```
### edge file format
```
# Undirected graph
# each edge in one line
# with format: src_id dst_id, followd its value
0   1   28
1   4   38
33  23  22
82  22  11
28  28  10
```
## Algorithm
#### [Single Source Shortest Path](https://en.wikipedia.org/wiki/Shortest_path_problem#Single-source_shortest_paths)
#### [PageRank](https://en.wikipedia.org/wiki/PageRank)
#### [Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search)
#### [Prim's Minimum Spanning Tree](https://en.wikipedia.org/wiki/Prim%27s_algorithm)

##  Run Command
```
./graph-engine --vfile <path-to-your-point-file> --efile <path-to-your-edge-file> --query <you-algorithm-query> --algo_dynamic_lib <the-dynamic-library-name-of-algorithm> --output <the-result-output-path>

- with sssp algorithm
./graph-engine --vfile ./graph_test/twitter.v --efile ./graph_test/twitter.e --query (4) --algo_dynamic_lib libapp_sssp.so --output ./
```

## 关于作者

```javascript
  var dzl = {
    name  : "王者荣耀",
    site : "http://pvp.qq.com"
  }
```
