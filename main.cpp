#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

vector<queue<int> > men, women; //priority lists
vector<string> findmname, findwname;
map<string, int> mnames, wnames;
vector<vector<int> > prior; //priotity of every man for every woman
vector<bool> in_search; //men's status
vector<int> variant; //potentian women's husbands
int ins(0); //amount of men in active search

void break_up(int M)
{
  men[M].pop();
  if (!in_search[M]) {
    in_search[M] = true;
    ins++;
  }
  if (men[M].empty()) {
    in_search[M] = false;
    ins--;
  }
}

void go_to_a_date(int M, int W)
{
  int maybe = variant[W];
  //checking if M is appropriate for W
  if (maybe == -1 || prior[maybe][W] < prior[M][W]) {
    variant[W] = M;
    in_search[M] = false;
    ins--;
    if (maybe > -1) {
      break_up(maybe);
    }
  }
  else {
    break_up(M);
  }
}

int main() {

  freopen("priority.txt", "r", stdin);
  freopen("marriage.txt", "w", stdout);

  int n;
  cin >> n;
  men.resize(n);
  prior.assign(n, vector<int>(n, -1));
  in_search.assign(n, true);
  variant.assign(n, -1);
  findmname.assign(n, "");
  findwname.assign(n, "");
  ins = n;

  string name, pretender;
  int nnumb, pnumb;
  for (int i(0); i < n; ++i) {
    cin >> name;
    nnumb = mnames.size();
    mnames[name] = nnumb;
    findmname[nnumb] = name;
    for (int j(0); j < n; ++j) {
      cin >> pretender;
      if (wnames.find(pretender) == wnames.end()) {
        pnumb = wnames.size();
        wnames[pretender] = pnumb;
        findwname[pnumb] = pretender;
      }
      else {
        pnumb = wnames[pretender];
      }
      men[nnumb].push(pnumb);
    }
  }

  for (int i(0); i < n; ++i) {
    cin >> name;
    nnumb = wnames[name];
    findwname[nnumb] = name;
    for (int j(0); j < n; ++j) {
      cin >> pretender;
      pnumb = mnames[pretender];
      prior[pnumb][nnumb] = j;
    }
  }

  while (ins > 0) {
    for (int i(0); i < n; ++i) {
      if (!in_search[i]) {
        continue;
      }
      go_to_a_date(i, men[i].front());
    }
  }

  for (int i(0); i < n; ++i) {
    string wom = findwname[i];
    string m = findmname[variant[i]];
    cout << wom << " and " << m << " together forever\n";
  }

  return 0;
}