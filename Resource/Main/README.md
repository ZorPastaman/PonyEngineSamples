# Resource main sample

Shows how to make a resource out of an asset at built time and load it at runtime.

In CMake scripts it creates a text resource out of a text asset, adds it to a pack, installs that pack.
Then in loads the text resource at runtime.

## Details

Resource building is in [CMakeLists](CMakeLists.txt).

First of all, you have to build resources. This process is dependent on a resource type and chosen compiler.
In this example, we build a text resource out of a text asset. The text compiler is called via `pony_compile_text()`.
It supports multi-resource load per asset. That's why before it we need to make a cmake variable that holds a list of loads: `pony_add_resource_load`.
Both data and load parameters are TOML files. Read the engine format docs for details.

Then you have to build resource packs. Add the resource to a list with `pony_add_resource()`.
Make a cmake variable that holds a list of pack manifests with `pony_add_pack_manifest()`.
And pack resources with `pony_pack_resources()`. The resource packer supports multi-manifests per pack.
Both data and manifest parameters are TOML files. Read the engien format docs for details.

Finally, add custom targets and install pack files.

You need to add `ADDITIONAL_DEPENDENCIES PonyEngineTools` to all the functions that interact with the engine tools.
It makes sure that they are built when those commands are called.

Resource loading is in [Game](Source/Game.cppm).

First, it mounts the pack via `PonyEngine::Resource::Pack::IPackService` by calling `MountPack()`.
Then, when it's finished, it requests a resource load via `PonyEngine::Resource::IResourceService` by calling `Load()`.
When it's finished, call `Resource()` on the load request.
