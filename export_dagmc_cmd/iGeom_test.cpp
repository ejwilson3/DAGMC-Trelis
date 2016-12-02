#include "iGeom_test.hpp"
#include "iGeom_funcs.hpp"
#include <vector>
#include "CubitInterface.hpp"

// CGM includes
//#include "GeometryQueryTool.hpp"
#include "GeometryModifyTool.hpp"
/*
#include "GeometryModifyEngine.hpp"
#include "ModelQueryEngine.hpp"
#include "GMem.hpp"

#include "RefEntityName.hpp"

*/
#include "Body.hpp"
#include "RefEntity.hpp"
/*
#include "Surface.hpp"
#include "Curve.hpp"

#include "RefGroup.hpp"
#include "RefFace.hpp"
#include "RefEdge.hpp"
#include "RefVertex.hpp"

#include "SenseEntity.hpp"
*/

iGeom_test::iGeom_test()
{
  //default values
  radius = 2.0;
  radius2 = 1.0;
}

iGeom_test::~iGeom_test()
{}

std::vector<std::string> iGeom_test::get_syntax()
{
  // Define the syntax for the command. Note the syntax is a modified BNF
  // format. Full documentation on the command specification syntax can be
  // found in the documentation.
  std::string syntax =
      "iGeom_test"
      "[<value:label='radius',help='<radius>'> ]"
      "[<value:label='radius2',help='<radius2>'>]";
      /*
     "[faceting_tolerance <value:label='faceting_tolerance',help='<faceting tolerance>'>] "
      "[length_tolerance <value:label='length_tolerance',help='<length tolerance>'>] "
      "[normal_tolerance <value:label='normal_tolerance',help='<normal tolerance>'>] "
      "[verbose] [fatal_on_curves]";
      */

  std::vector<std::string> syntax_list;
  syntax_list.push_back(syntax);

  return syntax_list;
}

std::vector<std::string> iGeom_test::get_syntax_help()
{
  std::vector<std::string> help;
  return help;
}

std::vector<std::string> iGeom_test::get_help()
{
  std::vector<std::string> help;
  return help;
}

bool iGeom_test::execute(CubitCommandData &data)
{

  iBase_EntityHandle datum;
  iBase_EntityHandle move;
  data.get_value("radius",radius);
  data.get_value("radius2",radius2);
  iGeom_createSphere( radius, &datum );
  iGeom_createBrick( radius, radius + 1 , radius2, &move );
//  iGeom_createCylinder( 5, radius, radius2, &move );
//  iGeom_createCone( 5, radius, 0.0, radius2, &move );
//  iGeom_createTorus( radius, radius2, &move );
  iGeom_moveEnt( move, 1, 2, 4 );
  return true;
}


