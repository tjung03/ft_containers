#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include "iterator.hpp"
# include "utils.hpp"

namespace	ft
{
	template	<
			typename Key,                                     // map::key_type
			typename T,                                       // map::mapped_type
			typename Compare = std::less<Key>,                     // map::key_compare
			typename Alloc = std::allocator< pair<const Key, T> >    // map::allocator_type
				>
	class	map
	{
	}; // class map template
} // namespace ft

#endif
