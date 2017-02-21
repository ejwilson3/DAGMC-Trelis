#ifndef DAGMCEXPORTGUI_HPP
#define DAGMCEXPORTGUI_HPP

#include <QObject>

class DAGMCExportGUI : public QObject
{
  Q_OBJECT

public:
  DAGMCExportGUI(QObject* parent = 0);
  ~DAGMCExportGUI();

  void add_export_types();
  void remove_export_types();

public slots:
  void handle_export(const QString& filename, const QString& filter);
};

#endif // DAGMCEXPORTGUI_HPP
