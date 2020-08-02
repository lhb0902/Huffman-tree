#include<iostream>
#include<string>
#include<cstring>
using namespace std;
string sentence_a;
//number用于计数有多少有效字符
int number=0;
//mageNum用于计数去重后的number
int mageNumber = 0;
//number_用于计数有number个叶子节点的树最多具有的节点数
int number_ = 0;
//validNumber用于计数整个数组中真正启用的节点
int validNumber = 0;
int x = 0;

//哈夫曼树的节点
struct HFM
{
	int weight;
	char letter;
	int lChild;
	int rChild;
	int parent;
	int sign;
};
struct HFM *hfm_ =NULL;


//储存字符和对应频度用的节点
struct DATA
{
	int weight;
	char character;
};
struct DATA frequency[52];
struct DATA *mageFre =NULL;


//编码表节点
struct TABLE
{
	char character;
	string coding;
};
struct TABLE * table_ =NULL;
struct TABLE *magetable = NULL;

//数据输入函数 时间复杂度O（1）
string input()
{
	//getline(cin,sentence_a);//这里不能用cin，cin遇到空格会停止读取，采用getline解决了此问题
	getline(cin,sentence_a);
	return sentence_a;
}


//频度统计函数 时间复杂度O（n）
struct DATA *analyze(string sentence_b)
{
	for (int i = 0; i < sentence_b.length(); i++)
	{
		cout << sentence_b[i];
	}
	for (int i = 0; i < 26;i++)
	{
		frequency[i].character = (char)(i + 65);
	}
	for (int i = 26; i < 52; i++)
	{
		frequency[i].character = (char)(i +71 );
	}
	for (int i = 0; i < 52; i++)
	{
		frequency[i].weight = 0;
	}
	for (int i = 0; i < sentence_b.length(); i++)
	{
		if((int)sentence_b[i] - 65>=0&& (int)sentence_b[i] - 65<26)
		{
			frequency[(int)sentence_b[i] - 65].weight += 1;
		}
		if ((int)sentence_b[i] - 97 >= 0 && (int)sentence_b[i] - 97 < 26)
		{
			frequency[(int)sentence_b[i] - 71].weight += 1;
		}
		
	}
	for (int i = 0; i < 52; i++)
	{
		cout<<frequency[i].character<<" ";
		cout<<frequency[i].weight<<endl;
	}
	return frequency;
}


//字符统计函数  时间复杂度O（n）
int count(string sentence_c)
{
	for (int i = 0; i < sentence_c.length(); i++)
	{
		if (sentence_c[i] == '\0')break;
		if(sentence_c[i] !=' ')number += 1;
	}	
	cout << number;
	return number;
}


//字符去重函数  时间复杂度O（1）
int manageNumber()
{
	for (int i = 0; i < 52; i++)
	{
		if (frequency[i].weight != 0)mageNumber+= 1;
	}
	return mageNumber;
}



//在frequency的基础上生成新的结构体数组，用于记录权值非零的字符  时间复杂度O（1）
int manageFrequency(struct DATA *mageFre_)
{
	cout << "manage successful" << endl;
	int work = 0;
	for(int i=0;i<52;i++)
	{
		if (frequency[i].weight != 0)
		{
			mageFre_[work].weight = frequency[i].weight;
			mageFre_[work].character = frequency[i].character;
			work += 1;
		}
	}
	return 0;
		
}


//节点赋值函数  时间复杂度O（n）
//如果不把hfm当做参数传入，会抛出访问控制权限的异常，未找到导致此问题的原因，暂时将此问题以传参方式解决
struct HFM * assign(int numAs_,struct DATA *mageFre_,struct HFM*hfm_)
{
	for (int i = 0; i < numAs_; i++)
	{
		hfm_[i].letter = mageFre_[i].character;
		hfm_[i].lChild =  -1;
		hfm_[i].parent = -1;
		hfm_[i].rChild = -1;
		hfm_[i].weight = mageFre_[i].weight;
		hfm_[i].sign = 0;
	}
	for (int i = 0; i < numAs_; i++)
	{
		cout << hfm_[i].letter << ' ' << hfm_[i].weight << ' ' << hfm_[i].rChild << ' ' << hfm_[i].lChild <<' '<< hfm_[i].parent <<' '<< hfm_[i].sign << endl;
	}
	return hfm_;
}

//获取所有有效节点中权值最小的函数  时间复杂度O（n）
int min1(int validNumber,struct HFM *hfm__)
{
	int work = 99999;
	int adress = 0;
	for(int i = 0;i < validNumber;i++)
	{
		if (hfm__[i].sign == 0 && hfm__[i].weight < work) 
		{ work = hfm__[i].weight; 
		adress = i; }
	}
	hfm__[adress].sign = -1;
	return adress;
}

//判断是否还有剩余有效节点的函数 时间复杂度O（n）
int rest(int validNumber,struct HFM *hfm_)
{
	//freshNumber用于计数整个数组中已启用的节点中未入树的节点数
	int freshNumber = 0;
	for (int i = 0; i < validNumber; i++)
	{
		if (hfm_[i].sign == 0)freshNumber+=1;
	}
	cout << freshNumber;
	return freshNumber;
}

//哈夫曼树建立函数  时间复杂度O（n）
struct HFM * buildTree(struct HFM *hfm_)
{
	cout << "hfming"<<endl;
	if (rest(validNumber,hfm_)>1)
	{
		int a = min1(validNumber,hfm_);
		int b= min1(validNumber,hfm_);
		hfm_[validNumber].lChild = a;
		hfm_[validNumber].rChild = b;
		hfm_[validNumber].weight = hfm_[a].weight + hfm_[b].weight;
		hfm_[validNumber].sign = 0;
		hfm_[validNumber].letter = ' ';
		hfm_[validNumber].parent = -2;
		hfm_[a].parent = validNumber;
		hfm_[b].parent = validNumber;
		hfm_[a].sign = -1;
		hfm_[b].sign = -1;
		validNumber += 1;
		for (int i = 0; i < validNumber; i++)
		{
			cout << hfm_[i].letter << ' ' << hfm_[i].weight << ' ' <<hfm_[i].lChild<<' '<<hfm_[i].rChild<<' '<<hfm_[i].parent<<' '<< hfm_[i].sign << endl;
		}
		buildTree(hfm_);
	}
	else 
	{
		cout << "建树完成" << endl;
		return 0;
	}
	
}

//编码表建立  时间复杂度O（n）
struct TABLE *CreateTable(struct HFM*hfm_,struct TABLE *table_)
{
	cout << "creating"<<endl;
	int work1 = 0;
	//此循环是为了定位所有的叶子节点
	for (int i = 0; i < mageNumber; i++)
	{
		if (hfm_[i].letter != ' ') 
		{
			table_[work1].character= hfm_[i].letter;
			table_[work1].coding = ' ';
			int work2 = i;
			//此循环是为了为每一个叶子节点做编码
			for (int x = 0; x < validNumber; x++)
			{
				if (hfm_[work2].parent == -2)break;
				else
				{
					if (hfm_[hfm_[work2].parent].rChild == work2)table_[work1].coding = table_[work1].coding+'1';
					if (hfm_[hfm_[work2].parent].lChild == work2)table_[work1].coding = table_[work1].coding+'0';
					work2 = hfm_[work2].parent;
				}
				cout << table_[work1].character << " " << table_[work1].coding << endl;
			}
			work1 += 1;
		
		}
	}
	cout << "creating successful" << endl;
	for (int z = 0; z < mageNumber; z++)
	{
		cout << table_[z].character << ' ' << table_[z].coding << endl;
	}
	return table_;
}

//字符串逆序函数 时间复杂度O（n）
int reverse(struct TABLE *table_,struct TABLE *magetable_)
{
	cout << "reversing"<<endl<<"以下是编码表"<<endl;
	for (int i = 0; i < mageNumber; i++)
	{
		magetable_[i].character = table_[i].character;
		string a;
		a = table_[i].coding;
		string b(a.rbegin(), a.rend());
		magetable_[i].coding = b;
	}
	for (int i = 0; i < mageNumber; i++)
	{
		cout << magetable_[i].character << " " << magetable_[i].coding << endl;
	}
	return 0;
}

//编码函数 时间复杂度O（n**2）
string Encoding(struct TABLE *magetable_, string sentence_d)
{
	int work1=0;
	string Encoded="";
	for (int i = 0; i < sentence_d.length(); i++)
	{
		for (int j = 0; j < mageNumber; j++)
		{
			if (sentence_d[i] == magetable_[j].character) { Encoded = Encoded + magetable_[j].coding; break;}
		}
	}
	return Encoded;
}

//解码函数  解码函数O（n）
int Decoding(struct HFM *hfm_,string mageEncoded_)
{
	cout << "Decoding"<<endl;
	cout << "以下是解码串" << endl;
	int head;
	//此循环用于搜索头结点
	for (int i = 0; i < validNumber; i++)
	{
		if (hfm_[i].parent == -2) 
		{
			head = i; 
			break;
		}
	}
	int work = head;
	for (int i=0;i<mageEncoded_.length()+1;i++)
	{
		if (hfm_[work].letter != ' ') 
		{
			cout << hfm_[work].letter;
			work = head;
		}
		if (mageEncoded_[i] == '0')work = hfm_[work].lChild;
		if (mageEncoded_[i] == '1')work = hfm_[work].rChild;
	}
	return 0;
}

int main()
{
	//输入函数
	string sentence = input();

	//字符统计
	count(sentence);

	//频度统计
	analyze(sentence);

	//字符去重
	manageNumber();

    int number_ = 3 * mageNumber;
	struct HFM *hfm = new HFM[number_];
    struct DATA *mageFre =new DATA[number];

	//记录权值非零字符
	manageFrequency(mageFre);
	validNumber = mageNumber;

	//哈夫曼树的建立
	buildTree(assign(validNumber,mageFre,hfm));
	
	delete [] mageFre;
	struct TABLE * table = new TABLE[mageNumber];

	//建立编码表
	CreateTable(hfm,table);

	struct TABLE *magetable = new TABLE[mageNumber];

	//Creatable函数创造的编码表的编码是逆序，这里调用reverse函数将原编码倒置
	reverse(table, magetable);
	
	cout << "以下是编码串"<<endl;
	cout<<Encoding(magetable, sentence_a)<<endl;
	string Encoded = Encoding(magetable, sentence_a);
	string mageEncoded;
	
	//此循环用于将原有已编码串去空格
	for (int i=0; i < Encoded.length(); i++)
	{
		if (Encoded[i] != ' ')mageEncoded = mageEncoded + Encoded[i];
	}
	
	//译码
	Decoding(hfm, mageEncoded);
	system("pause");
	try {
		if ((int)hfm[0].letter < 0)throw - 1;
		else{ delete hfm; }
	}
	catch (int a) 
	{
		cout << "delete fail";
	}
	return 0;
}