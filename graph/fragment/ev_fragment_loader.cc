#include "graph/fragment/ev_fragment_loader.h"

#include <fstream>

#include "graph/fragment/fragment_factory.h"

namespace graph {

void EVFragmentLoader::LoadFragment(unique_ptr<IFragment> &fragment,
                                    const GraphSpec &graph_spec) {
  fragment.reset();

  if (FLAGS_deserialize) {
    fragment = FragmentFactory::CreateFragment(graph_spec);
    fragment->Deserialize(graph_spec.graph_name());
  } else {
    Vector<Edge> edges;
    Vector<Vertex> vertices;

    LoadVfile(vertices, graph_spec.vertex_file());
    LoadEfile(edges, graph_spec.edge_file());

    fragment = FragmentFactory::CreateFragment(graph_spec);
    fragment->Init(vertices, edges);
    if (FLAGS_serialize) {
      fragment->Serialize(graph_spec.graph_name());
    }
  }
}

void EVFragmentLoader::LoadVfile(Vector<Vertex> &vertices,
                                 const String &vfile) {
  LOG(INFO) << "Load vfile \"" << vfile << "\"";
  FILE *fin = fopen(vfile.c_str(), "r");
  if (!fin) {
    LOG(ERROR) << "File " << vfile << " Open Failed.";
  }

  vid_t vid;
  double data;
  while (fscanf(fin, "%u%lg", &vid, &data) != EOF) {
    vertices.emplace_back(vid, data);
  }
  fclose(fin);
}

void EVFragmentLoader::LoadEfile(Vector<Edge> &edges, const String &efile) {
  LOG(INFO) << "Load efile \"" << efile << "\"";
  FILE *fin = fopen(efile.c_str(), "r");
  if (!fin) {
    LOG(ERROR) << "File " << efile << " Open Failed.";
  }

  vid_t src, dst;
  double data;
  while (fscanf(fin, "%u%u%lg", &src, &dst, &data) != EOF) {
    edges.emplace_back(src, dst, data);
  }
  fclose(fin);
}

}  // namespace graph