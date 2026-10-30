# Resource samples

Shows how to use the resource module.

The resource service in Pony Engine is quite complex but simple to use.
Its complexity comes from its flexibility.
The resource serive is a hub, it doesn't know about resources by itself.
There are resource providers. They add resource collections to the resource service.
Those providers know how to provide resource raw bytes from their sources.
But they don't know how to interpret those bytes and make runtime resources out of them.
That's where the resource loaders come. They are added to the resource service as well.
And they know how to read those bytes and make runtime resources that a game can use.

Every runtime resource has its unique ID, resource type, data meta, load meta and actual data.
An ID must be unique among all the mounted collections. Two different collections may have resources with the same ID but they can't be mounted at the same time.
A resource type helps to find a correct loader.
A data meta tells a loader how interpret the data. It's a type dependent thing.
A load meta tells a loader how to load the data. It's a type dependent thing.

The resource service caches resources. When you request a resource load, it first checks if that resource was previously loaded and is still alive.
If yes, it returns it immediately. Then it checks if that resource is already under load. If yes, it returns a current load process made from another request.
And only if both those checks fail, the resource service creates a new load process.

The engine tools that are used during a build phase follow this logic.
First, a compiler makes a resource container out of an asset. Every resource container consists of a data file and optional load files.
A data file contains resource data and essential info about the resource (type and data meta). Load files contain load metas.
But this type is intermediate format, it's not used in the game builds at runtime.
Then other tools build final game resources out of them. The engine provides tools for building resource packs.
Resource packs are build out of resource lists. A resource list contains a list of tuples: a resource ID (unique inside one list), a path to a resource data and a path to a resource load. 
As output you'll have a resource pack data and resource packs manifests.
One manifest per resource list. At runtime you mount a pack. Every pack is a pair of resource pack data and a resource pack manifest.

Read the engine docs including the sections about engine formats for more info.

## Samples

| Sample           | Description                                                                        |
|:-----------------|:-----------------------------------------------------------------------------------|
| [Main](Main)     | Shows how to make a resource out of an asset at built time and load it at runtime. |
