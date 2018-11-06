#include "main.h"


int main (int argc, char* argv[]) {
    printf("ECPSCollector STARTED\n");
    
    if (argc < 2) {
        showHelp();
        return 0;
    }
    
    string act(argv[1]);
    if (act == "test") {
        printf("TEST %s\n", argv[2]);
    }

    return 0;
}




void showHelp() {
    printf("\n");
    printf("Example:\n");
    printf("    ./ECPSCollector\n");
    printf("\n");
}
