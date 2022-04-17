#include "data_t.h"

#define function(f)				\
	if (strcmp(func, #f) == 0)	 \
		data.type = TYPE_##f;

#define case_func(f)		\
	case TYPE_##f:			 \
		stream << #f;		  \
		break;

namespace iLab
{
	//------------------------CLASS-data_t---------------------------------------	
	std::istream& operator>> (std::istream& stream, data_t& data)
	{
		char operand = 0;
		stream >> operand;

		switch (operand)
		{
		case TYPE_add: data.type = TYPE_add; break;
		case TYPE_sub: data.type = TYPE_sub; break;
		case TYPE_mul: data.type = TYPE_mul; break;
		case TYPE_div: data.type = TYPE_div; break;
		case TYPE_deg: data.type = TYPE_deg; break;
		default:
			if (isalpha(operand))
			{
				char func[5] = { 0 };
				func[0] = operand;
				operand = stream.get();
				for (int i = 1; isalpha(operand); i++, operand = stream.get())
					func[i] = operand;

				stream.putback(operand);

				function(sin)
				else function(cos)
				else function(ln)
				else function(lg)
				else function(tan)
				else function(cot)
				else function(sinh)
				else function(cosh)
				else function(coth)
				else function(tanh)

				if (func[1] == '\0')
				{
					data.type = TYPE_variable;
					data.value.char_value = func[0];
				}

			}
			else
			{
				stream.putback(operand);
				double num = 0;
				stream >> num;
				if (num - int(num) == 0)
				{
					data.type = TYPE_int_constant;
					data.value.int_value = int(num);
				}
				else
				{
					data.type = TYPE_double_constant;
					data.value.double_value = num;
				}
			}
			break;
		}
		return stream;
	}

	std::ostream& operator<< (std::ostream& stream, const data_t& data)
	{
		switch (data.type)
		{
		case TYPE_unknown:
			stream << "Unknown";
			break;
		case TYPE_double_constant:
			stream << data.value.double_value;
			break;
		case TYPE_int_constant:
			stream << data.value.int_value;
			break;
		case TYPE_variable:
			stream << data.value.char_value;
			break;
		case_func(sin)
		case_func(cos)
		case_func(ln)
		case_func(lg)
		case_func(tan)
		case_func(cot)
		case_func(sinh)
		case_func(cosh)
		case_func(tanh)
		case_func(coth)
		default:
			stream << char(data.type);
			break;
		}
		return stream;
	}

	data_t::data_t(data_t& data)
	{
		type = data.type;
		value = data.value;
	}

	data_t::data_t(type_t _type, int _value)
	{
		type = _type;
		value.int_value = _value;
	}

	data_t::data_t(type_t _type, double _value)
	{
		type = _type;
		value.double_value = _value;
	}

	data_t::data_t(type_t _type, char _value)
	{
		type = _type;
		value.char_value = _value;
	}

	data_t::data_t(type_t _type)
	{
		type = _type;
		value = { 0 };
	}

	data_t::data_t()
	{
		type = TYPE_unknown;
		value = { 0 };
	}

	data_t::~data_t()
	{
	}

	data_t& data_t::operator=(const data_t& data)
	{
		type = data.type;
		value = data.value;
		return *this;
	}
	//-------------------------------END-----------------------------------------
	// 
	// 
	//------------------------CLASS-node_t---------------------------------------
	node_t::node_t()
	{
		data = data_t();
		left = nullptr;
		right = nullptr;
	}

	node_t::node_t(const data_t& _data)
	{
		data = _data;
		left = nullptr;
		right = nullptr;
	}

	node_t::node_t(const data_t& _data, node_t* _left, node_t* _right)
	{
		data = _data;
		left = _left;
		right = _right;
	}

	node_t::node_t(node_t& node)
	{
		data = node.data;
		if (left != nullptr and node.left != nullptr)
		{
			*left = *node.left;
		}
		else if (left == nullptr and node.left != nullptr)
		{
			left = new node_t;
			*left = *node.left;
		}
		else if (left != nullptr and node.left == nullptr)
		{
			delete left;
			left = nullptr;
		}

		if (right != nullptr and node.right != nullptr)
		{
			*right = *node.right;
		}
		else if (right == nullptr and node.right != nullptr)
		{
			right = new node_t;
			*right = *node.right;
		}
		else if (right != nullptr and node.right == nullptr)
		{
			delete right;
			right = nullptr;
		}
	}

	node_t::node_t(node_t* node)
	{
		data = node->data;
		if (left != nullptr and node->left != nullptr)
		{
			*left = *(node->left);
		}
		else if (left == nullptr and node->left != nullptr)
		{
			left = new node_t;
			*left = *(node->left);
		}
		else if (left != nullptr and node->left == nullptr)
		{
			delete left;
			left = nullptr;
		}

		if (right != nullptr and node->right != nullptr)
		{
			*right = *(node->right);
		}
		else if (right == nullptr and node->right != nullptr)
		{
			right = new node_t;
			*right = *(node->right);
		}
		else if (right != nullptr and node->right == nullptr)
		{
			delete right;
			right = nullptr;
		}
	}

	node_t::~node_t()
	{
	}

	node_t& node_t::operator=(const node_t& node)
	{
		data = node.data;
		if (left != nullptr and node.left != nullptr)
		{
			*left = *node.left;
		}
		else if (left == nullptr and node.left != nullptr)
		{
			left = new node_t;
			*left = *node.left;
		}
		else if (left != nullptr and node.left == nullptr)
		{
			delete left;
			left = nullptr;
		}
		if (right != nullptr and node.right != nullptr)
		{
			*right = *node.right;
		}
		else if (right == nullptr and node.right != nullptr)
		{
			right = new node_t;
			*right = *node.right;
		}
		else if (right != nullptr and node.right == nullptr)
		{
			delete right;
			right = nullptr;
		}
		return *this;
	}

	node_t& operator+(node_t& node_left, node_t& node_right)
	{
		data_t new_data(TYPE_add);
		return *new node_t(new_data, &node_left, &node_right);
	}

	node_t& operator-(node_t& node_left, node_t& node_right)
	{
		data_t new_data(TYPE_sub);
		return *new node_t(new_data, &node_left, &node_right);
	}

	node_t& operator*(node_t& node_left, node_t& node_right)
	{
		data_t new_data(TYPE_mul);
		return *new node_t(new_data, &node_left, &node_right);
	}

	node_t& operator/(node_t& node_left, node_t& node_right)
	{
		data_t new_data(TYPE_div);
		return *new node_t(new_data, &node_left, &node_right);
	}

	node_t& operator^(node_t& node_left, int deg)
	{
		data_t new_data(TYPE_deg);
		data_t data_degree(TYPE_int_constant, deg);
		node_t* degree = new node_t(data_degree);
		return *new node_t(new_data, &node_left, degree);
	}	
	
	node_t& operator^(node_t& node_left, double deg)
	{
		data_t new_data(TYPE_deg);
		data_t data_degree(TYPE_double_constant, deg);
		node_t* degree = new node_t(data_degree);
		return *new node_t(new_data, &node_left, degree);
	}

	node_t& node_t::operator-()
	{
		data_t sub(TYPE_sub);
		node_t* right_node = new node_t(this);
		data = sub;
		left = nullptr;
		right = right_node;
		return *this;
	}


	//-------------------------------END-----------------------------------------
}

#undef function
#undef case_func

