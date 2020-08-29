#include <iostream>
#include <iomanip>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <conio.h>

using namespace std;

class student
{
   int rollno;
   char name[20],fname[20],mname[20],clas[5];
   char grade;
   float pm,cm,mm,em,csm;
   float total;
   float per;
public:
   void enter();                 //function to input the data.
   void calc();                 //function to calculate the total and grade.
   void display();              //function to display the data.
   void display_table();        //function to display the data in tabular form.
   void write_in_file();        //function to write the data in file.
   int getrollno();             //function to return the student's rollno.
   void specific_search();      //function to search a specific record of student.
   void add_data();             //function to add more data(append).
   void display_all_record();   //function to display all the records of the file.
   void delete_data();          //function to delete a specific record.
   void result();               //function to show result of student.
   void entry_edit_menu();      //function to display menu3.
   void result_menu();          //function to display menu2.
   void modify_data();          //function to modify a specific record.
   void scolarship();           //function to display no. of scolarships and their data.
   void failr();                //function to display no. of fail students and their data.
} s;             //declaring an object of class student globally.
void student::calc()
{
   total=pm+cm+csm+mm+em;
   per=(total*100)/500;
   if(per>=90)
	 grade='A';
   else if(per>=75)
	 grade='B';
   else if(per>=50)
	 grade='C';
   else if(per>=33)
	 grade='E';
   else
	 grade='F';
}
void student::enter()
{
   cout<<"Hi! Please enter the information as given below:";
   cout<<"\nEnter the Roll number of Student:";
   cin>>rollno;
   cout<<"\nEnter the Class of Student:";
   gets(clas);
   cout<<"\nEnter the Name of Student:";
   gets(name);
   cout<<"\nEnter the name of Father:"<<"Mr.";
   gets(fname);
   cout<<"\nEnter the name of Mother:"<<"Mrs.";
   gets(mname);
   cout<<"\nEnter Marks in Chemistry out of 100:";
   cin>>cm;
   cout<<"\nEnter Marks in Physics out of 100:";
   cin>>pm;
   cout<<"\nEnter Marks in  Mathematics out of 100:";
   cin>>mm;
   cout<<"\nEnter Marks in English out of 100:";
   cin>>em;
   cout<<"\nEnter Marks in Computer Science out of 100:";
   cin>>csm;
   calc();                  //function calling.
}
void student::display()
{
   cout<<"\nRoll number of Student :"<<rollno;
   cout<<"\nName of Student :"<<name;
   cout<<"\nClass of Student:" <<clas;
   cout<<"\nName of father : "<<"Mr."<<fname;
   cout<<"\nName of mother : "<<"Mrs."<<mname;
   cout<<"\nMarks in Chemistry : "<<cm;
   cout<<"\nMarks in Physics : "<<pm;
   cout<<"\nMarks in Mathematics : "<<mm;
   cout<<"\nMarks in English : "<<em;
   cout<<"\nMarks in Computer Science : "<<csm;
   cout<<"\nPercentage of Student : "<<setprecision(4)<<per<<"%";
   cout<<"\nGrade of Student : "<<grade;
}
void student::display_table()
{
   cout<<rollno<<"\t"<<name<<"\t\t"<<pm<<"\t"<<cm<<"\t"<<mm<<"\t"<<em
   <<"\t"<<csm<<"\t"<<setprecision(4)<<per<<"%"<<"\t"<<grade<<"\n";
}
int student::getrollno()
{
    return rollno;
}
void student::write_in_file()
{
   ofstream outfile;
   outfile.open("std.data",ios::binary|ios::app);
   s.enter();                          //function calling.
   outfile.write((char*)&s,sizeof(student));
   outfile.close();                       //file is closed.
   cout<<"\n\n\nStudent Record has been created !! ";
   getch();
}
void student::display_all_record()
{
    ifstream infile;
    infile.open("std.data",ios::binary);
    if(!infile)
    {
	 cout<<"File not found !!!! Press any key....";
	 getch();
	 return;
    }
    cout<<"\n\n\n\n\t\tDisplay all Record !!!!\n\n\n\n";
    while(infile.read((char*)&s,sizeof(s)))
    {
	 s.display();                    //function calling.
    }
    infile.close();                     //file is closed.
    getch();
}
void student::delete_data()
{
     ifstream fin("std.data",ios::in);
     ofstream file("temp.data",ios::out);
     int rnoo;
     char fd='f';
     char confirm='n';
     cout<<"\n\n\t\tEnter Roll Number of Student whose Record is to be Deleted:\n\n\t";
     cin>>rnoo;
     while(!fin.eof())
     {
	      fin.read((char*)&s,sizeof(s));
	      if(s.getrollno()==rnoo)         //function calling
	      {
			s.display();        //function calling.
			fd='t';
			cout<<"\n\n\t\tAre you sure , you want to delete this record?(y/n):\n\n\n";
			cin>>confirm;
			if(confirm=='n')
			file.write((char*)&s,sizeof(s));
	      }
	      else
			file.write((char*)&s,sizeof(s));
       }
       if(fd=='f')
	     {
	     cout<<"\n\n\t\tRecord not found!!!\n\n";
	     system("pause");
	     }
       fin.close();          /* both the files are closed*/
       file.close();
       remove("std.data");
       rename("temp.data","stud.data");
       fin.open("std.data",ios::in);           //file is reopened.
       cout<<"\n\n\t\tNow the file contains:";
       while(!fin.eof())
       {
		fin.read((char*)&s,sizeof(s));
		if(fin.eof())
			break;
		s.display();
       }
       fin.close();           //file is closed.
       getch();
}
void student::modify_data()
{
     int fn=0,rono;
     fstream io;
     io.open("std.data",ios::in|ios::out|ios::binary);
     cout<<"\n\n\t\tEnter the Roll Number which is to be modified:";
     cin>>rono;
     if(!io)
     {
	  cout<<"\n\n\t\tFile could not be opened!!!!Press any key....";
	  getch();
     }
     while(io.read((char*)&s,sizeof(s))&&fn==0)
     {
	   if(s.getrollno()==rono)      //function calling.
	   {
		       s.display();               //function calling.
		       cout<<"\n\n\t\tPlease enter the new details of the Student:";
		       s.enter();                 //function calling.
		       int pos=(-1)*sizeof(s);
		       io.seekp(pos,ios::cur);
		       io.write((char*)&s,sizeof(student));
		       cout<<"\n\n\t\tRecord has been Updated...";
		       fn=1;
	     }
     }
     io.close();       //file is closed.
     if(fn==0)
	   cout<<"\n\n\tRecord not found!!!";
	   getch();
}
void student::scolarship()
{
     int count=0;
     ifstream fin;
     fin.open("std.data",ios::binary);
     if(!fin)
     {
	   cout<<"File could not found!!!!!Press any key......";
	   getch();
     }
     cout<<"\n\n\tThe details of students having scolarship are:-";
     while(fin.read((char*)&s,sizeof(s)))
     {
	if(per>=75)
	{
	    count++;
	    cout<<"\nName:"<<name<<endl<<"Percentage:"<<per<<"%"<<endl<<"Father 's name:"<<fname;
	 }
     }
     cout<<"\n\n\t\tThe Number of students having scolarship are:"<<count;
     fin.close();
     getch();
}
void student::failr()
{
     int cot=0;
     ifstream fin;
     fin.open("std.data",ios::binary);
     if(!fin)
     {
	   cout<<"File could not found!!!!!Press any key......";
	   getch();
     }
     cout<<"\n\n\tThe details ofstudents who are failed are:-";
     while(fin.read((char*)&s,sizeof(s)))
     {
	if(per<=35)
	{
	    cot++;
	    cout<<"\nName:"<<name<<endl<<"Percentage:"<<per<<"%"<<endl<<"Father 's name:"<<fname;
	 }
     }
     cout<<"\n\n\t\tThe Number of students who are failed are:"<<cot;
     fin.close();
     getch();
}
void student::result()
{
    ifstream infile;
    infile.open("std.data",ios::binary);
    if(!infile)
    {
	 cout<<"\n\n\tFile could not Found!!Press any Key.................";
	 getch();
    }
    cout<<"\n\n\n\t\tALL STUDENT RESULT:-\n\n\n";
    cout<<"***************************************************************************"<<endl;
    cout<<"ROLL NO.  NAME    PHYSICS   CHEMISTRY   MATHS   ENGLISH   CS   %AGE  GRADE"<<endl;
    cout<<"***************************************************************************"<<endl;
    while(!infile.eof()&&infile.read((char*)&s,sizeof(student)))
    {
		 s.display_table();         //function calling.
    }
    infile.close();                //file is closed.
    getch();
}
void student::specific_search()
{
     int rno;
     char found='n';
     ifstream fin;
     fin.open("std.data",ios::binary);
     cout<<"\nEnter the Roll Number which is to be searched for:";
     cin>>rno;
     if(!fin)
	  {
	  cout<<"File not found!!!!!!!!!!";
	  }
     else
     {
	   while(fin.read((char*)&s,sizeof(s)))
	   {
		    if(s.getrollno()==rno)          //function calling.
		    {
			   s.display();             //function calling.
			   found='y';
			   break;
		     }
	    }
     }
     fin.close();                    //file is closed.
     if(found=='n')
	    {
	    cout<<"Roll Number not Found!!!!!!!!!!!!!!";
	    }
     getch();
}
void student::add_data()
{
    ofstream fout("std.data",ios::app);
    char ans='y';
    while(ans=='y')
    {
	    s.enter();            //function calling.
	    fout.write((char*)&s,sizeof(s));
	    cout<<"\n\n\tRecord is Added to File.......\n\n\n";
	    cout<<"Want to Enter more Records?)(y/n)\n\n";
	    cin>>ans;
    }
    fout.close();             //file is closed.
    getch();
}
void student::result_menu()
{
    char a;
    int n;
    cout<<"\n\n\n\t\tRESULT MENU:-\n\n\n";
    cout<<"\n\n\t1. Class Result";
    cout<<"\n\n\t2. Student Report Card";
    cout<<"\n\n\t3. Number of scolarships";
    cout<<"\n\n\t4. Number of failure students";
    cout<<"\n\n\t5. Back To Main Menu";
    cout<<"\n\n\n\t\tEnter Your Choice(1 or 2 or 3)";
    cin>>a;
    system("CLS");
    switch(a)
    {
	 case '1': s.result();
	 break;
	 case '2': s.specific_search();
	 break;
	 case '3': s.scolarship();
	 break;
	 case '4': s.failr();
	 break;
	 case '5': break;
	 default: cout<<'\a';
		  s.result_menu();
     }
}
void student::entry_edit_menu()
{
     char b;
     int m;
     system("CLS");
     cout<<"\n\n\n\t\tENTRY MENU:-";
     cout<<"\n\n\t1. Create Student Report Card";
     cout<<"\n\n\t2. Display All Sudent Record";
     cout<<"\n\n\t3. Search Student Record";
     cout<<"\n\n\t4. Modify Student Record";
     cout<<"\n\n\t5. Delete Student Record";
     cout<<"\n\n\t6. Add New Student Record";
     cout<<"\n\n\t7. Back To Main Menu";
     cout<<"\n\n\n\t\tEnter Your Choice (1-7):";
     cin>>b;
    system("CLS");
     switch(b)
     {
	   case '1': s.write_in_file();
	   break;
	   case '2': s.display_all_record();
	   break;
	   case '3': s.specific_search();
	   break;
	   case '4':s.modify_data();
	   break;
	   case '5': s.delete_data();
	   break;
	   case '6':s.add_data();
	   break;
	   case '7':  break;
	   default: cout<<"\a";
		    s.entry_edit_menu();
     }
}
int main()
{
   system("CLS");
   char c;
   do{
	system("CLS");
	cout<<"\n\n\n\t\tMain Menu:-";
	cout<<"\n\n\t\t1. Result Menu";
	cout<<"\n\n\t\t2. Entry/Edit Menu";
	cout<<"\n\n\t\t3. exit from Menu";
	cout<<"\n\n\t\tPlease select one option(1-3)";
	cin>>c;
	system("CLS");
	switch(c)
	{
		 case '1': s.result_menu();  break;
		 case '2': s.entry_edit_menu();  break;
		 case '3': exit(0);
		 default: cout<<"\a";
	}
    }while(c!=3);

return 0;
}
