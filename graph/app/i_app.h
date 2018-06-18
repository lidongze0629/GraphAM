#ifndef GRAPH_APP_I_APP_H_
#define GRAPH_APP_I_APP_H_

#include <memory>
#include <string>

#include "graph/app/i_app_helper.h"
#include "graph/fragment/i_fragment.h"
#include "graph/utils.h"

namespace graph {
/** App Interface.
 *
 * An abstraction of App. Containing the necessary operations during the running
 * of App.
 */
class IApp {
 public:
  /** Default constructor. */
  IApp() {}

  /** Default destructor. */
  virtual ~IApp() {}

  virtual void ExecAlgorithm(unique_ptr<IFragment> &fragment,
                             shared_ptr<IAppHelper> &app_helper_ptr,
                             const Vector<String> &query) = 0;

  virtual void WriteToFileResult(unique_ptr<IFragment> &fragment,
                                 shared_ptr<IAppHelper> &app_helper_ptr,
                                 const String prefix,
                                 const Vector<String> &query) = 0;
};

typedef IApp *create_t();
typedef void destroy_t(IApp *);

}  // namespace graph
#endif  // GRAPH_APP_I_APP_H_