#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string name;
    bool done;
};

struct Day {
    int date;
    vector<Task> tasks;
};

// Load data
void loadData(vector<Day> &month) {
    ifstream file("progress.txt");
    if (!file) return;

    for (auto &day : month) {
        for (auto &task : day.tasks) {
            file >> task.done;
        }
    }
    file.close();
}

// Save data
void saveData(vector<Day> &month) {
    ofstream file("progress.txt");

    for (auto &day : month) {
        for (auto &task : day.tasks) {
            file << task.done << " ";
        }
        file << endl;
    }

    file.close();
}

// Calculate percentage for a day
double dayPercentage(Day &day) {
    int done = 0;
    for (auto &task : day.tasks) {
        if (task.done) done++;
    }
    return (done * 100.0) / day.tasks.size();
}

// Calculate full month percentage
double monthPercentage(vector<Day> &month) {
    int total = 0, done = 0;

    for (auto &day : month) {
        for (auto &task : day.tasks) {
            total++;
            if (task.done) done++;
        }
    }

    return (done * 100.0) / total;
}

// Show planner
void showPlanner(vector<Day> &month) {
    for (auto &day : month) {
        cout << "\n📅 April " << day.date;
        cout << " (" << dayPercentage(day) << "% complete)\n";

        for (int i = 0; i < day.tasks.size(); i++) {
            cout << i + 1 << ". "
                 << (day.tasks[i].done ? "[✔] " : "[ ] ")
                 << day.tasks[i].name << endl;
        }
    }

    cout << "\n📊 Overall April Progress: "
         << monthPercentage(month) << "%\n";
}

// Mark task ✔ or ❌
void updateTask(vector<Day> &month) {
    int d, t, choice;

    cout << "\nEnter date (3-30): ";
    cin >> d;

    for (auto &day : month) {
        if (day.date == d) {
            cout << "\nTasks:\n";
            for (int i = 0; i < day.tasks.size(); i++) {
                cout << i + 1 << ". "
                     << (day.tasks[i].done ? "[✔] " : "[ ] ")
                     << day.tasks[i].name << endl;
            }

            cout << "\nEnter task number: ";
            cin >> t;

            cout << "1. Mark ✔ Complete\n2. Mark ❌ Incomplete\nChoice: ";
            cin >> choice;

            if (t > 0 && t <= day.tasks.size()) {
                if (choice == 1) {
                    day.tasks[t - 1].done = true;
                    cout << "✅ Marked Complete!\n";
                } else {
                    day.tasks[t - 1].done = false;
                    cout << "❌ Marked Incomplete!\n";
                }
            }
        }
    }
}

// Create planner
vector<Day> createPlanner() {
    vector<Day> month;

    for (int i = 3; i <= 30; i++) {
        Day d;
        d.date = i;

        // Daily tasks
        d.tasks.push_back({"Morning Walk (1 hr)", false});
        d.tasks.push_back({"Evening Walk (1 hr)", false});
        d.tasks.push_back({"DSA (3 Questions)", false});
        d.tasks.push_back({"ML Lecture", false});
        d.tasks.push_back({"Excel/SQL Practice", false});
        d.tasks.push_back({"Internship Apply", false});
        d.tasks.push_back({"❤️ Night Phone Discipline", false});

        // Special tasks
        if (i == 3) {
            d.tasks.push_back({"AI Unit 1", false});
            d.tasks.push_back({"AI Lab Practical", false});
            d.tasks.push_back({"Case Study Prep (3-6 PM)", false});
        }
        else if (i == 4) {
            d.tasks.push_back({"AI Unit 2", false});
            d.tasks.push_back({"Matrices + 3D", false});
            d.tasks.push_back({"Excel Advanced", false});
        }
        else if (i == 5) {
            d.tasks.push_back({"AI Unit 3", false});
            d.tasks.push_back({"Sparse Matrix", false});
            d.tasks.push_back({"Case Study Practice", false});
        }
        else if (i == 6) {
            d.tasks.push_back({"AI Unit 6", false});
            d.tasks.push_back({"SQL Practice", false});
            d.tasks.push_back({"Mock Interview", false});
        }
        else if (i == 7) {
            d.tasks.push_back({"Interview Day", false});
        }
        else {
            d.tasks.push_back({"Subject Unit / Revision", false});
        }

        month.push_back(d);
    }

    return month;
}

// Main menu
int main() {
    vector<Day> planner = createPlanner();
    loadData(planner);

    int choice;

    do {
        cout << "\n====== APRIL PLANNER ======\n";
        cout << "1. Show Planner\n";
        cout << "2. Update Task (✔ / ❌)\n";
        cout << "3. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                showPlanner(planner);
                break;
            case 2:
                updateTask(planner);
                break;
            case 3:
                saveData(planner);
                cout << "📁 Progress saved!\n";
                break;
        }

    } while (choice != 3);

    return 0;
}
