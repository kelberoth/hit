#include <iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>

using namespace std;

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

// 함수 불러오기 하기 위해 위에 처리함
void Game();

//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()
{
    cout << "mode con:cols=100 lines=25" << endl; // "mode con cols=가로 lines=세로 
    cout << "title Google Dinosaurs. By blockDMask." << endl; // title 창 제목
}

//커서의 위치를 x,y로 이동하는 함수
void GotoXY(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
    if (_kbhit() != 0)
    {
        return _getch();
    }
    return 0;
}

//공룡을 그리는 함수
void DrawDino(int dinoY)
{
    GotoXY(0, dinoY);//이 게임은 좌우로 움직이기 떄문에 dinoY 값만 y값으로 넘김
    static bool legFlag = true;
    cout << "        $$$$$$$ " << endl;
    cout << "       $$ $$$$$$" << endl;
    cout << "       $$$$$$$$$" << endl;
    cout << "$      $$$      " << endl;
    cout << "$$     $$$$$$$  " << endl;
    cout << "$$$   $$$$$     " << endl;
    cout << " $$  $$$$$$$$$$ " << endl;
    cout << " $$$$$$$$$$$    " << endl;
    cout << "  $$$$$$$$$$    " << endl;
    cout << "    $$$$$$$$    " << endl;
    cout << "     $$$$$$     " << endl;
    if (legFlag)//입력값이 안눌린 상태일떈 false값이 적용되어 아래 다리 모양이 출력
    {
        cout << "     $    $$$    " << endl;
        cout << "     $$          " << endl;
        legFlag = false;
    }
    else //입력값이 누른 상태일떈 true값이 적용되어 아래 다리 모양이 출력
    {
        cout << "     $$$  $     " << endl;
        cout << "          $$    " << endl;
        legFlag = true;
    }


}

//나무를 그리는 함수
void DrawTree(int treeX)
{
    GotoXY(treeX, TREE_BOTTOM_Y);
    cout << "$$$$" << endl;
    GotoXY(treeX, TREE_BOTTOM_Y + 1);
    cout << " $$ " << endl;
    GotoXY(treeX, TREE_BOTTOM_Y + 2);
    cout << " $$ " << endl;
    GotoXY(treeX, TREE_BOTTOM_Y + 3);
    cout << " $$ " << endl;
    GotoXY(treeX, TREE_BOTTOM_Y + 4);
    cout << " $$ " << endl;
}

//공룡이 나무에 충돌했을떄 게임오버 실행
void DrawGameOber(const int score)
{
    system("cls");//이전 화면 지우기
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    cout << "===========================" << endl;
    GotoXY(x, y + 1);
    cout << "======G A M E O V E R======" << endl;
    GotoXY(x, y + 2);
    cout << "===========================" << endl;
    GotoXY(x, y + 5);
    cout << "SCORE : " << score << endl;

    // 추가 // 게임 종료후 다시할지 종료할지
    int cho; // 입력 선택받기

    GotoXY(x, y + 8);
    cout << "1.재시작" << endl;
    GotoXY(x, y + 9);
    cout << "2.종료" << endl;
    GotoXY(x, y + 10);
    cout << "인력한값 : ";
    cin >> cho;

    
    if (cho == 1)
    {
        Game();
    }
    else if (cho == 2)
    {
        system("cls");
        //cout << "======게임종료======" << endl;
        exit(0); // 프로그램 종료
    }

    cout << "\n\n\n\n\n\n\n\n\n" << endl;
    system("pause"); // 멈추기


}

//충돌 했으면 true, 아니면 false
bool isCollision(const int treeX, const int dinoY)
{
    //트리의 x가 공룡의 몸체쪽에 있을떄,
    //공룡의 높이가 충분하지 않다면 충돌로 처리
    GotoXY(0, 0);
    cout << "treeX: " << treeX << " / " << "dinoY: " << dinoY << endl; //이런식으로 적절한 X, Y를 찾습니다.

    if(treeX <= 8 && treeX >= 4 &&
        dinoY > 8)
    {
        return true;
    }
    return false;
}

//게임 재시작을 위한 함수로 따로 뺴기
void Game()
{
    while (true)//게임루프
    {
        //게임 시작시 초기화
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 3;

        int dinoY = DINO_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int score = 0;
        clock_t start, curr; //점수 변수 초기화
        start = clock(); // 시작시간 초기화

        while (true) // 한 판에 대한 루프
        {
            if (isCollision(treeX, dinoY))
                break;

            //z키가 눌렸고, 바닥이 아닐떄 점프
            if (GetKeyDown() == 'z' && isBottom)
            {
                isJumping = true;
                isBottom = false;
            }

            //점프중이라면 Y를 감소, 점프가 끝났으면 Y를 증가
            if (isJumping)
            {
                dinoY -= gravity;
            }
            else
            {
                dinoY += gravity;
            }

            //Y가 계속해서 증가하는걸 막기위해 바닥을 지정
            if (dinoY >= DINO_BOTTOM_Y)
            {
                dinoY = DINO_BOTTOM_Y;
                isBottom = true;
            }

            //나무가 왼쪽으로 (x음수) 가도록 하고
            //나무의 위치가 왼쪽 끝으로 가면 다시 오른쪽 끝으로 소환
            treeX -= 2;
            if (treeX <= 0)
            {
                treeX = TREE_BOTTOM_X;
            }

            //점프의 맨 위를 찍으면 점프가 끝난 상황
            if (dinoY <= 3)
            {
                isJumping = false;
            }

            DrawDino(dinoY); //draw dino
            DrawTree(treeX); //draw Tree

            curr = clock(); // 현재시간 받아오기
            if (((curr - start) / CLOCKS_PER_SEC) >= 1) // 1초가 넘었을떄
            {
                score++; //스코어 UP
                start = clock(); //시작시간 초기화
            }
            Sleep(60);
            //cout << "cls" << endl;//화면 지우기
            system("cls");

            //(v2.0) 점수출력을 1초마다 해주는것이 아니라 항상 출력해주면서, 1초가 지났을때 ++ 해줍니다.z
            GotoXY(22, 0);    //커서를 가운데 위쪽으로 옮긴다. 콘솔창이 cols=100이니까 2*x이므로 22정도 넣어줌
            cout << "Score : " << score << endl;    //점수 출력해줌
        }

        //게임 오버 메뉴
        DrawGameOber(score);
        break;
    }
}

int main()
{
    SetConsoleView();

    while (true)//게임루프
    {
        Game();

    }

    return 0;
}