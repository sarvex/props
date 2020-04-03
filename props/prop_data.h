/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef PROP_DATA_H
#define PROP_DATA_H

#include "core/math/rect2.h"
#include "core/math/transform.h"
#include "core/math/vector2.h"
#include "core/math/vector3.h"
#include "core/reference.h"
#include "core/vector.h"

#include "servers/physics_server.h"

#include "prop_data_entry.h"
#include "prop_data_mesh.h"

#include "../../voxelman/meshers/voxel_mesher.h"

#include "../../texture_packer/texture_packer.h"

class Spatial;
class VoxelChunk;

class PropData : public Resource {
	GDCLASS(PropData, Resource);

public:
	int get_id() const;
	void set_id(const int value);

	bool get_snap_to_mesh() const;
	void set_snap_to_mesh(const bool value);

	Vector3 get_snap_axis() const;
	void set_snap_axis(const Vector3 &value);

	Ref<PropDataEntry> get_prop(const int index) const;
	void set_prop(const int index, const Ref<PropDataEntry> prop);
	void add_prop(const Ref<PropDataEntry> prop);
	void remove_prop(const int index);

	int get_prop_count() const;

	Vector<Variant> get_props();
	void set_props(const Vector<Variant> &props);

	void add_textures_into(Ref<TexturePacker> texture_packer);
	void add_prop_lights_into(Ref<VoxelChunk> chunk, Transform parent_transform, bool allow_snap);
	void add_meshes_into(Ref<VoxelMesher> mesher, Ref<TexturePacker> texture_packer, Transform parent_transform, Spatial *snap_spatial = NULL);
	void add_meshes_into_bind(Ref<VoxelMesher> mesher, Ref<TexturePacker> texture_packer, Transform parent_transform, Node *snap_spatial = NULL);

	Transform get_next_snapped_prop_transform(Spatial *s, Transform parent_transform, bool snap_to_mesh, Vector3 snap_axis);
	Transform get_next_snapped_prop_transform_bind(Node *spatial, Transform parent_transform, bool snap_to_mesh, Vector3 snap_axis);

	PropData();
	~PropData();

protected:
	static void _bind_methods();

private:
	int _id;
	bool _snap_to_mesh;
	Vector3 _snap_axis;

	Vector<Ref<PropDataEntry> > _props;
};

#endif
