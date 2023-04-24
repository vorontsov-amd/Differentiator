#pragma once
#include "data_t.h"


iLab::node_t* GetN();
iLab::node_t* GetT();
iLab::node_t* GetE();
iLab::node_t* GetP();
iLab::node_t* GetF();
iLab::node_t* GetV();
iLab::node_t* GetW();
iLab::node_t* GetG(const char* str);
int ReadFunc(iLab::type_t* n);
int ReadVar(char* c);



#define FUCK fprintf(stderr, "%d %s\n", __LINE__, __FUNCSIG__);




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
	void Filesize(FILE* stream, size_t* filesize);
	void ReadBuffer(char** buffer, FILE* stream);
	int Filesize(std::ifstream& f);


	
	class DifferTree
	{
		friend DifferTree& DifferentiateTree(DifferTree& old);
		friend DifferTree& DifferentiateTree(DifferTree& old_tree, std::ofstream& dumpfile);
		friend void TreeRead(DifferTree& tree, char* str);


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
		int TreeScan(const char* filename = "formula.txt");
		int Print();

		void TexDump(const char* filename = "TexDump.tex");
		void GraphDump(const char* graphname = "Dump");


		node_t* Root()
		{
			return root;
		}

	private:
		node_t* root;

		void CreateNode(const data_t& data, node_t*& node);
		void Read(std::ifstream& file, node_t*& node, data_t& element);
		void Write(std::ofstream& file, node_t* node);
		void DumpNode(std::ofstream& dumpfile, const node_t* node);
		void SimpleNodeUniq(node_t* node, int* flag);
		void SimpleNodeNum(node_t* node, int* flag);
		void SwapSon(node_t* parrent);

	};
}



