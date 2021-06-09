/*covid city records
NAME-VANSHIKA
COURSE-BTECH CS 2nd YEAR
SECTION-C
ROLL NO-1913162
ID:BTBTC19046
*/

/*
THIS SOFTWARE KEEPS TRACK OF ALL THE COVID CASES IN THE CITY OF BIJNOR (area wise)
IF ANY AREA HAS MORE THAN 10 CASES IT WILL BE DECLARED AS RED ZONE
ANY PERSON LIVING IN RED ZONE WILL BE SHOWN A MESSAGE
BOTH USER AND HOSPITALS CAN LOG IN 
ONLY HOSPITALS CAN ADD THE RECORDS OF COVID PATIENTS AND VACCINATION(User must be registered in the database)
THE RECORD ALTERED BY THE HOSPITAL WILL BE VISIBLE IN THE USER'S PANNEL AS WELL
RECORD OF CASES IN THE CITY CAN BE SEEN EVEN WITHOUT LOGGING IN 
*/
/*
WARNING:SAVE THE FILES ATTACHED IN E-DRIVE ONLY
*/
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
class Patient;
class Hospital;
class Area
{
	char address[500];
	int cases;
public:
	void set_val(int c,char s[],ofstream &F)
	{
		strcpy(address,s);
		F<<'\n'<<address<<" ";
		cases=c;
		F<<cases;
	}
	void get(ifstream &F)
	{
		F>>address;
		F>>cases;
	}
	void set(ofstream &F)
	{
		F<<address<<" ";
		F<<cases<<"\n";
	}
	void less()
	{
		cases--;
	}
	void update()
	{
		cases++;
	}
	friend void addPatient(Patient &p,Hospital &h);
	friend void recoverPatient(Patient &p,Hospital &h);
	friend int check(Patient p,Area a);
	friend void deadPatient(Patient &p,Hospital &h);
	int isRedZone()
	{
		if(cases>10)
			return 1;
		return 0;
	}
	void show()
	{
		cout<<address<<"\t\t"<<cases<<"\n";
	}
	int search(char a[])
	{
		if (strcmp(address,a)==0)
		{
			return 1;
		}
		else
			return 0;
	}
};
//initialiser for areas of bijnor
void setArea()
{
	ofstream F;
	F.open("E:/area.txt");
	char address[500];
	Area a;
	strcpy(address,"AWAS_VIKAS");
	a.set_val(0,address,F);
				strcpy(address,"NAI_BASTI");

	a.set_val(0,address,F);
				strcpy(address,"GOVINDPURAM");

	a.set_val(0,address,F);
				strcpy(address,"GEETA_NAGRI");

	a.set_val(0,address,F);
				strcpy(address,"CHASEERI");
	a.set_val(0,address,F);
				strcpy(address,"JATAAN");
	a.set_val(0,address,F);
				strcpy(address,"PANCHVATI");
	a.set_val(0,address,F);
				strcpy(address,"CIVIL_LINES");
	a.set_val(0,address,F);
				strcpy(address,"OTHER");
	a.set_val(0,address,F);
	F.close();
	cout<<"Area set"<<endl;

}
class User
{

protected:
	char name[50],password[50];
public:
	User()
	{
		name[0]='\0';
		password[0]='\0';
	}
	friend int exist(char s[]);

	void set_val(ofstream &F_h);
	void welcome()
	{
		cout<<"welcome @"<<name<<endl;

	}
};
class Hospital:public User
{
protected:
	int cov_pa,recovered,dead,CURRENT;
	char address[500];
public:

	friend int exist(char s[]);
	void set_val(ofstream &F_h)
	{
		User::set_val(F_h);
		if(strlen(password)==0)
		return;
		int y;
		cout<<"TOTAL NUMBER OF COVID PATIENTS TILL DATE:";
		cin>>cov_pa;
		F_h<<cov_pa<<" ";
		cout<<"TOTAL RECOVERIES TILL DATE:";
		cin>>recovered;
		F_h<<recovered<<" ";
		cout<<"TOTAL DEATH TILL NOW:";
		cin>>dead;

		F_h<<dead<<" ";
		CURRENT=cov_pa-(recovered+dead);

		F_h<<CURRENT<<" ";
		cout<<"CURRENT PATIENTS:"<<CURRENT<<endl;
		cout<<"AREA :::: (select from the following)"<<endl;
		cout<<"1:AWAS VIKAS\n2:NAI BASTI\n3:GOVIND PURAM\n4:GEETA NAGRI\n5:CHASEERI\n6:JATAAN\n7:PANCHVATI\n8:CIVIL LINES\n9:OTHER\n";
		cin>>y;
		switch(y)
		{
			case 1:
				strcpy(address,"AWAS_VIKAS");
			break;
			case 2:
				strcpy(address,"NAI_BASTI");
			break;
			case 3:
				strcpy(address,"GOVINDPURAM");
			break;
			case 4:
				strcpy(address,"GEETA_NAGRI");
			break;
			case 5:
				strcpy(address,"CHASEERI");
			break;
			case 6:
				strcpy(address,"JATAAN");
			break;
			case 7:
				strcpy(address,"PANCHVATI");
			break;
			case 8:
				strcpy(address,"CIVIL_LINES");
			break;
			default:
				strcpy(address,"OTHER");
		}

		F_h<<address;
		cout<<"****************SIGNED IN*******************"<<endl;
	}
	int login(ifstream &F,char n[],char p[])
	{
		int c=0;
		while(!F.eof())
		{
			F>>name;
			F>>password;
			F>>cov_pa;
			F>>recovered;
			F>>dead;
			F>>CURRENT;
			F>>address;
			if(strcmp(name,n)==0)
			{
				if (strcmp(password,p)==0)
				{
					cout<<"****************************LOGIN SUCESSFULL****************************"<<endl;
					return 1;
				}
				c=-1;
				break;
			}
			else
				c=-2;
		}
		if (c==-1)
		{
			cout<<"**********************WRONG PASSWORD***************************"<<endl;
		}
			if(c==-2)
			{
				cout<<"*******************************USER NOT FOUND****************************"<<endl;
			}
			return 0;
		
}
	void welcome()
	{
		User::welcome();
		cout<<"CURRENT COVID CASES:"<<CURRENT<<endl;
	}
	void show_h_details()
	{
		cout<<"***************************************\n";
		cout<<"name:"<<name<<endl;
		cout<<"total covid cases:"<<cov_pa<<endl;
		cout<<"current cases:"<<CURRENT<<endl;
		cout<<"total recovered cases:"<<recovered<<endl;
		cout<<"total deaths:"<<dead<<endl;
		cout<<"***************************************\n";
	}
	void get(ifstream &F)
	{
			F>>name;
			F>>password;
			F>>cov_pa;
			F>>recovered;
			F>>dead;
			F>>CURRENT;
			F>>address;
	}
	void set_val(ofstream &F,int i)
	{
			F<<"\n"<<name<<" ";
			F<<password<<" ";
			F<<cov_pa<<" ";
			F<<recovered<<" ";
			F<<dead<<" ";
			F<<CURRENT<<" ";
			F<<address;
	}
	friend int check_hospital(Patient p,Hospital h);
	friend void recoverPatient(Patient &p,Hospital &h);

	friend void addPatient(Patient &p,Hospital &h);
	friend void deadPatient(Patient &p,Hospital &h);
	friend int inmyarea(Patient &p,Hospital &h);
	int operator==(Hospital &h)
	{
		if(strcmp(name,h.name)==0)
			return 1;
		return 0;
	}
	void operator=(Hospital h)
	{
			strcpy(name,h.name);
			strcpy(password,h.password);
			cov_pa=h.cov_pa;
			recovered=h.recovered;
			dead=h.dead;
			CURRENT=h.CURRENT;
			strcpy(address,h.address);
			//show_name();
	}
	void show_name()
	{
		cout<<name<<endl;
	}
	void calc(int &t,int &d,int &c,int &r)
	{
		t=t+cov_pa;
		d=d+dead;
		c=c+CURRENT;
		r=r+recovered;
	}

};
class Patient:public User
{
protected:
	char hospital[500];
	int days;

	int covid,vaccination[2],age;//if covid=0 not a patient if covid 1 -patient covid 2 recovered covid 3 dead
	char address[500];
public:

	friend int exist(char s[]);
void set_val(ofstream &F)
{
	User::set_val(F);
	if(strlen(password)==0)
		return;
	strcpy(hospital,"-");
	F<<hospital<<" ";
	days=0;
	F<<days<<" ";
	cout<<"AGE:"<<endl;
	cin>>age;
	F<<age<<" ";
	covid=0;
	F<<covid<<" ";
	vaccination[0]=0;
	vaccination[1]=0;
	F<<vaccination[0]<<" ";
	F<<vaccination[1]<<" ";
	int y;
	cout<<"AREA :::: (select from the following)"<<endl;
		cout<<"1:AWAS VIKAS\n2:NAI BASTI\n3:GOVIND PURAM\n4:GEETA NAGRI\n5:CHASEERI\n6:JATAAN\n7:PANCHVATI\n8:CIVIL LINES\n9:OTHER\n";
		cin>>y;
		switch(y)
		{
			case 1:
				strcpy(address,"AWAS_VIKAS");
			break;
			case 2:
				strcpy(address,"NAI_BASTI");
			break;
			case 3:
				strcpy(address,"GOVINDPURAM");
			break;
			case 4:
				strcpy(address,"GEETA_NAGRI");
			break;
			case 5:
				strcpy(address,"CHASEERI");
			break;
			case 6:
				strcpy(address,"JATAAN");
			break;
			case 7:
				strcpy(address,"PANCHVATI");
			break;
			case 8:
				strcpy(address,"CIVIL_LINES");
			break;
			default:
				strcpy(address,"OTHER");
		}

		F<<address;
		cout<<"****************SIGNED IN*******************"<<endl;
}
	int login(ifstream &F,char n[],char p[])
	{
		int c=0;
		while(!F.eof())
		{
			F>>name;
			F>>password;
			F>>hospital;
			F>>days;
			F>>age;
			F>>covid;
			F>>vaccination[0];
			F>>vaccination[1];
			F>>address;
			if(strcmp(name,n)==0)
			{
				if (strcmp(password,p)==0)
				{
					cout<<"**************************LOGIN SUCESSFULL***************************"<<endl;
					return 1;
				}
				c=-1;
				break;
			}
			else
				c=-2;
		}
		if (c==-1)
		{
			cout<<"***********************WRONG PASSWORD***********************"<<endl;
		}
			if(c==-2)
			{
				cout<<"***********************USER NOT FOUND**********************"<<endl;
			}
			return 0;
		
}
	void get(ifstream &F)
	{
			F>>name;
			F>>password;
			F>>hospital;
			F>>days;
			F>>age;
			F>>covid;
			F>>vaccination[0];
			F>>vaccination[1];
			F>>address;
	}
	friend int check_hospital(Patient p,Hospital h);
	int check_patient()
	{
		if (covid==0)
		{
			return 0;
		}
		return 1;
	}
	void show_p()
	{
		cout<<name<<"\t"<<age<<"\t"<<address<<"\t";
		if (covid==2)
		{
			cout<<"Y"<<"\t\t"<<days<<endl;
		}
		else if (covid==3)
		{
			cout<<"DEAD"<<"\t\t"<<"-"<<endl;
		}
		else
			cout<<"N"<<"\t\t"<<"-"<<endl;
	}
	int search(char n[])
	{
		if (strcmp(name,n)==0)
		{
			return 1;
		}
		return 0;
	}
	void set_val(ofstream &F,int i)
	{
			F<<"\n"<<name<<" ";
			F<<password<<" ";
			F<<hospital<<" ";
			F<<days<<" ";
			F<<age<<" ";
			F<<covid<<" ";
			F<<vaccination[0]<<" ";
			F<<vaccination[1]<<" ";
			F<<address;
	}
	friend void addPatient(Patient &p,Hospital &h);
	friend void recoverPatient(Patient &p,Hospital &h);

	friend int check(Patient p,Area a);
	friend void deadPatient(Patient &p,Hospital &h);
	friend int inmyarea(Patient &p,Hospital &h);
	void vaccinate()
	{
			cout<<"**********************************************"<<endl;
		if(vaccination[0]==0)
		{
			cout<<"FIRST DOSE DONE\nCOME BACK AFTER 30 DAYS"<<endl;
			vaccination[0]=1;
		}
		else if(vaccination[1]==0)
		{
			cout<<"SECOND DOSE DONE\nPATIENT VACCINATED"<<endl;
			vaccination[1]=1;
		}
		else
			cout<<"ALREADY VACCINATED"<<endl;

			cout<<"**********************************************"<<endl;
	}
	int welcome_record()
	{
			cout<<"**********************************************"<<endl;
		if(covid==3)
		{
			cout<<"PATIENT IS DEAD"<<endl;
			cout<<"CANNOT LOG IN"<<endl;
			cout<<"**********************************************"<<endl;
			return 0;
		}
		if(covid==1)
		{
			cout<<"YOU ARE COVID POSITIVE\nSTAY QUARENTINED\n";
		}
		else if (covid==2)
		{
			cout<<"YOU HAVE RECOVERED FROM COVID\nYOU ARE IMMUNE\n";
		}
		else
		{
			ifstream A;
			A.open("E:/area.txt");
			Area a;
			int k;
			while(!A.eof())
			{
				a.get(A);
				int k=a.search(address);
				if(k==1)
				{
					int k=a.isRedZone();
					break;
				}
			}
			A.close();
			if(k==1)
				cout<<"YOU ARE IN RED ZONE\nSTAY SAFE\n";
			else
			{
				cout<<"YOU ARE SAFE";
				if(vaccination[1]==1)
					cout<<" AND VACCINATED";
				cout<<endl;
			}
		}
			cout<<"**********************************************"<<endl;
		return 1;
	}
	void show_vaccination()
	{

			cout<<"**********************************************"<<endl;
		if(vaccination[1]==1)
			cout<<"BOTH DOSES OF VACCINE TAKEN"<<endl;
		else if (vaccination[0]==1)
		{
			cout<<"ONLY 1 DOSE OF VACCINE TAKEN"<<endl;
		}
		else
		{
			if (age>45)
			{
				cout<<"Not VACCINATED"<<endl;
			}
			else if(age>18)
			{
				cout<<"NOT VACCINATED\nNOTE:vaccine only availaibe for people above 45 years age,WAIT FOR YOUR TURN\n";
			}
			else
			{
				cout<<"NOT VACCINATED\nNOTE:vaccine not availaibe for people below 18\n";
			}
		}
			cout<<"**********************************************"<<endl;
	}
	void show()
	{
		cout<<"****************************"<<endl;
		cout<<"NAME:"<<name<<"\nAGE:"<<age<<"\nAREA:"<<address<<endl;
		cout<<"****************************"<<endl;
	}
};
class Covid
{
	int tot,dead,current,recovered;
public:
	Covid()
	{
		tot=0;
		dead=0;
		current=0;
		recovered=0;
	}
	void calc()
	{
		ifstream F;
		F.open("E:/hospital.txt");
		Hospital h;
		while(!F.eof())
		{
			h.get(F);
			h.calc(tot,dead,current,recovered);
		}
		F.close();
	}
	void show()
	{
		cout<<"*******************************BIJNOR CITY RECORDS********************************\n";
		calc();
		cout<<"TOTAL CASES:"<<tot<<"\nDEATHS:"<<dead<<"\nCURRENT PATIENTS:"<<current<<"\n RECOVERED PATIENTS:"<<recovered<<endl;
			cout<<"******************************************************************************"<<endl;
	}
	
};
int check_hospital(Patient p,Hospital h)
{
	if(strcmp(p.hospital,h.name)==0)
	{
		return 1;
	}
	return 0;
}

int exist(char s[])
{
	ifstream F;
	F.open("E:/hospital.txt");
	Hospital h;
	while(!F.eof())
	{
		h.get(F);
		if (strcmp(h.name,s)==0)
		{
			cout<<h.name;
			cout<<"****************** USER EXISTS********************"<<endl;
			return 1;
		}
	}
	F.close();
	F.open("E:/user.txt");
	Patient ah;
	while(!F.eof())
	{
		ah.get(F);
		if (strcmp(ah.name,s)==0)
		{
			cout<<ah.name;
			cout<<"************************ USER EXISTS ********************"<<endl;
			return 1;
		}
	}
	F.close();
	return 0;
}

	void User::set_val(ofstream &F_h)
	{
		cout<<"USERNAME:";
		cin>>name;
		int k=exist(name);
		if (k==1)
		{
			return;
		}
		F_h<<"\n"<<name<<" ";
		cout<<"PASSWORD:";
		cin>>password;
		F_h<<password<<" ";
	}

int check(Patient p,Area a)
{
	if (strcmp(p.address,a.address)==0)
	{
		return 1;
	}
	return 0;
}
void addPatient(Patient &p,Hospital &h)
{
	if(p.covid!=0)
	{
		if (p.covid==1)
		{
			cout<<"***************************USER ALREADY REGISTERED*************************\n";
		}
		if (p.covid==2)
		{
			cout<<"****************************USER CURED***************************\n";
		}
		if (p.covid==3)
		{
			cout<<"*************************USER DEAD*************************\n";
		}
		return;
	}
	strcpy(p.hospital,h.name);
	p.covid=1;
	h.cov_pa=h.cov_pa+1;
	//h.show_h_details();
	h.CURRENT=h.CURRENT+1;
	ifstream F;
	F.open("E:/area.txt");
	ofstream F1;
	F1.open("E:/nextarea.txt");
	Area a;
	while(!F.eof())
	{
		a.get(F);
		int k=check(p,a);
		if (k==1)
		{
			a.update();
		}
		a.set(F1);
	}
	F.close();
	F1.close();
	remove("E:/area.txt");
	rename("E:/nextarea.txt","E:/area.txt");
	cout<<"*****************PATIENT ADDED******************"<<endl;
}
void recoverPatient(Patient &p,Hospital &h)
{
	if (p.covid==0)
	{
		cout<<"********************USER NOT POSITIVE************************\n";
		return;
	}
	if (p.covid==2)
		{
			cout<<"****************************USER ALREADY CURED***************************\n";
		return;
		}
		if (p.covid==3)
		{
			cout<<"*************************USER DEAD*************************\n";
		return;
		}
	strcpy(p.hospital,h.name);
	p.covid=2;
	h.CURRENT=h.CURRENT-1;
	h.recovered=h.recovered+1;
	cout<<"NO OF DAYS FOR RECOVERY:";
	cin>>p.days;
	ifstream F;
	F.open("E:/area.txt");
	ofstream F1;
	F1.open("E:/nextarea.txt");
	Area a;
	while(!F.eof())
	{
		a.get(F);
		int k=check(p,a);
		if (k==1)
		{
			a.less();
		}
		a.set(F1);
	}
	F.close();
	F1.close();
	remove("E:/area.txt");
	rename("E:/nextarea.txt","E:/area.txt");
	cout<<"*****************RECORD ADDED******************"<<endl;
}
void deadPatient(Patient &p,Hospital &h)
{
	if (p.covid==0)
	{
		cout<<"********************USER NOT POSITIVE************************\n";
		return;
	}
	if (p.covid==2)
		{
			cout<<"****************************USER ALREADY CURED***************************\n";
		return;
		}
		if (p.covid==3)
		{
			cout<<"*************************USER ALREADY DEAD*************************\n";
		return;
		}
	strcpy(p.hospital,h.name);
	p.covid=3;
	h.CURRENT=h.CURRENT-1;
	h.dead=h.dead+1;
	ifstream F;
	F.open("E:/area.txt");
	ofstream F1;
	F1.open("E:/nextarea.txt");
	Area a;
	while(!F.eof())
	{
		a.get(F);
		int k=check(p,a);
		if (k==1)
		{
			a.cases=a.cases-1;
		}
		a.set(F1);
	}
	F.close();
	F1.close();
	remove("E:/area.txt");
	rename("E:/nextarea.txt","E:/area.txt");
}
int inmyarea(Patient &p,Hospital &h)
{
	if (strcmp(p.address,h.address)==0)
	{
		//h.show_name();
		return 1;
	}
	return 0;
}
void logedin_h(Hospital &h)
{
	int x=1;
	while(x)
	{
		cout<<"1:DETAILS OF HOSPITAL\n2:DETAILS OF ALL PATIENTS HERE\n3:SEARCH FOR PATIENT\n4:ADD COVID PATIENT\n5:ADD RECOVERED/DEAD RECORD\n6:VACCINATE PATIENT\n7:LIST OF RED ZONES\n8:NUMBER OF CASES OF PARTICULAR AREA\n0:LOGOUT\n:::::::";
		int y;
		cin>>y;
		if (y==0)
		{
			cout<<"***********************LOGGING OUT**********************"<<endl;
			break;
		}
		else if (y==1)
		{
			h.show_h_details();
		}
		else if (y==2)
		{
			ifstream F;
			F.open("E:/user.txt");
			Patient p;
			int c=0;
			cout<<"**********************************************"<<endl;
			cout<<"\tNAME\tAGE\tAREA\t\tRECOVERED\tDAYS"<<endl;
			while(!F.eof())
			{
				p.get(F);
				int k=check_hospital(p,h);
				if(k==1)
					k=p.check_patient();
				if(k==1)
				{
					cout<<++c<<"\t";
					p.show_p();
				}
			}
			F.close();
			cout<<"**********************************************"<<endl;
		}
		else if (y==3)
		{
			ifstream F;
			F.open("E:/user.txt");
			Patient p;
			cout<<"USERNAME:";
			char name[500];
			cin>>name;
			int k=0;
			while(!F.eof())
			{
				p.get(F);
				 k=p.search(name);
				if(k==1)
				{
					break;
				}
			}
			F.close();
			if (k==0)
			{
				cout<<"*************************USER NOT FOUND*************************"<<endl;
				continue;
			}
			k=p.check_patient();
			if (k==0)
			{
			cout<<"**********************************************"<<endl;
				cout<<"USER IS NOT A COVID PATIENT\nCANNOT SEE RECORDS\n";
			cout<<"**********************************************"<<endl;
				continue;
			}
			k=check_hospital(p,h);
			if (k==0)
			{
			cout<<"**********************************************"<<endl;
				cout<<"USER DOESNOT BELONG TO THIS HOSPITAL\nCANNOT SEE RECORDS\n";
			cout<<"**********************************************"<<endl;
				continue;
			}		
			cout<<"**********************************************"<<endl;
			cout<<"NAME\tAGE\tAREA\t\tRECOVERED\tDAYS"<<endl;
			p.show_p();
			cout<<"**********************************************"<<endl;
		}
		else if (y==4)
		{
			ifstream F;
			ofstream F1;
			F.open("E:/user.txt");
			F1.open("E:/temp.txt");
			Patient p;
			cout<<"USERNAME:";
			char name[500];
			cin>>name;
			int k=0,c=0;
			while(!F.eof())
			{
				p.get(F);
				 k=p.search(name);
				if (k==1)
				{
					c=1;
					addPatient(p,h);
				}
				p.set_val(F1,1);
			}
			F.close();
			F1.close();
			if (c==0)
			{
				cout<<"************************USER NOT FOUND*********************";
			}
			remove("E:/user.txt");
			rename("E:/temp.txt","E:/user.txt");
			F.open("E:/hospital.txt");
			F1.open("E:/temp.txt");
			Hospital k1;
			while(!F.eof())
			{

				k1.get(F);
				//k1.show_h_details();
				k=(k1==h);
				if(k)
				{
					//cout<<"here";
					k1=h;
				}
				k1.set_val(F1,1);
			}
			F.close();
			F1.close();
			remove("E:/hospital.txt");
			rename("E:/temp.txt","E:/hospital.txt");
			
		}
		else if(y==5)
		{
			ifstream F;
			ofstream F1;
			F.open("E:/user.txt");
			Patient p;
			cout<<"USERNAME:";
			char name[500];
			cin>>name;
			int k=0;
			while(!F.eof())
			{
				p.get(F);
				 k=p.search(name);

				if (k==1)
				{
					break;
				}
			}
			F.close();
			if (k==0)
			{
				cout<<"******************USER NOT FOUND*******************"<<endl;
				continue;
			}
			k=p.check_patient();
			if (k==0)
			{
			cout<<"**********************************************"<<endl;
				cout<<"USER IS NOT A COVID PATIENT\nCANNOT ALTER RECORDS\n";
			cout<<"**********************************************"<<endl;
				continue;
			}
			k=check_hospital(p,h);
			if (k==0)
			{
			cout<<"**********************************************"<<endl;
				cout<<"USER DOESNOT BELONG TO THIS HOSPITAL\nCANNOT ALTER RECORDS\n";
			cout<<"**********************************************"<<endl;
				continue;
			}		
			
			int r;
			cout<<"1:RECOVERED\n2:DEAD\n:::::";
			cin>>r;
				F.open("E:/user.txt");
				F1.open("E:/temp.txt");
				
				k=0;
				while(!F.eof())
				{
					p.get(F);
					 k=p.search(name);
					if (k==1)
					{
						if(r==1)
						{
							recoverPatient(p,h);
						}
						else if (r==2)
						{
							deadPatient(p,h);
						}
					}
					p.set_val(F1,1);
				}
				F.close();
				F1.close();
				remove("E:/user.txt");
				rename("E:/temp.txt","E:/user.txt");
				F.open("E:/hospital.txt");
				F1.open("E:/temp.txt");
				Hospital k1;
				while(!F.eof())
				{
					k1.get(F);
					k=(k1==h);
					if(k)
						k1=h;
					k1.set_val(F1,1);
					//k1.show_h_details();
				}
				F.close();
				F1.close();
				remove("E:/hospital.txt");
				rename("E:/temp.txt","E:/hospital.txt");
			
		}
		else if (y==6)
		{
			ifstream F;
			ofstream F1;
			Patient p;
			cout<<"USERNAME:";
			char name[500];
			cin>>name;
			int k=0,c=0;
				F.open("E:/user.txt");
				F1.open("E:/temp.txt");
				
				k=0;
				while(!F.eof())
				{
					p.get(F);
					 k=p.search(name);
					if (k==1)
					{
						c=1;
						p.vaccinate();
					}
					p.set_val(F1,1);
				}
				F.close();
				F1.close();
			if (c==0)
			{
				cout<<"***********************USER NOT FOUND*********************"<<endl;
			}
				remove("E:/user.txt");
				rename("E:/temp.txt","E:/user.txt");
				F.open("E:/hospital.txt");
				F1.open("E:/temp.txt");
			
		}
		else if(y==7)
		{
			ifstream A;
			A.open("E:/area.txt");
			Area a;
			int c=0;
	cout<<"**************************************************"<<endl;
			cout<<"AREA\t\t\tCASES (Red zones are area with more than 10 cases)\n";
			while(!A.eof())
			{
				a.get(A);
				int k=a.isRedZone();
				if(k==1)
				{
					a.show();
					c++;
				}
			}
			if (c==0)
			{
				cout<<"NO RED ZONE IN BIJNOR\n";
			}
			A.close();
	cout<<"**************************************************"<<endl;
		}
		else if(y==8)
		{
			ifstream A;
			A.open("E:/area.txt");
			Area a;
			int y;
			char address[500];
			cout<<"AREA :::: (select from the following)"<<endl;
			cout<<"1:AWAS VIKAS\n2:NAI BASTI\n3:GOVIND PURAM\n4:GEETA NAGRI\n5:CHASEERI\n6:JATAAN\n7:PANCHVATI\n8:CIVIL LINES\n9:OTHER\n";
			cin>>y;
			switch(y)
			{
				case 1:
					strcpy(address,"AWAS_VIKAS");
				break;
				case 2:
					strcpy(address,"NAI_BASTI");
				break;
				case 3:
					strcpy(address,"GOVINDPURAM");
				break;
				case 4:
					strcpy(address,"GEETA_NAGRI");
				break;
				case 5:
					strcpy(address,"CHASEERI");
				break;
				case 6:
					strcpy(address,"JATAAN");
				break;
				case 7:
					strcpy(address,"PANCHVATI");
				break;
				case 8:
					strcpy(address,"CIVIL_LINES");
				break;
				default:
					strcpy(address,"OTHER");
			}	
			cout<<"AREA\t\tCASES\n";
			while(!A.eof())
			{
				a.get(A);
				int k=a.search(address);
				if(k==1)
				{
					a.show();
					break;
				}
			}
			A.close();
		}
		else
			cout<<"*********************************WRONG choice*****************************"<<endl;
	}
}
void logedin_p(Patient &p)
{
	int x=p.welcome_record();
	while(x)
	{
		cout<<"1:SHOW RED ZONES\n2:SHOW HOSPITALS IN MY AREA\n3:SHOW MY VACCINATION RECORDS\n4:SHOW CASES IN PARTICULAR AREA\n5:SHOW MY DETAILS\n0:LOGOUT OUT\n";
		int y;
		cin>>y;
		if (y==0)
		{
			cout<<"*************************LOGGING OUT**************************"<<endl;
			break;
		}
		else if (y==1)
		{
			ifstream A;
			A.open("E:/area.txt");
			Area a;
			int c=0;
			cout<<"AREA\t\t\tCASES (Red zones are area with more than 10 cases)\n";
			while(!A.eof())
			{
				a.get(A);
				int k=a.isRedZone();
				if(k==1)
				{
					c++;
					a.show();
				}
			}
			if (c==0)
			{
				cout<<"NO RED ZONES IN BIJNOR\n";
			}
			A.close();
		}
		else if (y==2)
		{
			ifstream F;
			F.open("E:/hospital.txt");
			Hospital h;
			cout<<"HOSPITALS :"<<endl;
			while(!F.eof())
			{
				h.get(F);
				int k=inmyarea(p,h);
				if(k==1)
				{
					//cout<<"hello";
					h.show_name();
				}
			}
			F.close();
		}
		else if (y==3)
		{
			p.show_vaccination();
		}
		else if (y==4)
		{
			ifstream A;
			A.open("E:/area.txt");
			Area a;
			int y;
			char address[500];
			cout<<"AREA :::: (select from the following)"<<endl;
			cout<<"1:AWAS VIKAS\n2:NAI BASTI\n3:GOVIND PURAM\n4:GEETA NAGRI\n5:CHASEERI\n6:JATAAN\n7:PANCHVATI\n8:CIVIL LINES\n9:OTHER\n";
			cin>>y;
			switch(y)
			{
				case 1:
					strcpy(address,"AWAS_VIKAS");
				break;
				case 2:
					strcpy(address,"NAI_BASTI");
				break;
				case 3:
					strcpy(address,"GOVINDPURAM");
				break;
				case 4:
					strcpy(address,"GEETA_NAGRI");
				break;
				case 5:
					strcpy(address,"CHASEERI");
				break;
				case 6:
					strcpy(address,"JATAAN");
				break;
				case 7:
					strcpy(address,"PANCHVATI");
				break;
				case 8:
					strcpy(address,"CIVIL_LINES");
				break;
				default:
					strcpy(address,"OTHER");
			}	
			cout<<"AREA\t\tCASES\n";
			while(!A.eof())
			{
				a.get(A);
				int k=a.search(address);
				if(k==1)
				{
					a.show();
					break;
				}
			}
			A.close();
		}
		else if(y==5)
			p.show();
		else
			cout<<"*******************************WRONG choice***********************"<<endl;
		p.welcome_record();
	}
}
int main(int argc, char const *argv[])
{
	//setArea();
	ofstream F_p,F_h,F_a;
	ifstream F1,F2;
	int x=1;
	cout<<"**************WELCOME TO BIJNOR COVID CENTRE***************\n";
	while(x)
	{
		cout<<"1:login\n2:signin\n3:show city records\n0:exit"<<endl;
		cin>>x;
		if(x==1)
		{
			cout<<"1:hospital\n2:normal user\n3:back"<<endl;
			int y;
			cin>>y;
			if (y==1)
			{
				Hospital h;
				char name[500],password[500];
				cout<<"USERNAME:";
				cin>>name;
				cout<<"PASSWORD:";
				cin>>password;
				F1.open("E:/hospital.txt");
				int n=h.login(F1,name,password);
				F1.close();
				if(n==1)
				{
					h.welcome();
					logedin_h(h);
				}
				else
				{
					continue;
				}
			}
			else if (y==2)
			{
				Patient h;
				char name[500],password[500];
				cout<<"USERNAME:";
				cin>>name;
				cout<<"PASSWORD:";
				cin>>password;
				F1.open("E:/user.txt");
				int n=h.login(F1,name,password);
				F1.close();
				if(n==1)
				{
					h.welcome();
					logedin_p(h);
				}
				else
					continue;
			}
			else if (y==3)
			{
				cout<<"0000XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX000000000"<<endl;
			}
			else
				cout<<"*****************************wrong choice***************************"<<endl;
		}
		else if (x==2)
		{
			cout<<"1:hospital\n2:normal user\n3:back"<<endl;
			int y;
			cin>>y;
			if (y==1)
			{
				Hospital h;
				F_h.open("E:/hospital.txt",ios::app);
				h.set_val(F_h);
				F_h.close();
			}
			else if (y==2)
			{
				Patient h;
				F_p.open("E:/user.txt",ios::app);
				h.set_val(F_p);
				F_p.close();
			}
			else if (y==3)
			{
				cout<<"0000000XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX000000"<<endl;
			}
			else
				cout<<"*********************************wrong choice***********************************"<<endl;
		}
		else if (x==3)
		{
			Covid c;
			c.show();	
		}
		else if (x==0)
		{
			break;
		}
		else
			cout<<"**************************************wrong choice************************************"<<endl;
	}
	return 0;
}
