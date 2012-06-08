#include <MAUtil/Moblet.h>
#include <MAUI/Screen.h>
#include <MAUI/Label.h>

using namespace MAUtil;
using namespace MAUI;

#include "FotoBewerker.hpp"

/**
 * Entry point of the program. The MAMain function
 * needs to be declared as extern "C".
 */
extern "C" int MAMain()
{
	Moblet::run( new FotoBewerker() );
	return 0;
}
