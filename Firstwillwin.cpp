#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;

class CardGame {
private:
    int n;  // total cards
    int m;  // max cards per draw
    int remain;

    int aiMove() {
        int base = (m + 1);
        int mod = remain % base;
        if (mod == 0) {
            return (rand() % m) + 1;
        }
        return mod;
    }

    int playerMove(int x) {
        if (x < 1 || x > m) return -1;
        if (x > remain) return -2;
        return x;
    }

public:
    void setRule(int n_, int m_) {
        n = n_;
        m = m_;
        remain = n;
        srand(time(0));
    }

    void showRule() {
        cout << "================ Game Rule ================" << endl;
        cout << "Initial cards: " << n << endl;
        cout << "Each player draws 1 ~ " << m << " cards each turn" << endl;
        cout << "The player who draws the last card loses!" << endl;
        cout << "===========================================" << endl;
    }

    bool draw(int cards) {
        if (cards < 1 || cards > m) {
            cout << "Invalid! Must draw 1 ~ " << m << " cards." << endl;
            return false;
        }
        if (cards > remain) {
            cout << "Invalid! Only " << remain << " cards left." << endl;
            return false;
        }
        remain -= cards;
        return true;
    }

    int getRemain() { return remain; }

    bool isEnd() { return remain == 0; }

    string aiThink() {
        int base = (m + 1);
        int mod = remain % base;
        ostringstream oss;

        if (mod == 0) {
            int cards = (rand() % m) + 1;
            oss << "AI draws " << cards << " card(s). (AI is in a losing position...)";
            return oss.str();
        } else {
            int cards = mod;
            oss << "AI draws " << cards << " card(s). (forced to winning position)";
            return oss.str();
        }
    }

    bool playerTurn() {
        int cards;
        cout << "Your turn - draw cards (1-" << min(m, remain) << "): ";
        cin >> cards;

        if (!draw(cards)) return false;

        if (isEnd()) {
            cout << "You drew the last " << cards << " card(s)! You LOSE!" << endl;
            return true;
        }
        return false;
    }

    bool aiTurn() {
        int aiCards = aiMove();
        cout << aiThink() << endl;
        remain -= aiCards;

        if (isEnd()) {
            cout << "AI drew the last " << aiCards << " card(s)! AI LOSES! You WIN!" << endl;
            return true;
        }
        return false;
    }

    void showRemain() {
        cout << "Cards remaining: " << remain << endl;
    }

    bool isWinningPosition() {
        return (remain % (m + 1)) != 0;
    }
};

int main() {
    int n, m;
    cout << "=== Card Draw Game ===" << endl;
    cout << "Enter total cards (n): ";
    cin >> n;
    cout << "Enter max cards per draw (m, must < n): ";
    cin >> m;

    while (m >= n) {
        cout << "m must < n, re-enter m: ";
        cin >> m;
    }

    CardGame game;
    game.setRule(n, m);
    game.showRule();

    bool playerFirst = (rand() % 2 == 0);

    if (playerFirst) {
        cout << "\n*** You go first! ***" << endl;
    } else {
        cout << "\n*** AI goes first! ***" << endl;
    }

    while (true) {
        cout << "\n--- Cards remaining: " << game.getRemain() << " ---" << endl;

        if (playerFirst) {
            if (game.playerTurn()) break;
            cout << "Cards left: " << game.getRemain() << endl;
            if (game.aiTurn()) break;
        } else {
            if (game.aiTurn()) break;
            cout << "Cards left: " << game.getRemain() << endl;
            if (game.playerTurn()) break;
        }
    }

    cout << "\n========== Game Over ==========" << endl;
    return 0;
}