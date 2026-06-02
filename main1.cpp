#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

// ================================================================
//  MEMBER 1 — Linked List, Stack (Undo), Queue
// ================================================================

struct Passenger {
    int id, age;
    string name, flightNo, seat;
    Passenger* next;
    Passenger(int i, string n, string f, string s, int a)
        : id(i), name(n), flightNo(f), seat(s), age(a), next(nullptr) {}
};

// ── Singly Linked List ──────────────────────────────────────────
class PassengerList {
public:
    Passenger* head;
    int count;

    PassengerList() : head(nullptr), count(0) {}

    void add(int id, string name, string fno, string seat, int age) {
        Passenger* p = new Passenger(id, name, fno, seat, age);
        if (!head) {
            head = p;
        } else {
            Passenger* t = head;
            while (t->next) t = t->next;
            t->next = p;
        }
        count++;
        cout << "[+] Passenger '" << name << "' added.\n";
    }

    bool remove(int id) {
        if (!head) return false;
        if (head->id == id) {
            Passenger* t = head;
            head = head->next;
            delete t;
            count--;
            return true;
        }
        Passenger* c = head;
        while (c->next && c->next->id != id) c = c->next;
        if (!c->next) return false;
        Passenger* t = c->next;
        c->next = t->next;
        delete t;
        count--;
        return true;
    }

    Passenger* findById(int id) {
        Passenger* c = head;
        while (c) {
            if (c->id == id) return c;
            c = c->next;
        }
        return nullptr;
    }

    void display() {
        if (!head) { cout << "  (no passengers)\n"; return; }
        cout << "\n  ID    Name                Flight    Seat    Age\n";
        cout << "  " << string(50, '-') << "\n";
        Passenger* c = head;
        while (c) {
            printf("  %-6d%-20s%-10s%-8s%d\n",
                   c->id, c->name.c_str(), c->flightNo.c_str(),
                   c->seat.c_str(), c->age);
            c = c->next;
        }
    }

    vector<Passenger*> toVector() {
        vector<Passenger*> v;
        Passenger* c = head;
        while (c) { v.push_back(c); c = c->next; }
        return v;
    }

    ~PassengerList() {
        while (head) { Passenger* t = head; head = head->next; delete t; }
    }
};

// ── Stack — Undo Operations ─────────────────────────────────────
struct UndoAction {
    string type; // "ADD" or "DEL"
    int id, age;
    string name, fno, seat;
};

class UndoStack {
    stack<UndoAction> stk;
public:
    void push(string type, int id, string n, string f, string s, int a) {
        stk.push({type, id, a, n, f, s});
    }
    void undo(PassengerList& pl) {
        if (stk.empty()) { cout << "Nothing to undo!\n"; return; }
        UndoAction a = stk.top(); stk.pop();
        if (a.type == "ADD") {
            pl.remove(a.id);
            cout << "[Undo] Removed passenger '" << a.name << "'\n";
        } else {
            pl.add(a.id, a.name, a.fno, a.seat, a.age);
            cout << "[Undo] Restored passenger '" << a.name << "'\n";
        }
    }
};

// ── Queue — Flight Scheduling ───────────────────────────────────
struct FlightEntry { string no, dest, time; };

class FlightQueue {
    queue<FlightEntry> q;
public:
    void schedule(string no, string dest, string time) {
        q.push({no, dest, time});
        cout << "[Queue] Flight " << no << " to " << dest << " @ " << time << " scheduled.\n";
    }
    void processNext() {
        if (q.empty()) { cout << "Queue empty.\n"; return; }
        FlightEntry f = q.front(); q.pop();
        cout << "[Dequeue] Boarding: " << f.no << " -> " << f.dest << " @ " << f.time << "\n";
    }
    void display() {
        if (q.empty()) { cout << "  (no flights in queue)\n"; return; }
        queue<FlightEntry> tmp = q;
        cout << "\n  --- Scheduled Flights ---\n";
        int i = 1;
        while (!tmp.empty()) {
            FlightEntry f = tmp.front(); tmp.pop();
            cout << "  " << i++ << ". " << f.no << " -> " << f.dest << " @ " << f.time << "\n";
        }
    }
};


// 
//  MEMBER 2 — Searching & Sorting
//

class Algorithms {
public:

    // Linear Search  O(n)
    static Passenger* linearSearch(vector<Passenger*>& v, const string& name) {
        for (auto p : v)
            if (p->name == name) return p;
        return nullptr;
    }

    // Binary Search  O(log n) — vector must be sorted by ID first
    static Passenger* binarySearch(vector<Passenger*>& v, int id) {
        int lo = 0, hi = (int)v.size() - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (v[mid]->id == id)     return v[mid];
            else if (v[mid]->id < id) lo = mid + 1;
            else                       hi = mid - 1;
        }
        return nullptr;
    }

    // Merge Sort by Name  O(n log n)
    static void mergeSort(vector<Passenger*>& v, int l, int r) {
        if (l >= r) return;
        int m = (l + r) / 2;
        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);
        merge_(v, l, m, r);
    }
    static void merge_(vector<Passenger*>& v, int l, int m, int r) {
        vector<Passenger*> L(v.begin() + l, v.begin() + m + 1);
        vector<Passenger*> R(v.begin() + m + 1, v.begin() + r + 1);
        int i = 0, j = 0, k = l;
        while (i < (int)L.size() && j < (int)R.size())
            v[k++] = (L[i]->name <= R[j]->name) ? L[i++] : R[j++];
        while (i < (int)L.size()) v[k++] = L[i++];
        while (j < (int)R.size()) v[k++] = R[j++];
    }

    // Quick Sort by ID  O(n log n) avg
    static void quickSort(vector<Passenger*>& v, int l, int r) {
        if (l >= r) return;
        int p = partition_(v, l, r);
        quickSort(v, l, p - 1);
        quickSort(v, p + 1, r);
    }
    static int partition_(vector<Passenger*>& v, int l, int r) {
        int pivot = v[r]->id, i = l - 1;
        for (int j = l; j < r; j++)
            if (v[j]->id <= pivot) swap(v[++i], v[j]);
        swap(v[i + 1], v[r]);
        return i + 1;
    }

    // Insertion Sort by Age  O(n²)
    static void insertionSort(vector<Passenger*>& v) {
        for (int i = 1; i < (int)v.size(); i++) {
            Passenger* key = v[i];
            int j = i - 1;
            while (j >= 0 && v[j]->age > key->age) { v[j + 1] = v[j]; j--; }
            v[j + 1] = key;
        }
    }

    static void printSorted(vector<Passenger*>& v, const string& by) {
        cout << "\n  --- Sorted by " << by << " ---\n";
        for (auto p : v)
            cout << "  ID:" << p->id << "  Name:" << p->name
                 << "  Flight:" << p->flightNo << "  Age:" << p->age << "\n";
    }

    // Big O Table
    static void bigO() {
        cout << "\n  Algorithm         Best        Worst       Space\n";
        cout << "  " << string(55, '-') << "\n";
        printf("  %-18s%-12s%-12s%s\n", "Linear Search",  "O(1)",       "O(n)",       "O(1)");
        printf("  %-18s%-12s%-12s%s\n", "Binary Search",  "O(1)",       "O(log n)",   "O(1)");
        printf("  %-18s%-12s%-12s%s\n", "Insertion Sort", "O(n)",       "O(n^2)",     "O(1)");
        printf("  %-18s%-12s%-12s%s\n", "Merge Sort",     "O(n log n)", "O(n log n)", "O(n)");
        printf("  %-18s%-12s%-12s%s\n", "Quick Sort",     "O(n log n)", "O(n^2)",     "O(log n)");
        printf("  %-18s%-12s%-12s%s\n", "BST Insert",     "O(log n)",   "O(n)",       "O(1)");
        printf("  %-18s%-12s%-12s%s\n", "BFS / DFS",      "O(V+E)",     "O(V+E)",     "O(V)");
        printf("  %-18s%-12s%-12s%s\n", "Linked List Add","O(1)",       "O(n)",       "O(1)");
        printf("  %-18s%-12s%-12s%s\n", "Stack Push/Pop", "O(1)",       "O(1)",       "O(1)");
        printf("  %-18s%-12s%-12s%s\n", "Queue Enq/Deq",  "O(1)",       "O(1)",       "O(1)");
        cout << "  " << string(55, '-') << "\n";
    }
};


// ================================================================
//  MEMBER 3 — BST (Flights), Graph Routes, BFS, DFS
// ================================================================

// ── BST — Flight Hierarchy ───────────────────────────────────────
struct BSTNode {
    int id, seats;
    string no, dest;
    BSTNode *l, *r;
    BSTNode(int i, string n, string d, int s)
        : id(i), no(n), dest(d), seats(s), l(nullptr), r(nullptr) {}
};

class FlightBST {
    BSTNode* root = nullptr;

    BSTNode* insert(BSTNode* node, int id, string no, string dest, int seats) {
        if (!node) return new BSTNode(id, no, dest, seats);
        if (id < node->id) node->l = insert(node->l, id, no, dest, seats);
        else if (id > node->id) node->r = insert(node->r, id, no, dest, seats);
        return node;
    }

    BSTNode* search(BSTNode* node, int id) {
        if (!node || node->id == id) return node;
        return id < node->id ? search(node->l, id) : search(node->r, id);
    }

    void inorder(BSTNode* node) {
        if (!node) return;
        inorder(node->l);
        cout << "  ID:" << node->id << "  Flight:" << node->no
             << "  Dest:" << node->dest << "  Seats:" << node->seats << "\n";
        inorder(node->r);
    }

public:
    void insert(int id, string no, string dest, int seats) {
        root = insert(root, id, no, dest, seats);
        cout << "[BST] Flight " << no << " inserted.\n";
    }
    void search(int id) {
        BSTNode* r = search(root, id);
        if (r) cout << "  Found -> " << r->no << " to " << r->dest << " | Seats: " << r->seats << "\n";
        else   cout << "  Flight ID " << id << " not found.\n";
    }
    void display() {
        cout << "\n  --- BST Flights (Inorder) ---\n";
        inorder(root);
    }
};

// ── Weighted Graph — Airline Routes ──────────────────────────────
class AirlineGraph {
    static const int MAXV = 6;
    string cities[MAXV];
    vector<pair<int, int>> adj[MAXV]; // {neighbor, distance_km}

public:
    AirlineGraph() {
        cities[0] = "Mumbai";    cities[1] = "Delhi";
        cities[2] = "Bangalore"; cities[3] = "Chennai";
        cities[4] = "Kolkata";   cities[5] = "Hyderabad";
    }

    void addRoute(int u, int v, int d) {
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
        cout << "[Graph] Route: " << cities[u] << " <-> " << cities[v]
             << " (" << d << " km)\n";
    }

    // BFS — minimum hops
    void BFS(int src) {
        cout << "\n  BFS from " << cities[src] << ": ";
        vector<bool> vis(MAXV, false);
        queue<int> q;
        vis[src] = true; q.push(src);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            cout << cities[u] << " ";
            for (auto [v, w] : adj[u])
                if (!vis[v]) { vis[v] = true; q.push(v); }
        }
        cout << "\n";
    }

    // DFS — all reachable cities
    void DFS(int src) {
        cout << "\n  DFS from " << cities[src] << ": ";
        vector<bool> vis(MAXV, false);
        dfsHelper(src, vis);
        cout << "\n";
    }

    void dfsHelper(int u, vector<bool>& vis) {
        vis[u] = true;
        cout << cities[u] << " ";
        for (auto [v, w] : adj[u])
            if (!vis[v]) dfsHelper(v, vis);
    }
};


// ================================================================
//  MAIN — Menu Driver
// ================================================================

void menu() {
    cout << "\n===== AIRLINE RESERVATION SYSTEM =====\n";
    cout << " [MEMBER 1 — Data Structures]\n";
    cout << "  1.  Add Passenger\n";
    cout << "  2.  Delete Passenger\n";
    cout << "  3.  Display All Passengers\n";
    cout << "  4.  Undo Last Operation\n";
    cout << "  5.  Schedule Flight (Enqueue)\n";
    cout << "  6.  Board Next Flight (Dequeue)\n";
    cout << "  7.  View Flight Queue\n";
    cout << " [MEMBER 2 — Search & Sort]\n";
    cout << "  8.  Linear Search by Name\n";
    cout << "  9.  Binary Search by ID\n";
    cout << "  10. Sort by Name (Merge Sort)\n";
    cout << "  11. Sort by ID   (Quick Sort)\n";
    cout << "  12. Sort by Age  (Insertion Sort)\n";
    cout << "  13. Show Big O Table\n";
    cout << " [MEMBER 3 — Trees & Graphs]\n";
    cout << "  14. Add Flight to BST\n";
    cout << "  15. Search Flight in BST\n";
    cout << "  16. Display BST (Inorder)\n";
    cout << "  17. BFS on Route Graph\n";
    cout << "  18. DFS on Route Graph\n";
    cout << "  0.  Exit\n";
    cout << "=======================================\n";
    cout << "Choice: ";
}

int main() {
    PassengerList pl;
    UndoStack     undo;
    FlightQueue   fq;
    FlightBST     bst;
    AirlineGraph  g;

    cout << "\n[System] Initializing route graph...\n";
    g.addRoute(0, 1, 1400); // Mumbai - Delhi
    g.addRoute(0, 2, 980);  // Mumbai - Bangalore
    g.addRoute(0, 5, 710);  // Mumbai - Hyderabad
    g.addRoute(1, 4, 1300); // Delhi - Kolkata
    g.addRoute(2, 3, 350);  // Bangalore - Chennai
    g.addRoute(3, 5, 620);  // Chennai - Hyderabad
    g.addRoute(1, 5, 1500); // Delhi - Hyderabad

    int ch;
    do {
        menu();
        cin >> ch; cin.ignore();

        switch (ch) {

        // ── MEMBER 1 ────────────────────────────────────────────
        case 1: {
            int id, age; string name, fno, seat;
            cout << "ID: ";      cin >> id;       cin.ignore();
            cout << "Name: ";    getline(cin, name);
            cout << "Flight#: "; getline(cin, fno);
            cout << "Seat: ";    getline(cin, seat);
            cout << "Age: ";     cin >> age;      cin.ignore();
            pl.add(id, name, fno, seat, age);
            undo.push("ADD", id, name, fno, seat, age);
            break;
        }
        case 2: {
            int id; cout << "Passenger ID to delete: "; cin >> id;
            Passenger* p = pl.findById(id);
            if (p) {
                undo.push("DEL", p->id, p->name, p->flightNo, p->seat, p->age);
                pl.remove(id);
                cout << "[-] Deleted.\n";
            } else {
                cout << "Not found.\n";
            }
            break;
        }
        case 3: pl.display(); break;
        case 4: undo.undo(pl); break;
        case 5: {
            string no, dest, t;
            cout << "Flight#: "; getline(cin, no);
            cout << "Dest: ";    getline(cin, dest);
            cout << "Time: ";    getline(cin, t);
            fq.schedule(no, dest, t);
            break;
        }
        case 6: fq.processNext(); break;
        case 7: fq.display(); break;

        // ── MEMBER 2 ────────────────────────────────────────────
        case 8: {
            string name; cout << "Name to search: "; getline(cin, name);
            auto v = pl.toVector();
            Passenger* r = Algorithms::linearSearch(v, name);
            if (r) cout << "  Found -> " << r->name << " | Flight: " << r->flightNo << "\n";
            else   cout << "  Not found.\n";
            break;
        }
        case 9: {
            int id; cout << "ID to search: "; cin >> id;
            auto v = pl.toVector();
            sort(v.begin(), v.end(), [](Passenger* a, Passenger* b) { return a->id < b->id; });
            Passenger* r = Algorithms::binarySearch(v, id);
            if (r) cout << "  Found -> " << r->name << " | Flight: " << r->flightNo << "\n";
            else   cout << "  Not found.\n";
            break;
        }
        case 10: {
            auto v = pl.toVector();
            if (v.empty()) { cout << "No passengers.\n"; break; }
            Algorithms::mergeSort(v, 0, (int)v.size() - 1);
            Algorithms::printSorted(v, "Name (Merge Sort)");
            break;
        }
        case 11: {
            auto v = pl.toVector();
            if (v.empty()) { cout << "No passengers.\n"; break; }
            Algorithms::quickSort(v, 0, (int)v.size() - 1);
            Algorithms::printSorted(v, "ID (Quick Sort)");
            break;
        }
        case 12: {
            auto v = pl.toVector();
            if (v.empty()) { cout << "No passengers.\n"; break; }
            Algorithms::insertionSort(v);
            Algorithms::printSorted(v, "Age (Insertion Sort)");
            break;
        }
        case 13: Algorithms::bigO(); break;

        // ── MEMBER 3 ────────────────────────────────────────────
        case 14: {
            int id, seats; string no, dest;
            cout << "Flight ID: "; cin >> id;    cin.ignore();
            cout << "Flight#: ";   getline(cin, no);
            cout << "Dest: ";      getline(cin, dest);
            cout << "Seats: ";     cin >> seats;
            bst.insert(id, no, dest, seats);
            break;
        }
        case 15: {
            int id; cout << "Flight ID: "; cin >> id;
            bst.search(id);
            break;
        }
        case 16: bst.display(); break;
        case 17: {
            cout << "  0-Mumbai  1-Delhi  2-Bangalore  3-Chennai  4-Kolkata  5-Hyderabad\n";
            int s; cout << "  Source: "; cin >> s;
            if (s >= 0 && s < 6) g.BFS(s); else cout << "Invalid.\n";
            break;
        }
        case 18: {
            cout << "  0-Mumbai  1-Delhi  2-Bangalore  3-Chennai  4-Kolkata  5-Hyderabad\n";
            int s; cout << "  Source: "; cin >> s;
            if (s >= 0 && s < 6) g.DFS(s); else cout << "Invalid.\n";
            break;
        }
        case 0: cout << "\nThank you! Safe travels.\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (ch != 0);

    return 0;
}