#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include "Lexema.h"

using namespace std;

int main()
{
	string str = "( 123 -10)+50/ 50 * 30";
	cout << str;
	Queue <Lexema> lex_res;
	lex_res = lex(str);

	cout << lex_res << endl;

	vector <Lexema> polska;

	polska = Reverse_Polska(lex_res);
	
	for (int i = 0; i < polska.size(); i++)
	{
		cout << polska[i] << " ";
	}

	cout << endl;
	cout << Calculate(polska);

    return 0;
}