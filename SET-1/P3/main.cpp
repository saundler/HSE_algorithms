#include <iostream>
#include <string>
#include <stack>
#include <algorithm>

std::string Decode(std::string &input) {
    std::stack<char> stack;
    std::string ans;
    ans.reserve(21);
    for (int i = 0; i < input.size(); ++i) {
        stack.push(input[i]);
        if (input[i] == ']') {
            ans = "";
            stack.pop();
            while (stack.top() != '[') {
                ans += stack.top();
                stack.pop();
            }
            std::reverse(ans.begin(), ans.end());
            stack.pop();
            int n = stack.top() - 48;
            stack.pop();
            for (int j = 0; j < n; ++j) {
                for (auto c : ans) {
                    stack.push(c);
                }
            }
        }
    }
    ans = "";
    while (!stack.empty()) {
        ans += stack.top();
        stack.pop();
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string input;
    getline(std::cin, input);

    std::cout << Decode(input);
    return 0;
}
