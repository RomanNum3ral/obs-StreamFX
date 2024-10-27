// AUTOGENERATED COPYRIGHT HEADER START
// Copyright (C) 2017-2023 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
// Copyright (C) 2022 lainon <GermanAizek@yandex.ru>
// AUTOGENERATED COPYRIGHT HEADER END

#pragma once
#include "common.hpp"
#include "gs-limits.hpp"
#include "gs-vertex.hpp"

#include "warning-disable.hpp"
#include <chrono>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include "warning-enable.hpp"

namespace streamfx::obs::gs {
	class vertexbuffer {
		uint32_t _capacity;
		uint32_t _size;
		uint8_t  _layers;

		// libOBS Data
		std::shared_ptr<gs_vertbuffer_t>  _buffer;
		std::shared_ptr<gs_vb_data>       _data;
		std::shared_ptr<gs_tvertarray>    _uv_layers;

		// Our Data
		std::shared_ptr<vec3>      _positions;
		std::shared_ptr<vec3>      _normals;
		std::shared_ptr<vec3>      _tangents;
		std::shared_ptr<uint32_t>  _colors;
		std::shared_ptr<vec4>     _uvs[MAXIMUM_UVW_LAYERS];

		// OBS compatability
		gs_vb_data* _obs_data;

		void initialize(uint32_t capacity, uint8_t layers);
		void finalize();

		public:
		virtual ~vertexbuffer();

		/*!
		* \brief Create a Vertex Buffer with the default number of Vertices.
		*/
		vertexbuffer() : vertexbuffer(MAXIMUM_VERTICES, MAXIMUM_UVW_LAYERS) {}

		/*!
		* \brief Create a Vertex Buffer with a specific number of Vertices.
		*
		* \param vertices Number of vertices to store.
		*/
		vertexbuffer(uint32_t vertices) : vertexbuffer(vertices, MAXIMUM_UVW_LAYERS) {}

		/*!
		* \brief Create a Vertex Buffer with a specific number of Vertices and uv layers.
		*
		* \param vertices Number of vertices to store.
		* \param layers Number of uv layers to store.
		*/
		vertexbuffer(uint32_t vertices, uint8_t layers);

		/*!
		* \brief Create a copy of a Vertex Buffer
		* Full Description below
		*
		* \param other The Vertex Buffer to copy
		*/
		vertexbuffer(gs_vertbuffer_t* other);

		// Copy Constructor & Assignments

		/*!
		* \brief Copy Constructor
		* 
		*
		* \param other 
		*/
		vertexbuffer(vertexbuffer const& other);

		/*!
		* \brief Copy Assignment
		* Unsafe operation and as such marked as deleted.
		*
		* \param other
		*/
		void operator=(vertexbuffer const& other);

		// Move Constructor & Assignments

		/*!
		* \brief Move Constructor
		*
		*
		* \param other
		*/
		vertexbuffer(vertexbuffer const&& other) noexcept;

		/*!
		* \brief Move Assignment
		*
		*
		* \param other
		*/
		void operator=(vertexbuffer const&& other) noexcept;

		void resize(uint32_t new_size);

		uint32_t size();

		uint32_t capacity();

		bool empty();

		const streamfx::obs::gs::vertex at(uint32_t idx);

		const streamfx::obs::gs::vertex operator[](uint32_t const pos);

		void set_uv_layers(uint8_t layers);

		uint8_t get_uv_layers();

		/*!
		* \brief Directly access the positions buffer
		* Returns the internal memory that is assigned to hold all vertex positions.
		*
		* \return A <vec3*> that points at the first vertex's position.
		*/
		vec3* get_positions();

		/*!
		* \brief Directly access the normals buffer
		* Returns the internal memory that is assigned to hold all vertex normals.
		*
		* \return A <vec3*> that points at the first vertex's normal.
		*/
		vec3* get_normals();

		/*!
		* \brief Directly access the tangents buffer
		* Returns the internal memory that is assigned to hold all vertex tangents.
		*
		* \return A <vec3*> that points at the first vertex's tangent.
		*/
		vec3* get_tangents();

		/*!
		* \brief Directly access the colors buffer
		* Returns the internal memory that is assigned to hold all vertex colors.
		*
		* \return A <uint32_t*> that points at the first vertex's color.
		*/
		uint32_t* get_colors();

		/*!
		* \brief Directly access the uv buffer
		* Returns the internal memory that is assigned to hold all vertex uvs.
		*
		* \return A <vec4*> that points at the first vertex's uv.
		*/
		vec4* get_uv_layer(uint8_t idx);

		gs_vertbuffer_t* update();

		gs_vertbuffer_t* update(bool refreshGPU);

		public:
		class pool {
			typedef streamfx::obs::gs::vertexbuffer                                    _underlying;
			typedef std::shared_ptr<_underlying>                                        _tracked;
			typedef std::pair<uint32_t, uint8_t>                                        _key;
			typedef std::pair<_tracked, std::chrono::high_resolution_clock::time_point> _value;

			std::map<_key, std::list<_value>> _pool;
			std::mutex                        _lock;

			private:
			pool();

			void release(_underlying* value);

			public:
			~pool();

			_tracked acquire(uint32_t capacity = MAXIMUM_VERTICES, uint8_t layers = MAXIMUM_UVW_LAYERS);

			void cleanup();

			public:
			static std::shared_ptr<streamfx::obs::gs::vertexbuffer::pool> instance();
		};
	};
} // namespace streamfx::obs::gs
