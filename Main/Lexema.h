#pragma once
#include <string>
#include <iostream>
#include "Queue.h"
#include "Stack.h"
#include <vector>
using namespace std;

enum TypeElement {
	Operation,
	Value,
	Null
};

class Lexema {
	string str;
	TypeElement type;
public:
	Lexema(string _str = " ", TypeElement _type = Null) : str(_str), type(_type) {};
	string getStr() { return str; }
	TypeElement getType() { return type; }
	friend ostream& operator << (ostream& out, Lexema& p) {
		out << "{" << p.str << ", ";
		if (p.type == Operation) {
			out << "operation";
		}
		else if (p.type == Value) {
			out << "value";
		};
		out << "}";
		return out;
	}
};


Queue <Lexema> lex(string input) {
	Queue<Lexema>res;
	input += ' ';
	int i = 0;
	string tmp = "";
	string op = "+-*/()";
	string sep = " \n\t";
	int state = 0;
	for (i = 0; i < input.size(); i++) {
		char c = input[i];
		int fres;
		switch (state)
		{
		case 0: 
			if (c >= '0' && c <= '9') {
				tmp = c;
				state = 1;
				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				tmp = c;
				Lexema l(tmp, Operation);
				res.Push(l);
				state = 0;
				break;
			}
			break;
		case 1: 
			if (c >= '0' && c <= '9') {
				tmp += c;
				state = 1;
				break;
			}
			fres = op.find(c);
			if (fres >= 0) {
				Lexema l1(tmp, Value);
				res.Push(l1);
				tmp = c;
				Lexema l2(tmp, Operation);
				res.Push(l2);
				state = 0;
				break;
			}
			fres = sep.find(c);
			if (fres >= 0) {
				Lexema l(tmp, Value);
				res.Push(l);
				state = 0;
				break;
			}
			break;
		}
	}
	return res;
}

vector <Lexema> Reverse_Polska(Queue<Lexema>& q)
{
	vector <Lexema> res;
	int bracket_num = 0;
	int prior1;
	int prior2;
	string op = "+-/*";
	Stack<Lexema> stack;
	char c;
	for (int i = 1; i < q.Get_Size() + 1; i++)
	{
		Lexema l = q.Get_Element(i);
		switch (l.getType())
		{
		case Operation:
			c = l.getStr()[0];
			switch (c)
			{
			case '(':
				stack.Push(l);
				bracket_num++;
				break;
			case '+':case '-':case'*':case'/':
				if (stack.IsEmpty())
				{
					stack.Push(l);
					break;
				}
				prior1 = op.find(c) / 2;
				while (!stack.IsEmpty())
				{
					prior2 = op.find(stack.Top().getStr()) / 2;
					if (prior1 <= prior2)
					{
						res.push_back(stack.Pop());
					}
					else
					{
						break;
					}
				}
				stack.Push(l);
				break;
			case ')':
				while (true)
				{
					if (!stack.IsEmpty())
					{
						if (stack.Top().getStr() != "(")
						{
							res.push_back(stack.Pop());
						}
						else
						{
							stack.Pop();
							bracket_num--;
							break;
						}
					}
					else
					{
						throw exception();
					}
				}
			}
			break;
		case Value:
			res.push_back(l);
			break;
		}
	}
	while (stack.IsEmpty() != true)
	{
		res.push_back(stack.Pop());
	}
	if (bracket_num != 0)
	{
		throw 1;
	}
	return res;
}

double StrToDouble(string& st)
{
	double num = 0;
	int x = 1;
	for (int i = st.size() - 1; i >= 0; i--)
	{
		num += (st[i] - 48) * x;
		x *= 10;
	}
	return num;
}

double Calculate(vector<Lexema>& vc)
{
	Stack<double> stack;
	int i = 0;
	double op1;
	double op2;
	while (i < vc.size())
	{
		if (vc[i].getType() == Value)
		{
			stack.Push(StrToDouble(vc[i].getStr()));
		}
		else
		{
			if (stack.Size() >= 2)
			{
				op2 = stack.Pop();
				op1 = stack.Pop();
				char c = vc[i].getStr()[0];
				switch (c)
				{
				case '+':
					stack.Push(op1 + op2);
					break;
				case '-':
					stack.Push(op1 - op2);
					break;
				case '*':
					stack.Push(op1 * op2);
					break;
				case '/':
					stack.Push(op1 / op2);
					break;
				}
			}
			else
			{
				throw exception();
			}
		}
		i++;
	}
	return stack.Pop();
}