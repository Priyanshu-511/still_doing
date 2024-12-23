#include <iostream>
#include <stack>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

class BrowserHistoryManager {
private:
    stack<string> backStack;        // Stack for backward navigation
    deque<string> forwardQueue;     // Deque for forward navigation
    vector<string> historyList;     // To display the full history

public:
    // Visit a new page
    void visitPage(const string& page) {
        backStack.push(page);      // Add the page to the back stack
        forwardQueue.clear();      // Clear forward history as new page is visited
        historyList.push_back(page); // Add to the history list
    }

    // Backward navigation
    bool back() {
        if (backStack.empty()) {
            cout << "No more pages to go back to!" << endl;
            return false;
        }

        // Pop from the back stack and push to the forward queue
        string page = backStack.top();
        backStack.pop();
        forwardQueue.push_front(page);
        cout << "Navigated back to: " << page << endl;
        return true;
    }

    // Forward navigation
    bool forward() {
        if (forwardQueue.empty()) {
            cout << "No more pages to go forward to!" << endl;
            return false;
        }

        // Pop from the forward queue and push to the back stack
        string page = forwardQueue.front();
        forwardQueue.pop_front();
        backStack.push(page);
        cout << "Navigated forward to: " << page << endl;
        return true;
    }

    // Display the full history list
    void displayHistory() {
        cout << "Full History: ";
        for (const string& page : historyList) {
            cout << page << " -> ";
        }
        cout << "End" << endl;
    }

    // Clear the entire history
    void clearAllHistory() {
        while (!backStack.empty()) backStack.pop();
        forwardQueue.clear();
        historyList.clear();
        cout << "All history cleared!" << endl;
    }

    // Clear specific history
    void clearSpecificHistory(const string& page) {
        // Remove from backStack
        stack<string> tempStack;
        while (!backStack.empty()) {
            if (backStack.top() == page) {
                backStack.pop();
                break;
            }
            tempStack.push(backStack.top());
            backStack.pop();
        }
        while (!tempStack.empty()) {
            backStack.push(tempStack.top());
            tempStack.pop();
        }

        // Remove from forwardQueue
        auto it = find(forwardQueue.begin(), forwardQueue.end(), page);
        if (it != forwardQueue.end()) {
            forwardQueue.erase(it);
        }

        // Remove from historyList
        auto historyIt = find(historyList.begin(), historyList.end(), page);
        if (historyIt != historyList.end()) {
            historyList.erase(historyIt);
        }

        cout << "Removed " << page << " from history!" << endl;
    }

    // Show current state
    void showState() {
        cout << "Back Stack: ";
        stack<string> temp = backStack;
        while (!temp.empty()) {
            cout << temp.top() << " ";
            temp.pop();
        }
        cout << endl;

        cout << "Forward Queue: ";
        for (const string& page : forwardQueue) {
            cout << page << " ";
        }
        cout << endl;

        displayHistory();
    }
};

int main() {
    BrowserHistoryManager browserHistory;

    browserHistory.visitPage("Page1");
    browserHistory.visitPage("Page2");
    browserHistory.visitPage("Page3");
    browserHistory.showState();

    browserHistory.back();   // Go back to Page2
    browserHistory.showState();

    browserHistory.forward(); // Go forward to Page3
    browserHistory.showState();

    browserHistory.clearSpecificHistory("Page2"); // Remove Page2 from history
    browserHistory.showState();

    browserHistory.clearAllHistory(); // Clear all history
    browserHistory.showState();

    return 0;
}
