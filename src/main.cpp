#include "main.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevIns, LPSTR lpszArgument, int iShow) {
main_common();
return 0;
}


//int main(int argc, char* argv[]) {

int main_common() {
    printf("ECPSCollector STARTED\n");
    
/*
    if (argc >= 2) {
        string act(argv[1]);
            if (act == "help") {
            showHelp();
            return 0;
        }
    }
*/
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)  {
        printf("Error init SDL!\n");
        return -1;
    }
    
    SDL_Window* mainWindow = NULL;
    //mainWindow = SDL_CreateWindow("Test Window", 0, 0, 500, 500, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_UTILITY  );
    mainWindow = SDL_CreateWindow("Test Window", 0, 0, 500, 500, SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS  );
    if (!mainWindow) {
        printf("Error create main window!\n");
        SDL_Quit();
        return -1;
    }
    
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {   // renderer creation may fail too
        printf("Error create renderer!\n");
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return -1;
    }
    
    
    SDL_Event event;
    for(;;) {
        if(SDL_WaitEvent(&event)==0) {
            printf("Error while waiting for an event!\n");
            break;
        }
        //check the type of event
        if(event.type == SDL_QUIT) {
            printf("Correct exit!\n");
            break;
        }
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
    return 0;
}




void showHelp() {
    printf("\n");
    printf("Example:\n");
    printf("    ./ECPSCollector\n");
    printf("\n");
}
