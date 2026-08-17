
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Subject Interface
class Internet {
public:
    virtual void connectTo(string serverHost) = 0;
    virtual ~Internet() {}
};

// 2. Real Subject (The expensive or protected service)
class RealInternet : public Internet {
public:
    void connectTo(string serverHost) override {
        cout << "Connecting successfully to network host: " << serverHost << "\n";
    }
};

// 3. Proxy Object (Acts as the gatekeeper)
class InternetProxy : public Internet {
private:
    RealInternet* realInternet;
    vector<string> blockedSites;

public:
    InternetProxy() {
        realInternet = new RealInternet();
        // Initialize the blocklist
        blockedSites.push_back("facebook.com");
        blockedSites.push_back("instagram.com");
        blockedSites.push_back("malicious-site.io");
    }

    ~InternetProxy() {
        delete realInternet;
    }

    void connectTo(string serverHost) override {
        // Convert to lowercase for uniform verification
        string host = serverHost;
        transform(host.begin(), host.end(), host.begin(), ::tolower);

        // Check if the site is blocked
        if (find(blockedSites.begin(), blockedSites.end(), host) != blockedSites.end()) {
            cout << "ACCESS DENIED: Connection to '" << serverHost << "' is restricted by company policy!\n";
        } else {
            // Forward request to the real service if valid
            realInternet->connectTo(serverHost);
        }
    }
};
int main() {
    // Client interacts with the proxy seamlessly through the Interface
    Internet* officeNetwork = new InternetProxy();

    cout << "--- Office Internet Browsing Session ---\n";
    
    // Test Case 1: Permitted Site
    officeNetwork->connectTo("google.com");
    
    // Test Case 2: Blocked Site
    officeNetwork->connectTo("facebook.com");
    
    // Test Case 3: Permitted Site
    officeNetwork->connectTo("github.com");

    delete officeNetwork;
    return 0;
}

