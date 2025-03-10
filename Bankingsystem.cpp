#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

class Account {
public:
    string accountNumber;
    string name;
    double balance;

    Account() {}
    Account(string accNum, string accName, double accBalance) {
        accountNumber = accNum;
        name = accName;
        balance = accBalance;
    }

    void displayDetails() {
        cout << "\n--------------------------------------" << endl;
        cout << " Account Number   : " << accountNumber << endl;
        cout << " Account Holder   : " << name << endl;
        cout << " Available Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "--------------------------------------\n" << endl;
    }
};

class BankingSystem {
private:
    vector<Account> accounts;

    string generateAccountNumber() {
        srand(time(0) + accounts.size());
        int randomNum = 1000 + rand() % 9000; // Generates a random number between 1000 and 9999
        return "ACC" + to_string(randomNum);
    }

    void saveAccountsToFile() {
        ofstream file("accounts.txt", ios::trunc);
        for (auto& acc : accounts) {
            file << acc.accountNumber << " " << acc.name << " " << acc.balance << endl;
        }
        file.close();
    }

    void loadAccountsFromFile() {
        ifstream file("accounts.txt");
        accounts.clear();
        string accNum, accName;
        double accBalance;
        while (file >> accNum >> accName >> accBalance) {
            accounts.push_back(Account(accNum, accName, accBalance));
        }
        file.close();
    }

public:
    BankingSystem() {
        loadAccountsFromFile();
    }

    void createAccount() {
        string accName;
        double initialDeposit;
        cout << "\nEnter Account Holder Name: ";
        cin >> accName;
        cout << "Enter Initial Deposit Amount: $";
        cin >> initialDeposit;
        string accNum = generateAccountNumber();
        accounts.push_back(Account(accNum, accName, initialDeposit));
        saveAccountsToFile();
        cout << "\nAccount created successfully!" << endl;
        cout << "Your Account Number is: " << accNum << "\n" << endl;
    }

    void depositMoney() {
        string accNum;
        double amount;
        cout << "\nEnter Account Number: ";
        cin >> accNum;
        for (auto& acc : accounts) {
            if (acc.accountNumber == accNum) {
                cout << "Enter Amount to Deposit: $";
                cin >> amount;
                acc.balance += amount;
                saveAccountsToFile();
                cout << "\nAmount deposited successfully!\n" << endl;
                acc.displayDetails();
                return;
            }
        }
        cout << "\nAccount not found!\n" << endl;
    }

    void withdrawMoney() {
        string accNum;
        double amount;
        cout << "\nEnter Account Number: ";
        cin >> accNum;
        for (auto& acc : accounts) {
            if (acc.accountNumber == accNum) {
                cout << "Enter Amount to Withdraw: $";
                cin >> amount;
                if (amount > acc.balance) {
                    cout << "\nInsufficient funds!\n" << endl;
                } else {
                    acc.balance -= amount;
                    saveAccountsToFile();
                    cout << "\nWithdrawal successful!\n" << endl;
                    acc.displayDetails();
                }
                return;
            }
        }
        cout << "\nAccount not found!\n" << endl;
    }

    void checkBalance() {
        string accNum;
        cout << "\nEnter Account Number: ";
        cin >> accNum;
        for (auto& acc : accounts) {
            if (acc.accountNumber == accNum) {
                acc.displayDetails();
                return;
            }
        }
        cout << "\nAccount not found!\n" << endl;
    }

    void prepopulateAccounts() {
        accounts.push_back(Account("ACC1001", "Alice", 500000.00));
        accounts.push_back(Account("ACC1002", "Bob", 300045.50));
        accounts.push_back(Account("ACC1003", "Charlie", 700260.75));
        accounts.push_back(Account("ACC1004", "David", 2500.30));
        accounts.push_back(Account("ACC1005", "ELITE", 2500.30));
        accounts.push_back(Account("ACC1006", "GIMI", 2500.30));
        accounts.push_back(Account("ACC1007", "ANUSHRI", 2500.30));
        accounts.push_back(Account("ACC1008", "PIDDI", 2500.30));
        saveAccountsToFile();
    }

    void run() {
        prepopulateAccounts();
        int choice;
        do {
            cout << "\n===================================" << endl;
            cout << "        BANKING SYSTEM MENU        " << endl;
            cout << "===================================" << endl;
            cout << " 1. Create Account" << endl;
            cout << " 2. Deposit Money" << endl;
            cout << " 3. Withdraw Money" << endl;
            cout << " 4. Check Balance" << endl;
            cout << " 5. Exit" << endl;
            cout << "===================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice) {
                case 1: createAccount(); break;
                case 2: depositMoney(); break;
                case 3: withdrawMoney(); break;
                case 4: checkBalance(); break;
                case 5: cout << "\nThank you for using our Banking System! Goodbye.\n" << endl; break;
                default: cout << "\nInvalid choice! Please try again.\n" << endl;
            }
        } while (choice != 5);
    }
};

int main() {
    BankingSystem bank;
    bank.run();
    return 0;
}