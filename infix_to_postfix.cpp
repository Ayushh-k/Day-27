#include <bits/stdc++.h>
using namespace std;

int prec(char c)
{
    if (c == '^')
    {
        return 3;
    }
    else if (c == '/' || c == '*')
    {
        return 2;
    }
    else if (c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string infixToPostfix(string infix) // convertion for infix to postfix.
{
    string postfix;
    stack<char> s;

    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        if (isalpha(ch) || isdigit(ch))
        {
            postfix.push_back(ch);
        }
        else if (ch == '(')
        {
            s.push(ch);
        }
        else if (ch == ')')
        {
            while (!s.empty() && s.top() != '(')
            {
                postfix.push_back(s.top());
                s.pop();
            }
            if (!s.empty())
            {
                s.pop();
            }
        }
        else
        {
            while (!s.empty() && prec(ch) <= prec(s.top()))
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }

    return postfix;
}

string infixToPrefix(string infix) // convertion for infix to prefix..
{
    reverse(infix.begin(), infix.end());

    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(')
        {
            infix[i] = ')';
        }
        else if (infix[i] == ')')
        {
            infix[i] = '(';
        }
    }
    string prefix = infixToPostfix(infix);

    reverse(prefix.begin(), prefix.end());

    return prefix;
}

int solveForPostfix(string postfix)
{
    stack<int> st;
    for (int i = 0; i < postfix.length(); i++)
    {
        char ele = postfix[i];
        if (ele == '+' || ele == '-' || ele == '*' || ele == '/')
        {
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();

            switch (ele)
            {
            case '+':
                st.push(a + b);
                break;
            case '-':
                st.push(a - b);
                break;
            case '*':
                st.push(a * b);
                break;
            case '/':
                st.push(a / b);
                break;
            }
        }
        else
        {
            st.push(ele - '0');
        }
    }

    return st.top();
}

int solveForPrefix(string prefix)
{
    stack<int> st;
    for (int i = prefix.length() - 1; i >= 0; i--)
    {
        char ele = prefix[i];
        if (ele == '+' || ele == '-' || ele == '*' || ele == '/')
        {
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();

            switch (ele)
            {
            case '+':
                st.push(a + b);
                break;
            case '-':
                st.push(a - b);
                break;
            case '*':
                st.push(a * b);
                break;
            case '/':
                st.push(a / b);
                break;
            }
        }
        else
        {
            st.push(ele - '0');
        }
    }

    return st.top();
}

int main()
{
    string infix = "2*3-4+1";
    cout << "Postfix: " << infixToPostfix(infix) << endl;
    int ans = solveForPostfix(infixToPostfix(infix));
    cout << "Postfix Result: " << ans << endl;

    return 0;
}
