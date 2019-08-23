#include <bits/stdc++.h>
using namespace std;


struct node{
    int lchild, rchild;
    string val;
    char op;
    bool eval;  //是否是操作符
    node(string v , bool e  = false, int l = -1, int r = -1)
            :val(v),eval(e),lchild(l),rchild(r){}
    node(char v, bool e = true, int l = -1, int r = -1):
        op(v),eval(e),lchild(l),rchild(r){}
};
vector<node> tree;

//关于操作符的操作
map<char,int> priority = {{'+',1},{'-',1},{'*',2},{'/',2},{'^',3},{'(',100},{')',100}}; //操作符号集合
bool isop(char c){
    return priority.count(c);
}

//如果是可以计算的数字
int tonum(string num){
    return atoi(num.c_str());
}
string tostr(int num){
    stringstream ss;
    ss << num;
    string ans;
    ss >> ans;
    return ans;
}
bool isnum(string s){
    for(int i = 0; i<s.size();i++){
        if(isop(s[i])) return false; 
    }
    return true;
}
int cal(string a, string b, char op){
    int ans;
    switch (op)
    {
    case '+':
        ans =  tonum(a)+tonum(b);
        break;
    case '-':
        ans = tonum(a)-tonum(b);
        break;
    case '*':
        ans = tonum(a)*tonum(b);
        break;
    case '/':
        ans = tonum(a)/tonum(b);
        break;
    case '^':
        ans = pow(tonum(a),tonum(b));
        break;
    }
    return ans;
}


//分割建树
void clear(string &s){ 
    while(s[0]=='('){
            int cnt = 0; int i;
            for(i = 0; i<s.size();i++){
                if(s[i]=='(') cnt++;
                if(s[i]==')') cnt--;
                if(cnt==0){
                    if(i==s.size()-1) s = s.substr(1,s.size()-2);
                    else{
                        return;
                    }
                }
            }
    }
}
int getrank(char op, int cnt){
    if(!isop(op)) return 100;
    else return priority[op]+cnt*100;
}
int getmid(string s){
    int inbracket = 0;
    vector<int> r;
    for(int i = 0; i<s.size(); i++){
        if(s[i]=='(') inbracket ++; 
        if(s[i]==')') inbracket --;
        r.push_back(getrank(s[i],inbracket));
    }
    int pos;
    int minn = 99999;
    for(int i = 0; i<s.size();i++){
        if(minn>=r[i]) pos = i, minn = r[i];
    }
    return pos;
}

int build(string s){

    if(isnum(s)) {tree.push_back(node(s)); return tree.size()-1;}
    clear(s);
    int pos = getmid(s);
    string left = s.substr(0,pos);
    string right = s.substr(pos+1);
    tree.push_back(node(s[pos],true,build(left),build(right)));
    return tree.size()-1;
}
void print(int i){
        
         if(tree[i].eval) cout << tree[i].op;
        else cout << tree[i].val ;
        if(i!=tree.size()-1)cout<<" "; 
        else cout << endl ;
}
void DLR(int root){
    print(root);
    if(tree[root].lchild!=-1){
        DLR(tree[root].lchild);
    } 
    if(tree[root].rchild!=-1){
        DLR(tree[root].rchild);
    }
}
void LDR(int root){
    
    if(tree[root].lchild!=-1){
        LDR(tree[root].lchild);
    }
    print(root); 
    if(tree[root].rchild!=-1){
        LDR(tree[root].rchild);
    }
}
void LRD(int root){
    
    if(tree[root].lchild!=-1){
        LRD(tree[root].lchild);
    } 
    if(tree[root].rchild!=-1){
        LRD(tree[root].rchild);
    }
    print(root);
}

void calculate(int node){
    if(tree[node].lchild==-1) return;
    calculate(tree[node].lchild);
    calculate(tree[node].rchild);
    string a = tree[tree[node].lchild].val;
    string b = tree[tree[node].rchild].val;
    tree[node].val = tostr(cal(a,b,tree[node].op));
    tree[node].lchild = tree[node].rchild = -1;
    tree[node].eval = false;
    // LRD(tree.size()-1);
}

int main(){
    string s;
    cin >> s;
    int root = build(s);
    LRD(root);
    calculate(root);
    cout << tree[tree.size()-1].val << endl;
    return 0;
}