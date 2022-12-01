#include "Lexema.h"
#include <gtest.h>

TEST(set1, Calculation)
{
    Queue<Lexema> lex_res = lex("(123 - 10)+ 50 / 50 * 30");
    vector <Lexema> polska = Reverse_Polska(lex_res);
    EXPECT_EQ(Calculate(polska), (123 - 10) + 50 / 50 * 30);
}

TEST(set1, throws_when_too_many_skobok)
{
    Queue<Lexema> lex_res = lex("(123 - 10)))+ 50 / 50 * 30))");
    vector <Lexema> polska;
    ASSERT_ANY_THROW(Reverse_Polska(lex_res));
}


TEST(set1, throws_when_too_many_operatioòs)
{
    Queue<Lexema> lex_res = lex("(123 -- 10)+ 50 // 50 *+ 30");
    vector <Lexema> polska = Reverse_Polska(lex_res);
    ASSERT_ANY_THROW(Calculate(polska));
}

TEST(set2, throws_when_pop_empty_stack)
{
    Stack<int> st;
    ASSERT_ANY_THROW(st.Pop());
}

TEST(set2, throws_when_no_top_elem)
{
    Stack<int> st;
    ASSERT_ANY_THROW(st.Top());
}

TEST(set3, throws_when_pop_empty_queue)
{
    Queue<int> q;
    ASSERT_ANY_THROW(q.Pop());
}

TEST(set3, equalation_of_queue)
{
    Queue<int> q1;
    Queue<int> q2;
    q1.Push(1);
    q2 = q1;
    EXPECT_EQ(q1.Get_Element(1), q2.Get_Element(1));
    
}