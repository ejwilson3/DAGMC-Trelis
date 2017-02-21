/*!
 *  \file DagComp.cpp
 *  \brief
 *    Provides an example of creating a custom component.
 *  \author Michael Plooster
 *  \date 11 Feb 2014
 */

#include "DagComp.hpp"

#include "DAGMCExportGUI.hpp"
#include "Broker.hpp"
#include "ComponentInfo.hpp"
//#include "MyObserver.hpp"

// Default constructor. Remember to include the component name (should match
// the module name in dagcomp.i).
DagComp::DagComp() :
  Component("dagcomp"),
  dagmcExport(NULL)//,
//  mListener(NULL)
{}


DagComp::~DagComp()
{
  if(dagmcExport)
    delete dagmcExport;

/*
  if(mListener)
    delete mListener;
    */
}

void DagComp::start_up(int withGUI)
{ 
  if(withGUI)
  {
    add_exports();
  }

//  setup_observers(withGUI);
}

void DagComp::clean_up()
{
  cleanup_exports();
//  cleanup_observers();

  // Let the framework know you are done.
  clean_up_complete();
}

void DagComp::add_exports()
{
  if(!dagmcExport)
  {
    dagmcExport = new DAGMCExportGUI();
    dagmcExport->add_export_types();
  }
}

void DagComp::cleanup_exports()
{
  if(dagmcExport)
    dagmcExport->remove_export_types();
}

/*
void DagComp::setup_observers(int withGUI)
{
  if(!mLIstener)
  {
    mListener = new MyObserver();

    // Let Trelis know that this class will be observing events
    mListener->register_observer();
  }
}

void DagComp::cleanup_observers()
{
  if(mListener)
  {
    //If cubitcomp is still loded, we need to unregister the observer.
    ComponentInfo cubitcomp_info;
    Broker::instance()->get_component_info("cubitcomp", cubitcomp_info);
    if(cubitcomp_info.get_state() == "Loaded")
      mListener->unregister_observer();

    delete mListener;
    mListener = NULL;
  }
}
    */
