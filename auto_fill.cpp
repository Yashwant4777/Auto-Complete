#include<bits/stdc++.h>
#include <fstream>
using namespace std;

vector<string> words_with_prefix;
			   					 				 
struct TrieNode{
	struct TrieNode* ch[26];
	bool wordend;
};
TrieNode* trie = new TrieNode();


void insert(string str){				
	TrieNode* node=trie;
	for(int i=0;i<str.size();++i){
		if(node->ch[str[i]-'a']==NULL){
			node->ch[str[i]-'a']=new TrieNode();
		}
		node=node->ch[str[i]-'a'];
	}
	node->wordend=true;
}

void build(){
	string word_in_list;
	ifstream word_list("word_list.txt");
	while(getline(word_list,word_in_list)){
		insert(word_in_list);
	}
	word_list.close();
}

bool search(string str){
	TrieNode* src=trie;
	for(int i=0;i<str.size();++i){
		if(src->ch[str[i]-'a']==NULL) return false;
		src=src->ch[str[i]-'a'];
	}
	if(src->wordend==true) return true;
	return false;
}

void prefix_words(TrieNode* root,string str_p){
	if(root->wordend==true){
		words_with_prefix.push_back(str_p);
	}
	int ptr=0;
	while(ptr<26){
		if(root->ch[ptr]!=NULL){
			prefix_words(root->ch[ptr],str_p+(char)(ptr+'a'));	
		}
		ptr++; 
	}
	return;
}

//bad


int main(){
	string prefix;
	cout<<"------------Enter the Prefix, of which u want words..!!--------------"<<endl;
	cin>>prefix;
	build();
	TrieNode* findword= trie;
	
	//cout<<search(prefix)<<endl;
	
	for(int j=0;j<prefix.size();++j){
		if(findword->ch[prefix[j]-'a']==NULL){
			cout<<"No Words With That Prefix Exists..!!"<<endl;
			return 0;
		}
		findword=findword->ch[prefix[j]-'a'];
	}
	prefix_words(findword,prefix);
	
	
	cout<<"----------The words are-------------"<<endl;
	for(int wrd_ptr=0;wrd_ptr<words_with_prefix.size();++wrd_ptr){
		cout<<words_with_prefix[wrd_ptr]<<endl;
	}
	
	/*ofstream myfile("output.txt");
	
	for(int wrd_ptr=0;wrd_ptr<words_with_prefix.size();++wrd_ptr){
		myfile<<words_with_prefix[wrd_ptr]<<endl;
	}
	myfile.close();*/
	return 0;
}
