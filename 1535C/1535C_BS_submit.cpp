#include <iostream>

typedef long long ll;

using namespace std;
pair<ll, ll> unexpectedBranch(const int unexpected, const int st, const int pivot, const int en, const string& str) {
    pair<ll, ll> rangeLR;
    ll lenL = 0;
    int unexp = unexpected;
    for (int i = pivot; i >= st; --i) {
        if (str[i] != '0' + unexp) {
            ++lenL;
            unexp = ~unexp + 2;
        } else {
            break;
        }
    }
    rangeLR.first = lenL;
    ll lenR = 0;
    unexp = unexpected;
    for (int i = pivot; i <= en; ++i) {
        if (str[i] != '0' + unexp) {
            ++lenR;
            unexp = ~unexp + 2;
        } else {
            break;
        }
    }
    rangeLR.second = lenR;
    return rangeLR;
}
ll includedSearch(const int st, const int pivot, const int en, const string& str) {
    ll count0 = 0;
    pair<ll, ll> rangeLR0;
    if (str[pivot] != '1') {
        int unexpected = 1;
        rangeLR0 = unexpectedBranch(unexpected, st, pivot, en, str);
        count0 = rangeLR0.first * rangeLR0.second;
    }
    ll count1 = 0;
    pair<ll, ll> rangeLR1;
    if (str[pivot] != '0') {
        int unexpected = 0;
        rangeLR1 = unexpectedBranch(unexpected, st, pivot, en, str);
        count1 = rangeLR1.first * rangeLR1.second;
    }
    return count0 + count1 - min(rangeLR0.first, rangeLR1.first) * min(rangeLR0.second, rangeLR1.second);
}

ll binarySearch(const int st, const int en, const string& str) {
    if (st == en) {
        return 1LL;
    }
    ll pivot = (st + en) / 2;
    if (en - st > 1) {
        ll left = binarySearch(st, pivot-1, str);
        ll middle = includedSearch(st, pivot, en, str);
        ll right = binarySearch(pivot+1, en, str);
        return left + middle + right;
    } else {
        ll middle = includedSearch(st, pivot, en, str);
        ll right = binarySearch(pivot+1, en, str);
        return middle + right;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        string str;
        cin >> str;
        cout << binarySearch(0, str.size()-1, str) << '\n';
    }
}