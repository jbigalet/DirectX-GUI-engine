#pragma once

namespace Calculation{

	class CCalculation {
	public:
		CCalculation() {};
		virtual int calculate() = 0;
	};

	typedef CCalculation* PCalculation;


	class CONSTI : public CCalculation {
		int x;
	public:
		CONSTI(int a) : x(a) {};
		int calculate() { return x; };
	};


	#define CREATE_OPERATOR2(name,op)											\
		class name : public CCalculation {										\
			CCalculation *x;													\
			CCalculation *y;													\
		public:																	\
			name(int a, CCalculation *b) : y(b) { x = new CONSTI(a); };			\
			name(CCalculation *a, int b) : x(a) { y = new CONSTI(b); };			\
			name(int a, int b) { x = new CONSTI(a); y = new CONSTI(b); };		\
			name(CCalculation *a, CCalculation *b) : x(a), y(b) {};				\
			int calculate() { return x->calculate() op y->calculate(); };		\
		}

	CREATE_OPERATOR2(ADD, +);
	CREATE_OPERATOR2(SUB, -);
	CREATE_OPERATOR2(MUL, *);
	CREATE_OPERATOR2(DIV, /);


	//#define CREATE_GET(name,toget)												\
	//	class name : public CCalculation {										\
	//		PItem item;															\
	//	public:																	\
	//		name(PItem i) : item(i) {};											\
	//		int calculate() { return item->#toget; };							\
	//	}

	//CREATE_GET(DIMX, iDimX);
	//CREATE_GET(DIMY, iDimY);

}	// namespace
