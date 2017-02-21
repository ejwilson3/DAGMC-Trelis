/*!
 *  \file DagComp.hpp
 *  \brief
 *    Provides an example of creating a custom component.
 *  \author Michael Plooster
 *  \date 11 Feb 2014
 */

#ifndef DAGCOMP_HPP
#define DAGCOMP_HPP

#include "Component.hpp"

/*
class MenuManager;
class ToolbarManager;
class PanelManager;
class ExportManager;

class MyObserver;
*/
class DAGMCExportGUI;

class DagComp : public Component
{
public:
  DagComp();
  ~DagComp();

  // Methods inherited from Component
  void start_up(int withGUI);
  void clean_up();

private:
  //! Add export types to the file menu
  void add_exports();
  void cleanup_exports();

/*
  void setup_observers(int withGUI);
  void cleanup_observers();
  */

  DAGMCExportGUI* dagmcExport;

  //MyObserver* mListener;
};

#endif // DAGCOMP_HPP
