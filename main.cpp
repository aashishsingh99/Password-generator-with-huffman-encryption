#include<bits/stdc++.h>
using namespace std;
char pass[100];
struct Node
{
    char ch;
    int freq;
    Node *left,*right;

};
Node* getnewNode(char ch,int freq, Node* left,Node*right)
{
    Node* node=new Node();
    node->ch=ch;
    node->freq=freq;
    node->left=left;
    node->right=right;
    return node;
}
void encoding(Node* root,string s,map<char,string> &code)
{
    if(root==NULL)
    {
        return;
    }
    if(!root->left && !root->right){
        code[root->ch]=s;
    }
    encoding(root->left,s+"0",code);
    encoding(root->right,s+"1",code);
}
void decoding(Node* root, int &i,string s)
{
    if(root==NULL)
    {
        return;
    }
    if(!root->left && !root->right)
    {
        cout<<root->ch;
        ofstream out("decodedpw.txt",fstream::app);
out<<root->ch;
out.close();
        return;
    }
    i++;
    if(s[i]=='0')
    {
        decoding(root->left,i,s);
    }
    else{
        decoding(root->right,i,s);
    }

}
struct compare
{
    bool operator()(Node* left,Node* right)
    {
        return left->freq>right->freq;
    }

};
void hufftree(string input)
{   int sum;
    map<char,int>freq;
    for(char ch:input)
    {
       freq[ch]++;
    }

priority_queue<Node*, vector<Node*>,compare>huff_pq;
for(auto pair: freq){
    huff_pq.push(getnewNode(pair.first,pair.second,nullptr,nullptr));
}
while(huff_pq.size()!=1)
{
    Node* left=huff_pq.top();
    huff_pq.pop();
    Node* right=huff_pq.top();
    huff_pq.pop();
    sum=left->freq+right->freq;
    huff_pq.push(getnewNode('\0',sum,left,right));

}
Node* root=huff_pq.top();
map<char,string>code;
encoding(root,"",code);
cout<<"\nCodes generated for each character\n"<<endl;
for(auto pair:code){
    cout<<pair.first<<"-"<<pair.second<<"\n";
}
cout<<"Your generated Password:"<<endl<<input;
string s="";
for(char ch:input){
    s=s+code[ch];
}
cout<<endl<<"after encoding\n"<<s<<endl;
ofstream out("encodedpw.txt",fstream::app);
out<<s<<endl<<endl;
out.close();
int index=-1;
cout<<"after decoding"<<endl;
while(index<(int)s.size()-2){
    decoding(root,index,s);
}
}


struct Node1{
    string num;
    Node1 *next;
};
struct Node1 *head=NULL;
void insertNode(string n){
    struct Node1 *newNode=new Node1;
    newNode->num=n;
    newNode->next=head;
    head=newNode;
}
void deleteItem(){
    if(head==NULL){
        cout<<"List is empty!"<<endl;
        return;
    }
    cout<<head->num<<" is removed."<<endl;
    head=head->next;
}
void display(){
    if(head==NULL){
        cout<<"List is empty!"<<endl;
        return;
    }
    struct Node1 *temp=head;
    while(temp!=NULL){
        cout<<temp->num<<" "<<endl;
        temp=temp->next;
    }
    cout<<endl;
}
string pickout(int c){
	struct Node1 *temp=head;
	int p=1;
	while(temp!=NULL){
		if(p==c)
		{
			return temp->num;
		}
		p++;
        temp=temp->next;
    }
}
int count(){
	int count=0;
	struct Node1 *temp=head;
    while(temp!=NULL){
        count++;
        temp=temp->next;
    }
    return count++;
}
const int TABLE_SIZE = 128;
class HashNode
{
    public:
    int key;
	string value;
	HashNode* next;
        HashNode(int key, string value)
        {
            this->key = key;
	    this->value = value;
	    this->next = NULL;
        }
};
class HashMap
{
    private:
        HashNode** htable;
    public:
        HashMap()
        {
            htable = new HashNode*[TABLE_SIZE];
            for (int i = 0; i < TABLE_SIZE; i++)
                htable[i] = NULL;
        }
        ~HashMap()
        {
            for (int i = 0; i < TABLE_SIZE; ++i)
	    {
                HashNode* entry = htable[i];
                while (entry != NULL)
	        {
                    HashNode* prev = entry;
                    entry = entry->next;
                    delete prev;
                }
            }
            delete[] htable;
        }
        void Insert(int key, string value)
        {
            int hash_val =key;
            HashNode* prev = NULL;
            HashNode* entry = htable[hash_val];
            while (entry != NULL)
            {
                prev = entry;
                entry = entry->next;
            }
            if (entry == NULL)
            {
                entry = new HashNode(key, value);
                if (prev == NULL)
	        {
                    htable[hash_val] = entry;
                }
	        else
	        {
                    prev->next = entry;
                }
            }
            else
            {
                entry->value = value;
            }
        }
        int Search(int key)
        {
            bool flag = false;
            HashNode* entry = htable[key];
            while (entry != NULL)
	    	{
                if (entry->key == key)
	        	{
                    insertNode(entry->value);
                    flag = true;
                }
                entry = entry->next;
            }
            if (!flag)
                return -1;
        }
};
using namespace std;
void print(char* a)
{
	cout<<endl<<endl<<"Your Password generated is :- "<<a<<endl;

}
int main()
{
	cout<<"Welcome to Password Generator"<<endl<<endl<<"How would you like to generate your Password ?"<<endl<<endl<<"Press 1 if you want a random Password"<<endl<<"Press 2 if you Want a Password to remember"<<endl;
	int c;
	int l;
	cin>>c;
//-------------------------------------------------------------------------------------------------------
	if(c==1)
	{
		char all[]="0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		int len=70;
		cout<<endl<<"Enter the length of your password"<<endl;
		cin>>l;
		if(cin.fail())
		{
			cout<<endl<<"Invalid Input"<<endl;
		}
		else
		{
			cout<<endl<<"Your Password generated is :- ";
			srand(time(0));
			for(int i=0;i<l;i++)
			{

				pass[i]=all[rand()%len];
				cout<<pass[i];
			}
           // pass[l]='\0';

			hufftree(pass);

		}
	}
//--------------------------------------------------------------------------------------------------------
	else if(c==2)
	{
			int c1;
			cout<<endl<<endl<<"What about including your name or your birthday or your bestie's name or Name of software or device or site for which password is to be made in it ?"<<endl<<endl<<"Enter 1 for Yes and 0 for No"<<endl<<endl;
			cin>>c1;
			if(c1==1)
			{
			try
			{
				char p[4][10];
				cout<<endl<<"Enter your first name only (Must contain minimum 3 and maximum 20 charachters)"<<endl;
				cin>>p[0];
				if(strlen(p[0])<3 || strlen(p[0])>20)
				throw "Invalid Input";
				char n[strlen(p[0])];
				strcpy(n,p[0]);
				cout<<endl<<"Enter your date of birth in dd/mm/yyyy format"<<endl;
				cin>>p[1];
				if(strlen(p[1])==10 && p[1][2]=='/' && p[1][5]=='/')
				{
					char m[strlen(p[1])];
					strcpy(m,p[1]);
					cout<<endl<<"Enter the first name of your best friend (Must contain minimum 3 and maximum 20 charachters)"<<endl;
					cin>>p[2];
					if(strlen(p[2])<3 || strlen(p[2])>20)
					throw "Invalid Input";
					char o[strlen(p[2])];
					strcpy(o,p[2]);
					cout<<endl<<"Enter name of software or device or site for which password is to be made (Must contain minimum 3 and maximum 20 charachters)"<<endl;
					cin>>p[3];
					if(strlen(p[3])<3 || strlen(p[3])>20)
					throw "Invalid Input";
					char h[strlen(p[3])];
					strcpy(h,p[3]);
					for(int i=0;i<4;i++)
					{
						for(int j=0;j<strlen(p[i]);j++)
						{
							p[i][j]++;
						}
					}
					int q=strlen(p[0]);
					int r=strlen(p[1]);
					int s=strlen(p[2]);
					int t=strlen(p[3]);
					srand(time(0));
					int b=(rand()%12);
					if(b==0)
				  	{
				  		char a[q];
				  		strcpy(a,p[0]);
				  		print(a);
				  		hufftree(a);

				  		cout<<endl<<"Remember factor :- Each letter of your name is incremented to next letter in alphabetical order"<<endl;
					}
					if(b==1)
				  	{
				  		char a[r];
				  		for(int i=0;i<r;i++)
				  		{
				  			if(i==2 || i==5 )
				  			{
				  				m[i]='@';
							}
							if(i==6 || i==7)
							{
								m[i]='#';
							}

						}
						strcpy(a,m);
				  		print(a);
				  		hufftree(a);
				  		//pass=a;
				  		cout<<endl<<"Remember factor :- your birthday written in dd@mm@##yy format"<<endl;
					}
					if(b==2)
				  	{
				  		char a[s];
				  		strcpy(a,p[2]);
				  		print(a);
				  		hufftree(a);
				  		//pass=a;
				  		cout<<endl<<"Remember factor :- Each letter of your friend's name is incremented to next to next letter in alphabetical order"<<endl;
					}
					if(b==3)
				  	{
				  		char a[t];
				  		strcpy(a,p[3]);
				  		print(a);
				  		hufftree(a);
				  //		pass=a;
				  		cout<<endl<<"Remember factor :- Each letter of software or device or site name is incremented to next letter in alphabetical order"<<endl;
					}

					if(b==4)
				  	{
					  char a[7];
					  char b[7];
				  		for(int i=0;i<3;i++)
				  		{
				  			b[i]=n[i];
						}
						b[3]='&';
						for(int j=0;j<3;j++)
				  		{
				  			b[j+4]=o[j];
						}
						strcpy(a,b);
						print(a);
						hufftree(a);
					//	pass=a;
						cout<<endl<<"Remember factor :- (your name) and(&) (friend's name)"<<endl;
					}
					if(b==5)
				  	{
					  char a[7];
					  char b[7];
				  		for(int i=0;i<3;i++)
				  		{
				  			b[i]=n[i];
						}
						b[3]='@';
						for(int j=0;j<3;j++)
				  		{
				  			b[j+4]=h[j];
						}
						strcpy(a,b);
						print(a);
						hufftree(a);
						//pass=a;
						cout<<endl<<"Remember factor :- (your name) at(@) (device or site or software's name)"<<endl;
					}
					if(b==6)
				  	{
					  	char a[7];
					  	char b[7];
				  		for(int i=0;i<3;i++)
				  		{
				  			b[i]=n[i];
						}
						b[3]='^';
						srand(time(0));
						int k=(rand()%2);
						if(k==0)
						{
							for(int j=0;j<2;j++)
				  			{
				  				b[j+4]=m[j];
							}
						}
						else if(k==1)
						{
							for(int j=0;j<2;j++)
				  			{
				  				b[j+4]=m[j+3];
							}
						}
						else if(k==2)
						{
							for(int j=0;j<2;j++)
				  			{
				  				b[j+4]=m[j+8];
							}
						}

						strcpy(a,b);
						print(a);
						hufftree(a);
						//pass=a;
						if(k=0)
						{
					  		cout<<endl<<"Remember factor :- (your name) on(^) (date of your birth)"<<endl;
						}
						else if(k=1)
					  	{
					  		cout<<endl<<"Remember factor :- (your name) on(^) (month of your birth)"<<endl;
					  	}
					  	else if(k=2)
					  	{
					  		cout<<endl<<"Remember factor :- (your name) on(^) (last two digits of year of your birth)"<<endl;
					  	}
					}
					if(b==7)
				  	{
					  	char a[11];
					  	char b[11];
				  		for(int i=0;i<2;i++)
				  		{
				  			b[i]=n[i];
						}
						b[2]='&';
						for(int j=0;j<2;j++)
				  		{
				  			b[j+3]=o[j];
						}
						b[5]='@';
						for(int j=0;j<2;j++)
				  		{
				  			b[j+6]=h[j];
						}
						b[8]='^';
						for(int j=0;j<2;j++)
				  		{
				  			b[j+9]=m[j];
						}
						strcpy(a,b);
					  	print(a);
					  	hufftree(a);
					  	//pass=a;
					  	cout<<endl<<"Remember factor :- (your name) and(&) (friend's name) at(@) (device or site or software's name) on(^) (date of birth)"<<endl;
					}
					if(b==8)
				  	{
				  		char a[q];
				  		for(int i=0;i<q/2;i++)
				  		{
				  			swap(n[i],n[q-i-1]);
						}
						strcpy(a,n);
				  		print(a);
				  		hufftree(a);
				  		//pass=a;
			  			cout<<endl<<"Remember factor :- your name is reversed"<<endl;
					}
					if(b==9)
				  	{
				  		char a[r];
			  			for(int i=0;i<r;i++)
			  			{
			  				if(i==2 || i==5 )
			  				{
				  				m[i]='@';
							}
							if(i==6 || i==7)
							{
							m[i]='#';
							}
						}
						r=strlen(m);
						for(int i=0;i<r/2;i++)
			  			{
			  				swap(m[i],m[r-i-1]);
						}
						strcpy(a,m);
				  		print(a);
				  		hufftree(a);
				  		//pass=a;
						cout<<endl<<"Remember factor :- your birthday written in yy##@mm@dd format"<<endl;
					}
					if(b==10)
			  		{
			  			char a[s];
			  			for(int i=0;i<s/2;i++)
			  			{
				  			swap(o[i],o[s-i-1]);
						}
						strcpy(a,o);
			  			print(a);
			  			hufftree(a);
			  			//pass=a;
			  			cout<<endl<<"Remember factor :- your friend's name is reversed"<<endl;
					}
					if(b==11)
			  		{
			  			char a[t];
			 	 		for(int i=0;i<t/2;i++)
			  			{
			  				swap(h[i],h[t-i-1]);
						}
						strcpy(a,h);
			  			print(a);
			  			hufftree(a);
			  			//pass=a;
			  			cout<<endl<<"Remember factor :- software or device or site name is reversed"<<endl;
					}

				}
				else
				{
					cout<<endl<<endl<<"Invalid Input"<<endl;
				}
			}
			catch(const char*msg)
			{
				cout<<endl<<msg<<endl;
			}
			}
//------------------------------------------------------------------------------------------------------------------------
			else if(c1==0)
			{
				cout<<endl<<"Enter the length of your password with minimum 4 and maximum 10"<<endl;
				cin>>l;
				if(l>3 && l<11)
				{
				int key;
				HashMap hash;
				string value;
    			fstream file;
    			string sen, t, q;
    			file.open("aashish.txt");
  				while (getline(file,sen))
    			{
    				key=1;
    				for(int i=0;i<sen.length();i++)
    				if(sen[i]==' ')
    					key++;
        			hash.Insert(key,sen);
    			}
    			hash.Search(l);
    			int coun=count();
    			srand(time(0));
    			int p=(rand()%coun);
    			string selected=pickout(p);
    			int c=1;
    			char pw[l];
    			pw[0]=selected[0];
			   	for(int i=0;i<selected.length();i++)
  				{
    				if(selected[i]==' ')
   				 	{
      					pw[c]=selected[i+1];
      					c++;
    				}
  				}
				print(pw);
				hufftree(pw);
				//pass=pw;
				cout<<endl<<"Remember taking the 1st letters of each word of :- "<<selected<<endl;
				}
				else
				{
					cout<<endl<<"Invalid Input"<<endl;
				}

			}
			else
			{
				cout<<endl<<"Invalid Input"<<endl;
			}
	}
//-------------------------------------------------------------------------------------------------------------------------------------
	else
	{
		cout<<endl<<"Input Invalid"<<endl;
	}
}
