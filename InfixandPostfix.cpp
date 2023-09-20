#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
stringstream ss;

class Stack {
public:
  int size();
  int top();
  int pop();
  void add(int num);
  vector<int> stack;
  int length = 0;
};

// gets the size of the stack
int Stack::size() { return length; }
// gets the top value of the stack do not remove
int Stack::top() {
  int last;
  last = stack.back();
  return last;
}
// pop() remove the element at the current top of the stack and returns it.
int Stack::pop() {

  int popped;
  popped = stack.back();
  // stack.erase(stack.end());
  stack.pop_back();
  length--;
  return popped;
}
// adds element to top of stack
void Stack::add(int num) {
  stack.push_back(num);
  length++;
}
/////////END OF CLASSS STUFFF//////////
////BODMAS OR PEMDAS EITHER OR :/

int pemdas(char operation) {
  if (operation == '^')
    return 3;
  else if (operation == '/' || operation == '*')
    return 2;
  else if (operation == '+' || operation == '-')
    return 1;
  else
    return -1;
}

//////INFIX TO POST FIX/////////////
string translate(string infix) {
  char temp;
  char numHold;
  Stack operators;
  string equation = "";

  for (int i = 0; i < infix.length(); i++) {
    temp = infix[i];
    if (temp >= '0' && temp <= '9') {
      equation += char(temp);
    } else if (temp == '(') {
      operators.add(temp);

    } else if (temp == ')') {
      while (char(operators.top()) != '(') {
        equation += char(operators.top());
        operators.pop();
      }
      operators.pop();
    } else {
      while ((operators.size() > 0) &&
             pemdas(temp) <= pemdas(operators.top())) {
        equation += char(operators.top());
        operators.pop();
      }
      operators.add(temp);
    }
  }
  while (operators.size() > 0) {
    equation += char(operators.top());
    operators.pop();
  }
  ss << equation;
  return equation;
}
////////////// postfixing
float postfix(string equation) {
  Stack nums;
  char value;

  for (int i = 0; i < equation.length(); i++) {
    value = equation[i];
    /// NUMBERSSSSS
    if (value >= '0' && value <= '9') {
      int temp;
      temp = value - '0';
      nums.add(temp);
    }
    ////// Operations
    else {
      if (nums.size() > 1) {
        int first = nums.pop();
        int second = nums.pop();
        first = first;
        second = second;
        int result;
        switch (value) {
        case '+':
          result = second + first;
          nums.add(result);
          break;

        case '-':
          result = second - first;
          nums.add(result);
          break;
        case '*':
          result = second * first;
          nums.add(result);
          break;
        case '/':
          result = second / first;
          nums.add(result);
          break;
        case '^':
          result = pow(second, first);
          nums.add(result);
          break;
        }
      }
    }
  }
  float answer;
  answer = nums.top();

  ss << setprecision(1) << fixed << answer;
  return answer;
}
void postcheck(string equation) {
  char value;
  int numbers = 0;
  int characters = 0;
  for (int i = 0; i < equation.length(); i++) {
    value = equation[i];
    if (value >= '0' && value <= '9') {
      numbers++;
    } else {
      characters++;
    }
  }
  if (numbers - 1 == characters){
    postfix(equation);

  } else {
    ss << "nv";
  }
}
int main(int argc, char **argv) {

  string equation = "55+3^";
  ofstream fout;

  postcheck(equation);
  cout << ss.str();
  fout.close();

  return 0;
}
