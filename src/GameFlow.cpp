#include <unistd.h>
#include "GameFlow.h"
#include "kbhit.h"
#include "GameSettings.h"

GameFlow::GameFlow()
{
    
}

void GameFlow::RenderAbout()
{
    WINDOW* window_about = newwin(MAP_Y - 2, MAP_X * 3 - 3, 2, 3);
    keypad(window_about, TRUE);

    wborder(window_about, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    mvwprintw(window_about, 0, 22, "  How  To  Play  ");
    for(int i = 0 ; i < 17 ; i++)
    {
      mvwprintw(window_about, i+1, 2, "%s", explain[i].c_str());
    }

    wrefresh(window_about);
    wgetch(window_about);

    EraseWindow(window_about);
}

// 크레딧 출력하는 창
void GameFlow::RenderMakers()
{
    WINDOW* window_makers = newwin(18, 19, 3, 24);
    keypad(window_makers, TRUE);

    mvwprintw(window_makers, 1, 1, "");
    for(int i = 0 ; i < 400 ; i++)
    {
        wprintw(window_makers, "%c", text[i]);
        wborder(window_makers, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
        wrefresh(window_makers);
        usleep(40000);
        if(kbhit()) break;
    }
    // 버퍼비워주기
    getchar();

    EraseWindow(window_makers);
}

// 첫화면 시작메뉴 (처음 한번만 호출)
int GameFlow::RenderStartMenu()
{
  WINDOW* window_start = newwin(12, 16, 5, 25);
  keypad(window_start, TRUE);
  wborder(window_start, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);

  // start/exit 중 선택된것
  int choice = 0;
  int key;
  
  while(1)
  {
    if(choice < 0) choice += 3;
    choice = choice % 3;
    // choice 기준으로 start / about / exit 하이라이트 표시
    if(choice == 0)
    {
      wattron(window_start, A_REVERSE);
      mvwprintw(window_start, 3, 3, " > start  ");
      wattroff(window_start, A_REVERSE);
      mvwprintw(window_start, 5, 3, " about    ");
      mvwprintw(window_start, 7, 3, " exit     ");
    }
    else if(choice == 1)
    {
      mvwprintw(window_start, 3, 3, " start    ");
      wattron(window_start, A_REVERSE);
      mvwprintw(window_start, 5, 3, " > about  ");
      wattroff(window_start, A_REVERSE);
      mvwprintw(window_start, 7, 3, " exit     ");
    }
    else
    {
      mvwprintw(window_start, 3, 3, " start    ");
      mvwprintw(window_start, 5, 3, " about    ");
      wattron(window_start, A_REVERSE);
      mvwprintw(window_start, 7, 3, " > exit  ");
      wattroff(window_start, A_REVERSE);
    }
    
    wrefresh(window_start);

    // 키입력받아서 엔터 누를 경우엔 choice 값 반환
    key = wgetch(window_start);
    switch(key)
    {
      case KB_UP:
      case KB_LEFT:
      case KB_W:
      case KB_A:
        choice--;
        break;
      case KB_DOWN:
      case KB_RIGHT:
      case KB_S:
      case KB_D:
        choice++;
        break;
      case KB_BACKSPACE:
        EraseWindow(window_start);
        return 2;
        break;
      case KB_ENTER:
        EraseWindow(window_start);
        return choice;
        break;
    }
  }
}


// 게임 종료 시 한번 호출
void GameFlow::RenderGameEnd()
{
  WINDOW* window_end = newwin(MAP_Y, MAP_X * 3, 1, 1);

  werase(window_end);
  wborder(window_end, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
  for(int i = 1 ; i < MAP_Y - 1 ; i++)
  {
    for(int j = 1 ; j < MAP_X * 3 - 1 ; j++)
    {
      mvwprintw(window_end, i, j, " ");
    }
  }
  wrefresh(window_end);

  //usleep(1000000);
  EraseWindow(window_end);
}

// 게임매니저가 첫 스테이지 시작 전 호출 (각 스테이지 클리어 시 자동호출)
int GameFlow::RenderStageEnter(const int stage)
{ 
  WINDOW* window_enter = newwin(MAP_Y, MAP_X * 2, 1, 1);

  keypad(window_enter, TRUE);
  werase(window_enter);
  mvwprintw(window_enter, 8, 18, "Stage %d", stage);
  mvwprintw(window_enter, 11, 12, "Press Key to Start!");
  wrefresh(window_enter);

  int key = wgetch(window_enter);
  EraseWindow(window_enter);

  if(key == 263)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

// 게임매니저가 스테이지 클리어 시 호출
int GameFlow::RenderStageClear(const int stage)
{
  WINDOW* window_clear = newwin(MAP_Y, MAP_X * 2, 1, 1);

  mvwprintw(window_clear, 9, 13, "Stage %d Clear!", stage);
  wrefresh(window_clear);

  usleep(1500000);
  EraseWindow(window_clear);

  if(stage < MAX_STAGE)
  {
    if(RenderStageEnter(stage + 1))
    {
      return 1;
    }
  }

  return 0;
}

void GameFlow::EraseWindow(WINDOW* window)
{
  keypad(window, FALSE);
  werase(window);
  wrefresh(window);
  delwin(window);
}