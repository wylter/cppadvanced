#pragma once

namespace cppadvanced
{
	struct node_base
	{
		node_base* next;

		node_base()
			: next(nullptr)
		{
		}

		virtual ~node_base() 
		{}
	};

	template < typename T >
	struct SList_node : node_base
	{
		T value;

		virtual ~SList_node()
		{
		}
	};

	struct indexed_node_base
	{
		size_t next;

		indexed_node_base()
		{}

		indexed_node_base(size_t val) 
			: next(val)
		{}

		virtual ~indexed_node_base()
		{
		}
	};

	template < typename T >
	struct indexed_node : indexed_node_base
	{
		T value;

		virtual ~indexed_node()
		{
		}
	};
}
