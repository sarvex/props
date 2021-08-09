/*
Copyright (c) 2019-2021 Péter Magyar

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

#ifndef PROP_CACHE_H
#define PROP_CACHE_H

#include "core/version.h"

#if VERSION_MAJOR > 3
#include "core/object/object.h"
#include "core/math/color.h"
#include "core/object/reference.h"
#include "core/templates/hash_map.h"
#include "core/templates/vector.h"
#else
#include "core/hash_map.h"
#include "core/color.h"
#include "core/object.h"
#include "core/reference.h"
#include "core/vector.h"
#endif

#include "scene/resources/material.h"

#include "core/os/mutex.h"

#include "../props/prop_data.h"

class PropMaterialCache;

class PropCache : public Object {
	GDCLASS(PropCache, Object);

public:
	static PropCache *get_singleton();

	StringName get_default_prop_material_cache_class();
	void set_default_prop_material_cache_class(const StringName &cls_name);

#ifdef TEXTURE_PACKER_PRESENT
	int get_texture_flags() const;
	void set_texture_flags(const int flags);

	int get_max_atlas_size() const;
	void set_max_atlas_size(const int size);

	bool get_keep_original_atlases() const;
	void set_keep_original_atlases(const bool value);

	Color get_background_color() const;
	void set_background_color(const Color &color);

	int get_margin() const;
	void set_margin(const int margin);
#endif

	PoolStringArray material_paths_get() const;
	void material_paths_set(const PoolStringArray &array);

	void material_add(const Ref<Material> &value);
	void material_set(const int index, const Ref<Material> &value);
	void material_remove(const int index);
	int material_get_num() const;
	void materials_clear();
	void materials_load();

	Vector<Variant> materials_get();
	void materials_set(const Vector<Variant> &materials);

	Ref<PropMaterialCache> material_cache_get(const Ref<PropData> &prop);
	void material_cache_unref(const Ref<PropData> &prop);

	Ref<PropMaterialCache> material_cache_custom_key_get(const uint64_t key);
	void material_cache_custom_key_unref(const uint64_t key);

private:
	static PropCache *_instance;

public:
	PropCache();
	~PropCache();

protected:
	static void _bind_methods();

	StringName _default_prop_material_cache_class;

	Map<uint64_t, Ref<PropMaterialCache>> _material_cache;
	Map<uint64_t, Ref<PropMaterialCache>> _custom_keyed_material_cache;

	Mutex _material_cache_mutex;
	Mutex _custom_keyed_material_cache_mutex;

#ifdef TEXTURE_PACKER_PRESENT
	int _texture_flags;
	int _max_atlas_size;
	bool _keep_original_atlases;
	Color _background_color;
	int _margin;
#endif

	PoolStringArray _material_paths;
	Vector<Ref<Material>> _materials;
};

#endif