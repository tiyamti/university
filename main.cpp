#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;
const double pi = M_PI;
template <typename T>
class Stack {
private:
    vector<T> data;

public:
    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    T& top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty.");
        }
        return data.back();
    }

    const T& top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty.");
        }
        return data.back();
    }

    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty.");
        }
        data.pop_back();
    }
};
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '!' ||
           c == 's' || c == 'c' || c == 't' || c == 'l' || c == 'q' || c == 'x';
}

double factorial(double n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

double my_sin(double x) {
    x = fmod(x, 2 * pi);
    double result = 0.0;
    double term = x;
    double power = x;
    double n = 1.0;
    while (abs(term) > 1e-15) {
        result += term;
        power *= -1 * x * x / ((2 * n) * (2 * n + 1));
        term = power / factorial(2 * n + 1);
        n += 1.0;
    }
    return result;
}

double my_cos(double x) {
    x = fmod(x, 2 * pi);
    double result = 1.0;
    double term = 1.0;
    double power = 1.0;
    double n = 1.0;
    while (abs(term) > 1e-15) {
        power *= -1 * x * x / ((2 * n - 1) * (2 * n));
        term = power / factorial(2 * n);
        result += term;
        n += 1.0;
    }
    return result;
}

double my_tan(double x) {
    return my_sin(x) / my_cos(x);
}
double my_sqrt(double x) {
    if (x < 0) {
        throw runtime_error("Cannot take square root of a negative number");
    }
    double guess = x / 2;
    double prevGuess = 0.0;
    while (abs(guess - prevGuess) > 1e-15) {
        prevGuess = guess;
        guess = (guess + x / guess) / 2;
    }
    return guess;
}

double my_log(double x) {
    if (x <= 0) {
        throw runtime_error("Logarithm is undefined for non-positive numbers");
    }
    double result = 0.0;
    double term = (x - 1) / (x + 1);
    double power = term;
    double n = 1.0;
    while (abs(power) > 1e-15) {
        result += power / n;
        power *= term * term;
        n += 2.0;
    }
    return 2 * result;
}

double my_log10(double x) {
    return my_log(x) / my_log(10);
}



double apply_operator(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        case '!': return factorial(a);
        case 's': return my_sin(a);
        case 'c': return my_cos(a);
        case 't': return my_tan(a);
        case 'l': return my_log(a);
        case 'q': return my_sqrt(a);
        case 'x': return my_log10(a);
        default: throw runtime_error("Unknown operator");
    }
}
string infix_to_postfix(const string& infix) {
    Stack<char> ops;
    ostringstream postfix;
    bool lastWasOperator = true;

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];

        if (isspace(c)) {
            continue;
        } else if (isdigit(c) || c == '.' || (c == '-' && lastWasOperator)) {
            postfix << c;
            if (i == infix.size() - 1 || (!isdigit(infix[i + 1]) && infix[i + 1] != '.')) {
                postfix << ' ';
            }
            lastWasOperator = false;
        } else if (c == '(') {
            ops.push(c);
            lastWasOperator = true;
        } else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') {
                postfix << ops.top() << ' ';
                ops.pop();
            }
            if (ops.empty() || ops.top() != '(') {
                throw runtime_error("Mismatched parentheses");
            }
            ops.pop();
            lastWasOperator = false;
        } else if (is_operator(c)) {
            if ((c == 's' || c == 'c' || c == 't' || c == 'l' || c == 'q' || c == 'x') &&
                (i + 1 < infix.size() && infix[i + 1] == '(')) {
                ops.push(c);
                lastWasOperator = true;
            } else {
                while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
                    postfix << ops.top() << ' ';
                    ops.pop();
                }
                ops.push(c);
                lastWasOperator = true;
            }
        } else if (c == 'e') {
            postfix << "2.718281828459045 ";
            lastWasOperator = false;
        } else if (c == 'p' && i + 1 < infix.size() && infix[i + 1] == 'i') {
            postfix << pi << ' ';
            ++i;
            lastWasOperator = false;
        } else {
            throw runtime_error("Invalid character");
        }
    }

    while (!ops.empty()) {
        if (ops.top() == '(') {
            throw runtime_error("Mismatched parentheses");
        }
        postfix << ops.top() << ' ';
        ops.pop();
    }

    return postfix.str();
}

double evaluate_postfix(const string& postfix) {
    Stack<double> values;
    istringstream iss(postfix);
    string token;

    while (iss >> token) {
        if (token[0] == '-' && token.size() > 1 && isdigit(token[1])) {
            values.push(-stod(token.substr(1)));
        } else if (token == "0" && !values.empty() && values.top() == 0) {
            continue;
        } else if (token == "(") {
            string nextToken;
            iss >> nextToken;
            if (nextToken[0] == '-' && nextToken.size() > 1 && isdigit(nextToken[1])) {
                values.push(-stod(nextToken.substr(1)));
            } else {
                values.push(stod(nextToken));
            }
        } else if (is_operator(token[0])) {
            if (token == "!") {
                if (values.empty()) {
                    throw runtime_error("Not enough operands");
                }
                double a = values.top();
                values.pop();
                values.push(factorial(a));
            } else if (token[0] == '^') {
                if (values.size() < 2) {
                    throw runtime_error("Not enough operands");
                }
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(pow(a, b));
            } else if (token[0] == 's' || token[0] == 'c' || token[0] == 't' ||
                       token[0] == 'l' || token[0] == 'q' || token[0] == 'x' ) {
                if (values.empty()) {
                    throw runtime_error("Not enough operands");
                }
                double a = values.top();
                values.pop();
                values.push(apply_operator(token[0], a, 0));
            } else {
                if (values.size() < 2) {
                    throw runtime_error("Not enough operands");
                }
                double b = values.top();
                values.pop();
                double a = values.top();
                values.pop();
                values.push(apply_operator(token[0], a, b));
            }
        } else {
            values.push(stod(token));}
    }

    if (values.size() != 1) {
        throw runtime_error("Invalid expression");
    }

    return values.top();
}

int main() {
    string infix;
    while (true) {
        cout << "Enter an expression (or 'q' to quit): ";
        getline(cin, infix);
        if (infix == "q") break;
        try {
            string postfix = infix_to_postfix(infix);

            double result = evaluate_postfix(postfix);
            cout << "Result: " << result << endl;
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    return 0;
}
