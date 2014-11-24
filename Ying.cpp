#include <iostream>
#include <vector>
using namespace std;

typedef char ElemType;
typedef vector<vector<ElemType> > Fig;
typedef vector<ElemType> Line;
const char Space = -10;
const char Left = '/';
const char Right = '\\';

struct Tree
{
	Tree* left, *right;
	ElemType data;
	Tree(const ElemType& d, Tree* L=NULL, Tree* R=NULL)
	:data(d), left(L), right(R){}
};

Fig Merge(const Fig& L, const Fig& R, const ElemType& RootData){
	int LeftBound = 0, RightBound = 0;
	if(L.size() != 0)
		LeftBound = L[0].size();
	if(R.size() != 0)
		RightBound = R[0].size();
//cout << LeftBound << ' ' << RightBound << endl;
//int a; cin >> a;
	if(LeftBound == 0 && RightBound == 0){
		Fig ans;
		Line a;
		a.push_back(RootData);
		ans.push_back(a);
		return ans;
	}
	else{
		Fig ans;
		Line a, b;
		for(int i=0; i<LeftBound; ++i){
			a.push_back(Space);
			b.push_back(Space);
		}
		a.push_back(Space);
		if(LeftBound != 0) b.push_back(Left);
		a.push_back(RootData);
		b.push_back(Space);
		a.push_back(Space);
		if(RightBound != 0) b.push_back(Right);
		for(int i=0; i<RightBound; ++i){
			a.push_back(Space);
			b.push_back(Space);
		}
		ans.push_back(a);
		ans.push_back(b);
		int LeftHeight = L.size(), RightHeight = R.size();
		int Height = max(LeftHeight, RightHeight);
//cout << "Height: " << LeftHeight << ' ' << RightHeight << ' ' << Height << endl;
//int c; cin >> c;
		for(int i=0; i<Height; ++i){
			Line temp;
			for(int j=0; j<LeftBound; ++j){
				if(i >= LeftHeight)
					temp.push_back(Space);
				else temp.push_back(L[i][j]);
			}
			temp.push_back(Space);temp.push_back(Space);temp.push_back(Space);
			for(int j=0; j<RightBound; ++j){
				if(i >= RightHeight)
					temp.push_back(Space);
				else temp.push_back(R[i][j]);
			}
			ans.push_back(temp);
		}
		return ans;
	}
}
void PrintFig(const Fig& fig){
	//cout << "hahaa: " << fig.size() << endl;
	for(int row = 0; row < fig.size(); ++row){
		for(int col = 0; col < fig[row].size(); ++col){
			switch(fig[row][col]){
				case Space: cout << ' '; break;
				case Left: cout << '/'; break;
				case Right: cout << '\\'; break;
				default: cout << fig[row][col]; break;
			}
		}
		cout << endl;
	}
}
Fig getFig(Tree* root){
	if(root == NULL)
		return Fig();
	Fig L = getFig(root->left);
	Fig R = getFig(root->right);
	Fig ans(Merge(L, R, root->data));
	return ans;
}

int main(){
	Tree* left1 = new Tree('A');
	//Tree* right1 = new Tree('B');
	Tree* left2 = new Tree('C');
	Tree* right2 = new Tree('D');
	Tree* left = new Tree('E', left1);
	//Tree* left = new Tree('E', left1, right1);
	Tree* right = new Tree('F', left2, right2);
	Tree* root = new Tree('H', left, right);
	PrintFig(getFig(root));
	return 0;
}
