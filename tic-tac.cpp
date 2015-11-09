#include <bits/stdc++.h>
using namespace std;
int n = 3;
int posx;
int posy;
int row(char a[][3],int r,int p)
{
    int i;
    int count = 0;
    for(i = 0; i < n; i++) {
        if(a[r][i] == p) {
            count++;
        }
    }
    if(count == n) {
        return 1;
    }
    else {
        return 0;
    }
}
int col(char a[][3],int c,int p)
{
    int i;
    int count = 0;
    for(i = 0; i < n; i++) {
        if(a[i][c] == p) {
            count++;
        }
    }
    if(count == n) {
        return 1;
    }
    else {
        return 0;
    }
}
int dig1(char a[][3],int i,int j,int p)
{
    if(i >= n || j >= n) {
        return 0;
    }
    if(a[i][j] == p) {
        return 1 + dig1(a,i+1,j+1,p);
    }
    else {
        return dig1(a,i+1,j+1,p);
    }
}
int dig2(char a[][3],int i,int j,int p)
{
    if(i < 0 || j < 0 || i >= n || j >= n) {
        return 0;
    }
    if(a[i][j] == p) {
        return 1 + dig2(a,i+1,j-1,p);
    }
    else {
        return dig2(a,i+1,j-1,p);
    }
}
int gamescore(char a[][3],char c,char p)
{
    int i;
    for(i = 0; i < n; i++) {
        if(row(a,i,p))  {
            if(p == c) {
                return 10;
            }
            else {
                return -10;
            }
        }
        if(col(a,i,p)) {
            if(p == c) {
                return 10;
            }
            else {
                return -10;
            }
        }
    }
    if(dig1(a,0,0,p) == n) {
        if(p == c) {
            return 10;
        }
        else {
            return -10;
        }
    }
    if(dig2(a,0,n-1,p) == n) {
        if(p == c) {
            return 10;
        }
        else {
            return -10;
        }
    }
    return 0;
}
int checkdraw(char a[][3],char c,char p)
{
    int i;
    int j;
    int flag = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(a[i][j] == '-') {
                flag = 1;
                return 0;
            }
        }
    }
    if(flag == 0 && gamescore(a,c,p) == 0) {
        return 1;
    }
    return 0;
}
void print(char a[][3])
{
    int i;
    int j;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            cout<<a[i][j]<<' ';
        }
        cout<<endl;
    }

}
int min_max(char a[][3],char c,char p,char turn,int g)
{
    int mx = -1000;
    int mn = 1000;
    int i;
    int j;
    char p1;
    if(turn == p) {
        p1 = c;
    }
    else {
        p1 = p;
    }
    //print(a);
    int check = gamescore(a,c,p1);
    if(check == 10) {
        return 10;
    }
    else if(check == -10) {
        return -10;
    }
    else if(checkdraw(a,c,p1)) {
        return 0;
    }

    if(turn == c) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(a[i][j] == '-') {
                    a[i][j] = c;
                    int x = min_max(a,c,p,p,g+1);
                    if(x > mx) {
                        mx = x;
                        if(g == 0) {
                            posx = i;
                            posy = j;
                        }
                    }
                    a[i][j] = '-';
                }
            }
        }
        return mx;
    }
    else {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(a[i][j] == '-') {
                    a[i][j] = p;
                    int x = min_max(a,c,p,c,g+1);
                    if(x < mn) {
                        mn = x;
                        if(g == 0) {
                            posx = i;
                            posy = j;
                        }
                    }
                    a[i][j] = '-';
                }
            }
        }
        return mn;
    }
}
int main()
{
    int i;
    int j;
    int k;
    int flag = 0;
    char a[3][3];
    int mn;
    int x;
    char c;
    char p;
    char turn;
    int choice;

    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            a[i][j] = '-';
        }
    }
    k = 0;
    int y;
    c = 'O';
    p = 'X';
    cout<<"---------------WELCOME TO TIC-TAC TOE GAME---------------\n";
    cout<<"INSTRUCTIONS:\n1.You are the palyer 'X' and you can choose to play first or second when promted.\n2.You have to enter the row and column number respectively of the grid where you want to make a move\n";
    cout<<"Now you are ready to play"<<endl;
    cout<<"Want to play 1st or second?Enter 1 or 2:";
    cin>>choice;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            if(choice == 1) {
                if(k % 2 == 0) {
                    print(a);
                    cout<<"Enter move:";
                    cin>>x>>y;
                    a[x-1][y-1] = p;
                    if(gamescore(a,c,p) == -10) {
                        flag = 1;
                        cout<<"---------CONGO!YOU WON--------"<<endl;
                    }
                }
                else {
                    min_max(a,c,p,c,0);
                    a[posx][posy] = c;
                    if(gamescore(a,c,c) == 10) {
                        print(a);
                        cout<<"---------SORRY!YOU LOST-------"<<endl;
                        flag = 1;
                    }
                }
            }
        else {
            if(k % 2 == 1) {
                print(a);
                cout<<"enter move:";
                cin>>x>>y;
                a[x-1][y-1] = p;
                if(gamescore(a,c,p) == -10) {
                    flag = 1;
                    print(a);
                    cout<<"you won"<<endl;
                }
            }
            else {
                min_max(a,c,p,c,0);
                a[posx][posy] = c;
                print(a);
                if(gamescore(a,c,c) == 10) {
                    cout<<"you lost"<<endl;
                    flag = 1;
                }
            }
        }
        k++;
        if(flag == 1) {
            break;
        }
    }
    if(flag == 1) {
        break;
    }
    }
    if(flag == 0) {
        print(a);
        cout<<"---------IT'S A DRAW---------"<<endl;
    }
    
}


 
