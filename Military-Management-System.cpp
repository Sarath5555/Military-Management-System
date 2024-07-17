#include <iostream>
#include <mysql.h>
#include<cstring>
#include<windows.h>
#include<sstream>
#include<stdio.h>
#include<conio.h>
#include<string>
#include<iomanip>
using namespace std;
char host[]="localhost";
char user[]="root";
char pass[]="Nn@9392442163";
class NewApplications {
    private:
        string state;
        string aadhar;
        string CandidateName;
        string FatherName;
        string MotherName;
        string Email;
        string MobileNumber;
        int Gender;
        float Height;
        int MeritalStatus;
        string HigherQualifiaction[4];
        string username;
        string password;
        bool applicationStatus;
};
string EMAIL1;
char ID;
enum IN {
    IN_BACK = 8, //backspace indication key
    IN_RET = 13  // Enter indication key
};
void SignUp(MYSQL* conn);
void Register(MYSQL* conn);
string TakePasswordFromUser(char sp = '*');
void Login(MYSQL* conn);
void Dashboard(MYSQL* conn);
void ApplyOnline(MYSQL* conn);
void MyProfile(MYSQL* conn);
void ApplicationStatus(MYSQL* conn);
void ChangePassword(MYSQL* conn);
void changeCanName(MYSQL* conn);
void changeFatName(MYSQL* conn);
void changeMothName(MYSQL* conn);
void changeNumber(MYSQL* conn);
void changeAadhar(MYSQL* conn);
void changeGender(MYSQL* conn);
void changeEmail(MYSQL* conn);
void changeHeight(MYSQL* conn);
void changeHeight(MYSQL* conn);
void changeMeritalStatus(MYSQL* conn);
void changeState(MYSQL* conn);
void EditApplication(MYSQL* conn);
void Dashboard1(MYSQL* conn);
void deleteRecord(MYSQL* conn);
void CreateSoldier(MYSQL* conn);
void MainPage(MYSQL* conn);
void LoginPage(MYSQL* conn);
void CommanderLogin(MYSQL* conn);
void FieldMarshal(MYSQL* conn);
void General(MYSQL* conn);
void LieutanatGeneral(MYSQL* conn);
void MajorGeneral(MYSQL* conn);
void Brigadier(MYSQL* conn);
void Colonel(MYSQL* conn);
void LieutantColonel(MYSQL* conn);
void ShowHeadQuarters(MYSQL* conn);
void ShowCommand(MYSQL* conn);
void ShowDivision(MYSQL* conn);
void ShowBrigade(MYSQL* conn);
void ShowRegiment(MYSQL* conn);
void ShowCompany(MYSQL* conn);
void SearchFM(MYSQL* conn);
void SearchGeneral(MYSQL* conn);
void SearchLG(MYSQL* conn);
void SearchMG(MYSQL* conn);
void SearchBrigade(MYSQL* conn);
void SearchColonel(MYSQL* conn);
void SearchLC(MYSQL* conn);

string TakePasswordFromUser(char sp)
{
	// Stores the password
	string passwd = "";
	char ch_ipt;

	// Until condition is true
	while (true) {
		ch_ipt = getch();
		// if the ch_ipt
		if (ch_ipt == IN::IN_RET) {
			cout << endl;
			return passwd;
		}
		else if (ch_ipt == IN::IN_BACK && passwd.length() != 0) {
			//passwd.pop_back(); //It removes values from end
			cout << "\b \b";  //The usual way of erasing the last character on the console is to use the sequence "\b \b"
			continue;
		}
		else if (ch_ipt == IN::IN_BACK && passwd.length() == 0) {
			continue;
		}

		passwd.push_back(ch_ipt);
		cout << sp;
	}
}
string EMAIL;
void delete_application(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        int qstate=0;
        string email;
        cout<<"\t\t\t\tEnter email:   "<<endl;
        getline(cin >> ws, email);
        stringstream ss;
        ss<<" DELETE FROM applicants WHERE email='"<<email<<"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record upadated..." << endl;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
        }
    }else{
        cout << "Connection Error" << endl;
    }
}
void SignUp(MYSQL* conn) {
    int choice=0;
    while(choice!=3) {
        system("cls");
        cout << "\n\n\n\n\n\t\t\t\t\t\t\tWelcome to Indian Army Portal";
        cout << "\n\n\t\t\t\t1.Register";
        cout << "\n\n\t\t\t\t2.Login";
        cout << "\n\n\t\t\t\t3.delete application";
        cout << "\n\n\t\t\t\t4.Exit";
        cout << "\n\n\t\t\tEnter correct choice:  ";
        cin >> choice;
        switch(choice) {
            case 1:
                Register(conn);
                break;
            case 2:
                Login(conn);
                break;
            case 3:
            	delete_application();
            	break;
            case 4:
                choice=3;
                break;
            default:
                cout << "\n\n\t\t\tEnter correct choice!";
                break;
        }
    }
}

void Register(MYSQL* conn) {
	int qstate =0;
    cout << "\n\n\n\n\t\t\t\t\t\t\t============== Registration Process ==============\n\n\n";
    string email, password1,password2;
    cout << "\t|   Enter your Email ID :     |      ";
    getline(cin >> ws, email);
    cout << "\t|   Enter password      :     |      ";
    password1=TakePasswordFromUser();
    cout << "\t|   Confirm password    :     |      ";
    password2=TakePasswordFromUser();
    if(password1==password2) {
        EMAIL = email;
        stringstream ss;
        ss<<"INSERT INTO applicants(email,password) VALUES('"<<email<<"','"<<password1<<"')";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "\n\t\t\t\t\tData Inserted Into the Database..." << endl;
        }else{
            cout << "\n\t\t\t\t\tData Insertion Failed" << mysql_error(conn) << endl;
        }
        cout << "\n\t\t\t\t\tRegistration Compleated....\n\n\n";
        Dashboard(conn);
    }
    else {
        cout << "\t\t\t\t\tInvalid Password!\n";
    }
}

void Login(MYSQL* conn) {
    cout << "\n\n\n\n\t\t\t\t\t\t\t============== Login Process ==============\n\n\n";
    string email, password;
    cout << "\t|\tEnter Email ID  :       |     ";
    getline(cin >> ws, email);
    cout << "\t\tEnter Password   :       |     ";
    password=TakePasswordFromUser();
    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
    ss<<"SELECT * FROM applicants WHERE email = '"<<email<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    if (!(mysql_query(conn, q))) {
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
            if(row[0]==email && row[1]==password) {
                EMAIL = email;
                Dashboard1(conn);
            }
            else {
		        cout <<"\n\t\t\tEntered Invalid Email/Password!\n";
		    }
		}
	}
	else
	{
		cout << "\n\n * Query Failed **";
	}
    

}


void all_applications(){
	MYSQL * conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase",3306,NULL,0);
    cout << "|   Email    |   Password   |    Candidate    |   Father   |   Mother    |   State   |    Gender    |   Aadhar   |   Mobile   |   Height   |    Merital   |\n\n";
    //cout<<"|  Email"<<"\t | \t"<<"password"<<"\t | \t"<<"candidate"<<"\t | \t"<<"father"<<"\t | \t"<<"mother"<<"\t | \t"<<"state"<<"\t | \t"<<"gender"<<"\t | \t"<<"aadhar"<<"\t | \t"<<"Mobile nuber"<<"\t | \t"<<"height"<<"\t | \t"<<"Merital"<<endl;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM applicants");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout << "\n|" << row[0] <<"\t |" << row[1] <<"\t |" << row[2] <<"\t |" << row[3] <<"\t |"<<row[4] <<"\t | "<<row[5]<<"\t |"<<row[6]<<"\t |"<<row[7]<<"\t |"<<row[8]<<"\t | "<<row[9]<<"\t |"<<row[10]<<endl;
             }
        }
    }
}
void Dashboard(MYSQL* conn) {
    int choice=0;
    while(choice!=6) {
       cout << "\n\n\n\n\t\t\t\t\t\t\t============== DashBoard ==============\n\n\n";
       cout << "\t\t\t\t\t\t__\n";
       cout << "\n\n\n";
       cout << "\t\t\t\t\t\t1.Apply Online\n";
       cout << "\t\t\t\t\t\t2.My Profile\n";
       cout << "\t\t\t\t\t\t3.Change Password\n";
       cout << "\t\t\t\t\t\t4.All application details\n";
       cout << "\t\t\t\t\t\t5.Logout\n";  
       cout << "\t\t\t\t\t\t6.Exit\n";  
       cout << "\t\t\t\t\tEnter correct choice:  ";
       cin >> choice;
       switch(choice) {
        case 1:
            ApplyOnline(conn);
            break;
        case 2:
            MyProfile(conn);
            break;
        case 3:
            ChangePassword(conn);
            break;
        case 4:
       	    all_applications();
       	    break;
        case 5:
            deleteRecord(conn);
            break;
        case 6:
            choice=6;
            break;
        default:
            cout << "\t\t\t\t\t\tEnter correct option!\n";
            break;
       }
    }
}

void deleteRecord(MYSQL* conn) {
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        int qstate=0;
        stringstream ss;
        ss<<" DELETE FROM applicants WHERE email='"<<EMAIL<<"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record upadated..." << endl;
            cout << "Press B to go back";
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
    }
    system("pause");
    system("cls");
    SignUp(conn);
}


void Dashboard1(MYSQL* conn) {
    int choice=0;
    while(choice!=6) {
       cout << "\n\n\n\n\t\t\t\t\t\t\t============== DashBoard ==============\n\n\n";
       cout << "\t\t\t\t\t\t__\n";
       cout << "\n\n\n";
       cout << "\t\t\t\t\t\t1.Edit profile\n";
       cout << "\t\t\t\t\t\t2.My Profile\n";
       cout << "\t\t\t\t\t\t3.Change Password\n";
       cout << "\t\t\t\t\t\t4.All application details\n";
		cout << "\t\t\t\t\t\t5.Logout\n";  
       cout << "\t\t\t\t\t\t6.Exit\n";  		  
       cout << "\t\t\t\t\tEnter correct choice:  ";
       cin >> choice;
       switch(choice) {
        case 1:
            EditApplication(conn);
            break;
        case 2:
            MyProfile(conn);
            break;
        case 3:
            ChangePassword(conn);
            break;
        case 4:
       	    all_applications();
       	    break;
        case 5:
            deleteRecord(conn);
            break;
        case 6:
            choice=6;
            break;
        default:
            cout << "\t\t\t\t\t\tEnter correct option!\n";
            break;
       }
    }
}
void changeCanName(MYSQL* conn) {
    MyProfile(conn);
    string Name;
    cout << "\n\n\t\t\t\tEnter new candidate name : ";
    getline(cin >> ws, Name);

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
	int qstate = 0;
    ss<<"UPDATE applicants SET candidate = '"<<Name<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}

void changeFatName(MYSQL* conn) {
    MyProfile(conn);
    string Name;
    cout << "\n\n\t\t\t\tEnter new father name : ";
    getline(cin >> ws, Name);

    stringstream ss;
    MYSQL_RES* res;
	int qstate = 0;
	MYSQL_ROW row;
    ss<<"UPDATE applicants SET father = '"<<Name<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}


void changeMothName(MYSQL* conn) {
    MyProfile(conn);
    string Name;
    cout << "\n\n\t\t\t\tEnter new mother name : ";
    getline(cin >> ws, Name);

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
	int qstate = 0;
    ss<<"UPDATE applicants SET mother = '"<<Name<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}

void changeNumber(MYSQL* conn) {
    MyProfile(conn);
    string Name;
    cout << "\n\n\t\t\t\tEnter new mobile number : ";
    getline(cin >> ws, Name);

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
	int qstate = 0;
    ss<<"UPDATE applicants SET number = '"<<Name<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}


void changeAadhar(MYSQL* conn) {
    MyProfile(conn);
    string Name;
    cout << "\n\n\t\t\t\tEnter new aadhar number : ";
    getline(cin >> ws, Name);

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
int qstate = 0;
    ss<<"UPDATE applicants SET aadhar = '"<<Name<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}



void changeGender(MYSQL* conn) {
    MyProfile(conn);
    int num;
    cout << "\n\n\t\t\t\tEdit Gender : ";
    cin >> num;

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
int qstate = 0;
    ss<<"UPDATE applicants SET gender = "<<num<<" WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}


void changeEmail(MYSQL* conn) {
    MyProfile(conn);
    string Name;
    cout << "\n\n\t\t\t\tEnter new email : ";
    getline(cin >> ws, Name);

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
int qstate = 0;
    ss<<"UPDATE applicants SET email = '"<<Name<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "\n\n\t\t\t\tInsertion Error" << mysql_error(conn) << endl;
    }
}


void changeHeight(MYSQL* conn) {
    MyProfile(conn);
    float height;
    cout << "Enter new candidate name : ";
    cin >> height;

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
int qstate = 0;
    ss<<"UPDATE applicants SET height = "<<height<<" WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "Insertion Error" << mysql_error(conn) << endl;
    }
}



void changeMeritalStatus(MYSQL* conn) {
    MyProfile(conn);
    int num;
    cout << "\n\n\t\t\t\tEdit Merital Status : ";
    cin >> num;

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
int qstate = 0;
    ss<<"UPDATE applicants SET merital = "<<num<<" WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "Insertion Error" << mysql_error(conn) << endl;
    }
}


void changeState(MYSQL* conn) {
    MyProfile(conn);
    string state;
    cout << "\n\n\t\t\t\tEdit State : ";
    getline(cin>>ws,state);

    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
int qstate = 0;
    ss<<"UPDATE applicants SET state = '"<<state<<"' WHERE email='"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "Insertion Error" << mysql_error(conn) << endl;
    }
}

void EditApplication(MYSQL* conn) {
    int choice;
    cout << "\n\t\t\t\t1. Email";
    cout << "\n\t\t\t\t2. CandidateName";
    cout << "\n\t\t\t\t3. FatherName";
    cout << "\n\t\t\t\t4. MotherName";
    cout << "\n\t\t\t\t5. Gender";
    cout << "\n\t\t\t\t6. Mobile Number";
    cout << "\n\t\t\t\t7. Aadhar";
    cout << "\n\t\t\t\t8. Merital Status";
    cout << "\n\t\t\t\t9. State";
    cout << "\n\t\t\t\t10. Height";
    cout << "\n\t\t\t\tEnter appropriate value for editing the values  :  "; 
    cin >> choice;
    switch(choice) {
        case 1:
            changeEmail(conn);
            break;
        case 2:
            changeCanName(conn);
            break;
        case 3:
            changeFatName(conn);
            break;
        case 4:
            changeMothName(conn);
            break;
        case 5:
            changeGender(conn);
            break;
        case 6:
            changeNumber(conn);
            break;
	  case 7:
            changeAadhar(conn);
            break;
        case 8:
            changeMeritalStatus(conn);
            break;
        case 9:
            changeState(conn);
            break;
        case 10:
            changeHeight(conn);
            break;
        default:
            cout << "Enter correct choice : ";
    } 

}


void ApplyOnline(MYSQL* conn) {
    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
	int qstate = 0;
    string state;
    string aadhar;
    string CandidateName;
    string FatherName;
    string MotherName;
    string date;
    string MobileNumber;
    int Gender;
    float Height;
    int MeritalStatus;
    cout << "\n\n\n\n\t\t\t\t\t=================== Indian Army ==================\n\n";
    cout << "\t\t\t\t   Application Form    :    \n";
    cout << "\n\t\t\t\t Personal Details :    \n";
    cout << "\n\t\t\t\t\t\t|    State           :      |      ";
    getline(cin >> ws, state);
    cout << "\t\t\t\t\t\t|    Candidate Name  :      |      ";
    getline(cin >> ws, CandidateName);
    cout << "\t\t\t\t\t\t|    Father Name     :      |      ";
    getline(cin >> ws, FatherName);
    cout << "\t\t\t\t\t\t|    Mother Name     :      |      ";
    getline(cin >> ws, MotherName);
    cout << "\n\t\t\t\t\t\t|    Gender        :          ";
    cout << "\n\t\t\t\t\t\t\t1.Male";
    cout << "\n\t\t\t\t\t\t\t2.Female";
    cout << "\n\t\t\t\t\t\t\t";
    cin >> Gender;
    cout << "\t\t\t\t\t\t|    Marital Status:          ";
    cout << "\n\t\t\t\t\t\t\t1.Married";
    cout << "\n\t\t\t\t\t\t\t2.UnMarried";
    cout << "\n\t\t\t\t\t\t\t";
    cin >> MeritalStatus;
    
    cout << "\t\t\t\t\t\t|    Height        :     |     ";
    cin >> Height;

    cout << "\n\t\t\t\t\t  Contact Details :\n";
    cout << "\t\t\t\t\t\t|    Mobile Number :    |    ";
    getline(cin >> ws, MobileNumber);
    
    cout << "\t\t\t\t\t\t|    Aadhar Number :    |    ";
    getline(cin >> ws, aadhar);

    ss<<"UPDATE applicants SET candidate = '"<<CandidateName<<"', father = '"<<FatherName<<"', mother = '"<<MotherName<<"', state = '"<<state<<"', gender = '"<<Gender<<"', aadhar = '"<<aadhar<<"', number = '"<<MobileNumber<<"', height = "<<Height<<", merital = "<<MeritalStatus<<" WHERE email = '"<<EMAIL<<"'";
    string query = ss.str();
    const char* q = query.c_str();
    qstate = mysql_query(conn, q);
    if(qstate == 0){
        cout << "\n\t\t\t\t\t Data Inserted Successfully..." << endl;       
    } else{
        cout << "Insertion Error" << mysql_error(conn) << endl;
    }
}
void MyProfile(MYSQL* conn) { 
    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
    ss << "SELECT * FROM applicants WHERE email= '"<<EMAIL<<"' ";
    string query = ss.str();
	const char* q = query.c_str();
    if (!(mysql_query(conn, q))) {
        res = mysql_store_result(conn);
        while (row = mysql_fetch_row(res))
        {
            cout << "\n\n\n\n\t\t\t\t\t============== Indian Army ==============\n\n\n";
            cout << "\t\t\t\t\t|       My Profile         |\n";
            cout << "\n\n\t\t\t\t\t\t===== Personal Details =====\n";
            cout << "\n\t\t\t\t\t\t|   Name            :         " << row[2];
            cout << "\n\t\t\t\t\t\t|   State           :         " << row[5];
            cout << "\n\t\t\t\t\t\t|   Father Name     :         " << row[3];
            cout << "\n\t\t\t\t\t\t|   Mother Name     :         " << row[4];
            cout << "\n\t\t\t\t\t\t|   Aadhar          :         " << row[7];
            cout << "\n\t\t\t\t\t\t|   Gender          :         ";
            if(row[6]) {
                cout << "Male ";
            }
            else {
                cout << "Female";
            }
            cout << "\n\t\t\t\t\t\t|   Merital Status  :         ";
            if(row[10]) {
                cout << "UnMarried ";
            }
            else {
                cout << "married";
            }
            cout << "\n\t\t\t\t\t\t|   Height          :          " << row[9];
            cout << "\n\n\t\t\t\t\t\t===== Contact Details =====\n";
            cout << "\n\t\t\t\t\t\t|   Mobile Number   :           " << row[8];

        }
    }
}
void ChangePassword(MYSQL* conn) {
    stringstream ss;
    MYSQL_RES* res;
	MYSQL_ROW row;
	int qstate = 0;
    string password1;
    string password2;
    string password3;
    cout << "\n\t\t\t\t\t\tEnter old Password  :    ";
    getline(cin >> ws, password1);
    cout << "\t\t\t\t\t\tEnter new Password  :    ";
    getline(cin >> ws, password2);
    cout << "\t\t\t\t\t\tConfirm Password    :    ";
    getline(cin >> ws, password3);
    if(password2==password3) {
        ss<<"UPDATE applicants SET password = '"<<password3<<"' WHERE email = '"<<EMAIL<<"'";
	    string query = ss.str();
	    const char* q = query.c_str();
	    qstate = mysql_query(conn, q);
	    if(qstate == 0){
	    cout << "\n\t\t\t\t\t\tPassword Changed Successfully!";
	    }else{
	    	cout << "Insertion Error" << mysql_error(conn) << endl;
    	} 
    }
    else {
        cout << "\n\t\t\t\t\t\tEntered a Wrong Password!" << endl;      
    }
}
string getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=8;
  const char RETURN=13;
  string password;
  unsigned char ch=0;
  cout <<prompt;
  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else if(ch==0 || ch==224) // handle escape sequences
         {
             getch(); // ignore non printable chars
             continue;
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

class weapon{
	public:
	void addrec();
	void deletion();
	void updating();
	void reupdating();
	void all_details();	
	void particular_details();
};
void weapon::addrec(){
    MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        string name,ammotype,range;
        int qstate=0,mafdat,license,stock;
        cout << "\tEnter name of the weapon: ";
        getline(cin >> ws, name);
        
        cout << "\tEnter the weapon manfacturing year:  ";
        cin>>mafdat;
        
        cout << "\tEnter the weapon license number:  ";
        cin>>license;
    
        cout<<"\tEnter the stock that we have:  ";
        cin>>stock;
        
        cout<<"\tEnter the type of ammo:  ";
        getline(cin >> ws, ammotype);
        
        stringstream ss;
        ss << "INSERT INTO weapon_details(name,mafdat,license,stock,ammotype) VALUES('"<<name<<"',"<< mafdat << ","<<license << "," <<stock <<",'"<<ammotype<<"')";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            //cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            //cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        //cin >> dummy;
    }

    system("pause");
    system("cls");
}
void weapon::deletion()
	{
	
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        int qstate=0;
        string name;
        cout<<"\n\t\t\t\tEnter the weapon name to delete from the database"<<endl;
        getline(cin >> ws, name);
        stringstream ss;
        ss<<" DELETE FROM weapon_details WHERE name='"<<name<<"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record upadated..." << endl;
            cout << "Press B to go back";
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
    }
    system("pause");
    system("cls");
}
void weapon::updating(){
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        int qstate=0,stock;
        string name;
        cout<<"\n\t\t\t\tEnter the name of the weapon that has taken: "<<endl;
        getline(cin >> ws, name);
        cout<<"\n\t\t\t\tEnter how many you are taking: "<<endl;
        cin>>stock;
        stringstream ss;
        ss<<" UPDATE weapon_details SET stock= stock - "<<stock<<" WHERE name='"<<name<<"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record upadated..." << endl;
            cout << "Press B to go back";
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
    }
    system("pause");
    system("cls");
}
void weapon::reupdating(){
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        int qstate=0,stock;
        string name;
        cout<<"\n\t\t\t\tEnter the name of the returning weapon:  ";
        cin>>name;
        cout<<"\n\t\t\t\tEnter how many weapons you are returning:  ";
        cin>>stock;
        stringstream ss;
        ss<<" UPDATE weapon_details SET stock=stock + "<<stock<<" WHERE name='"<<name<<"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record upadated..." << endl;
            cout << "Press B to go back";
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
    }
    system("pause");
    system("cls");
}
void weapon::all_details(){
	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase",3306,NULL,0);
    cout << "\n\n";
    cout<<"\t\t\ts_no"<<"\t | \t"<<"name"<<"\t | \t"<<"mafdat"<<"\t | \t"<<"license"<<"\t | \t"<<"stock"<<"\t | \t"<<"ammotype"<<endl;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM weapon_details");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout << "\t\t\t" << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t"<<row[4] <<"\t | \t"<<row[5]<<endl;
             }
        }
    }
    
}
void weapon::particular_details(){
	MYSQL* conn;
    MYSQL_ROW row;
    string name;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase",3306,NULL,0);
    if(conn){
       cout << "\n\t\t\t\tEnter Name of the weapon: ";
       getline(cin >> ws, name);
    	stringstream ss;
        ss << "select * FROM weapon_details  WHERE name = '" << name << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
               cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t"<<row[4] <<"\t | \t"<<row[5]<<endl;
                
             }
        }
    }
}
void weapons(){
	weapon obj;
	int n;
	int testing=1;
	const char *correct_password="1234";
    string password=getpass("\n\t\t\t Please enter the password:  ",true); // Show asterisks
    if(password==correct_password){
    cout<<"\n\t\t\t The password entered is correct"<<endl;
	while(testing==1){
		//system("cls");
		cout<<"\n\n\n\t\t1. To Add Weapon Details"<<endl;
		cout<<"\t\t2. To take a weapon from military base"<<endl;
		cout<<"\t\t3. For returning the weapon"<<endl;
		cout<<"\t\t4. For delete the data"<<endl;
		cout<<"\t\t5. For all weapon details"<<endl;
		cout<<"\t\t6. For particular details"<<endl;
		cout<<"\t\t7. Exit"<<endl;
		cout<<"\t\t Enter your choice:  ";
		cin>>n;
		switch(n){
			case 1:
			 obj.addrec();	
			 break;
			case 2:
		    obj.updating();
		    break;
		    case 3:
		    obj.reupdating();
		    break;
		    case 4:
		    obj.deletion();
		    break;
		    case 5:
		    obj.all_details();
		    break;
		    case 6:
		    obj.particular_details();
		    break;
		    case 7:
		    testing=0;
		    break;
		}
	}
}
 else {
 	cout<<"\n\t\t\t\tEntered wrong password"<<endl;
 }
}
void application(){
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn) {
        SignUp(conn);
    }
    else{
            cout << "Connection Error" << endl;
            cout << "Press B to go back";
    }   	 
}
void A_med(){
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        string name,company,Batch_number;
        int qstate=0,quantity,Remaining_quantity;
        cout << "\t\t\t\tEnter company name: ";
        getline(cin >> ws, company);
        
        cout << "\t\t\t\tEnter name:  ";
        getline(cin >> ws, name);
        
        cout << "\t\t\t\tEnter Batch number:  ";
        getline(cin >> ws, Batch_number);
        
        cout << "\t\t\t\tEnter quantity:  ";
        cin>>quantity;
        
        cout << "\t\t\t\tEnter Remaining quantity:  ";
        cin>>Remaining_quantity;
        
        stringstream ss;
        ss << "INSERT INTO medicine(company,name,Batch_number,quantity,Remaining_quantity) VALUES('"<<company<<"','"<<name<<"','"<<Batch_number<<"',"<<quantity<<","<<Remaining_quantity<<")";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record Inserted..." << endl;
            cout << "Press B to go back";
            //cin >> dummy;
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
            //cin >> dummy;
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
        //cin >> dummy;
    }

    system("pause");
    system("cls");
}
void T_med(){
	MYSQL* conn;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase", 3306, NULL, 0);
    if(conn){
        int qstate=0,Remaining_quantity;
        string company;
        cout<<"\t\t\t\tEnter medicine name : ";
        getline(cin >> ws, company);
        cout<<"\t\t\t\tEnter Required quantity: ";
        cin>>Remaining_quantity;
        stringstream ss;
        ss<<" UPDATE medicine SET Remaining_quantity= Remaining_quantity - "<<Remaining_quantity<<" WHERE company='"<<company<<"'";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "Record upadated..." << endl;
            cout << "Press B to go back";
        }else{
            cout << "Insert Error" << mysql_error(conn) << endl;
            cout << "Press B to go back";
        }
    }else{
        cout << "Connection Error" << endl;
        cout << "Press B to go back";
    }
    system("pause");
    system("cls");
}
void s_med(){
   	MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase",3306,NULL,0);
    cout<<"s_no"<<"\t | \t"<<"company"<<"\t | \t"<<"name"<<"\t | \t"<<"Batch_number"<<"\t | \t"<<"quantity"<<"\t | \t"<<"Remaining quantity"<<endl;
    if(conn){
        int qstate = mysql_query(conn, "SELECT * FROM medicine");
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
                cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t"<<row[4] <<"\t | \t"<<row[5]<<endl;
             }
        }
    }
}
void p_med(){
	MYSQL* conn;
    MYSQL_ROW row;
    string company;
    MYSQL_RES* res;
    conn = mysql_init(0);
    conn = mysql_real_connect(conn,host,user,pass,"militarybase",3306,NULL,0);
    if(conn){
       cout << "Enter Name of company: ";
       getline(cin >> ws, company);
    	stringstream ss;
        ss << "select * FROM medicine  WHERE company = '" << company << "'";
        string query = ss.str();
        const char* q = query.c_str();
        int qstate = mysql_query(conn, q);
        if(!qstate){
            res = mysql_store_result(conn);
            while(row = mysql_fetch_row(res)){
              cout << row[0] <<"\t | \t" << row[1] <<"\t | \t" << row[2] <<"\t | \t" << row[3] <<"\t | \t"<<row[4] <<"\t | \t"<<row[5]<<endl;  
             }
        }
    }
}
void medicines(){
	int n;
	int k=1;
	while(k==1){
	cout<<"\n\n\n\t\t\t\t1. Add medicine\n"<<endl;
	cout<<"\t\t\t\t2. Take medicine\n"<<endl;
	cout<<"\t\t\t\t3. show medicines\n"<<endl;
	cout<<"\t\t\t\t4. particular medicine\n"<<endl;
	cout<<"\t\t\t\t5. exit\n"<<endl;
	cout<<"\t\t\t\tEnter your choice:   ";
	cin>>n;
	switch(n){
	case 1:
	A_med();
	break;
	case 2:
	T_med();
	break;
	case 3:
	s_med();
	break;
	case 4:
	p_med();
	break;
	case 5:
	k=0;
	break;	
	}
	}
}
void login(MYSQL* conn){
	int k;
	int test=1;
	while(test==1){
	 system("cls");
	 cout<<"\t============================================================================================================\n"<<endl<<endl;
	 cout<<"\t\t\t\t\t  military management system    "<<endl<<endl;
	 cout<<"\t============================================================================================================\n"<<endl<<endl;
	 cout<<"\n\n\t\t Enter '1' for application details\n"<<endl;
	 cout<<"\t\t Enter '2' for weapon deatils\n"<<endl;
	 cout<<"\t\t Enter '3' for medicine details\n"<<endl;
	 cout<<"\t\t Enter '4' for military officials\n"<<endl;
	 cout<<"\t\t Enter '5' for exit\n"<<endl;
	 cout<<"\t\t Enter your choice:   ";
	 cin>>k;
	 switch(k){
	 	case 1:
	 	application();
	 	break;
	 	case 2:
	 	weapons();
	 	break;
	 	case 3:
	 	medicines();
	 	break;
	 	case 4:
	 	MainPage(conn);
	 	break;
	 	case 5:
	 	test=0;
	 	break;
	 }
	}
}
int main(){
    MYSQL* con;
     con = mysql_init(0);
    con = mysql_real_connect(con,host,user,pass,"militarybase",3306,NULL,0);
    string usname;
    string psswd;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, 13);
    cout<<endl;
    cout << setw(30) << "\t\t\t"<< "*\n\n";
    cout << setw(30) << "\t\t\t" <<"*"<<"                                 "<<"  *"<<endl;
    cout << setw(43) << "\t\t" << "MILITARY MANAGEMENT SYSTEM" << endl ;
    cout << setw(30) << "\t\t\t" <<"*"<<"                                 "<<"  *"<<endl<<endl;
    cout << setw(30) << "\t\t\t" << "*\n\n\n\n";
    SetConsoleTextAttribute(hConsole, 13);
    cout << setw(36)<<"\t\t\t\t" << "LOGIN\n\n";
    cout << setw(30) <<" "<< "Enter Login Credentials\n\n";
    cout << setw(30) << " " << "Enter Username: ";
    getline(cin >> ws, usname);
	cout << endl;
    cout << setw(30) << " " << "Enter Password: ";
    psswd=TakePasswordFromUser();
    MYSQL_RES* res;
    MYSQL_ROW  row;
    stringstream a;
    a << "SELECT * FROM login WHERE Username = '" << usname << "' ";
    string b = a.str();
    const char* query = b.c_str();
    if (!(mysql_query(con, query))) {

        res = mysql_store_result(con);
        while (row = mysql_fetch_row(res))
        {

            if (psswd == row[2] && usname == row[1]) {
                system("COLOR 02");
                cout << endl << endl << setw(35) << " ";
                for (int i = 0; i <=7; i++) {
                    cout << "* ";
                    Sleep(200);
                }              
                cout << endl<< setw(34) << " " << "WELCOME TO PORTAL" << endl;

                cout<<  setw(35) << " ";
                for (int i = 0; i <= 7; i++) {
                    cout << "* ";
                    Sleep(200);
                }
                system("cls");
                login(con);
            }
            else {
                cout << "Credentials are wrong" << endl;
            }
        }
    }
}
void CreateSoldier(MYSQL* conn) {

	string Name;
    int Id;
    int Command;
    int Division;
    int Brigade;
    int Regiment;
    int RifleCompany;
    int Platoon;
    int Section;
	stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;
        int qstate = 0;

        cout << "\n\n\n\n\n\t\t\t\t\t\t\tSoldier Details";
        cout << "\n\t\t\t\t|   Enter ID           :   ";
        cin >> Id;
        cout << "\n\t\t\t\t|   Enter soldier Name :   ";
        getline(cin >> ws, Name);
        cout << "\n\t\t\t\t|   Enter Command      :   ";
        cin >> Command;
        cout << "\n\t\t\t\t|   Enter Division     :   ";
        cin >> Division;
        cout << "\n\t\t\t\t|   Enter Brigade      :   ";
        cin >> Brigade;
        cout << "\n\t\t\t\t|   Enter Regiment     :   ";
        cin >> Regiment;
        cout << "\n\t\t\t\t|   Enter RifleCompany :   ";
        cin >> RifleCompany;
        cout << "\n\t\t\t\t|   Enter Platoon      :   ";
        cin >> Platoon;
        cout << "\n\t\t\t\t|   Enter Section      :   ";
        cin >> Section;

        ss << "INSERT INTO soldier(soldier_id, name, command_id, division_id, brigade_id, regiment_id, company_id, platoon_id, section_id) VALUES("<<Id<<", '"<<Name<<"', "<<Command<<", "<<Division<<", "<<Brigade<<", "<<Regiment<<", "<<RifleCompany<<", "<<Platoon<<", "<<Section<<")";
        string query = ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0){
            cout << "\n\t\t\t\t\tData Inserted Into the Database..." << endl;
        }else{
            cout << "\n\t\t\t\t\tData Insertion Failed" << mysql_error(conn) << endl;
        }
        cout << "\n\t\t\t\t\tSoldier Details Entered Successfully!" << endl;
   
}


void MainPage(MYSQL* conn) {
    int choice=0;
    while(choice!=3) {
        cout << "\n\n\n\n\n\t\t\t\t\t\t\tWelcome to Military Base";
        cout << "\n\n\t\t\t\t1.Enter New Soldier Details";
        cout << "\n\n\t\t\t\t2.Login";
        cout << "\n\n\t\t\t\t3.Exit";
        cout << "\n\n\t\t\tEnter correct choice:  ";
        cin >> choice;
        switch(choice) {
            case 1:
                CreateSoldier(conn);
                break;
            case 2:
                LoginPage(conn);
                break;
            case 3:
                choice=3;
                break;
            default:
                cout << "\n\n\t\t\tEnter correct choice!";
                break;
        }
    }
}

void LoginPage(MYSQL* conn) {
  int choice=0;
  while(choice!=8) {
    cout << "\n\n\n\n\n\t\t\t\t\t\t\t====== Login ======";
    cout << "\n\t\t\t\t1. Field Marshal";
    cout << "\n\t\t\t\t2. General";
    cout << "\n\t\t\t\t3. Lieutanat General";
    cout << "\n\t\t\t\t4. Major General";
    cout << "\n\t\t\t\t5. Brigadier";
    cout << "\n\t\t\t\t6. Colonel";
    cout << "\n\t\t\t\t7. Lieutant Colonel";
    cout << "\n\t\t\t\t8. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
   
    switch (choice)
    {
    case 1:
      CommanderLogin(conn);
      break;
    case 2:
      CommanderLogin(conn);
      break;
    case 3:
      CommanderLogin(conn);
      break;
    case 4:
      CommanderLogin(conn);
      break;
    case 5:
      CommanderLogin(conn);
      break;
    case 6:
      CommanderLogin(conn);
      break;
    case 7:
      CommanderLogin(conn);
      break;
    case 8:
      choice=8;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
 
}

void CommanderLogin(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  string email, password;
  cout << "\n\t\t\t\tEnter Email:";
  getline(cin >> ws, email);
  cout << "\n\t\t\t\tEnter Password:";
  getline(cin >> ws, password);

  ss << "SELECT * FROM ranks WHERE email= '"<<email<<"' ";
  string query = ss.str();
const char* q = query.c_str();

  if (!(mysql_query(conn, q))) {
 res = mysql_store_result(conn);
    while (row = mysql_fetch_row(res))
    {
        if(row[0]==email && row[1]==password) {
            EMAIL1 = email;
if(*row[2]=='0') {
ID = *row[3];
LieutanatGeneral(conn);
}
else if(*row[2]=='1') {
ID = *row[3];
Colonel(conn);
}
else if(*row[2]=='2') {
ID = *row[3];
Brigadier(conn);
}
else if(*row[2]=='3') {
ID = *row[3];
MajorGeneral(conn);
}
else if(*row[2]=='4') {
ID = *row[3];
LieutanatGeneral(conn);
}
else if(*row[2]=='5') {
ID = *row[3];
FieldMarshal(conn);
}
        }
        else {
            cout <<"\n\t\t\tEntered Invalid Email/Password!\n";
        }
    }
}
else
{
cout << "\n\n * Query Failed **";
}
}


void FieldMarshal(MYSQL* conn) {
  int choice=0;
  while(choice!=3) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== Field Marshal =======";
    cout << "\n\t\t\t\t\t1. Show Commands Details";
    cout << "\n\t\t\t\t\t2. Search Soldier Details";
    cout << "\n\t\t\t\t\t3. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ShowHeadQuarters(conn);
      break;
    case 2:
      SearchFM(conn);
      break;
    case 3:
      choice=3;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void General(MYSQL* conn) {
  int choice=0;
  while(choice!=5) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== General =======";
    cout << "\n\t\t\t\t\t1. Show Weapons Details";
    cout << "\n\t\t\t\t\t2. Search Weapon Details";
    cout << "\n\t\t\t\t\t3. Update Weapon Details";
    cout << "\n\t\t\t\t\t4. Update Profile";
    cout << "\n\t\t\t\t\t5. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
     
      break;
    case 2:
     
      break;
    case 3:
     
      break;
    case 4:
     
      break;
    case 5:
      choice=5;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void LieutanatGeneral(MYSQL* conn) {
  int choice=0;
  while(choice!=3) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== LieutanatGeneral =======";
    cout << "\n\t\t\t\t\t1. Show Command Details";
    cout << "\n\t\t\t\t\t2. Search Soldier Details";
    cout << "\n\t\t\t\t\t3. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ShowCommand(conn);
      break;
    case 2:
      SearchLG(conn);
      break;
    case 3:
      choice=3;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void MajorGeneral(MYSQL* conn) {
  int choice=0;
  while(choice!=3) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== MajorGeneral =======";
    cout << "\n\t\t\t\t\t1. Show Division Details";
    cout << "\n\t\t\t\t\t2. Search Soldier Details";
    cout << "\n\t\t\t\t\t3. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ShowDivision(conn);
      break;
    case 2:
      SearchMG(conn);
      break;
    case 3:
      choice=3;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void Brigadier(MYSQL* conn) {
  int choice=0;
  while(choice!=3) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== Brigadier =======";
    cout << "\n\t\t\t\t\t1. Show Brigade Details";
    cout << "\n\t\t\t\t\t2. Search Soldier Details";
    cout << "\n\t\t\t\t\t3. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ShowBrigade(conn);
      break;
    case 2:
      SearchBrigade(conn);
      break;
    case 3:
      choice=3;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void Colonel(MYSQL* conn) {
  int choice=0;
  while(choice!=3) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== Colonel =======";
    cout << "\n\t\t\t\t\t1. Show Regiment Details";
    cout << "\n\t\t\t\t\t2. Search Soldier Details";
    cout << "\n\t\t\t\t\t5. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ShowRegiment(conn);
      break;
    case 2:
      SearchColonel(conn);
      break;
    case 3:
      choice=3;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void LieutantColonel(MYSQL* conn) {
  int choice=0;
  while(choice!=3) {
    cout << "\n\n\n\t\t\t\t\t\t\t======== Lieutant Colonel =======";
    cout << "\n\t\t\t\t\t1. Show Rifel Company Details";
    cout << "\n\t\t\t\t\t2. Search Soldier Details";
    cout << "\n\t\t\t\t\t3. Exit";
    cout << "\n\t\t\t\tChoose correct choice  :  ";
    cin >> choice;
    switch (choice)
    {
    case 1:
      ShowCompany(conn);
      break;
    case 2:
      SearchLC(conn);
      break;
    case 3:
      choice=3;
      break;
    default:
      cout << "\n\t\t\t\tEnter correct Choice!";
      break;
    }
  }
}

void ShowHeadQuarters(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  //cout << "\t|ID\t|Name\t|Command ID\t|Division ID\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|";
  cout << "\n\t|ID\t|Name\t|Command Id\t|Division Id\t|Brigade Id\t|Regiment ID\t|Company Id\t|Platoon Id\t|Section Id\t|\n";
  ss << "SELECT * FROM soldier ORDER BY command_id, division_id, brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[2] << "\t|" << row[3] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }

}

void ShowCommand(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Command ID\t|Division ID\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT * FROM soldier WHERE command_id = "<<1<<" ORDER BY command_id, division_id, brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\t|" << row[0] << "\t|" << row[1] << "\t|" << row[2] << "\t|" << row[3] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }

}

void ShowDivision(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Division ID\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, division_id, brigade_id, regiment_id, company_id, platoon_id, section_id FROM soldier WHERE division_id = "<<1<<" ORDER BY division_id, brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[3] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }

}

void ShowBrigade(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, brigade_id, regiment_id, company_id, platoon_id, section_id FROM soldier WHERE brigade_id = "<<1<<" ORDER BY brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }

}

void ShowRegiment(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, regiment_id, company_id, platoon_id, section_id FROM soldier WHERE regiment_id = "<<1<<" ORDER BY regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }

}

void ShowCompany(MYSQL* conn) {
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, company_id, platoon_id, section_id FROM soldier WHERE company_id = "<<1<<" ORDER BY company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[6] << "\t|" << row[7] << "\t|";
      }
  }
}

void SearchFM(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name  :   ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter Command ID    :  ";
  cin >> id;

  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Command ID\t|Division ID\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT * FROM soldier WHERE command_id = "<<id<<" AND name = '"<<name<<"'";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[2] << "\t|" << row[3] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }
}

void SearchGeneral(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name  :   ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter ID            :   ";
  cin >> id;
}

void SearchLG(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name  :  ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter Division ID   :  ";
  cin >> id;

  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Command ID\t|Division ID\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT * FROM soldier WHERE command_id = "<<ID<<" AND name = '"<<name<<"' AND id = "<<id<<"  ORDER BY command_id, division_id, brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[2] << "\t|" << row[3] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }
}

void SearchMG(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name  :   ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter Brigade ID    :   ";
  cin >> id;

  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Division ID\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, division_id, brigade_id, regiment_id, company_id, platoon_id, section_id FROM soldier WHERE division_id = "<<ID<<" AND name = '"<<name<<"' AND id = "<<id<<" ORDER BY division_id, brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[3] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }
}

void SearchBrigade(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name  :   ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter Regiment ID   :   ";
  cin >> id;

  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Brigade ID\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, brigade_id, regiment_id, company_id, platoon_id, section_id FROM soldier WHERE brigade_id = "<<ID<<" AND name = '"<<name<<"' AND id = "<<id<<" ORDER BY brigade_id, regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[4] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }

}

void SearchColonel(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name  :   ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter Company ID    :   ";
  cin >> id;

  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;

  cout << "\n\t|ID\t|Name\t|Regiment ID\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, regiment_id, company_id, platoon_id, section_id FROM soldier WHERE regiment_id = "<<ID<<" AND name = '"<<name<<"' AND id = "<<id<<" ORDER BY regiment_id, company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[5] << "\t|" << row[6] << "\t|" << row[7] << "\t|" << row[8] << "\t|";
      }
  }
}

void SearchLC(MYSQL* conn) {
  string name;
  int id;
  cout << "\n\t\t\t\tEnter Soldier Name   :   ";
  getline(cin>> ws, name);
  cout << "\n\t\t\t\tEnter Platoon ID     :   ";
  cin >> id;
  stringstream ss;
  MYSQL_RES* res;
  MYSQL_ROW row;
  int qstate = 0;
  cout << "\n\t|ID\t|Name\t|Company ID\t|Platoon ID\t|Section ID\t|\n";
 
  ss << "SELECT soldier_id, name, company_id, platoon_id, section_id FROM soldier WHERE company_id = "<<ID<<" AND name = '"<<name<<" AND id = "<<id<<" ORDER BY company_id, platoon_id, section_id ASC";
  string query = ss.str();
  const char* q = query.c_str();
  qstate = mysql_query(conn, q);
  if(!qstate){
      res = mysql_store_result(conn);
      while(row = mysql_fetch_row(res)){
        cout << "\n\t|" << row[0] << "\t|" << row[1] << "\t|" << row[6] << "\t|" << row[7] << "\t|";
      }
  }
}