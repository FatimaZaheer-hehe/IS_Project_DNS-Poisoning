#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <windows.h>
using namespace std;

// Simple color functions
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setGreen() {
    SetConsoleTextAttribute(hConsole, 10); // Green color
}

void setRed() {
    SetConsoleTextAttribute(hConsole, 12); // Red color
}

void setYellow() {
    SetConsoleTextAttribute(hConsole, 14); // Yellow color
}

void setWhite() {
    SetConsoleTextAttribute(hConsole, 15); // White color
}

void resetColor() {
    SetConsoleTextAttribute(hConsole, 7); // Default white
}

// Structure to store DNS records
struct DNSCacheEntry {
    string domain;
    string ipAddress;
    bool isPoisoned;
};

// DNS Cache Class
class DNSCache {
private:
    vector<DNSCacheEntry> cache;

public:
    // Add legitimate DNS record
    void addRecord(string domain, string ip) {
        DNSCacheEntry newEntry;
        newEntry.domain = domain;
        newEntry.ipAddress = ip;
        newEntry.isPoisoned = false;
        cache.push_back(newEntry);
        
        setGreen();
        cout << "[+] Added to cache: " << domain << " -> " << ip << endl;
        resetColor();
    }

    // Lookup IP address
    string lookup(string domain) {
        for(int i = 0; i < cache.size(); i++) {
            if(cache[i].domain == domain) {
                if(cache[i].isPoisoned) {
                    setRed();
                    cout << "[!] WARNING: This record has been POISONED!" << endl;
                    resetColor();
                }
                return cache[i].ipAddress;
            }
        }
        return "NOT FOUND";
    }

    // Attacker poisons the cache
    void poisonCache(string domain, string fakeIP) {
        for(int i = 0; i < cache.size(); i++) {
            if(cache[i].domain == domain) {
                cache[i].ipAddress = fakeIP;
                cache[i].isPoisoned = true;
                setRed();
                cout << "[ATTACKER] Successfully poisoned " << domain << " -> " << fakeIP << endl;
                resetColor();
                return;
            }
        }
        // If domain doesn't exist, attacker adds fake record
        DNSCacheEntry fakeEntry;
        fakeEntry.domain = domain;
        fakeEntry.ipAddress = fakeIP;
        fakeEntry.isPoisoned = true;
        cache.push_back(fakeEntry);
        setRed();
        cout << "[ATTACKER] Added fake record: " << domain << " -> " << fakeIP << endl;
        resetColor();
    }

    // Display all cache entries
    void showCache() {
        cout << "\n========================================" << endl;
        cout << "         CURRENT DNS CACHE" << endl;
        cout << "========================================" << endl;
        for(int i = 0; i < cache.size(); i++) {
            cout << cache[i].domain << "  ->  " << cache[i].ipAddress;
            if(cache[i].isPoisoned) {
                setRed();
                cout << "  [POISONED - FAKE!]";
                resetColor();
            }
            cout << endl;
        }
        cout << "========================================\n" << endl;
    }
};

int main() {
    system("cls");  // Clear screen
    
    setYellow();
    cout << "\n";
    cout << "========================================" << endl;
    cout << "     DNS CACHE POISONING SIMULATION" << endl;
    cout << "     Attack & Defense Demonstration" << endl;
    cout << "========================================\n" << endl;
    resetColor();
    
    // Create DNS cache
    DNSCache dns;
    
    // STEP 1: Normal DNS records
    cout << "--- STEP 1: Setting up legitimate DNS records ---" << endl;
    dns.addRecord("google.com", "142.250.185.46");
    dns.addRecord("facebook.com", "157.240.22.35");
    dns.addRecord("bank.com", "192.168.1.100");
    
    dns.showCache();
    
    cout << "Press Enter to continue...";
    cin.get();
    
    // STEP 2: Normal user queries
    cout << "\n--- STEP 2: User accessing websites normally ---" << endl;
    string ip = dns.lookup("google.com");
    setGreen();
    cout << "User typed 'google.com' -> Resolved to: " << ip << " (Safe website)" << endl;
    resetColor();
    
    ip = dns.lookup("bank.com");
    setGreen();
    cout << "User typed 'bank.com' -> Resolved to: " << ip << " (Safe website)" << endl;
    resetColor();
    
    cout << "\nPress Enter to continue...";
    cin.get();
    
    // STEP 3: Attacker poisons the cache
    cout << "\n--- STEP 3: ATTACKER performs DNS Cache Poisoning ---" << endl;
    dns.poisonCache("bank.com", "5.5.5.5");
    
    dns.showCache();
    
    cout << "Press Enter to continue...";
    cin.get();
    
    // STEP 4: User is redirected to fake website
    cout << "\n--- STEP 4: User tries to access bank.com AFTER poisoning ---" << endl;
    ip = dns.lookup("bank.com");
    setRed();
    cout << "User typed 'bank.com' -> Resolved to: " << ip << endl;
    cout << "\n[!!!] CRITICAL: User is now on FAKE banking website!" << endl;
    cout << "[!!!] Attacker can steal usernames, passwords, and money!" << endl;
    resetColor();
    
    cout << "\nPress Enter to continue...";
    cin.get();
    
    // STEP 5: Defense mechanisms
    cout << "\n--- STEP 5: Defense Mechanisms against DNS Cache Poisoning ---" << endl;
    
    setGreen();
    cout << "\n1. DNSSEC (DNS Security Extensions)" << endl;
    resetColor();
    cout << "   - Adds digital signatures to DNS records" << endl;
    cout << "   - Verifies that DNS responses are authentic" << endl;
    
    setGreen();
    cout << "\n2. Randomize Source Ports and Transaction IDs" << endl;
    resetColor();
    cout << "   - Makes it harder for attackers to guess query IDs" << endl;
    
    setGreen();
    cout << "\n3. Short TTL Values" << endl;
    resetColor();
    cout << "   - Reduces the time poisoned records stay in cache" << endl;
    
    setGreen();
    cout << "\n4. DNS over HTTPS (DoH) / DNS over TLS (DoT)" << endl;
    resetColor();
    cout << "   - Encrypts DNS queries to prevent interception" << endl;
    
    setYellow();
    cout << "\n========================================" << endl;
    cout << "         SIMULATION COMPLETE" << endl;
    cout << "========================================" << endl;
    resetColor();
    
    setGreen();
    cout << "\nThank you for using DNS Cache Poisoning Simulator" << endl;
    resetColor();
    setRed();
    cout << "Educational purposes only - Never attack real systems" << endl;
    resetColor();
    
    cout << "\n";
    return 0;
}