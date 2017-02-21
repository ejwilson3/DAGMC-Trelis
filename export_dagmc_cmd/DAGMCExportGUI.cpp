#include "CubitInterface.hpp"
#include "DAGMCExportGUI.hpp"
#include "DAGMCExportCommand.hpp"
#include "Claro.hpp"
#include "ClaroFileMenu.hpp"
#include "CommandWindow.hpp"

DAGMCExportGUI::DAGMCExportGUI(QObject *parent) :
  QObject(parent)
{}

DAGMCExportGUI::~DAGMCExportGUI()
{}

void DAGMCExportGUI::add_export_types()
{
  Claro *gui = Claro::instance();
  if(gui)
  {
    ClaroFileMenu *file_menu = gui->file_menu();
    QString filter_names = "DAGMC (*.h5m)";
    QObject *filter = file_menu->add_export(filter_names.toUtf8().data(), "DAGMC_export_plugin");

    //Connect the filter to the method that will handle the export
    connect(filter, SIGNAL(filterSelected(const QString&, const QString&)), this, SLOT(handle_export(const QString&, const QString&)));
  }
}

void DAGMCExportGUI::remove_export_types()
{
  Claro *gui = Claro::instance();
  if(gui)
  {
    ClaroFileMenu *file_menu = gui->file_menu();
    file_menu->remove_component_items("DAGMC_export_plugin");
  }
}

void DAGMCExportGUI::handle_export(const QString &filename, const QString &filter)
{
  CommandWindow* cw = Claro::instance()->command_line();
  QString message = "The \"" + filter + "\" filter was selected ";
  message += "with the filename \"" + filename + "\"\n";
  cw->print_data(message);

 testing();

  if(filter.contains("DAGMC"))
  {
    cw->print_data("actually not yet.\n");
  }
}
