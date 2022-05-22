#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>

#define LOX printf("%d\n", __LINE__);

namespace iLab
{
	class data_t;
	class DifferTree;
	class node_t;
	union value_t;

	enum type_t
	{
		TYPE_int_constant = 1,
		TYPE_double_constant,
		TYPE_variable,
		TYPE_sin,
		TYPE_cos,
		TYPE_tan,
		TYPE_cot,
		TYPE_ln,
		TYPE_lg,
		TYPE_sinh,
		TYPE_cosh,
		TYPE_tanh,
		TYPE_coth,
		TYPE_add = '+',
		TYPE_sub = '-',
		TYPE_mul = '*',
		TYPE_div = '/',
		TYPE_deg = '^',
		TYPE_unknown,
	};

	union value_t
	{
		double double_value;
		int int_value;
		char char_value;
	};

	class data_t
	{
		friend DifferTree;
		friend node_t;

		friend std::istream& operator>> (std::istream& stream, data_t& data);
		friend std::ostream& operator<< (std::ostream& stream, const data_t& data);
		friend node_t& DifferentiateNode(node_t& node);
		friend node_t& DifferentiateNode(node_t& node, std::ofstream& dumpfile, std::ifstream& cringe);
		friend void TexDumpTree(std::ofstream& dumpfile, const node_t* node);


	public:
		data_t();
		~data_t();
		data_t(data_t& data);
		data_t(type_t _type, int _value);
		data_t(type_t _type, double _value);
		data_t(type_t _type, char _value);
		data_t(type_t _type);

		data_t& operator=(const data_t& data);
		bool operator==(int num)
		{
			if (num != 0)
				return value.int_value == num;
			else return value.int_value == 0 || value.double_value == 0.0;
		}

	private:
		type_t type;
		value_t value;
	};

	class node_t
	{
		friend DifferTree;
		friend node_t& DifferentiateNode(node_t& node);
		friend node_t& DifferentiateNode(node_t& node, std::ofstream& dumpfile, std::ifstream& cringe);
		friend inline void TexDumpDiffNode(std::ofstream& dumpfile, const node_t* node);
		friend void TexDumpNode(std::ofstream& dumpfile, const node_t* node);
		friend void TexDumpTree(std::ofstream& dumpfile, const node_t* node);
		friend inline void TextMul(std::ofstream& dumpfile, node_t& node);
		friend inline void TextDiv(std::ofstream& dumpfile, node_t& node);
		friend inline void TextSub(std::ofstream& dumpfile, node_t& node);
		friend inline void TextAdd(std::ofstream& dumpfile, node_t& node);
		friend inline void TextPowFunc(std::ofstream& dumpfile, node_t& node, int power);
		friend inline void TextPowFunc(std::ofstream& dumpfile, node_t& node, double power);
		friend inline void TextExpFunc(std::ofstream& dumpfile, node_t& node);
		friend inline void TextTowerFunc(std::ofstream& dumpfile, node_t& node);
		friend inline void TextSin(std::ofstream& dumpfile, node_t& node);
		friend inline void TextSinh(std::ofstream& dumpfile, node_t& node);
		friend inline void TextCos(std::ofstream& dumpfile, node_t& node);
		friend inline void TextCosh(std::ofstream& dumpfile, node_t& node);
		friend inline void TextTan(std::ofstream& dumpfile, node_t& node);
		friend inline void TextTanh(std::ofstream& dumpfile, node_t& node);
		friend inline void TextCot(std::ofstream& dumpfile, node_t& node);
		friend inline void TextCoth(std::ofstream& dumpfile, node_t& node);
		friend inline void TextLn(std::ofstream& dumpfile, node_t& node);
		friend inline void TextLg(std::ofstream& dumpfile, node_t& node);
		friend inline void TextConst(std::ofstream& dumpfile, node_t& node, int number);






		friend std::ostream& operator<<(std::ostream& stream, node_t const& node)
		{
			return stream << node.data;
		}
		friend node_t& operator+(node_t& node_left, node_t& node_right);
		friend node_t& operator-(node_t& node_left, node_t& node_right);
		friend node_t& operator*(node_t& node_left, node_t& node_right);
		friend node_t& operator/(node_t& node_left, node_t& node_right);
		friend node_t& operator^(node_t& node_left, int deg);
		friend node_t& operator^(node_t& node_left, double deg);
		friend node_t& operator^(node_t& node_left, node_t& node_right);



	public:
		node_t();
		node_t(const data_t& _data);
		node_t(node_t& node);
		node_t(node_t* node);
		node_t(const data_t& _data, node_t* _left, node_t* _right);
		~node_t();

		node_t& operator=(const node_t& node);
		node_t& operator-(int number);
		node_t& operator-();
		operator data_t()
		{
			return data;
		}

		value_t value()
		{
			return data.value;
		}

		type_t type()
		{
			return data.type;
		}

	protected:
		data_t data;
		node_t* left;
		node_t* right;
	};
}