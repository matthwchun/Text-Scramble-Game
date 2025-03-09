#include "ModeSelect.h"
#include "Benchmark.h"
#include "Attrition.h"
#include "words.h"
#include "TextDisplay.h"
#include "ProfileManager.h"
#include "ProfileUpdater.h"

using namespace std;
using namespace std::chrono;

int main () {
    cout << "\x1b[H\x1b[2J";
    ProfileUpdater files;
    ProfileManager user(files);
    user.chooseProfile();
    ModeSelect mainMen(user);
    mainMen.mainMenu();

    return 0;
}


