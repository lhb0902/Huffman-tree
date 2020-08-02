#include<iostream>
#include<string>
#include<cstring>
using namespace std;
string sentence_a;
//number���ڼ����ж�����Ч�ַ�
int number=0;
//mageNum���ڼ���ȥ�غ��number
int mageNumber = 0;
//number_���ڼ�����number��Ҷ�ӽڵ���������еĽڵ���
int number_ = 0;
//validNumber���ڼ��������������������õĽڵ�
int validNumber = 0;
int x = 0;

//���������Ľڵ�
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


//�����ַ��Ͷ�ӦƵ���õĽڵ�
struct DATA
{
	int weight;
	char character;
};
struct DATA frequency[52];
struct DATA *mageFre =NULL;


//�����ڵ�
struct TABLE
{
	char character;
	string coding;
};
struct TABLE * table_ =NULL;
struct TABLE *magetable = NULL;

//�������뺯�� ʱ�临�Ӷ�O��1��
string input()
{
	//getline(cin,sentence_a);//���ﲻ����cin��cin�����ո��ֹͣ��ȡ������getline����˴�����
	getline(cin,sentence_a);
	return sentence_a;
}


//Ƶ��ͳ�ƺ��� ʱ�临�Ӷ�O��n��
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


//�ַ�ͳ�ƺ���  ʱ�临�Ӷ�O��n��
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


//�ַ�ȥ�غ���  ʱ�临�Ӷ�O��1��
int manageNumber()
{
	for (int i = 0; i < 52; i++)
	{
		if (frequency[i].weight != 0)mageNumber+= 1;
	}
	return mageNumber;
}



//��frequency�Ļ����������µĽṹ�����飬���ڼ�¼Ȩֵ������ַ�  ʱ�临�Ӷ�O��1��
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


//�ڵ㸳ֵ����  ʱ�临�Ӷ�O��n��
//�������hfm�����������룬���׳����ʿ���Ȩ�޵��쳣��δ�ҵ����´������ԭ����ʱ���������Դ��η�ʽ���
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

//��ȡ������Ч�ڵ���Ȩֵ��С�ĺ���  ʱ�临�Ӷ�O��n��
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

//�ж��Ƿ���ʣ����Ч�ڵ�ĺ��� ʱ�临�Ӷ�O��n��
int rest(int validNumber,struct HFM *hfm_)
{
	//freshNumber���ڼ������������������õĽڵ���δ�����Ľڵ���
	int freshNumber = 0;
	for (int i = 0; i < validNumber; i++)
	{
		if (hfm_[i].sign == 0)freshNumber+=1;
	}
	cout << freshNumber;
	return freshNumber;
}

//����������������  ʱ�临�Ӷ�O��n��
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
		cout << "�������" << endl;
		return 0;
	}
	
}

//�������  ʱ�临�Ӷ�O��n��
struct TABLE *CreateTable(struct HFM*hfm_,struct TABLE *table_)
{
	cout << "creating"<<endl;
	int work1 = 0;
	//��ѭ����Ϊ�˶�λ���е�Ҷ�ӽڵ�
	for (int i = 0; i < mageNumber; i++)
	{
		if (hfm_[i].letter != ' ') 
		{
			table_[work1].character= hfm_[i].letter;
			table_[work1].coding = ' ';
			int work2 = i;
			//��ѭ����Ϊ��Ϊÿһ��Ҷ�ӽڵ�������
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

//�ַ��������� ʱ�临�Ӷ�O��n��
int reverse(struct TABLE *table_,struct TABLE *magetable_)
{
	cout << "reversing"<<endl<<"�����Ǳ����"<<endl;
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

//���뺯�� ʱ�临�Ӷ�O��n**2��
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

//���뺯��  ���뺯��O��n��
int Decoding(struct HFM *hfm_,string mageEncoded_)
{
	cout << "Decoding"<<endl;
	cout << "�����ǽ��봮" << endl;
	int head;
	//��ѭ����������ͷ���
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
	//���뺯��
	string sentence = input();

	//�ַ�ͳ��
	count(sentence);

	//Ƶ��ͳ��
	analyze(sentence);

	//�ַ�ȥ��
	manageNumber();

    int number_ = 3 * mageNumber;
	struct HFM *hfm = new HFM[number_];
    struct DATA *mageFre =new DATA[number];

	//��¼Ȩֵ�����ַ�
	manageFrequency(mageFre);
	validNumber = mageNumber;

	//���������Ľ���
	buildTree(assign(validNumber,mageFre,hfm));
	
	delete [] mageFre;
	struct TABLE * table = new TABLE[mageNumber];

	//���������
	CreateTable(hfm,table);

	struct TABLE *magetable = new TABLE[mageNumber];

	//Creatable��������ı����ı����������������reverse������ԭ���뵹��
	reverse(table, magetable);
	
	cout << "�����Ǳ��봮"<<endl;
	cout<<Encoding(magetable, sentence_a)<<endl;
	string Encoded = Encoding(magetable, sentence_a);
	string mageEncoded;
	
	//��ѭ�����ڽ�ԭ���ѱ��봮ȥ�ո�
	for (int i=0; i < Encoded.length(); i++)
	{
		if (Encoded[i] != ' ')mageEncoded = mageEncoded + Encoded[i];
	}
	
	//����
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