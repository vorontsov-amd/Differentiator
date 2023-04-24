#include "Differentiator.h"
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
		default: puts("ERROR UNKNOWN TYPE");
			exit(0);
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
	
#define NO_CHANGES (1)
#define YE_CHANGES (0)

	DifferTree& iLab::DifferTree::Simple()
	{
		int flag = NO_CHANGES;
		do
		{
			flag = NO_CHANGES;
			SimpleNodeUniq(root, &flag);
			SimpleNodeNum(root, &flag);
		} while (flag != NO_CHANGES);
		return *this;
	}

#define DATA_TYPE_IS_OPERATOR (node->data.type == TYPE_add or node->data.type == TYPE_sub or node->data.type == TYPE_mul or \
	node->data.type == TYPE_div or node->data.type == TYPE_deg)

#define RIGHT_TYPE_IS_OPERATOR (node->right->data.type == TYPE_add or node->right->data.type == TYPE_sub or \
	node->right->data.type == TYPE_mul or node->right->data.type == TYPE_div or node->right->data.type == TYPE_deg)

#define LEFT_TYPE_IS_OPERATOR (node->left->data.type == TYPE_add or node->left->data.type == TYPE_sub or \
	node->left->data.type == TYPE_mul or node->left->data.type == TYPE_div or node->left->data.type == TYPE_deg)

#define LEFT_TYPE_IS_NUM (node->left->data.type == TYPE_double_constant or node->left->data.type == TYPE_int_constant) 
#define RIGHT_TYPE_IS_NUM (node->right->data.type == TYPE_double_constant or node->right->data.type == TYPE_int_constant) 

#define RIGHT_LEFT_TYPE_IS_NUM (node->right->left->data.type == TYPE_int_constant or node->right->left->data.type == TYPE_double_constant)
#define RIGHT_RIGHT_TYPE_IS_NUM (node->right->left->data.type == TYPE_int_constant or node->right->left->data.type == TYPE_double_constant)
#define LEFT_RIGHT_TYPE_IS_NUM (node->left->right->data.type == TYPE_int_constant or node->left->right->data.type == TYPE_double_constant)
#define LEFT_LEFT_TYPE_IS_NUM (node->left->left->data.type == TYPE_int_constant or node->left->left->data.type == TYPE_double_constant)


#define VALUE (node->data.value.int_value)
#define LEFT_VALUE (node->left->data.value.int_value)
#define RIGHT_VALUE (node->right->data.value.int_value)
#define RIGHT_LEFT_VALUE (node->right->left->data.value.int_value)
#define RIGHT_RIGHT_VALUE (node->right->right->data.value.int_value)
#define LEFT_LEFT_VALUE (node->left->left->data.value.int_value)
#define LEFT_RIGHT_VALUE (node->left->right->data.value.int_value)


	void iLab::DifferTree::SimpleNodeNum(node_t* node, int* flag)
	{	

		if (node->left) SimpleNodeNum(node->left, flag);
		if (node->right) SimpleNodeNum(node->right, flag);
	
		if (node->left != nullptr)
		{			
			if (DATA_TYPE_IS_OPERATOR && LEFT_TYPE_IS_NUM && RIGHT_TYPE_IS_NUM)
			{
				switch (node->data.type)
				{
				case TYPE_mul: VALUE = LEFT_VALUE * RIGHT_VALUE; break;
				case TYPE_sub: VALUE = LEFT_VALUE - RIGHT_VALUE; break;
				case TYPE_add: VALUE = LEFT_VALUE + RIGHT_VALUE; break;
				case TYPE_div: VALUE = LEFT_VALUE / RIGHT_VALUE; break;
				case TYPE_deg: VALUE = (int)pow(LEFT_VALUE, RIGHT_VALUE); break;
				}
				node->data.type = TYPE_int_constant;
				*flag = YE_CHANGES;
				delete node->left;
				node->left = nullptr;

				delete node->right;
				node->right = nullptr;
			}
			else if (node->right->left != nullptr)
			{
				if (DATA_TYPE_IS_OPERATOR && LEFT_TYPE_IS_NUM && RIGHT_TYPE_IS_OPERATOR && RIGHT_LEFT_TYPE_IS_NUM && node->data.type == node->right->data.type)
				{
					node_t* save = node->right->right;
					switch (node->data.type)
					{
					case TYPE_mul: LEFT_VALUE = LEFT_VALUE * RIGHT_LEFT_VALUE;
						delete node->right->left;
						node->right->left = nullptr;
						delete node->right;
						node->right = save;
						break;
					case TYPE_sub: LEFT_VALUE = LEFT_VALUE - RIGHT_LEFT_VALUE;
						delete node->right->left;
						node->right->left = nullptr;
						delete node->right;
						node->right = save;
						node->data.type = TYPE_add;
						break;
					case TYPE_add: LEFT_VALUE = LEFT_VALUE + RIGHT_LEFT_VALUE;
						delete node->right->left;
						node->right->left = nullptr;
						delete node->right;
						node->right = save;
						break;
					case TYPE_deg: LEFT_VALUE = LEFT_VALUE ^ RIGHT_LEFT_VALUE;
						delete node->right->left;
						node->right->left = nullptr;
						delete node->right;
						node->right = save;
						break;
					default: break;
					}
					*flag = YE_CHANGES;
				}
				else if (DATA_TYPE_IS_OPERATOR && LEFT_TYPE_IS_NUM && RIGHT_TYPE_IS_OPERATOR && RIGHT_RIGHT_TYPE_IS_NUM && node->data.type == node->right->data.type)
				{
					node_t* save = node->right->right;
					switch (node->data.type)
					{
					case TYPE_mul: LEFT_VALUE = LEFT_VALUE * RIGHT_RIGHT_VALUE;
						delete node->right->right;
						node->right->right = nullptr;
						delete node->right;
						node->right = save;
						break;
					case TYPE_sub: LEFT_VALUE = LEFT_VALUE + RIGHT_RIGHT_VALUE;
						delete node->right->right;
						node->right->right = nullptr;
						delete node->right;
						node->right = save;
						break;
					case TYPE_add: LEFT_VALUE = LEFT_VALUE + RIGHT_RIGHT_VALUE;
						delete node->right->right;
						node->right->right = nullptr;
						delete node->right;
						node->right = save;
						break;
					default: break;
					}
					*flag = YE_CHANGES;
				}
			}
			else if (node->left->left != nullptr)
			{
				if (DATA_TYPE_IS_OPERATOR && LEFT_TYPE_IS_OPERATOR && RIGHT_TYPE_IS_NUM && LEFT_RIGHT_TYPE_IS_NUM && node->data.type == node->left->data.type)
				{
					node_t* save = node->left->left;
					switch (node->data.type)
					{
					case TYPE_mul: RIGHT_VALUE = RIGHT_VALUE * LEFT_RIGHT_VALUE;
						delete node->left->right;
						node->left->right = nullptr;
						delete node->left;
						node->left = save;
						SwapSon(node);
						break;
					case TYPE_sub: RIGHT_VALUE = RIGHT_VALUE + LEFT_RIGHT_VALUE;
						delete node->left->right;
						node->left->right = nullptr;
						delete node->left;
						node->left = save;
						break;
					case TYPE_add: RIGHT_VALUE = RIGHT_VALUE + LEFT_RIGHT_VALUE;
						delete node->left->right;
						node->left->right = nullptr;
						delete node->left;
						node->left = save;
						break;
					default: break;
					}
					*flag = YE_CHANGES;
				}
				else if (DATA_TYPE_IS_OPERATOR && LEFT_TYPE_IS_OPERATOR && RIGHT_TYPE_IS_NUM && LEFT_LEFT_TYPE_IS_NUM && node->data.type == node->left->data.type)
				{
					node_t* save = node->left->right;
					switch (node->data.type)
					{
					case TYPE_mul: RIGHT_VALUE = RIGHT_VALUE * LEFT_LEFT_VALUE;
						delete node->left->left;
						node->left->left = nullptr;
						delete node->left;
						node->left = save;
						SwapSon(node);
						break;
					case TYPE_sub: LEFT_VALUE = LEFT_LEFT_VALUE - RIGHT_VALUE;
						delete node->left->left;
						node->left->left = nullptr;
						delete node->right;
						node->right = save;
						break;
					case TYPE_add: RIGHT_VALUE = RIGHT_VALUE + LEFT_LEFT_VALUE;
						delete node->left->left;
						node->left->left = nullptr;
						delete node->left;
						node->left = save;
						break;
					default: break;
					}
					*flag = YE_CHANGES;
				}
			}
		}
	}





	void iLab::DifferTree::SimpleNodeUniq(node_t* node, int* flag)
	{		
		if (node->left) SimpleNodeUniq(node->left, flag);
		if (node->right) SimpleNodeUniq(node->right, flag);
		
		node_t this_node = node;
		if (node->left != nullptr and node->right != nullptr)
		{
			switch (node->data.type)
			{
			case TYPE_mul:
				if (node->left->data.type == TYPE_int_constant && node->left->data.value.int_value == 0)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}		
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 0)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
				else if (node->left->data.type == TYPE_int_constant && node->left->data.value.int_value == 1)
				{
					node->data.type = this_node.right->data.type;
					node->data.value = this_node.right->data.value;
					node->left = this_node.right->left;
					node->right = this_node.right->right;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 1)
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
					*flag = YE_CHANGES;
				}
				break;
			case TYPE_add:
				if (node->left->data.type == TYPE_int_constant && node->left->data.value.int_value == 0)
				{
					node->data.type = this_node.right->data.type;
					node->data.value = this_node.right->data.value;
					node->left = this_node.right->left;
					node->right = this_node.right->right;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 0)
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_variable && node->left->data.type == TYPE_variable)
				{
					node->data.type = TYPE_mul;
					node->left->data.type = TYPE_int_constant;
					node->left->data.value.int_value = 2;
					*flag = YE_CHANGES;
				}
				break;
			case TYPE_sub:
				if (node->left->data.type == TYPE_int_constant && node->left->data.value.int_value == 0)
				{
					delete node->left;
					node->left = nullptr;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 0)
				{
					delete node->right;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
				else if (node->left->data.type == TYPE_variable and node->right->data.type == TYPE_variable
					and node->left->data.value.char_value == node->right->data.value.char_value)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
				break;
			case TYPE_deg:
				if (node->left->data.type == TYPE_int_constant && node->left->data.value.int_value == 1)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 1;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 1)
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 0)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 1;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
				break;
			case TYPE_div:
				if (node->left->data.type == TYPE_int_constant && node->left->data.value.int_value == 0)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
				else if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 1)
				{
					node->data.type = this_node.left->data.type;
					node->data.value = this_node.left->data.value;
					node->left = this_node.left->left;
					node->right = this_node.left->right;
					*flag = YE_CHANGES;
				}

				else if (node->left->data.type == TYPE_variable and node->right->data.type == TYPE_variable
					and node->left->data.value.char_value == node->right->data.value.char_value)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 1;
					delete node->left;
					delete node->right;
					node->left = nullptr;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
			default:
				break;
			}
		}
		if (node->right != nullptr)
		{
			if (node->data.type == TYPE_ln)
			{
				if (node->right->data.type == TYPE_int_constant && node->right->data.value.int_value == 1)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->right;
					node->right = nullptr;
					*flag = YE_CHANGES;
				}
			}
			if (node->data.type == TYPE_lg)
			{
				if (node->left->data.value.int_value == 1)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 0;
					delete node->left;
					node->left = nullptr;
					*flag = YE_CHANGES;
				}
				else if (node->left->data.value.int_value == 10)
				{
					node->data.type = TYPE_int_constant;
					node->data.value.int_value = 1;
					delete node->left;
					node->left = nullptr;
					*flag = YE_CHANGES;
				}
			}						
		}
	}

	void iLab::DifferTree::SwapSon(node_t* parrent)
	{
		node_t* node = new node_t(parrent->left);
		parrent->left = parrent->right;
		parrent->right = node;
	}

	void LabaMatan(DifferTree& tree)
	{
		tree.GraphDump();
		std::ofstream dumpfile;
		dumpfile.open("Laboratory work in math analys.tex");
		Preamble(dumpfile);

		dumpfile << "$";
		TexDumpDiffNode(dumpfile, tree.root);
		dumpfile << "$ \n \\newline";

		iLab::DifferTree dif_tree = iLab::DifferentiateTree(tree, dumpfile);
		dif_tree.GraphDump("dtree");
		dif_tree.Simple();
		dif_tree.GraphDump("simple");

		dumpfile << "\\text{Finally:} $$\n";
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
	tree.TreeScan("formula.txt");
	tree.GraphDump();
	iLab::LabaMatan(tree);
}