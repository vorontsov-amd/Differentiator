#include "Differenciator.h"
#pragma warning(disable:4996)

using namespace std;

namespace iLab
{
	DifferTree::DifferTree()
	{
		root = nullptr;
	}

	DifferTree::DifferTree(DifferTree& tree)
	{
		root = new node_t(tree.root);
	}

	DifferTree::~DifferTree()
	{
		if (root) Free(root);
	}

	void DifferTree::Write(std::ofstream& file, node_t* node)
	{
		file << "(";
		if (node->left)  Write(file, node->left);
		file << node->data;
		if (node->right) Write(file, node->right);
		file << ")"; 
			
	}

	void DifferTree::Read(std::ifstream& file, node_t*& node, data_t& element)
	{
		char test = 0;
		file >> test;
		if (test == '(')
		{
			CreateNode(element, node);
			Read(file, node->left, element);
			file >> element;
			node->data = element;
			Read(file, node->right, element);
		}
		else
		{
			file.putback(test);
			return;
		}
		file >> test;
	}

	int DifferTree::Scan(const char* filename)
	{
		std::ifstream in;
		in.open(filename);
		data_t element;
		DifferTree::Read(in, root, element);
		in.close();

		return 0;
	}

	int DifferTree::Print()
	{
		std::ofstream out;
		out.open("DataBase.txt");
		Write(out, root);
		out.close();

		return 0;
	}

	void DifferTree::TexDump(const char* filename)
	{
		std::ofstream dumpfile;
		dumpfile.open(filename);
		dumpfile << "\\documentclass{article}\n\n";
		dumpfile << "\\usepackage[left=2cm,right=2cm,\
			top = 2cm, bottom = 2cm, bindingoffset = 0cm]{ geometry }";
		dumpfile << "\\begin{document}\n";
		dumpfile << "First document.This is a simple example, with no extra parameters or packages included.\n";
		dumpfile << "\\newline";
		dumpfile << "$\n";
		TexDumpTree(dumpfile, root);
		dumpfile << "\n$\n";

		dumpfile << "\\end{document}";

		dumpfile.close();
		system("pdflatex TexDump.tex");
	}

	void TexDumpTree(std::ofstream& dumpfile, const node_t* node)
	{
		dumpfile << " ";
		switch (node->data.type)
		{
		case TYPE_div:
			dumpfile << "\\frac{";
			if (node->left) TexDumpTree(dumpfile, node->left);
			dumpfile << "}{";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "}";
			break;
		case TYPE_sin:
			dumpfile << "\\sin \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_cos:
			dumpfile << "\\cos \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_tan:
			dumpfile << "\\tan \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_cot:
			dumpfile << "\\cot \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_sinh:
			dumpfile << "\\sinh \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_cosh:
			dumpfile << "\\cosh \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_tanh:
			dumpfile << "\\tanh \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_coth:
			dumpfile << "\\coth \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_ln:
			dumpfile << "\\ln \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_lg:
			dumpfile << "\\lg \\left(";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "\\right)";
			break;
		case TYPE_deg:
			if (node->left->data.type == TYPE_add or
				node->left->data.type == TYPE_sub or
				node->left->data.type == TYPE_mul or
				node->left->data.type == TYPE_div)
				dumpfile << "\\left(";
			if (node->left) TexDumpTree(dumpfile, node->left);
			if (node->left->data.type == TYPE_add or
				node->left->data.type == TYPE_sub or
				node->left->data.type == TYPE_mul or
				node->left->data.type == TYPE_div)
				dumpfile << "\\right)";
			dumpfile << char(node->data.type);
			dumpfile << "{";
			if (node->right)  TexDumpTree(dumpfile, node->right);
			dumpfile << "}";
			break;
		case TYPE_mul:
			if (node->left->data.type == TYPE_add or
				node->left->data.type == TYPE_sub or
				node->left->data.type == TYPE_div)
			{
				dumpfile << "\\left(";
				TexDumpTree(dumpfile, node->left);
				dumpfile << "\\right)";
			}
			else if ((node->left->data.type > TYPE_coth or node->left->data.type < TYPE_sin) and
				(node->right->data.type > TYPE_coth or node->right->data.type < TYPE_sin) and
				not (((node->left->data.type == TYPE_int_constant) or (node->left->data.type == TYPE_double_constant)) 
					and node->right->data.type == TYPE_variable)
				and not ((node->left->data.type == TYPE_int_constant or node->left->data.type == TYPE_double_constant) and node->right->data.type == TYPE_deg))
			{
				TexDumpTree(dumpfile, node->left);
				dumpfile << "\\cdot ";

			}
			else TexDumpTree(dumpfile, node->left);

			if (node->right->data.type == TYPE_add or
				node->right->data.type == TYPE_sub or
				node->right->data.type == TYPE_div)
			{
				dumpfile << "\\left(";
				if (node->left) TexDumpTree(dumpfile, node->right);
				dumpfile << "\\right)";
			}	
			else TexDumpTree(dumpfile, node->right);
			break;
		default:
			if (node->left) TexDumpTree(dumpfile, node->left);
			switch (node->data.type)
			{
			case TYPE_add:
			case TYPE_sub:
				dumpfile << char(node->data.type);
				break;
			case TYPE_double_constant:
				dumpfile << node->data.value.double_value;
				break;
			case TYPE_int_constant:
				dumpfile << node->data.value.int_value;
				break;
			case TYPE_variable:
				dumpfile << node->data.value.char_value;
				break;
			default:
				break;
			}
			if (node->right)  TexDumpTree(dumpfile, node->right);
			break;
		}
	}

	void DifferTree::GraphDump(const char* graphname)
	{
		size_t length = strlen(graphname) + 50;
		char* command = new char[length] {};
		strncpy(command, graphname, length);
		strncat(command, ".dot", length);

		std::ofstream dumpfile;
		dumpfile.open(command);

		dumpfile << "digraph " << graphname << "{\n";
		DumpNode(dumpfile, root);
		dumpfile << "}";

		dumpfile.close();

		strncpy(command, "iconv -f cp1251 -t utf-8 ", length);
		strncat(command, graphname, length);
		strncat(command, ".dot > ", length);
		strncat(command, graphname, length);
		strncat(command, "-utf8.dot", length);
		system(command);

		strncpy(command, "dot -Tpdf ", length);
		strncat(command, graphname, length);
		strncat(command, "-utf8.dot", length);
		strncat(command, " -o ", length);
		strncat(command, graphname, length);
		strncat(command, ".pdf", length);

		system(command);
		delete[] command;
	}

	void DifferTree::DumpNode(std::ofstream& dumpfile, const node_t* node)
	{
		dumpfile << "Node" << node << "[shape=\"record\", label=\"" << node->data << "\"];\n";

		if (node->left)
		{
			DumpNode(dumpfile, node->left);
			dumpfile << "Node" << node << "->" << "Node" << node->left << ";\n";
		}
		if (node->right)
		{
			DumpNode(dumpfile, node->right);
			dumpfile << "Node" << node << "->" << "Node" << node->right << ";\n";
		}
	}

	void DifferTree::Free(node_t* tree)
	{
		if (tree->left)  Free(tree->left);
		if (tree->right) Free(tree->right);
		if (tree)
		{
			delete tree;
			tree = nullptr;
		}
	}

	void DifferTree::CreateNode(const data_t& data, node_t*& node)
	{
		node_t* new_node = new node_t;
		new_node->data = data;
		node = new_node;
	}
	//---------------------------------------END-------------------------------------------------


	DifferTree& DifferentiateTree(DifferTree& old_tree, std::ofstream& dumpfile)
	{
		static DifferTree new_tree;
		std::ifstream cringe;
		cringe.open("cringe.txt");
		new_tree.root = &DifferentiateNode(*old_tree.root, dumpfile, cringe);
		return new_tree;
	}

#define dLeft (DifferentiateNode(*node.left, dumpfile, cringe))
#define dRight (DifferentiateNode(*node.right, dumpfile, cringe))
#define cLeft (CopyNode(*node.left))
#define cRight (CopyNode(*node.right))
#define cThis (CopyNode(node))

#define is_int_power_function node.right->data.type == TYPE_int_constant
#define is_double_power_function node.right->data.type == TYPE_double_constant
#define is_exponencial_function node.left->data.type == TYPE_int_constant or node.left->data.type == TYPE_double_constant

	node_t& DifferentiateNode(node_t& node, std::ofstream& dumpfile, std::ifstream& cringe)
	{
		dumpfile << " ";

		CringeStr(dumpfile, cringe);
		dumpfile << " ";


		switch (node.data.type)
		{
		case TYPE_double_constant:
		case TYPE_int_constant:
			TextConst(dumpfile, node, 0);
			return num(0);
			break;
		case TYPE_variable:
			TextConst(dumpfile, node, 1);
			return num(1);
			break;
		case TYPE_add:
			TextAdd(dumpfile, node);
			return dLeft + dRight;
			break;
		case TYPE_sub:
			if (node.left != nullptr)
			{
				TextSub(dumpfile, node);
				return dLeft - dRight;
			}
			else return -dRight;
			break;
		case TYPE_mul:
			TextMul(dumpfile, node);
			return dLeft * cRight + cLeft * dRight;
			break;
		case TYPE_div:
			TextDiv(dumpfile, node);
			return (dLeft * cRight - cLeft * dRight) / (cRight ^ 2);
			break;
		case TYPE_deg:
			if (is_int_power_function)
			{
				int power = node.right->data.value.int_value - 1;
				TextPowFunc(dumpfile, node, power);
				return cRight * (cLeft ^ power) * dLeft;
			}
			else if (is_double_power_function)
			{
				double power = node.right->data.value.double_value - 1;
				TextPowFunc(dumpfile, node, power);
				return cRight * (cLeft ^ power) * dLeft;
			}
			else if (is_exponencial_function)
			{
				TextExpFunc(dumpfile, node);
				return cThis * ln(cLeft);
			}
			else
			{
				TextTowerFunc(dumpfile, node);
				return cThis * (dRight * ln(cLeft) + (cRight / cLeft) * dLeft);
			}
			break;
		case TYPE_sinh:
			TextSinh(dumpfile, node);
			return cosh(cRight) * dRight;
			break;
		case TYPE_cosh:
			TextCosh(dumpfile, node);
			return sinh(cRight) * dRight;
			break;
		case TYPE_tanh:
			TextTanh(dumpfile, node);
			return dRight / (cosh(cRight) ^ 2);
			break;
		case TYPE_coth:
			TextCoth(dumpfile, node);
			return dRight / (sinh(cRight) ^ 2);
			break;
		case TYPE_sin:
			TextSin(dumpfile, node);
			return cos(cRight) * dRight;
			break;
		case TYPE_cos:
			TextCos(dumpfile, node);
			return -sin(cRight) * dRight;
			break;
		case TYPE_tan:
			TextTan(dumpfile, node);
			return dRight / (cos(cRight) ^ 2);
			break;
		case TYPE_cot:
			TextCoth(dumpfile, node);
			return -dRight / (sin(cRight) ^ 2);
			break;
		case TYPE_ln:
			TextLn(dumpfile, node);
			return dRight / cRight;
			break;
		case TYPE_lg:
			TextLg(dumpfile, node);
			return dRight / (cRight * ln(num(10)));
			break;
		}
	}

	inline void TexDumpDiffNode(std::ofstream& dumpfile, const node_t* node)
	{
		dumpfile << " \\left(";
		TexDumpTree(dumpfile, node);
		dumpfile << " \\right)'";
	}

	inline void TexDumpNode(std::ofstream& dumpfile, const node_t* node)
	{
		dumpfile << " \\left(";
		TexDumpTree(dumpfile, node);
		dumpfile << " \\right)";
	}

	inline void TextConst(std::ofstream& dumpfile, node_t& node, int number)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";
		dumpfile << number;
		dumpfile << "$$\n \\newline";
	}

	inline void TextMul(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpDiffNode(dumpfile, node.left);
		dumpfile << " \\cdot";
		TexDumpNode(dumpfile, node.right);
		dumpfile << " + ";
		TexDumpNode(dumpfile, node.left);
		dumpfile << " \\cdot";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextDiv(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << "\\frac{";
		TexDumpDiffNode(dumpfile, node.left);
		dumpfile << " \\cdot";
		TexDumpNode(dumpfile, node.right);
		dumpfile << " - ";
		TexDumpNode(dumpfile, node.left);
		dumpfile << " \\cdot";
		TexDumpDiffNode(dumpfile, node.right);
		dumpfile << "}{";
		TexDumpNode(dumpfile, node.right);
		dumpfile << "^2}";

		dumpfile << "$$\n \\newline";
	}

	inline void TextSub(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpDiffNode(dumpfile, node.left);
		dumpfile << " - ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextAdd(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpDiffNode(dumpfile, node.left);
		dumpfile << " + ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextPowFunc(std::ofstream& dumpfile, node_t& node, int power)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << power + 1;
		dumpfile << " \\cdot";
		TexDumpNode(dumpfile, node.left);
		dumpfile << " ^ " << power << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.left);

		dumpfile << "$$\n \\newline";
	}

	inline void TextPowFunc(std::ofstream& dumpfile, node_t& node, double power)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << power + 1;
		dumpfile << " \\cdot";
		TexDumpNode(dumpfile, node.left);
		dumpfile << " ^ " << power << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.left);

		dumpfile << "$$\n \\newline";
	}

	inline void TextExpFunc(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpNode(dumpfile, &node);
		dumpfile << " \\cdot";
		TexDumpTree(dumpfile, &ln(cLeft));
		dumpfile << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextTowerFunc(std::ofstream& dumpfile, node_t& node)

	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpTree(dumpfile, &node);
		dumpfile << " \\cdot";

		dumpfile << " \\left(";
		TexDumpDiffNode(dumpfile, node.right);
		dumpfile << " \\cdot ";
		TexDumpTree(dumpfile, &ln(cLeft));
		dumpfile << " + ";
		dumpfile << " \\frac{";
		TexDumpTree(dumpfile, node.right);
		dumpfile << "}{";
		TexDumpTree(dumpfile, node.left);
		dumpfile << "}";
		dumpfile << " \\cdot";
		TexDumpDiffNode(dumpfile, node.left);
		dumpfile << " \\right)";


		dumpfile << "$$\n \\newline";
	}

	inline void TextSin(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpTree(dumpfile, &cos(cRight));
		dumpfile << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextSinh(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpTree(dumpfile, &cosh(cRight));
		dumpfile << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextCos(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << "-";
		TexDumpTree(dumpfile, &sin(cRight));
		dumpfile << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextCosh(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		TexDumpTree(dumpfile, &sinh(cRight));
		dumpfile << " \\cdot ";
		TexDumpDiffNode(dumpfile, node.right);

		dumpfile << "$$\n \\newline";
	}

	inline void TextTan(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << " \\frac{";
		TexDumpDiffNode(dumpfile, &cRight);
		dumpfile << "}{";
		TexDumpTree(dumpfile, &(cos(cRight) ^ 2));
		dumpfile << "}";

		dumpfile << "$$\n \\newline";
	}

	inline void TextTanh(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << " \\frac{";
		TexDumpDiffNode(dumpfile, &cRight);
		dumpfile << "}{";
		TexDumpTree(dumpfile, &(cosh(cRight) ^ 2));
		dumpfile << "}";

		dumpfile << "$$\n \\newline";
	}

	inline void TextCot(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << "-\\frac{";
		TexDumpDiffNode(dumpfile, &cRight);
		dumpfile << "}{";
		TexDumpTree(dumpfile, &(sin(cRight) ^ 2));
		dumpfile << "}";

		dumpfile << "$$\n \\newline";
	}

	inline void TextCoth(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << "\\frac{";
		TexDumpDiffNode(dumpfile, &cRight);
		dumpfile << "}{";
		TexDumpTree(dumpfile, &(sinh(cRight) ^ 2));
		dumpfile << "}";

		dumpfile << "$$\n \\newline";
	}

	inline void TextLn(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << "\\frac{";
		TexDumpDiffNode(dumpfile, node.right);
		dumpfile << "}{";
		TexDumpTree(dumpfile, node.right);
		dumpfile << "}";

		dumpfile << "$$\n \\newline";
	}

	inline void TextLg(std::ofstream& dumpfile, node_t& node)
	{
		dumpfile << "$$";
		TexDumpDiffNode(dumpfile, &node);
		dumpfile << " = ";

		dumpfile << "\\frac{";
		TexDumpDiffNode(dumpfile, node.right);
		dumpfile << "}{";
		TexDumpTree(dumpfile, node.right);
		dumpfile << "\\cdot";
		TexDumpTree(dumpfile, &ln(num(10)));
		dumpfile << "}";

		dumpfile << "$$\n \\newline";
	}

#undef dRight
#undef dLeft
#undef cRight
#undef cLeft
#undef cThis
#undef is_int_power_function
#undef is_double_power_function
#undef is_exponencial_function
	
	inline node_t& num(int number)
	{
		data_t new_data(TYPE_int_constant, number);
		return *new node_t(new_data);
	}

	node_t& cosh(node_t& arg)
	{
		data_t cosh_t(TYPE_cosh);
		return *new node_t(cosh_t, nullptr, &arg);
	}

	node_t& sinh(node_t& arg)
	{
		data_t sinh_t(TYPE_sinh);
		return *new node_t(sinh_t, nullptr, &arg);
	}

	node_t& sin(node_t& arg)
	{
		data_t sin_t(TYPE_sin);
		return *new node_t(sin_t, nullptr, &arg);
	}

	node_t& cos(node_t& arg)
	{
		data_t cos_t(TYPE_cos);
		return *new node_t(cos_t, nullptr, &arg);
	}

	node_t& ln(node_t& arg)
	{
		data_t ln_t(TYPE_ln);
		return *new node_t(ln_t, nullptr, &arg);
	}

	node_t& CopyNode(node_t& node)
	{
		return *new node_t(node);
	}
	
	DifferTree& iLab::DifferTree::Simple()
	{
		SimpleNode(root);
		return *this;
	}

	void iLab::DifferTree::SimpleNode(node_t* node)
	{
		if (node->left)  if (node->left->left and node->left->right) SimpleNode(node->left);
		if (node->right) if (node->right->left and node->right->right) SimpleNode(node->right);

		node_t this_node = node;
		if (node->left and node->right)
		{
			switch (node->data.type)
			{
			case TYPE_mul:
				if ((node->left->data == 0 and (node->left->data.type == TYPE_int_constant or node->left->data.type == TYPE_double_constant)))
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
				}		
				else if ((node->right->data == 0 and (node->right->data.type == TYPE_int_constant or node->right->data.type == TYPE_double_constant)))
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
				}
				else if (node->left->data == 1 and (node->left->data.type == TYPE_int_constant or node->left->data.type == TYPE_double_constant))
				{
					node->data.type = this_node.right->data.type;
					node->data.value = this_node.right->data.value;
					node->left = this_node.right->left;
					node->right = this_node.right->right;
				}
				else if (node->right->data == 1 and (node->right->data.type == TYPE_int_constant or node->right->data.type == TYPE_double_constant))
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
				}
				break;
			case TYPE_add:
				if ((node->left->data == 0 and (node->left->data.type == TYPE_int_constant or node->left->data.type == TYPE_double_constant)))
				{
					node->data.type = this_node.right->data.type;
					node->data.value = this_node.right->data.value;
					node->left = this_node.right->left;
					node->right = this_node.right->right;
				}
				else if ((node->right->data == 0 and (node->right->data.type == TYPE_int_constant or node->right->data.type == TYPE_double_constant)))
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
				}
				break;
			case TYPE_sub:
				if ((node->left->data == 0 and (node->left->data.type == TYPE_int_constant or node->left->data.type == TYPE_double_constant)))
				{
					delete node->left;
					node->left = nullptr;
				}
				else if ((node->right->data == 0 and (node->right->data.type == TYPE_int_constant or node->right->data.type == TYPE_double_constant)))
				{
					delete node->right;
					node->right = nullptr;
				}
				break;
			case TYPE_deg:
				if (node->left->data == 1 and (node->left->data.type == TYPE_int_constant or node->left->data.type == TYPE_double_constant))
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					delete node->right;
					node->right = nullptr;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
				}
				else if (node->right->data == 1 and (node->right->data.type == TYPE_int_constant or node->right->data.type == TYPE_double_constant))
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
				}
				break;
			default:
				break;
			}
		}
	}

	void LabaMatan(DifferTree& tree)
	{
		std::ofstream dumpfile;
		dumpfile.open("Laboratory work in math analys.tex");
		Preamble(dumpfile);

		dumpfile << "$";
		TexDumpDiffNode(dumpfile, tree.root);
		dumpfile << "$ \n \\newline";

		iLab::DifferTree dif_tree = iLab::DifferentiateTree(tree, dumpfile);
		dif_tree.Simple();

		dumpfile << "\\text{Finaly:} $$\n";
		TexDumpDiffNode(dumpfile, tree.root);
		dumpfile << "= $$ \\newline $";
		TexDumpTree(dumpfile, dif_tree.root);
		dumpfile << "$\n";

		dumpfile << "\\end{document}";
		dumpfile.close();


		system("pdflatex \"Laboratory work in math analys.tex\"");
	}

	void Preamble(std::ofstream& fout)
	{
		std::ifstream preamble;
		std::string buf;
		preamble.open("Preamble.tex");
		while (!preamble.eof())
		{
			std::getline(preamble, buf);
			fout << buf << std::endl;
		}
		preamble.close();
	}

	void CringeStr(std::ofstream& fout, std::ifstream& fin)
	{
		std::string cringe_str;
		std::getline(fin, cringe_str);
		fout << "\n" << cringe_str << "\\newline";
	}
}



int main()
{
	iLab::DifferTree tree;
	tree.Scan("formula.txt");
	tree.GraphDump();
	iLab::LabaMatan(tree);
	std::cout << GetG("2+5*(7+3)$");
}