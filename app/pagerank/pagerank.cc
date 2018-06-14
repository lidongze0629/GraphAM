#include "app/pagerank/pagerank.h"

#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <iostream>

#include "graph/utils.h"
#include "graph/fragment/immutable_edgecut_fragment.h"

namespace graph {

void PageRank::ExecAlgorithm(unique_ptr<IFragment> &fragment,
                             shared_ptr<IAppHelper> &app_helper_ptr,
                             const Vector<String> &query) {

  // (0.85 0.01 100 100000) means (alpha eps max_round result_limit)
  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());

  vid_t tvnum = frag->GetVerticesNum();

  std::vector<double> oedegrees(tvnum);
  std::vector<double> updates(tvnum, 0.0);

  double pr_init_value = 1.0 / tvnum;
  double pr_alpha = atof(query[0].c_str());
  double pr_accuracy = atof(query[1].c_str());
  unsigned pr_max_round = atoi(query[2].c_str());


  // set pagerank init value (1/N)
  auto vertices = frag->vertices();
  for (auto &v : vertices) {
    frag->SetPResult(v, pr_init_value);
  }

  for (unsigned i = 0; i < tvnum; i++) {
    auto es = frag->GetOutgoingEdges(i);
    unsigned OEdgesNum = 0;
    for (auto iter = es.begin(); iter != es.end(); iter++) {
      OEdgesNum++;
    }
    oedegrees[i] = OEdgesNum;
  }

  double total_updates = std::numeric_limits<double>::max();
  unsigned current_step = 0;

  while (total_updates >= pr_accuracy * tvnum && current_step < pr_max_round) {
    for (unsigned i = 0; i < tvnum; i++) {
      auto es = frag->GetOutgoingEdges(i);
      if (oedegrees[i] > 0) {
        double current_pr_value = frag->GetPResult(i);
        double compute_pr_value = current_pr_value / oedegrees[i];
        for (auto &oe : es) {
          vid_t dst = oe.dst();
          updates[dst] += compute_pr_value;
        }
      }
    }

    double temp_total_updates = 0;
    for (unsigned i = 0; i < tvnum; i++) {
      temp_total_updates += updates[i];
      double new_pr_value = pr_alpha * updates[i] + (1 - pr_alpha) / tvnum;
      frag->SetPResult(i, new_pr_value);
    }

    updates.clear();
    updates.resize(tvnum, 0.0);
    total_updates = temp_total_updates;
    current_step++;
  } // while

  LOG(INFO) << "Total Round: " << current_step;
}

void PageRank::WriteToFileResult(unique_ptr<IFragment> &fragment,
                                 shared_ptr<IAppHelper> &app_helper_ptr,
                                 const String prefix, const Vector<String> &query) {

  // todo no result limits, need sort first
  std::string path = GetResultFileName(prefix);
  std::ofstream fout;
  fout.setf(std::ios::fixed);
  fout.open(path.c_str());

  ImmutableEdgecutFragment *frag = dynamic_cast<ImmutableEdgecutFragment *>(fragment.get());
  vid_t tvnum = frag->GetVerticesNum();
  for (unsigned i = 0; i < tvnum; i++) {
    fout << i << "\t" << std::setprecision(12) << frag->GetPResult(i) << "\n";
  }
  fout.close();
  LOG(INFO) << "result output: " << path;
}

} // namespace graph
