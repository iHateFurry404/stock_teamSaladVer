#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <cstring>

using namespace std;

bool signedIn = false;

struct accountInfo {
  int year, month, day;
  int birthYear, birthMonth, birthDay;
  int password;
  int balance;
  char name[50];
};

accountInfo account;

void menu();
void checkItBuddy(int selection);
void makeAccount();
void checkAccount();
void resetFile();
int login();

int main() {
  cout << "계정을 이미 가지고 있습니까? (Y/N)\n>>> ";

  char input;
  cin >> input;

  if (input == 'N' || input == 'n') {
    menu();
  } else {
    ifstream file("accountData.file0");

    if (!file) {
      cout << "Error opening file.";
      return -1;
    }

    file >> account.year >> account.month >> account.day;
    file >> account.birthYear >> account.birthMonth >> account.birthDay;
    file >> account.password;
    file >> account.balance;
    file.ignore();
    file.getline(account.name, 50);

    file.close();
  }
  system("clear");

  menu();

  return 0;
}

void resetFile() {
  ofstream file("accountData.file0");
  file << account.year << '\n'
       << account.month << '\n'
       << account.day << '\n'
       << account.birthYear << '\n'
       << account.birthMonth << '\n'
       << account.birthDay << '\n'
       << account.password << '\n'
       << account.balance << '\n'
       << account.name << endl;
  file.close();
}

void menu() {
  int selection;

  cout << "$$$$ 마사장의 은행 $$$$\n";
  cout << "1. 계좌 만들기\n";
  cout << "2. 계좌 확인\n";
  cout << "3. 로그인\n";
  cout << "4. 도망치기\n";
  cout << ">>> ";

  cin >> selection;

  system("clear");

  checkItBuddy(selection);
}

void checkItBuddy(int selection) {
  switch (selection) {
    case 1:
      makeAccount();
      break;
    case 2:
      checkAccount();
      break;
    case 3:
      login();
      break;
    case 4:
      exit(0);
      break;
    default:
      system("clear");
      menu();
  }
}

void makeAccount() {
  if (account.password) {
    char a;
    cout << "계정을 덮어 씌웁니까? (Y/N)\n>>> ";
    cin >> a;
    if (a == 'N' || a == 'n') {
      system("clear");
      menu();
    }
  }

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  account.year = tm.tm_year + 1900;
  account.month = tm.tm_mon + 1;
  account.day = tm.tm_mday;

  cout << "이름을 입력하세요 >> ";
  cin >> account.name;

  cout << "비밀번호를 입력하세요 >> ";
  cin >> account.password;

  system("clear");

  cout << "당신이 태어난 연도를 알려주세요 >> ";
  cin >> account.birthYear;

  cout << "당신이 태어난 달을 알려주세요 >> ";
  cin >> account.birthMonth;

  cout << "당신이 태어난 일을 알려주세요 >> ";
  cin >> account.birthDay;

  account.balance = 1000;

  resetFile();
  signedIn = false;

  system("clear");
  menu();
}

void checkAccount() {
  if (!account.password) {
    cout << "계좌를 만들어주세요." << endl;
    makeAccount();
  } else if (!signedIn) {
    cout << "로그인 해주세요." << endl;
    login();
  }
  int input;
  system("clear");
  cout << "#### " << account.name << "의 계좌 정보 ####" << endl;
  cout << "계좌 생성일 : " << account.month << "/" << account.day << "/"
       << account.year << endl;
  cout << account.name << "의 생일 : " << account.birthMonth << "/"
       << account.birthDay << "/" << account.birthYear << endl;
  cout << "계좌에 있는 돈 : " << account.balance << " $" << endl;
  cout << ">>> (아무 숫자를 눌러 창 닫기...) ";
  cin >> input;
  system("clear");
  menu();
}

int login() {
  if (signedIn) {
    cout << "이미 로그인이 되어있습니다." << endl;
    system("clear");
    menu();
    return 0;
  }

  char name[50];
  int password;
  cout << "계정 이름을 입력하세요\n>>> ";
  cin >> name;
  if (strcmp(name, account.name) != 0) {
    cout << "보안 경고!\n3초 안에 프로그램을 종료함.";
    this_thread::sleep_for(chrono::milliseconds(3000));
    exit(-1);
  }
  system("clear");
  cout << "비밀번호를 입력하세요\n>>> ";
  cin >> password;
  if (password != account.password) {
    cout << "보안 경고!\n3초 안에 프로그램을 종료함.";
    this_thread::sleep_for(chrono::milliseconds(3000));
    exit(-1);
  }
  system("clear");
  signedIn = true;
  cout << "로그인 성공!\n";
  this_thread::sleep_for(chrono::milliseconds(2000));

  system("clear");
  menu();

  return 0;
}
