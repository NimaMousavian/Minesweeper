#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <random>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <cstdio>
#include <conio.h>

using namespace std;
std::clock_t start;

int duration;
int grow = 0;
int gcol = 0;
int gmine = 0;
int flag_counter = 0;
char gusername[100];
char difficulty[30];
char result[20];
char g_back_board[100][100];
char g_front_board[100][100];

struct user_info
{
    char username[100];
    char password[100];
};

struct date_and_time
{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
};

struct save_info
{
    char difficulty[30];
    int reveals;
    int flags;
    int row;
    int col;
    int mine;
    char back_board[100][100];
    char front_board[100][100];
    date_and_time date;
    char result[20];
    int dur;
};

void login_page();
void login();
void sign_up ();
void ext();
void main_menu();
void new_game();
void load_game();
void chang_password();
void logout();
void custom();
void game_ready(int, int, int);
bool test_win();
void won();
void play_game(int, int);
void draw_board(int, int);
void left_click(int, int);
void right_click(int, int);
void lost(int, int);
void reveal_0(int, int);
void reveal(int, int);
void save_game();
void save_history();
void show_hostory();
void admin_page();
void users_info();
void users_saves();
void ban_user();
void users_history();


int main()
{
    system("color E5");
    cout << "\n\t\t    WELCOM5E TO MINESWEEPER\n\n";
    Sleep(1500);
    login_page();
    return 0;
}

void login_page()
{
    int choice;
    cout << "\n\t\tLogin page \n";
    cout << "1.Login\n";
    cout << "2.Sign up\n";
    cout << "3.Exit\n\n";
    cout << "Please enter your choice (1-3) : ";
    //cin >> choice;
    choice = _getch();
    choice -= '0';

    switch (choice)
    {
    case 1:
        login();
        break;
    case 2:
        sign_up();
        break;
    case 3:
        ext();
        break;
    default:
        cout << "\n\nYour choice is incorect!";
        Sleep(2000);
        system("cls");
        main();
        return;
        break;
    }

}

void login()
{
    system("cls");
    cout << "\n\t\tLogin\n\n";
    int flag=0;
    user_info user, exp;
    cout << "Please enter username: ";
    cin >> user.username;
    cout << "\nPlease enter password: ";
    cin >> user.password;

    if(strcmp(user.username, "admin") == 0 && strcmp(user.password, "admin") == 0)
    {
        cout << "\nAdmin login succesfully";
        Sleep(2500);
        admin_page();
        return;
    }

    FILE *log;
    log = fopen("c:\\database.txt", "a+");
    if(log != NULL)
    {
        while(fscanf(log, "%s %s", exp.username, exp.password) > 0)
        {
            if(strcmp(exp.username, user.username) == 0 && strcmp(exp.password, user.password) == 0)
            {
                flag = 1;
            }
        }
        fclose(log);
        if(flag == 1)
        {
            strcpy(gusername, user.username);
            cout << "\nLogin succesfully";
            cout << "\nWelcome to your acount\n";
            Sleep(2500);
            main_menu();
            return;
        }
        else
        {
            cout << "\nUsername or password is incorect!";
            cout << "\nPlease try again\n";
            cout << "\n1.Try again\t" << "2.Back to login page";
            cout << "\n\nPlease enter your choice (1-2) : ";
            int e;
            //cin >> e;
            e = _getch();
            e -= '0';
            if(e == 1)
            {
                cout << endl;
                login();
                return;
            }
            else
            {
                system("cls");
                login_page();
                return;
            }
        }
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to login page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int c;
        c = _getch();
        c -= '0';
        //cin >> c;
        if(c == 1)
        {
            cout << endl;
            login();
            return;
        }
        else
        {
            system("cls");
            login_page();
            return;
        }
    }
}

void sign_up()
{
    system("cls");
    cout << "\n\t\tSign up\n\n";
    int flag=0;
    user_info user, u;
    cout << "Please enter username: ";
    cin >> user.username;

    FILE *sign, *read;
    read = fopen("c:\\database.txt", "a+");
    if(read != NULL)
    {
        while (fscanf(read, "%s %s", u.username, u.password) >0)
        {
            if(strcmp(u.username, user.username) == 0)
            {
                flag = 1;
            }
        }
        fclose(read);
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again";
        cout << "\n1.Try again\t" << "2.Back to login page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        char p;
        p =_getch();
        //cin >> p;
        if(p == '1')
        {
            cout << endl;
            sign_up();
            return;
        }
        else
        {
            system("cls");
            login_page();
            return;
        }
    }

    if(flag == 1)
    {
        cout << "\nThis username has already chosen!";
        cout << "\nPlease enter another username\n";
        cout << "\n1.Try again\t" << "2.Back to login page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        char r;
        r = _getch();
        //cin >> r;
        if(r == '1')
        {
            cout << endl;
            sign_up();
            return;
        }
        else
        {
            system("cls");
            login_page();
            return;
        }
    }

    else
    {
        cout << "\nPlease enter password: ";
        cin >> user.password;
        if(strlen(user.password)<8)
        {
            cout << "\n\nYour password is too short\n";
            cout << "Your password digits must be more than or equal 8";
            cout << "\nPlease try again";
            cout << "\n1.Try again\t" << "2.Back to login page";
            cout << "\n\nPlease enter your choice (1-2) : ";
            char q;
            q = _getch();
            //cin >> q;
            if(q == '1')
            {
                cout << endl;
                sign_up();
                return;
            }
            else
            {
                system("cls");
                login_page();
                return;
            }
        }
        sign = fopen("c:\\database.txt", "a");
        if(sign != NULL)
        {

            mkdir("c:\\information");
            char dirname[100];
            sprintf(dirname, "c:\\information\\%s", user.username);
            if(mkdir(dirname) == -1)
            {
                cout << "\nYou cann't create acount!";
                cout << "\nyou may have baned by admin";
                cout << "\nPlease try again";
                cout << "\n1.Try again\t" << "2.Back to login page";
                cout << "\n\nPlease enter your choice (1-2) : ";
                fclose(sign);
                char l;
                l = _getch();
                //cin >> l;
                if(l == '1')
                {
                    cout << endl;
                    sign_up();
                    return;
                }
                else
                {
                    system("cls");
                    login_page();
                    return;
                }


            }
            else
            {
                fprintf(sign, "%s %s \n", user.username, user.password);
                fclose(sign);

                cout << "\nSign up successfully ";
                cout << "\nPlease login to your acount";
                Sleep(3000);
                system("cls");
                login_page();
                return;
            }
        }
        else
        {
            cout << "\nFile cann't be opened!";
            cout << "\nPlease try again";
            cout << "\n1.Try again\t" << "2.Back to login page";
            cout << "\n\nPlease enter your choice (1-2) : ";
            int c;
            c = _getch();
            c -= '0';
            //cin >> c;
            if(c == 1)
            {
                cout << endl;
                sign_up();
                return;
            }
            else
            {
                system("cls");
                login_page();
                return;
            }
        }
    }
}

void ext()
{
    int c;
    cout << "\n\nAre you sure you want to exit?\n";
    cout << "1.Yes\t";
    cout << "2.No\n";
    cout << "\nEnter your choice (1-2) : ";
    c = _getch();
    c -= '0';
    cout << endl;
    //cin >> c;
    if(c == 1)
        exit(0);
    else
    {
        system("cls");
        login_page();
        return;
    }
}

void main_menu ()
{
    system("cls");
    int choice;
    cout << "\n\t\tMain menu\n";
    cout << "1.New game\n";
    cout << "2.Load game\n";
    cout << "3.Change password\n";
    cout << "4.Show history\n";
    cout << "5.Logout\n\n";
    cout << "Please enter your choice (1-5) : ";
    choice = _getch();
    choice -= '0';
    //cin >> choice;

    switch (choice)
    {
    case 1:
        new_game();
        break;
    case 2:
        load_game();
        break;
    case 3:
        chang_password();
        break;
    case 4:
        show_hostory();
        break;
    case 5:
        logout();
        break;
    default:
        cout << "\nYour choice is incorect!";
        Sleep(2000);
        main_menu();
        break;
    }
    return;
}

void new_game()
{
    system("cls");
    int choice;
    cout << "\n\t\tStart game";
    cout << "\n\n1.Beginner (9x9)";
    cout << "\n2.Intermediate (16x16)";
    cout << "\n3.Advanced (16x30)";
    cout << "\n4.Choose yourself ";
    cout << "\n5.Back to main menu\n\n";
    cout << "Please choose difficulty (1-5) : ";
    choice = _getch();
    choice -= '0';
    //cin >> choice;
    cout << endl;
    switch (choice)
    {
    case 1:
        strcpy(difficulty, "Beginner");
        game_ready(9, 9, 10);
        break;
    case 2:
        strcpy(difficulty, "Intermediate");
        game_ready(16, 16, 40);
        break;
    case 3:
        strcpy(difficulty, "Advanced");
        game_ready(16, 30, 99);
        break;
    case 4:
        custom();
        break;
    case 5:
        main_menu();
        return;
        break;
    default:
        cout << "\n\nYour choice is incorect!";
        cout << "\nPlease try again\n\n";
        system("pause");
        new_game();
        break;
    }
}

void load_game()
{
    system("cls");
    cout << "\n\t\tLoad game";
    cout << "\n\n1.save1";
    cout << "\n2.save2";
    cout << "\n3.save3\n";
    cout << "\n4.Back to main menu\n\n";
    cout << "Please enter your choice to show information (1-4) : ";
    int choice;
    choice = _getch();
    choice -= '0';
    //cin >> choice;

    if(choice == 1 || choice == 2 || choice == 3)
    {
        cout << "\n\n";
        char filename1[100];
        sprintf(filename1, "c:\\information\\%s\\save%d.bin", gusername, choice);
        FILE *show;
        show = fopen(filename1, "rb");
        if(show == NULL)
        {
            cout << "\tEmpty!\n";
            cout << "1.Try again\t" << "2.back to main menu\n\n";
            cout << "Please enter your choice (1-2) : ";
            int u;
            u = _getch();
            u -= '0';
            //cin >> u;
            if(u ==1)
            {
                load_game();
                return;
            }
            else
            {
                main_menu();
                return;
            }
        }
        else
        {
            int i, j;
            save_info load_inf;
            fread(&load_inf, sizeof (save_info), 1, show);

            cout << "\tDifficulty" << "\tRevealed spots" << "\tFlagged spots\t" << "Last accese date & time\n\n";
            cout << "\t" << load_inf.difficulty << "\t\t" << load_inf.reveals << "\t\t" << load_inf.flags << "\t" << load_inf.date.day << "/" << load_inf.date.month  << "/" << load_inf.date.year << "  " << load_inf.date.hour << ":" << load_inf.date.min << ":" << load_inf.date.sec << "\n\n";
            cout << "Do you want to play this game?\n";
            cout << "1.Yes\t" << "2.No";
            cout << "\n\nPlease enter your choice (1-2) : ";
            int d;
            d = _getch();
            d -= '0';
            //cin >> d;
            if(d == 1)
            {
                grow = load_inf.row;
                gcol = load_inf.col;
                gmine = load_inf.mine;
                flag_counter = load_inf.mine - load_inf.flags;

                for(i=0; i<load_inf.row; i++)
                    for(j=0; j<load_inf.col; j++)
                        g_back_board[i][j] = load_inf.back_board[i][j];

                for(i=0; i<load_inf.row; i++)
                    for(j=0; j<load_inf.col; j++)
                        g_front_board[i][j] = load_inf.front_board[i][j];

                fclose(show);
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                return;
            }
            else
            {
                fclose(show);
                load_game();
                return;
            }
        }
    }
    else if(choice == 4)
    {
        main_menu();
        return;
    }
    else
    {
        cout << "\n\n";
        cout << "Your choice is incorect\n";
        cout << "1.Try again\t" << "2.back to main menu\n\n";
        cout << "Please enter your choice (1-2) : ";
        int x;
        x = _getch();
        x -= '0';
        //cin >> x;
        if(x ==1)
        {
            load_game();
            return;
        }
        else
        {
            main_menu();
            return;
        }
    }
}

void chang_password()
{
    system("cls");
    cout << "\n\t\tChange password\n\n";
    int flag=0, s=0, i;
    user_info user, exp, u[100];
    char newp[50];
    cout << "Please enter username: ";
    cin >> user.username;
    cout << "\nPlease enter password: ";
    cin >> user.password;

    FILE *chn, *write;
    chn = fopen("c:\\database.txt", "r");
    if(chn != NULL)
    {
        while(fscanf(chn, "%s %s", exp.username, exp.password) > 0)
        {
            if(strcmp(exp.username, user.username) == 0 && strcmp(exp.password, user.password) == 0)
            {
                flag = 1;
                cout << "\nPlease enter your new password : ";
                cin >> newp;
                strcpy(exp.password, newp);
            }
            strcpy(u[s].username, exp.username);
            strcpy(u[s].password, exp.password);
            s++;
        }
        fclose(chn);

        if(flag == 1)
        {
            write = fopen("c:\\database.txt", "w");
            if( write != NULL)
            {
                for(i=0; i<s; i++)
                {
                    fprintf(write, "%s %s \n", u[i].username, u[i].password);
                }
                fclose(write);
                cout << "\n\nYour password succesfully changed\n\n";
                system("pause");
                main_menu();
                return;
            }
            else
            {
                cout << "\nFile cann't be opened!";
                cout << "\nPlease try again\n";
                cout << "\n1.Try again\t" << "2.Back to main menu";
                cout << "\n\nPlease enter your choice (1-2) : ";
                int c;
                c = _getch();
                c -= '0';
                //cin >> c;
                if(c == 1)
                {
                    cout << endl;
                    chang_password();
                    return;
                }
                else
                {
                    main_menu();
                    return;
                }
            }
        }
        else
        {
            cout << "\nUsername or password is incorect!";
            cout << "\nPlease try again\n";
            cout << "\n1.Try again\t" << "2.Back to main menu";
            cout << "\n\nPlease enter your choice (1-2) : ";
            int u;
            u = _getch();
            u -= '0';
            //cin >> u;
            if(u == 1)
            {
                cout << endl;
                chang_password();
                return;
            }
            else
            {
                main_menu();
                return;
            }
        }
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to main menu";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int e;
        e = _getch();
        e -= '0';
        //cin >> e;
        if(e == 1)
        {
            cout << endl;
            chang_password();
            return;
        }
        else
        {
            main_menu();
            return;
        }
    }
}

void logout()
{
    cout << "\n\nAre you sure to logout?\n";
    cout << "1.Yes\t" << "2.No\n";
    cout << "\nPlease enter your choice (1-2) : ";
    int j;
    j = _getch();
    j -= '0';
    //cin >> j;
    if(j ==1)
    {
        system("cls");
        login_page();
        return;
    }
    else
    {
        main_menu();
        return;
    }
}

void custom()
{
    system("cls");
    int row, col, mine;
    cout << "Please enter the number of row (1-99) : ";
    cin >> row;
    if(row<=0 || row>=100)
    {
        cout << "\n\nInvalid row number\n";
        cout << "Please choose a number between 1 and 99\n\n";
        system("pause");
        custom();
        return;
    }
    cout << "\n\nPlease enter the number of column (1-99) : ";
    cin >> col;
    if(col<=0 || col>=100)
    {
        cout << "\n\nInvalid col number\n";
        cout << "Please choose a number between 1 and 99\n\n";
        system("pause");
        custom();
        return;
    }
    cout << "\n\nPlease enter the number of mines : ";
    cin >> mine;
    if(mine<=0 || mine>=(row*col))
    {
        cout << "\n\nInvalid row number\n";
        cout << "Please choose a number between 1 and " << (row*col) << "\n\n";
        system("pause");
        custom();
        return;
    }
    cout << endl;
    strcpy(difficulty, "Choose yourself");
    game_ready(row, col, mine);
}

void game_ready(int row, int col, int mine)
{
    grow = row;
    gcol = col;
    gmine = mine;
    flag_counter = mine;
    int i, j, s=0, mine_counter=0;

    //creating back board
    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
            g_back_board[i][j] = '0';

    //puting mines
    srand(time(0));
    while(mine_counter < mine)
    {
        i=rand() % row;
        j=rand() % col;
        if(g_back_board[i][j] != '*')
        {
            g_back_board[i][j] = '*';
            mine_counter++;
        }
    }

    //counting mines
    for(i=0; i<row; i++)
        for(j=0; j<col; j++)
        {
            if(g_back_board[i][j] != '*')
            {
                if(i==0 && j==0)
                {
                    s=0;
                    if(g_back_board[i+1][j] == '*')
                        s++;
                    if(g_back_board[i][j+1] == '*')
                        s++;
                    if(g_back_board[i+1][j+1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else if(i==0 && j==col-1)
                {
                    s=0;
                    if(g_back_board[i+1][j] == '*')
                        s++;
                    if(g_back_board[i][j-1] == '*')
                        s++;
                    if(g_back_board[i+1][j-1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else if(i==row-1 && j==0)
                {
                    s=0;
                    if(g_back_board[i-1][j] == '*')
                        s++;
                    if(g_back_board[i][j+1] == '*')
                        s++;
                    if(g_back_board[i-1][j+1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else if(i==row-1 && j==col-1)
                {
                    s=0;
                    if(g_back_board[i-1][j] == '*')
                        s++;
                    if(g_back_board[i][j-1] == '*')
                        s++;
                    if(g_back_board[i-1][j-1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }

                else if(i==0 && j>0 && j<col-1)
                {
                    s=0;
                    if(g_back_board[i][j-1] == '*')
                        s++;
                    if(g_back_board[i][j+1] == '*')
                        s++;
                    if(g_back_board[i+1][j] == '*')
                        s++;
                    if(g_back_board[i+1][j-1] == '*')
                        s++;
                    if(g_back_board[i+1][j+1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else if(i==row-1 && j>0 && j<col-1)
                {
                    s=0;
                    if(g_back_board[i][j-1] == '*')
                        s++;
                    if(g_back_board[i][j+1] == '*')
                        s++;
                    if(g_back_board[i-1][j] == '*')
                        s++;
                    if(g_back_board[i-1][j-1] == '*')
                        s++;
                    if(g_back_board[i-1][j+1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else if(i>0 && i<row-1 && j==0)
                {
                    s=0;
                    if(g_back_board[i+1][j] == '*')
                        s++;
                    if(g_back_board[i-1][j] == '*')
                        s++;
                    if(g_back_board[i-1][j+1] == '*')
                        s++;
                    if(g_back_board[i][j+1] == '*')
                        s++;
                    if(g_back_board[i+1][j+1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else if(i>0 && i<row-1 && j==col-1)
                {
                    s=0;
                    if(g_back_board[i+1][j] == '*')
                        s++;
                    if(g_back_board[i-1][j] == '*')
                        s++;
                    if(g_back_board[i-1][j-1] == '*')
                        s++;
                    if(g_back_board[i][j-1] == '*')
                        s++;
                    if(g_back_board[i+1][j-1] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
                else
                {
                    s=0;
                    if(g_back_board[i][j+1] == '*')
                        s++;
                    if(g_back_board[i][j-1] == '*')
                        s++;
                    if(g_back_board[i-1][j+1] == '*')
                        s++;
                    if(g_back_board[i-1][j-1] == '*')
                        s++;
                    if(g_back_board[i-1][j] == '*')
                        s++;
                    if(g_back_board[i+1][j+1] == '*')
                        s++;
                    if(g_back_board[i+1][j-1] == '*')
                        s++;
                    if(g_back_board[i+1][j] == '*')
                        s++;
                    char c = '0' + s;
                    g_back_board[i][j] = c;
                }
            }
        }

    // creting front board
    for(i=row-1; i>=0; i--)
        for(j=0; j<col; j++)
            g_front_board[i][j] = '#';
    cout << endl;

    system("cls");
    start = std::clock(); // get current time
    draw_board(row, col);
    play_game(row, col);
}

bool test_win()
{
    int i, j, s=0, p=0;
    int max = (grow*gcol) - gmine;
    for(i=0; i<grow; i++)
    {
        for(j=0; j<gcol; j++)
        {
            if(g_back_board[i][j] == '*')
                continue;
            else
            {
                if(g_back_board[i][j] == g_front_board[i][j])
                    s++;
            }
        }
    }
    if(flag_counter == 0)
    {
        for(i=0; i<grow; i++)
        {
            for(j=0; j<gcol; j++)
            {
                if(g_back_board[i][j] == '*')
                {
                    if(g_front_board[i][j] == '@')
                        p++;
                }
            }
        }
    }
    if(s == max || p == gmine)
        return true;
    else
        return false;
}

void won()
{
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    strcpy(result, "won");
    save_history();

    int i, j, c;
    for(i=0; i<grow; i++)
    {
        for(j=0; j<gcol; j++)
        {
            if(g_back_board[i][j] == '*')
            {
                g_front_board[i][j] = '@';
            }
            else
            {
                g_front_board[i][j] = g_back_board[i][j];
            }
        }
    }

    system("cls");
    cout << "\n\t\t******** Congratulation!!! You won ********\n";
    draw_board(grow, gcol);
    cout << endl;
    cout << "Do you want to play again?\n";
    cout << "1.Play again\t";
    cout << "2.Back to main menu\n";
    cout << "\nPlease enter your choice : ";
    c =_getch();
    c -= '0';
    //cin >> c;
    if(c ==1)
    {
        new_game();
        return;
    }
    else
    {
        main_menu();
        return;
    }
}

void play_game(int row, int col)
{
    int in_row, in_col;
    char choice;

    if(test_win() == true)
    {
        won();
        return;
    }
    else
    {
        cout << "Number of flag(s) : " << flag_counter;
        cout << endl << endl;

        cout << "For reveal press \"r\"\n";
        cout << "For flag/unflag press \"f\"\n\n";
        cout << "For save the game press \"s\"\n";
        cout << "For exit the game press \"e\"\n\n";
        cout << "Enter your choice (r-f-s-e) : ";
        //choice = _getch();
        cin >> choice;
        cout << endl;

        if(choice == 'r' || choice == 'f')
        {
            cout << "Enter number of column : ";
            cin >> in_col;
            cout << endl;
            if(in_col <= 0 || in_col > gcol)
            {
                cout << "Invalid column number!\n";
                cout << "Please choose a number between 1 and " << col << endl << endl;
                system("pause");
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                return;
            }

            cout << "Enter number of row : ";
            cin >> in_row;
            cout << endl;

            if(in_row <= 0 || in_row > grow)
            {
                cout << "Invalid row number!\n";
                cout << "Please choose a number between 1 and " << row << endl << endl;
                system("pause");
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                return;
            }

            switch (choice)
            {
            case 'r':
                left_click(in_row, in_col);
                break;
            case 'f':
                right_click(in_row, in_col);
                break;
            case 's':
                save_game();
                break;
            case 'e':
                cout << "Do you want to exit game?\n";
                cout << "1.Resume the game\t" << "2.Start a new game\t" << "3.Back to main menu\n\n";
                cout << "Please enter your choice (1-3) : ";
                int a;
                cin >> a;
                if(a ==1)
                {
                    system("cls");
                    draw_board(grow, gcol);
                    play_game(grow, gcol);
                    return;
                }
                else if(a == 2)
                {
                    new_game();
                    return;
                }
                else
                {
                    main_menu();
                    return;
                }
                break;
            default:
                cout << "Your choice is incorect!\n";
                cout << "Pleas try again\n\n";
                system("pause");
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                break;
            }
            return;
        }
        else
        {
            switch (choice)
            {
            case 'r':
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                break;
            case 'f':
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                break;
            case 's':
                save_game();
                break;
            case 'e':
                cout << "Do you want to exit game?\n";
                cout << "1.Resume the game\t" << "2.Start a new game\t" << "3.Back to main menu\n\n";
                cout << "Please enter your choice (1-3) : ";
                int a;
                a = _getch();
                a -= '0';
                //cin >> a;
                if(a ==1)
                {
                    system("cls");
                    draw_board(grow, gcol);
                    play_game(grow, gcol);
                    return;
                }
                else if(a == 2)
                {
                    new_game();
                    return;
                }
                else
                {
                    main_menu();
                    return;
                }
                break;
            default:
                cout << "Your choice is incorect!\n";
                cout << "Pleas try again\n\n";
                system("pause");
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                break;
            }
            return;
        }
    }
}

void draw_board(int row, int col)
{
    int i, j;
    cout << endl;
    if(col <= 9)
    {
        cout << "\t";
        for(j=0; j<col; j++)
        {
            cout << j+1 << " ";
        }
        cout << endl << endl;
    }
    else if (col>9 && col<100)
    {
        if(col < 20)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<col-9; j++)
                cout << 1 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<col-9; j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 20 && col < 30)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=10; j<col-9; j++)
                cout << 2 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(18+1); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 30 && col <40)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=20; j<col-9; j++)
                cout << 3 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(27+2); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 40 && col <50)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=30; j<col-9; j++)
                cout << 4 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(36+3); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 50 && col <60)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=40; j<col-9; j++)
                cout << 5 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(45+4); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 60 && col <70)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=50; j<col-9; j++)
                cout << 6 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(54+5); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 70 && col <80)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=0; j<10 ; j++)
                cout << 6 << " ";
            for(j=60; j<col-9; j++)
                cout << 7 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(63+6); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 80 && col <90)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=0; j<10 ; j++)
                cout << 6 << " ";
            for(j=0; j<10 ; j++)
                cout << 7 << " ";
            for(j=70; j<col-9; j++)
                cout << 8 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(72+7); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(col >= 90 && col <100)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=0; j<10 ; j++)
                cout << 6 << " ";
            for(j=0; j<10 ; j++)
                cout << 7 << " ";
            for(j=0; j<10 ; j++)
                cout << 8 << " ";
            for(j=80; j<col-9; j++)
                cout << 9 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<col-(81+8); j++)
                cout << j << " ";
            cout << endl << endl;
        }
    }

    for(i=row-1; i>=0; i--)
    {
        cout << "\t";
        for(j=0; j<col; j++)
            cout <<  g_front_board[i][j] << " ";
        cout << "  " << i+1 << endl;
    }
    cout << endl;
}

void right_click(int in_row, int in_col)
{
    in_row--;
    in_col--;

    if(g_front_board[in_row][in_col] == '#')
    {
            g_front_board[in_row][in_col] = '@';
            flag_counter--;
    }
    else if(g_front_board[in_row][in_col] == '@')
    {
        g_front_board[in_row][in_col] = '#';
        flag_counter++;
    }
    else {
        cout << "You cann't put flag in this location\n";
        cout << "Please choose another location\n\n";
        system("pause");
        system("cls");
        draw_board(grow, gcol);
        play_game(grow, gcol);
        return;
    }
    system("cls");
    draw_board(grow, gcol);
    play_game(grow, gcol);
}

void left_click(int in_row, int in_col)
{
    in_row--;
    in_col--;

    if(g_front_board[in_row][in_col] == '@')
    {
        system("cls");
        draw_board(grow, gcol);
        play_game(grow, gcol);
        return;
    }
    else
    {
        switch (g_back_board[in_row][in_col])
        {
        case '*':
            lost(in_row, in_col);
            break;
        case '0':
            reveal_0(in_row, in_col);
            system("cls");
            draw_board(grow, gcol);
            play_game(grow, gcol);
            break;
        default:
            reveal(in_row, in_col);
            break;
        }
    }
}

void lost(int in_row, int in_col)
{
    system("cls");
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    int i, j, c;
    cout << "\n\t\t******** Sorry, you lost! ********\n";
    g_back_board[in_row][in_col] = '&';

    //draw
    if(gcol <= 9)
    {
        cout << "\t";
        for(j=0; j<gcol; j++)
        {
            cout << j+1 << " ";
        }
        cout << endl << endl;
    }
    else if (gcol>9 && gcol<100)
    {
        if(gcol < 20)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<gcol-9; j++)
                cout << 1 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<gcol-9; j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 20 && gcol < 30)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=10; j<gcol-9; j++)
                cout << 2 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(18+1); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 30 && gcol <40)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=20; j<gcol-9; j++)
                cout << 3 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(27+2); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 40 && gcol <50)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=30; j<gcol-9; j++)
                cout << 4 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(36+3); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 50 && gcol <60)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=40; j<gcol-9; j++)
                cout << 5 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(45+4); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 60 && gcol <70)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=50; j<gcol-9; j++)
                cout << 6 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(54+5); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 70 && gcol <80)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=0; j<10 ; j++)
                cout << 6 << " ";
            for(j=60; j<gcol-9; j++)
                cout << 7 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(63+6); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 80 && gcol <90)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=0; j<10 ; j++)
                cout << 6 << " ";
            for(j=0; j<10 ; j++)
                cout << 7 << " ";
            for(j=70; j<gcol-9; j++)
                cout << 8 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(72+7); j++)
                cout << j << " ";
            cout << endl << endl;
        }
        if(gcol >= 90 && gcol <100)
        {
            cout << "\t";
            for(j=0; j<9; j++)
                cout << "  ";
            for(j=0; j<10 ; j++)
                cout << 1 << " ";
            for(j=0; j<10 ; j++)
                cout << 2 << " ";
            for(j=0; j<10 ; j++)
                cout << 3 << " ";
            for(j=0; j<10 ; j++)
                cout << 4 << " ";
            for(j=0; j<10 ; j++)
                cout << 5 << " ";
            for(j=0; j<10 ; j++)
                cout << 6 << " ";
            for(j=0; j<10 ; j++)
                cout << 7 << " ";
            for(j=0; j<10 ; j++)
                cout << 8 << " ";
            for(j=80; j<gcol-9; j++)
                cout << 9 << " ";
            cout << endl;
            cout << "\t";
            for(j=0; j<9; j++)
                cout << j+1 << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<10 ; j++)
                cout << j << " ";
            for(j=0; j<gcol-(81+8); j++)
                cout << j << " ";
            cout << endl << endl;
        }
    }
    for(i=grow-1; i>=0; i--)
    {
        cout << "\t";
        for(j=0; j<gcol; j++)
            cout <<  g_back_board[i][j] << " ";
        cout << "  " << i+1;
        cout << endl;
    }

    strcpy(result, "lost");
    save_history();

    cout << endl;
    cout << "Do you want to play again?\n";
    cout << "1.Play again\t";
    cout << "2.Back to main menu\n";
    cout << "\nPlease enter your choice : ";
    c = _getch();
    c -= '0';
    //cin >> c;
    if(c ==1)
    {
        new_game();
        return;
    }
    else
    {
        main_menu();
        return;
    }
}

void reveal_0(int in_row,int in_col)
{
    int i, j;
    i = in_row;
    j = in_col;
    g_front_board[i][j] = g_back_board[i][j];

    if(i==0 && j==0)
    {
        if(g_front_board[i+1][j] == '@')
            flag_counter++;
        if(g_front_board[i+1][j] != '0')
        {
            if(g_back_board[i+1][j] == '0')
                reveal_0(i+1, j);
            else
                g_front_board[i+1][j] = g_back_board[i+1][j];
        }
        if(g_front_board[i][j+1] == '@')
            flag_counter++;
        if(g_front_board[i][j+1] != '0')
        {
            if(g_back_board[i][j+1] == '0')
                reveal_0(i, j+1);
            else
                g_front_board[i][j+1] = g_back_board[i][j+1];
        }
        if(g_front_board[i+1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j+1] != '0')
        {
            if(g_back_board[i+1][j+1] == '0')
                reveal_0(i+1, j+1);
            else
                g_front_board[i+1][j+1] = g_back_board[i+1][j+1];
        }
    }
    else if(i==0 && j==gcol-1)
    {
        if(g_front_board[i+1][j] == '@')
            flag_counter++;
        if(g_front_board[i+1][j] != '0')
        {
            if(g_back_board[i+1][j] == '0')
                reveal_0(i+1, j);
            else
                g_front_board[i+1][j] = g_back_board[i+1][j];
        }
        if(g_front_board[i][j-1] == '@')
            flag_counter++;
        if(g_front_board[i][j-1] != '0')
        {
            if(g_back_board[i][j-1] == '0')
                reveal_0(i, j-1);
            else
                g_front_board[i][j-1] = g_back_board[i][j-1];
        }
        if(g_front_board[i+1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j-1] != '0')
        {
            if(g_back_board[i+1][j-1] == '0')
                reveal_0(i+1, j-1);
            else
                g_front_board[i+1][j-1] = g_back_board[i+1][j-1];
        }
    }
    else if(i==grow-1 && j==0)
    {
        if(g_front_board[i-1][j] == '@')
            flag_counter++;
        if(g_front_board[i-1][j] != '0')
        {
            if(g_back_board[i-1][j] == '0')
                reveal_0(i-1, j);
            else
                g_front_board[i-1][j] = g_back_board[i-1][j];
        }
        if(g_front_board[i][j+1] == '@')
            flag_counter++;
        if(g_front_board[i][j+1] != '0')
        {
            if(g_back_board[i][j+1] == '0')
                reveal_0(i, j+1);
            else
                g_front_board[i][j+1] = g_back_board[i][j+1];
        }
        if(g_front_board[i-1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j+1] != '0')
        {
            if(g_back_board[i-1][j+1] == '0')
                reveal_0(i-1, j+1);
            else
                g_front_board[i-1][j+1] = g_back_board[i-1][j+1];
        }
    }
    else if(i==grow-1 && j==gcol-1)
    {
        if(g_front_board[i-1][j] == '@')
            flag_counter++;
        if(g_front_board[i-1][j] != '0')
        {
            if(g_back_board[i-1][j] == '0')
                reveal_0(i-1, j);
            else
                g_front_board[i-1][j] = g_back_board[i-1][j];
        }
        if(g_front_board[i][j-1] == '@')
            flag_counter++;
        if(g_front_board[i][j-1] != '0')
        {
            if(g_back_board[i][j-1] == '0')
                reveal_0(i, j-1);
            else
                g_front_board[i][j-1] = g_back_board[i][j-1];
        }
        if(g_front_board[i-1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j-1] != '0')
        {
            if(g_back_board[i-1][j-1] == '0')
                reveal_0(i-1, j-1);
            else
                g_front_board[i-1][j-1] = g_back_board[i-1][j-1];
        }
    }

    else if(i==0 && j>0 && j<gcol-1)
    {
        if(g_front_board[i][j-1] == '@')
            flag_counter++;
        if(g_front_board[i][j-1] != '0')
        {
            if(g_back_board[i][j-1] == '0')
                reveal_0(i, j-1);
            else
                g_front_board[i][j-1] = g_back_board[i][j-1];
        }
        if(g_front_board[i][j+1] == '@')
            flag_counter++;
        if(g_front_board[i][j+1] != '0')
        {
            if(g_back_board[i][j+1] == '0')
                reveal_0(i, j+1);
            else
                g_front_board[i][j+1] = g_back_board[i][j+1];
        }
        if(g_front_board[i+1][j] == '@')
            flag_counter++;
        if(g_front_board[i+1][j] != '0')
        {
            if(g_back_board[i+1][j] == '0')
                reveal_0(i+1, j);
            else
                g_front_board[i+1][j] = g_back_board[i+1][j];
        }
        if(g_front_board[i+1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j-1] != '0')
        {
            if(g_back_board[i+1][j-1] == '0')
                reveal_0(i+1, j-1);
            else
                g_front_board[i+1][j-1] = g_back_board[i+1][j-1];
        }
        if(g_front_board[i+1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j+1] != '0')
        {
            if(g_back_board[i+1][j+1] == '0')
                reveal_0(i+1, j+1);
            else
                g_front_board[i+1][j+1] = g_back_board[i+1][j+1];
        }
    }
    else if(i==grow-1 && j>0 && j<gcol-1)
    {
        if(g_front_board[i][j-1] == '@')
            flag_counter++;
        if(g_front_board[i][j-1] != '0')
        {
            if(g_back_board[i][j-1] == '0')
                reveal_0(i, j-1);
            else
                g_front_board[i][j-1] = g_back_board[i][j-1];
        }
        if(g_front_board[i][j+1] == '@')
            flag_counter++;
        if(g_front_board[i][j+1] != '0')
        {
            if(g_back_board[i][j+1] == '0')
                reveal_0(i, j+1);
            else
                g_front_board[i][j+1] = g_back_board[i][j+1];
        }
        if(g_front_board[i-1][j] == '@')
            flag_counter++;
        if(g_front_board[i-1][j] != '0')
        {
            if(g_back_board[i-1][j] == '0')
                reveal_0(i-1, j);
            else
                g_front_board[i-1][j] = g_back_board[i-1][j];
        }
        if(g_front_board[i-1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j-1] != '0')
        {
            if(g_back_board[i-1][j-1] == '0')
                reveal_0(i-1, j-1);
            else
                g_front_board[i-1][j-1] = g_back_board[i-1][j-1];
        }
        if(g_front_board[i-1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j+1] != '0')
        {
            if(g_back_board[i-1][j+1] == '0')
                reveal_0(i-1, j+1);
            else
                g_front_board[i-1][j+1] = g_back_board[i-1][j+1];
        }
    }
    else if(i>0 && i<grow-1 && j==0)
    {
        if(g_front_board[i+1][j] == '@')
            flag_counter++;
        if(g_front_board[i+1][j] != '0')
        {
            if(g_back_board[i+1][j] == '0')
                reveal_0(i+1, j);
            else
                g_front_board[i+1][j] = g_back_board[i+1][j];
        }
        if(g_front_board[i-1][j] == '@')
            flag_counter++;
        if(g_front_board[i-1][j] != '0')
        {
            if(g_back_board[i-1][j] == '0')
                reveal_0(i-1, j);
            else
                g_front_board[i-1][j] = g_back_board[i-1][j];
        }
        if(g_front_board[i-1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j+1] != '0')
        {
            if(g_back_board[i-1][j+1] == '0')
                reveal_0(i-1, j+1);
            else
                g_front_board[i-1][j+1] = g_back_board[i-1][j+1];
        }
        if(g_front_board[i][j+1] == '@')
            flag_counter++;
        if(g_front_board[i][j+1] != '0')
        {
            if(g_back_board[i][j+1] == '0')
                reveal_0(i, j+1);
            else
                g_front_board[i][j+1] = g_back_board[i][j+1];
        }
        if(g_front_board[i+1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j+1] != '0')
        {
            if(g_back_board[i+1][j+1] == '0')
                reveal_0(i+1, j+1);
            else
                g_front_board[i+1][j+1] = g_back_board[i+1][j+1];
        }
    }
    else if(i>0 && i<grow-1 && j==gcol-1)
    {
        if(g_front_board[i+1][j] == '@')
            flag_counter++;
        if(g_front_board[i+1][j] != '0')
        {
            if(g_back_board[i+1][j] == '0')
                reveal_0(i+1, j);
            else
                g_front_board[i+1][j] = g_back_board[i+1][j];
        }
        if(g_front_board[i-1][j] == '@')
            flag_counter++;
        if(g_front_board[i-1][j] != '0')
        {
            if(g_back_board[i-1][j] == '0')
                reveal_0(i-1, j);
            else
                g_front_board[i-1][j] = g_back_board[i-1][j];
        }
        if(g_front_board[i-1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j-1] != '0')
        {
            if(g_back_board[i-1][j-1] == '0')
                reveal_0(i-1, j-1);
            else
                g_front_board[i-1][j-1] = g_back_board[i-1][j-1];
        }
        if(g_front_board[i][j-1] == '@')
            flag_counter++;
        if(g_front_board[i][j-1] != '0')
        {
            if(g_back_board[i][j-1] == '0')
                reveal_0(i, j-1);
            else
                g_front_board[i][j-1] = g_back_board[i][j-1];
        }
        if(g_front_board[i+1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j-1] != '0')
        {
            if(g_back_board[i+1][j-1] == '0')
                reveal_0(i+1, j-1);
            else
                g_front_board[i+1][j-1] = g_back_board[i+1][j-1];
        }
    }
    else
    {
        if(g_front_board[i][j+1] == '@')
            flag_counter++;
        if(g_front_board[i][j+1] != '0')
        {
            if(g_back_board[i][j+1] == '0')
                reveal_0(i, j+1);
            else
                g_front_board[i][j+1] = g_back_board[i][j+1];
        }
        if(g_front_board[i][j-1] == '@')
            flag_counter++;
        if(g_front_board[i][j-1] != '0')
        {
            if(g_back_board[i][j-1] == '0')
                reveal_0(i, j-1);
            else
                g_front_board[i][j-1] = g_back_board[i][j-1];
        }
        if(g_front_board[i-1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j+1] != '0')
        {
            if(g_back_board[i-1][j+1] == '0')
                reveal_0(i-1, j+1);
            else
                g_front_board[i-1][j+1] = g_back_board[i-1][j+1];
        }
        if(g_front_board[i-1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i-1][j-1] != '0')
        {
            if(g_back_board[i-1][j-1] == '0')
                reveal_0(i-1, j-1);
            else
                g_front_board[i-1][j-1] = g_back_board[i-1][j-1];
        }
        if(g_front_board[i-1][j] == '@')
            flag_counter++;
        if(g_front_board[i-1][j] != '0')
        {
            if(g_back_board[i-1][j] == '0')
                reveal_0(i-1, j);
            else
                g_front_board[i-1][j] = g_back_board[i-1][j];
        }
        if(g_front_board[i+1][j+1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j+1] != '0')
        {
            if(g_back_board[i+1][j+1] == '0')
                reveal_0(i+1, j+1);
            else
                g_front_board[i+1][j+1] = g_back_board[i+1][j+1];
        }
        if(g_front_board[i+1][j-1] == '@')
            flag_counter++;
        if(g_front_board[i+1][j-1] != '0')
        {
            if(g_back_board[i+1][j-1] == '0')
                reveal_0(i+1, j-1);
            else
                g_front_board[i+1][j-1] = g_back_board[i+1][j-1];
        }
        if(g_front_board[i+1][j] == '@')
            flag_counter++;
        if(g_front_board[i+1][j] != '0')
        {
            if(g_back_board[i+1][j] == '0')
                reveal_0(i+1, j);
            else
                g_front_board[i+1][j] = g_back_board[i+1][j];
        }
    }
}

void reveal(int in_row, int in_col)
{
    g_front_board[in_row][in_col] = g_back_board[in_row][in_col];
    system("cls");
    draw_board(grow, gcol);
    play_game(grow, gcol);
}

void save_game()
{
    system("cls");
    int i, j, s=0;
    save_info save_inf;
    // counting reveals
    for(i=0; i<grow; i++)
    {
        for(j=0; j<gcol; j++)
        {
            if(g_front_board[i][j] == '#' || g_front_board[i][j] == '@')
                continue;
            else
                s++;
        }
    }

    strcpy(save_inf.difficulty, difficulty);
    save_inf.reveals = s;
    save_inf.flags = gmine - flag_counter;
    save_inf.row = grow;
    save_inf.col = gcol;
    save_inf.mine = gmine;
    time_t now = time(0);
    tm *local = localtime(&now);
    save_inf.date.year = local->tm_year+1900;
    save_inf.date.month = local->tm_mon+1;
    save_inf.date.day = local->tm_mday;
    save_inf.date.hour = local->tm_hour;
    save_inf.date.min = local->tm_min;
    save_inf.date.sec = local->tm_sec;


    for(i=0; i<grow; i++)
        for(j=0; j<gcol; j++)
            save_inf.back_board[i][j] = g_back_board[i][j];

    for(i=0; i<grow; i++)
        for(j=0; j<gcol; j++)
            save_inf.front_board[i][j] = g_front_board[i][j];

    cout << "\n\t\tSave game";
    cout << "\n\n1.save1";
    cout << "\n2.save2";
    cout << "\n3.save3\n\n";
    cout << "4.Back to game\n";
    cout << "5.Back to main menu\n\n";
    cout << "Please enter your choice to save the game (1-5) : ";
    int choice;
    choice = _getch();
    choice -= '0';
    //cin >> choice;
    cout << "\n\n";

    if(choice == 1 || choice == 2 || choice == 3)
    {
        char filename1[100];
        sprintf(filename1, "c:\\information\\%s\\save%d.bin", gusername, choice);
        FILE *check;
        check = fopen(filename1, "rb");
        if(check == NULL)
        {
            char filename[100];
            sprintf(filename, "c:\\information\\%s\\save%d.bin", gusername, choice);
            FILE *save;
            save = fopen(filename, "wb");
            if(save != NULL)
            {
                fwrite(&save_inf, sizeof (save_info), 1, save);
                fclose(save);
                cout << "Your game succesfully saved\n";
                cout << "1.Resume the game\t" << "2.Back to main menu\n\n";
                cout << "Please enter your choise : ";
                int v;
                v = _getch();
                v -= '0';
                //cin >> v;
                cout << "\n\n";
                if(v == 1)
                {
                    system("cls");
                    draw_board(grow, gcol);
                    play_game(grow, gcol);
                    return;
                }
                else
                {
                    main_menu();
                    return;
                }
            }
            else
            {
                cout << "\nFile cann't be opened!";
                cout << "\nPleas try again\n";
                cout << "\n1.Try again\t" << "2.Back to main menu";
                cout << "\n\nPlease enter your choice (1-2) : ";
                int c;
                c = _getch();
                c -= '0';
                //cin >> c;
                if(c == 1)
                {
                    cout << endl;
                    save_game();
                    return;
                }
                else
                {
                    main_menu();
                    return;
                }
            }
            fclose(check);
        }
        else if (check != NULL)
        {
            cout << "You have already save a game in this file\n";
            cout << "If you save this game, the old game will be deleted\n";
            cout << "Do you want to save?\n";
            cout << "1.Save and delete old game\t" << "2.Choose another file to save\t" << "3.Resume the game\t" << "4.Back to main menu";
            cout << "\nPlease enter your choice : ";
            int z;
            z = _getch();
            z -= '0';
            //cin >> z;
            cout << "\n\n";
            if(z == 1)
            {
                char filename2[100];
                sprintf(filename2, "c:\\information\\%s\\save%d.bin", gusername, choice);
                FILE *save;
                save = fopen(filename2, "wb");
                if(save != NULL)
                {
                    fwrite(&save_inf, sizeof (save_info), 1, save);
                    fclose(save);
                    cout << "Your game succesfully saved\n\n";
                    cout << "1.Resume the game\t" << "2.Back to main menu\n\n";
                    cout << "Please enter your choise : ";
                    int k;
                    k = _getch();
                    k -= '0';
                    //cin >> k;
                    cout << "\n\n";
                    if(k == 1)
                    {
                        system("cls");
                        draw_board(grow, gcol);
                        play_game(grow, gcol);
                        return;
                    }
                    else
                    {
                        main_menu();
                        return;
                    }
                }
                else
                {
                    cout << "\nFile cann't be opened!";
                    cout << "\nPleas try again\n";
                    cout << "\n1.Try again\t" << "2.Back to main menu";
                    cout << "\n\nPlease enter your choice (1-2) : ";
                    int w;
                    w = _getch();
                    w -= '0';
                    //cin >> w;
                    if(w == 1)
                    {
                        cout << endl;
                        save_game();
                        return;
                    }
                    else
                    {
                        main_menu();
                        return;
                    }
                }
            }
            else if (z == 2)
            {
                save_game();
                return;
            }
            else if(z == 3)
            {
                system("cls");
                draw_board(grow, gcol);
                play_game(grow, gcol);
                return;
            }
            else if(z == 4)
            {
                main_menu();
                return;
            }
            else
            {
                cout << "Your choice is incorect\n";
                cout << "Please try again\n";
                cout << "\n1.Try again\t" << "2.Back to main menu";
                cout << "\n\nPlease enter your choice (1-2) : ";
                int t;
                t = _getch();
                t -= '0';
                //cin >> t;
                if(t == 1)
                {
                    cout << endl;
                    save_game();
                    return;
                }
                else
                {
                    main_menu();
                    return;
                }
            }
        }
    }
    else if(choice == 4)
    {
        system("cls");
        draw_board(grow, gcol);
        play_game(grow, gcol);
        return;
    }
    else if(choice == 5)
    {
        main_menu();
        return;
    }
    else
    {
        cout << "Your choice is incorect\n";
        cout << "1.Try again\t" << "2.back to main menu\n\n";
        cout << "Please enter your choice (1-2) : ";
        int x;
        x = _getch();
        x -= '0';
        //cin >> x;
        if(x ==1)
        {
            save_game();
            return;
        }
        else
        {
            main_menu();
            return;
        }
    }
}

void save_history()
{
    // finding a null file
    int i=1;
    char filename[100];
    sprintf(filename, "c:\\information\\%s\\history%d.bin", gusername, i);
    FILE *find;
    find = fopen(filename, "rb");

    while (find != NULL)
    {
        i++;
        sprintf(filename, "c:\\information\\%s\\history%d.bin", gusername, i);
        find = fopen(filename, "rb");
    }
    fclose(find);

    // saving
    save_info save_inf;
    strcpy(save_inf.difficulty, difficulty);
    strcpy(save_inf.result, result);
    time_t now = time(0);
    tm *local = localtime(&now);
    save_inf.date.year = local->tm_year+1900;
    save_inf.date.month = local->tm_mon+1;
    save_inf.date.day = local->tm_mday;
    save_inf.dur = duration;


    FILE *save;
    save = fopen(filename, "ab");
    if(save != NULL)
    {
        fwrite(&save_inf, sizeof (save_info), 1, save);
        fclose(save);
    }
    else {
        cout << "error" << endl;
    }


}

void show_hostory()
{
    system("cls");
    cout << "\n\t\tHistory\n\n";
    cout << "\tDate" << "\tDifficulty" << "\tResult" << "\tDuration\n\n";

    int i=1;
    save_info show;

    char filename[100];
    sprintf(filename, "c:\\information\\%s\\history%d.bin", gusername, i);
    FILE *print;
    print = fopen(filename, "rb");

    while (print != NULL)
    {
        fread(&show, sizeof (save_info), 1, print);
        cout << "   " << i << "." << show.date.day << "/" << show.date.month << "/" << show.date.year << "\t";
        cout << show.difficulty << "\t" << show.result << "\t" << show.dur << " s" << "\n\n";

        i++;
        sprintf(filename, "c:\\information\\%s\\history%d.bin", gusername, i);
        print = fopen(filename, "rb");
    }


    cout << "\n\nPlease enter 0 to back to main menu : ";
    int r;
    r = _getch();
    main_menu();
    return;
}

void admin_page()
{
    system("cls");
    cout << "\n\t\tAdmin page\n\n";
    cout << "1.Users information\n";
    cout << "2.Users saves\n";
    cout << "3.Users history\n";
    cout << "4.Ban user\n";
    cout << "5.Logout\n\n";
    cout << "Please enter your choice (1-5) : ";
    int x;
    x = _getch();
    x -= '0';
    switch (x)
    {
    case 1:
        users_info();
        break;
    case 2:
        users_saves();
        break;
    case 3:
        users_history();
        break;
    case 4:
        ban_user();
        break;
    case 5:
        logout();
        break;
    default:
        cout << "\n\nYour choice is incorect\n";
        cout << "Please try again\n";
        Sleep(3000);
        admin_page();
        break;
    }
    return;
}

void users_info()
{
    system("cls");
    cout << "\n\t\tUsers information\n\n";
    cout << "\tUsername\t" << "Password\n\n";

    int i;
    user_info user;
    FILE *read;
    read = fopen("c:\\database.txt", "r");

    if(read != NULL)
    {
        for (i=1; fscanf(read, "%s %s", user.username, user.password) > 0; i++)
        {
            cout << "\t" << i << "." << user.username << "\t" << user.password << "\n";
        }
        fclose(read);
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int c;
        c = _getch();
        c -= '0';
        if(c == 1)
        {
            users_info();
            return;
        }
        else
        {
            admin_page();
            return;
        }
    }

    cout << "\n\nPlease enter 0 to back to admin page : ";
    int y;
    y = _getch();

    admin_page();
    return;
}

void users_saves()
{
    system("cls");
    cout << "\n\t\tUsers saves\n\n";
    cout << "\tUsername\n\n";

    save_info load_inf;
    user_info u, user[100];
    int s=1, i;

    FILE *read;
    read = fopen("c:\\database.txt", "r");
    if(read != NULL)
    {
        while (fscanf(read, "%s %s", u.username, u.password) >0)
        {
            strcpy(user[s].username, u.username);
            strcpy(user[s].password, u.password);
            s++;
        }
        fclose(read);

        for(i=1; i<s; i++)
        {
            cout << "\t" << i << "." << user[i].username << "\n";
        }
        cout << "\n\n";
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int c;
        c = _getch();
        c -= '0';
        if(c == 1)
        {
            users_info();
            return;
        }
        else
        {
            admin_page();
            return;
        }
    }

    cout << "0.Back to admin page\n\n";
    cout << "Please enter number of each username (0-" << s-1 << ") : ";
    int choice;
    cin >> choice;

    if(choice > s-1)
    {
        cout << "\n\nYour choice is incorect\n";
        cout << "Please try again\n\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int l;
        l = _getch();
        l -= '0';
        if(l == 1)
        {
            users_saves();
            return;
        }
        else
        {
            admin_page();
            return;
        }

    }
    else if(choice == 0)
    {
        admin_page();
        return;
    }
    else
    {
        system("cls");
        cout << "\n\t\t" << user[choice].username;
        cout << "\n\n";
        for(i=1; i<=3; i++)
        {
            char filename[100];
            sprintf(filename, "c:\\information\\%s\\save%d.bin", user[choice].username, i);
            FILE *save;
            save = fopen(filename, "rb");
            if(save != NULL)
            {
                cout << i << ".Available\n";
                fclose(save);
            }
            else
            {
                cout << i << ".Empty!\n";
            }
        }
    }

    cout << "\n\n0.Back to users saves";
    cout << "\n\nIf any item is available, enter its number to show information (1-3) (or 0 to exit) : ";
    int y;
    y = _getch();
    y -= '0';

    if(y == 0)
    {
        users_saves();
        return;
    }
    else
    {
        char fnama[100];
        sprintf(fnama, "c:\\information\\%s\\save%d.bin", user[choice].username, y);
        FILE *load;
        load = fopen(fnama, "rb");
        if(load != NULL)
        {
            fread(&load_inf, sizeof (save_info), 1, load);
            // printing thhe information...
            cout << "\n\n\tDifficulty" << "\tRevealed spots" << "\tFlagged spots\t" << "Last accese date & time\n\n";
            cout << "\t" << load_inf.difficulty << "\t\t" << load_inf.reveals << "\t\t" << load_inf.flags << "\t";
            cout << load_inf.date.day << "/" << load_inf.date.month  << "/" << load_inf.date.year << "  " << load_inf.date.hour << ":" << load_inf.date.min << ":" << load_inf.date.sec << "\n\n";

            fclose(load);

            cout << "\n\n1.Back to users saves\t" << "2.Back to admin page\n\n";
            cout << "Please enter your choice : ";
            int r;
            r = _getch();
            r -= '0';
            if(r == 1)
            {
                users_saves();
                return;
            }
            else
            {
                admin_page();
                return;
            }
        }
        else
        {
            cout << "\nThis save is empty!";
            cout << "\nPlease try again\n";
            cout << "\n1.Try again\t" << "2.Back to admin page";
            cout << "\n\nPlease enter your choice (1-2) : ";
            int l;
            l = _getch();
            l -= '0';
            if(l == 1)
            {
                users_saves();
                return;
            }
            else
            {
                admin_page();
                return;
            }

        }
    }
}

void ban_user()
{
    system("cls");
    cout << "\n\t\tBan users\n\n";
    cout << "\tUsername\n\n";

    int s=1, i, p=0;
    user_info u, user[100];

    FILE *read;
    read = fopen("c:\\database.txt", "r");
    if(read != NULL)
    {
        while (fscanf(read, "%s %s", u.username, u.password) >0)
        {
            strcpy(user[s].username, u.username);
            strcpy(user[s].password, u.password);
            s++;
        }
        fclose(read);

        for(i=1; i<s; i++)
        {
            cout << "\t" << i << "." << user[i].username << "\n";
        }
        cout << "\n\n";
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int c;
        c = _getch();
        c -= '0';
        if(c == 1)
        {
            users_info();
            return;
        }
        else
        {
            admin_page();
            return;
        }
    }

    cout << "0.Back to admin page\n\n";
    cout << "Please enter number of each username to ban (0-" << s-1 << ") : ";
    int choice;
    cin >> choice;

    if(choice > s-1)
    {
        cout << "\n\nYour choice is incorect\n";
        cout << "Please try again\n\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int l;
        l = _getch();
        l -= '0';
        if(l == 1)
        {
            users_saves();
            return;
        }
        else
        {
            admin_page();
            return;
        }

    }
    else if(choice == 0)
    {
        admin_page();
        return;
    }
    else
    {
        for(i=1; i<s; i++)
        {
            if(strcmp(user[i].username, user[choice].username) == 0)
                continue;
            strcpy(user[p].username, user[i].username);
            strcpy(user[p].password, user[i].password);
            p++;
        }

        FILE *write;
        write = fopen("c:\\database.txt", "w");
        if(write != NULL)
        {
            for(i=0; i<p; i++)
            {
                fprintf(write, "%s %s\n", user[i].username, user[i].password);
            }
            fclose(write);
            cout << "\n\nUser succesfully baned\n\n";
            system("pause");
            admin_page();
            return;
        }
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int o;
        o = _getch();
        o -= '0';
        if(o == 1)
        {
            users_info();
            return;
        }
        else
        {
            admin_page();
            return;
        }
    }

}

void users_history()
{
    system("cls");
    cout << "\n\t\tUsers hostory\n\n";
    cout << "\tUsername\n\n";

    int s=1, i, p=0;
    user_info u, user[100];

    FILE *read;
    read = fopen("c:\\database.txt", "r");
    if(read != NULL)
    {
        while (fscanf(read, "%s %s", u.username, u.password) >0)
        {
            strcpy(user[s].username, u.username);
            strcpy(user[s].password, u.password);
            s++;
        }
        fclose(read);

        for(i=1; i<s; i++)
        {
            cout << "\t" << i << "." << user[i].username << "\n";
        }
        cout << "\n\n";
    }
    else
    {
        cout << "\nFile cann't be opened!";
        cout << "\nPlease try again\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int c;
        c = _getch();
        c -= '0';
        if(c == 1)
        {
            users_info();
            return;
        }
        else
        {
            admin_page();
            return;
        }
    }

    cout << "0.Back to admin page\n\n";
    cout << "Please enter number of each username to show history (0-" << s-1 << ") : ";
    int choice;
    cin >> choice;

    if(choice > s-1)
    {
        cout << "\n\nYour choice is incorect\n";
        cout << "Please try again\n\n";
        cout << "\n1.Try again\t" << "2.Back to admin page";
        cout << "\n\nPlease enter your choice (1-2) : ";
        int l;
        l = _getch();
        l -= '0';
        if(l == 1)
        {
            users_saves();
            return;
        }
        else
        {
            admin_page();
            return;
        }

    }
    else if(choice == 0)
    {
        admin_page();
        return;
    }
    else
    {
        system("cls");
        i=1;
        save_info show;

        char filename[100];
        sprintf(filename, "c:\\information\\%s\\history%d.bin", user[choice].username, i);
        FILE *print;
        print = fopen(filename, "rb");

        cout << "\n\n\tDate" << "\tDifficulty" << "\tResult" << "\tDuration\n\n";

        while (print != NULL)
        {
            fread(&show, sizeof (save_info), 1, print);
            cout << "   " << i << "." << show.date.day << "/" << show.date.month << "/" << show.date.year << "\t";
            cout << show.difficulty << "\t" << show.result << "\t" << show.dur << " s" << "\n\n";

            i++;
            sprintf(filename, "c:\\information\\%s\\history%d.bin", user[choice].username, i);
            print = fopen(filename, "rb");
        }

        cout << "\n\nPlease enter 0 to back to users history : ";
        int r;
        r = _getch();
        users_history();
        return;
    }
}
