#ifndef RB_NODE_HPP
# define RB_NODE_HPP

# define RED 1
# define BLACK 0

namespace	ft
{
	template <typename T>
	struct rb_node
	{
		typedef	T	value_type;

		bool		_color;	// RED: true(1), BLACK: false(0)
		value_type	_value;

		rb_node		*_parent;
		rb_node		*_left;
		rb_node		*_right;

		rb_node(const bool color = RED, const value_type &val = value_type(), \
				rb_node *parent = NULL, rb_node *left = NULL, rb_node *right = NULL)
			: _color(color), _value(val), _parent(parent), _left(left), _right(right)
		{ }
	};

}

#endif
