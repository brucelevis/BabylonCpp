#include <babylon/samples/materialslibrary/_materials_library_samples_index.h>

#include <babylon/samples/materialslibrary/cell_material_scene.h>
#include <babylon/samples/materialslibrary/gradient_material_scene.h>
#include <babylon/samples/materialslibrary/gradient_material_sphere_scene.h>
#include <babylon/samples/materialslibrary/grid_material_scene.h>
#include <babylon/samples/materialslibrary/normal_material_scene.h>

namespace BABYLON {
namespace Samples {

_MaterialsLibrarySamplesIndex::_MaterialsLibrarySamplesIndex()
{
  // -- Materials Library examples --

  // Cell Material Scene
  _samples["CellMaterialScene"] = ::std::make_tuple(
    true,                                                    //
    [](ICanvas* iCanvas) {                                   //
      return ::std::make_unique<CellMaterialScene>(iCanvas); //
    });                                                      //
  // Gradient Material Scene
  _samples["GradientMaterialScene"] = ::std::make_tuple(
    true,                                                        //
    [](ICanvas* iCanvas) {                                       //
      return ::std::make_unique<GradientMaterialScene>(iCanvas); //
    });                                                          //
  // Gradient Material Sphere Scene
  _samples["GradientMaterialSphereScene"] = ::std::make_tuple(
    true,                                                              //
    [](ICanvas* iCanvas) {                                             //
      return ::std::make_unique<GradientMaterialSphereScene>(iCanvas); //
    });                                                                //
  // Grid Material Scene
  _samples["GridMaterialScene"] = ::std::make_tuple(
    true,                                                    //
    [](ICanvas* iCanvas) {                                   //
      return ::std::make_unique<GridMaterialScene>(iCanvas); //
    });                                                      //
  // Normal Material Scene
  _samples["NormalMaterialScene"] = ::std::make_tuple(
    true,                                                      //
    [](ICanvas* iCanvas) {                                     //
      return ::std::make_unique<NormalMaterialScene>(iCanvas); //
    });                                                        //
}

_MaterialsLibrarySamplesIndex::~_MaterialsLibrarySamplesIndex()
{
}

} // end of namespace Samples
} // end of namespace BABYLON