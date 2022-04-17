#pragma once
#include "data_t.h"


int GetN();
int GetT();
int GetE();
int GetP();
int GetG(const char* str);








namespace iLab
{	
	class DifferTree;	
	void Preamble(std::ofstream& fout);
	node_t& CopyNode(node_t& node);
	node_t& cosh(node_t& arg);
	node_t& sinh(node_t& arg);
	node_t& sin(node_t& arg);
	node_t& cos(node_t& arg);
	node_t& ln(node_t& arg);
	inline node_t& num(int number);
	void CringeStr(std::ofstream& fin, std::ifstream& fout);

	
	class DifferTree
	{
		friend DifferTree& DifferentiateTree(DifferTree& old);
		friend DifferTree& DifferentiateTree(DifferTree& old_tree, std::ofstream& dumpfile);


		friend void TexDump(iLab::DifferTree& tree, iLab::DifferTree& dif_tree);
		friend void TexDumpTree(std::ofstream& dumpfile, const node_t* node);
		friend void LabaMatan(DifferTree& tree);


	public:
		DifferTree();
		DifferTree(DifferTree& tree);
		~DifferTree();
		void Free(node_t* tree);

		DifferTree& Simple();

		int Scan(const char* filename = "formula.txt");
		int Print();

		void TexDump(const char* filename = "TexDump.tex");
		void GraphDump(const char* graphname = "Dump");



	private:
		node_t* root;

		void CreateNode(const data_t& data, node_t*& node);
		void Read(std::ifstream& file, node_t*& node, data_t& element);
		void Write(std::ofstream& file, node_t* node);
		void DumpNode(std::ofstream& dumpfile, const node_t* node);
		void SimpleNode(node_t* node);
	};
}



