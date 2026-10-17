#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstdlib>
#include <ctime>

const int SCREEN_W = 720;
const int SCREEN_H = 1280;
SDL_Renderer* g_renderer = nullptr;
TTF_Font* font = nullptr;

void drawText(const char* txt, int x, int y, SDL_Color c)
{
    if(!font) return;
    SDL_Surface* sf = TTF_RenderUTF8_Blended(font, txt, c);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(g_renderer, sf);
    SDL_Rect rc{x,y, sf->w, sf->h};
    SDL_RenderCopy(g_renderer, tex, nullptr, &rc);
    SDL_FreeSurface(sf);
    SDL_DestroyTexture(tex);
}

struct Button{
    SDL_Rect r;
    std::string text;
};

int main(int argc, char* argv[])
{
    srand((unsigned)time(nullptr));
    int target = rand() % 100 + 1;
    int guess = 0;
    int count = 0;
    std::string msg = "🎮猜数字游戏 1~100";
    std::string input;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* win = SDL_CreateWindow("GuessNumber",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        SCREEN_W,SCREEN_H,0);
    g_renderer = SDL_CreateRenderer(win,-1,SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("fonts/Roboto-Regular.ttf",42);

    bool run = true;
    SDL_Event e;

    Button btns[12] = {
        {{60,550,160,110},"1"},{{260,550,160,110},"2"},{{460,550,160,110},"3"},
        {{60,680,160,110},"4"},{{260,680,160,110},"5"},{{460,680,160,110},"6"},
        {{60,810,160,110},"7"},{{260,810,160,110},"8"},{{460,810,160,110},"9"},
        {{60,940,160,110},"0"},{{260,940,160,110},"⌫"},{{460,940,260,110},"✅"},
    };

    while(run)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) run = false;
            if(e.type == SDL_FINGERDOWN)
            {
                float fx = e.tfinger.x * SCREEN_W;
                float fy = e.tfinger.y * SCREEN_H;
                for(auto &b : btns)
                {
                    if(fx >= b.r.x && fx <= b.r.x + b.r.w
                       && fy >= b.r.y && fy <= b.r.y + b.r.h)
                    {
                        if(b.text == "⌫")
                        {
                            if(!input.empty()) input.pop_back();
                        }
                        else if(b.text == "✅")
                        {
                            if(!input.empty())
                            {
                                guess = stoi(input);
                                count++;
                                if(guess > target) msg = "📈太大了！";
                                else if(guess < target) msg = "📉太小了！";
                                else msg = "🎉猜对了！次数:" + std::to_string(count);
                                input = "";
                            }
                        }
                        else
                        {
                            if(input.size()<3) input += b.text;
                        }
                    }
                }
            }
        }
        SDL_SetRenderDrawColor(g_renderer,20,25,35,255);
        SDL_RenderClear(g_renderer);
        SDL_Color yellow{255,220,0,255};
        SDL_Color white{255,255,255,255};
        drawText(msg.c_str(),40,60,yellow);
        drawText(("输入: "+input).c_str(),40,160,white);
        for(auto &b:btns)
        {
            SDL_SetRenderDrawColor(g_renderer,60,80,120,255);
            SDL_RenderFillRect(g_renderer,&b.r);
            drawText(b.text.c_str(),b.r.x+30,b.r.y+25,white);
        }
        SDL_RenderPresent(g_renderer);
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
