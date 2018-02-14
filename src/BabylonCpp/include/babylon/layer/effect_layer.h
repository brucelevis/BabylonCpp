#ifndef BABYLON_LAYER_EFFECT_LAYER_H
#define BABYLON_LAYER_EFFECT_LAYER_H

#include <babylon/babylon_global.h>
#include <babylon/layer/ieffect_layer_options.h>
#include <babylon/math/color4.h>
#include <babylon/math/size.h>
#include <babylon/tools/observable.h>

namespace BABYLON {

struct EmissiveTextureAndColor {
  BaseTexture* texture = nullptr;
  Color4 color;
}; // end of struct EmissiveTextureAndColor

/**
 * @brief The effect layer Helps adding post process effect blended with the
 * main pass.
 *
 * This can be for instance use to generate glow or higlight effects on the
 * scene.
 *
 * The effect layer class can not be used directly and is intented to inherited
 * from to be customized per effects.
 */
class BABYLON_SHARED_EXPORT EffectLayer {

public:
  void addToScene(unique_ptr_t<EffectLayer>&& newEffectLayer);
  virtual ~EffectLayer();

  /**
   * @brief Gets the camera attached to the layer.
   */
  Camera* camera() const;

  /**
   * @brief Get the effect name of the layer.
   * @return The effect name
   */
  virtual string_t getEffectName() const = 0;

  /**
   * @brief Checks for the readiness of the element composing the layer.
   * @param subMesh the mesh to check for
   * @param useInstances specify wether or not to use instances to render the
   * mesh
   * @return true if ready otherwise, false
   */
  virtual bool isReady(SubMesh* subMesh, bool useInstances) = 0;

  /**
   * @brief Returns wether or nood the layer needs stencil enabled during the
   * mesh rendering.
   * @returns true if the effect requires stencil during the main canvas render
   * pass.
   */
  virtual bool needStencil() const = 0;

  /**
   * @brief Free any resources and references associated to a mesh.
   * Internal use
   * @param mesh The mesh to free.
   */
  virtual void _disposeMesh(Mesh* mesh) = 0;

  /**
   * @brief Renders the glowing part of the scene by blending the blurred
   * glowing meshes on top of the rendered scene.
   */
  void render();

  /**
   * @brief Determine if a given mesh will be used in the current effect.
   * @param mesh mesh to test
   * @returns true if the mesh will be used
   */
  virtual bool hasMesh(AbstractMesh* mesh) const;

  /**
   * @brief Returns true if the layer contains information to display, otherwise
   * false.
   * @returns true if the glow layer should be rendered
   */
  virtual bool shouldRender() const;

  /**
   * @brief Rebuild the required buffers.
   * Internal use only.
   */
  void _rebuild();

  /**
   * @brief Dispose the highlight layer and free resources.
   */
  void dispose();

protected:
  /**
   * @brief Instantiates a new effect Layer and references it in the scene.
   * @param name The name of the layer
   * @param scene The scene to use the layer in
   */
  EffectLayer(const string_t& name, Scene* scene);

  /**
   * @brief Create the merge effect. This is the shader use to blit the
   * information back to the main canvas at the end of the scene rendering.
   * @returns The effect containing the shader used to merge the effect on the
   * main canvas
   */
  virtual Effect* _createMergeEffect() = 0;

  /**
   * @brief Creates the render target textures and post processes used in the
   * effect layer.
   */
  virtual void _createTextureAndPostProcesses() = 0;

  /**
   * @brief Implementation specific of rendering the generating effect on the
   * main canvas.
   * @param effect The effect used to render through
   */
  virtual void _internalRender(Effect* effect) = 0;

  /**
   * @brief Sets the required values for both the emissive texture and and the
   * main color.
   */
  virtual void _setEmissiveTextureAndColor(Mesh* mesh, SubMesh* subMesh,
                                           Material* material)
    = 0;

  /**
   * @brief Initializes the effect layer with the required options.
   * @param options Sets of none mandatory options to use with the layer (see
   * IEffectLayerOptions for more information)
   */
  void _init(const IEffectLayerOptions& options);

  /**
   * @brief Creates the main texture for the effect layer.
   */
  void _createMainTexture();

  /**
   * @brief Checks for the readiness of the element composing the layer.
   * @param subMesh the mesh to check for
   * @param useInstances specify wether or not to use instances to render the
   * mesh
   * @param emissiveTexture the associated emissive texture used to generate the
   * glow
   * @return true if ready otherwise, false
   */
  bool _isReady(SubMesh* subMesh, bool useInstances,
                BaseTexture* emissiveTexture);

  /**
   * @brief Returns true if the mesh should render, otherwise false.
   * @param mesh The mesh to render
   * @returns true if it should render otherwise false
   */
  virtual bool _shouldRenderMesh(Mesh* mesh) const;

  /**
   * @brief Returns true if the mesh should render, otherwise false.
   * @param mesh The mesh to render
   * @returns true if it should render otherwise false
   */
  virtual bool _shouldRenderEmissiveTextureForMesh(Mesh* mesh) const;

  /**
   * @brief Renders the submesh passed in parameter to the generation map.
   */
  void _renderSubMesh(SubMesh* subMesh);

private:
  /**
   * @brief Generates the index buffer of the full screen quad blending to the
   * main canvas.
   */
  void _generateIndexBuffer();

  /**
   * @brief Generates the vertex buffer of the full screen quad blending to the
   * main canvas.
   */
  void _generateVertexBuffer();

  /**
   * @brief Sets the main texture desired size which is the closest power of two
   * of the engine canvas size.
   */
  void _setMainTextureSize();

  /**
   * @brief Dispose only the render target textures and post process.
   */
  void _disposeTextureAndPostProcesses();

public:
  /**
   * The Friendly of the effect in the scene
   */
  string_t name;

  /**
   * The clear color of the texture used to generate the glow map.
   */
  Color4 neutralColor;

  /**
   * Specifies wether the highlight layer is enabled or not.
   */
  bool isEnabled;

  /**
   * An event triggered when the effect layer has been disposed.
   */
  Observable<EffectLayer> onDisposeObservable;

  /**
   * An event triggered when the effect layer is about rendering the main
   * texture with the glowy parts.
   */
  Observable<EffectLayer> onBeforeRenderMainTextureObservable;

  /**
   * An event triggered when the generated texture is being merged in the scene.
   */
  Observable<EffectLayer> onBeforeComposeObservable;

  /**
   * An event triggered when the generated texture has been merged in the scene.
   */
  Observable<EffectLayer> onAfterComposeObservable;

  /**
   * An event triggered when the efffect layer changes its size.
   */
  Observable<EffectLayer> onSizeChangedObservable;

protected:
  Scene* _scene;
  Engine* _engine;
  int _maxSize;
  ISize _mainTextureDesiredSize;
  unique_ptr_t<RenderTargetTexture> _mainTexture;
  bool _shouldRender;
  vector_t<PostProcess*> _postProcesses;
  vector_t<BaseTexture*> _textures;
  EmissiveTextureAndColor _emissiveTextureAndColor;

private:
  unordered_map_t<string_t, unique_ptr_t<VertexBuffer>> _vertexBuffers;
  unique_ptr_t<GL::IGLBuffer> _indexBuffer;
  string_t _cachedDefines;
  Effect* _effectLayerMapGenerationEffect;
  IEffectLayerOptions _effectLayerOptions;
  Effect* _mergeEffect;

}; // end of struct EffectLayer

} // end of namespace BABYLON

#endif // end of BABYLON_LAYER_EFFECT_LAYER_H