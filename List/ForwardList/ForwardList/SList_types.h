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
}
