#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct angsort{
  ll x;
  ll y;
};

ll cross(angsort p,angsort q){
  return p.x * q.y - q.x * p.y;
}

bool cmp(angsort p,angsort q){
  bool pispos = (p.x > 0 || (p.x == 0 && p.y > 0));
  bool qispos = (q.x > 0 || (q.x == 0 && q.y > 0));
  if(pispos != qispos){
    if(qispos) return true;
    else return false;
  }
  else return cross(p,q) > 0;
}

bool eql(angsort p,angsort q){
  bool pispos = (p.x > 0 || (p.x == 0 && p.y > 0));
  bool qispos = (q.x > 0 || (q.x == 0 && q.y > 0));
  if(pispos != qispos) return false;
  else return cross(p,q) == 0;
}